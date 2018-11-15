#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>

using namespace glimac;

class Vertex2DUV {
	public:
		Vertex2DUV();
		Vertex2DUV(const glm::vec2 &pos, const glm::vec2 &tex);
		glm::vec2 position;
		glm::vec2 texture;
};

Vertex2DUV::Vertex2DUV() {
	position = glm::vec2(0.f, 0.f);
	texture = glm::vec2(0.f, 0.f);
}

Vertex2DUV::Vertex2DUV(const glm::vec2 &pos, const glm::vec2 &tex) {
	position = pos;
	texture = tex;
}

glm::mat3 translate(float tx, float ty) {
	return glm::mat3(glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(tx, ty, 1));
}

glm::mat3 scale(float sx, float sy) {
	return glm::mat3(glm::vec3(sx, 0, 0), glm::vec3(0, sy, 0), glm::vec3(0, 0, 1));
}

glm::mat3 rotate(float a) {
	a = glm::radians(a);
	return glm::mat3(glm::vec3(cos(a), sin(a), 0), glm::vec3(-sin(a), cos(a), 0), glm::vec3(0, 0, 1));
}

int main(int argc, char** argv) {
	// Initialize SDL and open a window
	SDLWindowManager windowManager(600, 600, "GLImac");

	// Initialize glew for OpenGL3+ support
	GLenum glewInitError = glewInit();
	if(GLEW_OK != glewInitError) {
		std::cerr << glewGetErrorString(glewInitError) << std::endl;
		return EXIT_FAILURE;
	}

	FilePath applicationPath(argv[0]);
	Program program = loadProgram(applicationPath.dirPath() + "shaders/tex2D.vs.glsl",
								  applicationPath.dirPath() + "shaders/tex2D.fs.glsl");
	program.use();
	GLint matrixLocation = glGetUniformLocation(program.getGLId(), "uModelMatrix");
	GLint colorLocation = glGetUniformLocation(program.getGLId(), "uColor");
	GLint textureLocation = glGetUniformLocation(program.getGLId(), "uTexture");
	
	float time = 0.f;
	glm::mat3 transformMatrix = rotate(time);
	glm::vec3 color = glm::vec3(0.f);

	std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

	/*********************************
	 * HERE SHOULD COME THE INITIALIZATION CODE
	 *********************************/

	// Textures
	std::unique_ptr<Image> image = loadImage("/home/torresf/Documents/CG/imac2-cg/GLImac-Template/assets/textures/triforce.png");

	if (image == NULL)
		std::cerr << "Erreur au chargement de l'image" << std::endl;

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D,
		0,
		GL_RGBA,
		image->getWidth(),
		image->getHeight(),
		0,
		GL_RGBA,
		GL_FLOAT,
		image->getPixels());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);

	// Création du VBO
	GLuint vbo;
	glGenBuffers(1, &vbo);

	// Binding du VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Envoie des données de vertex
	Vertex2DUV vertices[] = {
		Vertex2DUV(glm::vec2(-1, -1), glm::vec2(0.5, 0)),
		Vertex2DUV(glm::vec2( 1, -1), glm::vec2(0, 1)),
		Vertex2DUV(glm::vec2( 0,  1), glm::vec2(1, 1))
	};
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(Vertex2DUV), vertices, GL_STATIC_DRAW);
	
	// Débinding du VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Création du VAO
	GLuint vao;
	glGenVertexArrays(1, &vao);

	// Binding du VAO
	glBindVertexArray(vao);
	// Activation de l'attribut de sommet 0 (la position)
	const GLuint VERTEX_ATTR_POSITION = 0;
	const GLuint VERTEX_ATTR_TEXTURE = 1;
	glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
	glEnableVertexAttribArray(VERTEX_ATTR_TEXTURE);

	// Spécification de l'attribut de sommet et de texture
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV), (const GLvoid*) offsetof(Vertex2DUV, position));
	glVertexAttribPointer(VERTEX_ATTR_TEXTURE, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV), (const GLvoid*) offsetof(Vertex2DUV, texture));
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Débinding du VAO
	glBindVertexArray(0);

	// Application loop:
	bool done = false;
	while(!done) {
		// Event loop:
		SDL_Event e;
		while(windowManager.pollEvent(e)) {
			if(e.type == SDL_QUIT) {
				done = true; // Leave the loop after this iteration
			}
		}

		/*********************************
		 * HERE SHOULD COME THE RENDERING CODE
		 *********************************/

		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(textureLocation, 0);

		// Drawing Code
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(vao);

		transformMatrix = rotate(time/2) * translate(0.5, 0.5) * scale(0.25, 0.25) * rotate(-time);
		color = glm::vec3(1.f, 0.f, 0.f);
		glUniformMatrix3fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
		glUniform3fv(colorLocation, 1, glm::value_ptr(color));
		glDrawArrays(GL_TRIANGLES, 0, 3);

		transformMatrix = rotate(time/2) * translate(-0.5, -0.5) * scale(0.25, 0.25) * rotate(-time);
		color = glm::vec3(1.f, 1.f, 0.f);
		glUniformMatrix3fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
		glUniform3fv(colorLocation, 1, glm::value_ptr(color));
		glDrawArrays(GL_TRIANGLES, 0, 3);

		transformMatrix = rotate(time/2) * translate(-0.5, 0.5) * scale(0.25, 0.25) * rotate(time);
		color = glm::vec3(0.f, 1.f, 1.f);
		glUniformMatrix3fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
		glUniform3fv(colorLocation, 1, glm::value_ptr(color));
		glDrawArrays(GL_TRIANGLES, 0, 3);

		transformMatrix = rotate(time/2) * translate(0.5, -0.5) * scale(0.25, 0.25) * rotate(time);
		color = glm::vec3(1.f, 0.f, 1.f);
		glUniformMatrix3fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
		glUniform3fv(colorLocation, 1, glm::value_ptr(color));
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		time += .01;
		// Update the display
		windowManager.swapBuffers();
	}

	// Libérations des ressources
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
	glDeleteTextures(1, &texture);

	return EXIT_SUCCESS;
}
