#include <glimac/SDLWindowManager.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <glimac/FreeflyCamera.hpp>
#include <glm/gtc/random.hpp>
#include <GL/glew.h>
#include <iostream>

using namespace glimac;

struct EarthProgram {
	Program m_Program;

	GLint uMVPMatrix;
	GLint uMVMatrix;
	GLint uNormalMatrix;
	GLint uEarthTexture;
	GLint uCloudTexture;

	EarthProgram(const FilePath& applicationPath):
		m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
							  applicationPath.dirPath() + "shaders/multiTex3D.fs.glsl")) {
		uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
		uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
		uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
		uEarthTexture = glGetUniformLocation(m_Program.getGLId(), "uEarthTexture");
		uCloudTexture = glGetUniformLocation(m_Program.getGLId(), "uCloudTexture");
	}
};

struct MoonProgram {
	Program m_Program;

	GLint uMVPMatrix;
	GLint uMVMatrix;
	GLint uNormalMatrix;
	GLint uTexture;

	MoonProgram(const FilePath& applicationPath):
		m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
							  applicationPath.dirPath() + "shaders/tex3D.fs.glsl")) {
		uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
		uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
		uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
		uTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
	}
};

int main(int argc, char** argv) {
	// Initialize SDL and open a window
	SDLWindowManager windowManager(800, 600, "GLImac");

	// Initialize glew for OpenGL3+ support
	GLenum glewInitError = glewInit();
	if(GLEW_OK != glewInitError) {
		std::cerr << glewGetErrorString(glewInitError) << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

	/*********************************
	 * HERE SHOULD COME THE INITIALIZATION CODE
	 *********************************/

	// Shaders
	FilePath applicationPath(argv[0]);
	EarthProgram earthProgram(applicationPath);
	MoonProgram moonProgram(applicationPath);

	// Location des variables uniformes
	// GLint MVPMatrixLocation = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
	// GLint MVMatrixLocation = glGetUniformLocation(program.getGLId(), "uMVMatrix");
	// GLint NormalMatrixLocation = glGetUniformLocation(program.getGLId(), "uNormalMatrix");
	// GLint uTextureLocation = glGetUniformLocation(program.getGLId(), "uEarthTexture");
	// GLint uCloudTextureLocation = glGetUniformLocation(program.getGLId(), "uCloudTexture");
	
	// Indique à OpenGL qu'il doit aller chercher sur l'unité de texture 0 
	// pour lire dans la texture uEarthTexture:
	// glUniform1i(uCloudTextureLocation, 0);
	// // Indique à OpenGL qu'il doit aller chercher sur l'unité de texture 2
	// // pour lire dans la texture uCloudTexture:
	// glUniform1i(uCloudTextureLocation, 1);

	glEnable(GL_DEPTH_TEST); // Permet d'activer le test de profondeur du GPU

	// Chargement d'une texture
	std::unique_ptr<Image> earthTexture = loadImage("/home/torresf/Documents/CG/imac2-cg/GLImac-Template/assets/textures/EarthMap.jpg");
	std::unique_ptr<Image> moonTexture = loadImage("/home/torresf/Documents/CG/imac2-cg/GLImac-Template/assets/textures/MoonMap.jpg");
	std::unique_ptr<Image> cloudTexture = loadImage("/home/torresf/Documents/CG/imac2-cg/GLImac-Template/assets/textures/CloudMap.jpg");

	if (earthTexture == NULL)
		std::cerr << "Erreur au chargement de l'image de la Terre." << std::endl;
	if (moonTexture == NULL)
		std::cerr << "Erreur au chargement de l'image de la Lune." << std::endl;
	if (cloudTexture == NULL)
		std::cerr << "Erreur au chargement de l'image des nuages." << std::endl;

	unsigned int nbTextures = 3;
	GLuint *textures = new GLuint[nbTextures];
	glGenTextures(nbTextures, textures);

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		earthTexture->getWidth(),
		earthTexture->getHeight(),
		0,
		GL_RGBA,
		GL_FLOAT,
		earthTexture->getPixels());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		moonTexture->getWidth(),
		moonTexture->getHeight(),
		0,
		GL_RGBA,
		GL_FLOAT,
		moonTexture->getPixels());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		cloudTexture->getWidth(),
		cloudTexture->getHeight(),
		0,
		GL_RGBA,
		GL_FLOAT,
		cloudTexture->getPixels());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);

	glm::mat4 projMatrix = glm::perspective(glm::radians(70.f), 800 / 600.f, 0.1f, 100.f);
	glm::mat4 globalMVMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, -5));
	// glm::mat4 normalMatrix = glm::transpose(glm::inverse(MVMatrix));

	// Création d'une sphère
	Sphere sphere(1, 64, 32);

	GLuint vbo;
	glGenBuffers(1, &vbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Envoie des données de vertex
	glBufferData(GL_ARRAY_BUFFER, sphere.getVertexCount() * sizeof(ShapeVertex), sphere.getDataPointer(), GL_STATIC_DRAW);
	
	// Débinding du VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Création du VAO
	GLuint vao;
	glGenVertexArrays(1, &vao);

	// Binding du VAO
	glBindVertexArray(vao);
	const GLuint VERTEX_ATTR_POSITION = 0;
	const GLuint VERTEX_ATTR_NORMAL = 1;
	const GLuint VERTEX_ATTR_TEXCOORD = 2;
	glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
	glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
	glEnableVertexAttribArray(VERTEX_ATTR_TEXCOORD);

	// Spécification de l'attribut de sommet et de texture
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, position));
	glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, normal));
	glVertexAttribPointer(VERTEX_ATTR_TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, texCoords));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Débinding du VAO
	glBindVertexArray(0);

	int nbLunes = 32;
	std::vector<glm::vec3> randomTransform;
	for (int i = 0; i < nbLunes-1; ++i)
	{
		randomTransform.push_back(glm::sphericalRand(2.f));
	}

	// Création de la caméra
	FreeflyCamera camera;

	float speed = 1.0f;
	float rotateSpeed = 1.0f;

	// Application loop:
	bool done = false;
	while(!done) {
		// Event loop:
		SDL_Event e;
		while(windowManager.pollEvent(e)) {
			switch (e.type) {
				case SDL_QUIT:
					done = true;
					break;
				case SDL_KEYDOWN:
					switch (e.key.keysym.sym) {
						case SDLK_ESCAPE:
							done = true;
							break;
						case SDLK_z:
							// Avancer
							camera.moveFront(speed);
							break;
						case SDLK_s:
							// Reculer
							camera.moveFront(-speed);
							break;
						case SDLK_q:
							// Gauche
							camera.moveLeft(speed);
							break;
						case SDLK_d:
							// Droite
							camera.moveLeft(-speed);
							break;
						default:
							break;
					}
					break;
				case SDL_MOUSEMOTION:
					if (windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)) {
						if (e.motion.xrel != 0)
							camera.rotateLeft(e.motion.xrel * rotateSpeed);
						if (e.motion.yrel != 0)
							camera.rotateUp(e.motion.yrel * rotateSpeed);
						break;
					}
				default:
					break;
			}
		}

		/*********************************
		 * HERE SHOULD COME THE RENDERING CODE
		 *********************************/

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		earthProgram.m_Program.use();

		glUniform1i(earthProgram.uEarthTexture, 0);
		glUniform1i(earthProgram.uCloudTexture, 1);

		// globalMVMatrix = glm::translate(glm::mat4(1), glm::vec3(0, 0, -5)); // Translation

		globalMVMatrix = camera.getViewMatrix();

		// std::cout << globalMVMatrix << std::endl;

		glm::mat4 earthMVMatrix = glm::rotate(globalMVMatrix, windowManager.getTime(), glm::vec3(0, 1, 0)); // Translation * Rotation

		glUniformMatrix4fv(earthProgram.uMVMatrix, 1, GL_FALSE, 
			glm::value_ptr(earthMVMatrix));
		glUniformMatrix4fv(earthProgram.uNormalMatrix, 1, GL_FALSE, 
			glm::value_ptr(glm::transpose(glm::inverse(earthMVMatrix))));
		glUniformMatrix4fv(earthProgram.uMVPMatrix, 1, GL_FALSE, 
			glm::value_ptr(projMatrix * earthMVMatrix));

		glBindVertexArray(vao);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textures[0]); // la texture earthTexture est bindée sur l'unité GL_TEXTURE0
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textures[2]); // la texture cloudTexture est bindée sur l'unité GL_TEXTURE1

		// Dessin de la terreglm::cross(glm::vec3(1, 1, 1), randomTransform[i]
		glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
		
		// Dessin des lunes
		moonProgram.m_Program.use();

		for (int i = 0; i < nbLunes; ++i)
		{
			// Transformations nécessaires pour les Lune
			glm::mat4 moonMVMatrix = glm::mat4();
			moonMVMatrix = glm::rotate(globalMVMatrix, (1+randomTransform[i][0]+randomTransform[i][1]+randomTransform[i][2]) * windowManager.getTime(), glm::cross(glm::vec3(1, 1, 1), randomTransform[i])); // Translation * Rotation
			moonMVMatrix = glm::translate(moonMVMatrix, randomTransform[i]); // Translation * Rotation * Translation
			moonMVMatrix = glm::scale(moonMVMatrix, glm::vec3(0.2, 0.2, 0.2)); // Translation * Rotation * Translation * Scale

			glUniformMatrix4fv(moonProgram.uMVMatrix, 1, GL_FALSE, 
				glm::value_ptr(moonMVMatrix));
			glUniformMatrix4fv(moonProgram.uNormalMatrix, 1, GL_FALSE, 
				glm::value_ptr(glm::transpose(glm::inverse(moonMVMatrix))));
			glUniformMatrix4fv(moonProgram.uMVPMatrix, 1, GL_FALSE, 
				glm::value_ptr(projMatrix * moonMVMatrix));

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textures[1]);

			glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
		}

		glBindVertexArray(0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0); // débind sur l'unité GL_TEXTURE0

		// Update the display
		windowManager.swapBuffers();
	}

	// Libérations des ressources
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	delete textures;

	return EXIT_SUCCESS;
}
