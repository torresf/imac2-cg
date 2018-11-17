#include <glimac/SDLWindowManager.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <glimac/TrackballCamera.hpp>
#include <glm/gtc/random.hpp>
#include <GL/glew.h>
#include <iostream>

using namespace glimac;

struct EarthProgram {
	Program m_Program;

	GLint uMVPMatrix;
	GLint uMVMatrix;
	GLint uNormalMatrix;

	EarthProgram(const FilePath& applicationPath):
		m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
							  applicationPath.dirPath() + "shaders/directionallight.fs.glsl")) {
		uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
		uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
		uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
	}
};

struct MoonProgram {
	Program m_Program;

	GLint uMVPMatrix;
	GLint uMVMatrix;
	GLint uNormalMatrix;

	MoonProgram(const FilePath& applicationPath):
		m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
							  applicationPath.dirPath() + "shaders/directionallight.fs.glsl")) {
		uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
		uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
		uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
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

	Program program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
								applicationPath.dirPath() + "shaders/directionallight.fs.glsl"));

	GLint uLightIntensity = glGetUniformLocation(program.getGLId(), "uLightIntensity");
	GLint uLightDir_vs = glGetUniformLocation(program.getGLId(), "uLightDir_vs");
	GLint uKd = glGetUniformLocation(program.getGLId(), "uKd");
	GLint uKs = glGetUniformLocation(program.getGLId(), "uKs");
	GLint uShininess = glGetUniformLocation(program.getGLId(), "uShininess");

	glEnable(GL_DEPTH_TEST); // Permet d'activer le test de profondeur du GPU

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
	glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
	glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);

	// Spécification de l'attribut de sommet et de normal
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, position));
	glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, normal));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Débinding du VAO
	glBindVertexArray(0);

	int nbLunes = 32;
	std::vector<glm::vec3> randomTransform;
	std::vector<float> randomColor;
	for (int i = 0; i < nbLunes; ++i)
	{
		randomTransform.push_back(glm::sphericalRand(2.f));
		randomColor.push_back(glm::linearRand(0.1f, 1.f));
	}

	// Création de la caméra
	TrackballCamera camera;

	float zoom = 1.0f;
	float speed = .25f;

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
							camera.moveFront(zoom);
							break;
						case SDLK_s:
							camera.moveFront(-zoom);
							break;
						default:
							break;
					}
					break;
				case SDL_MOUSEMOTION:
					if (windowManager.isMouseButtonPressed(SDL_BUTTON_RIGHT)) {
						if (e.motion.xrel != 0)
							camera.rotateUp(e.motion.xrel * speed);
						if (e.motion.yrel != 0)
							camera.rotateLeft(e.motion.yrel * speed);
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

		globalMVMatrix = camera.getViewMatrix();

		glm::mat4 earthMVMatrix = glm::rotate(globalMVMatrix, windowManager.getTime(), glm::vec3(0, 1, 0)); // Translation * Rotation

		glUniformMatrix4fv(earthProgram.uMVMatrix, 1, GL_FALSE, 
			glm::value_ptr(earthMVMatrix));
		glUniformMatrix4fv(earthProgram.uNormalMatrix, 1, GL_FALSE, 
			glm::value_ptr(glm::transpose(glm::inverse(earthMVMatrix))));
		glUniformMatrix4fv(earthProgram.uMVPMatrix, 1, GL_FALSE, 
			glm::value_ptr(projMatrix * earthMVMatrix));

		glBindVertexArray(vao);

		// Dessin de la terre
		glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());

		// Gestion de la lumière
		glm::mat4 lightMVMatrix = glm::rotate(globalMVMatrix, windowManager.getTime(), glm::vec3(0, 1, 0)); // Translation * Rotation
		glm::vec3 lightDir_vs(lightMVMatrix * glm::vec4(1, 1, 1, 0));

		glUniform3f(uLightIntensity, 1, .5f, .5f);
		glUniform3fv(uLightDir_vs, 1, glm::value_ptr(lightDir_vs));
		glUniform3f(uKd, 0, 0, 1);
		glUniform3f(uKs, 1, 0, 1);
		glUniform1f(uShininess, 2);

		// Dessin des lunes
		moonProgram.m_Program.use();

		for (int i = 0; i < nbLunes; ++i)
		{
			// Transformations nécessaires pour la Lune
			glm::mat4 moonMVMatrix = glm::rotate(globalMVMatrix, (1+randomTransform[i][0]+randomTransform[i][1]+randomTransform[i][2]) * windowManager.getTime(), glm::cross(glm::vec3(1, 1, 1), randomTransform[i])); // Translation * Rotation
			moonMVMatrix = glm::translate(moonMVMatrix, randomTransform[i]); // Translation * Rotation * Translation
			moonMVMatrix = glm::scale(moonMVMatrix, glm::vec3(0.2, 0.2, 0.2)); // Translation * Rotation * Translation * Scale

			glUniformMatrix4fv(moonProgram.uMVMatrix, 1, GL_FALSE, 
				glm::value_ptr(moonMVMatrix));
			glUniformMatrix4fv(moonProgram.uNormalMatrix, 1, GL_FALSE, 
				glm::value_ptr(glm::transpose(glm::inverse(moonMVMatrix))));
			glUniformMatrix4fv(moonProgram.uMVPMatrix, 1, GL_FALSE, 
				glm::value_ptr(projMatrix * moonMVMatrix));

			glUniform3f(uLightIntensity, .25, .25, .25);
			glUniform3fv(uLightDir_vs, 1, glm::value_ptr(lightDir_vs));
			glUniform3f(uKd, .1, 0, 1);
			glUniform3f(uKs, randomColor[i], .05, .2);
			glUniform1f(uShininess, 1);

			glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());
		}

		glBindVertexArray(0);

		// Update the display
		windowManager.swapBuffers();
	}

	// Libérations des ressources
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);

	return EXIT_SUCCESS;
}
