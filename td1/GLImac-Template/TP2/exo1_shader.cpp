#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <cstddef>

using namespace glimac;

class Vertex2DColor {
	public:
		Vertex2DColor();
		Vertex2DColor(const glm::vec2 &pos, const glm::vec3 &col);
		glm::vec2 position;
		glm::vec3 color;
};

Vertex2DColor::Vertex2DColor() {
	position = glm::vec2(0.f, 0.f);
	color = glm::vec3(0.f, 0.f, 0.f);
}

Vertex2DColor::Vertex2DColor(const glm::vec2 &pos, const glm::vec3 &col) {
	position = pos;
	color = col;
}


int main(int argc, char** argv) {
	// Initialize SDL and open a window
	SDLWindowManager windowManager(800, 600, "GLImac");

	// Initialize glew for OpenGL3+ support
	GLenum glewInitError = glewInit();
	if(GLEW_OK != glewInitError) {
		std::cerr << glewGetErrorString(glewInitError) << std::endl;
		return EXIT_FAILURE;
	}

	FilePath applicationPath(argv[0]);
	Program program = loadProgram(applicationPath.dirPath() + "shaders/color2D.vs.glsl",
	                              applicationPath.dirPath() + "shaders/color2D.fs.glsl");
	program.use();

	std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;

	// INITIALIZATION CODE

	// Création du VBO
	GLuint vbo;
	glGenBuffers(1, &vbo);

	// Binding du VBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Envoie des données de vertex
	Vertex2DColor vertices[] = {
	    Vertex2DColor(glm::vec2(-0.5, -0.5), glm::vec3(1, 0, 0)),
	    Vertex2DColor(glm::vec2(0.5, -0.5), glm::vec3(0, 1, 0)),
	    Vertex2DColor(glm::vec2(0, 0.5), glm::vec3(0, 0, 1))
	};
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(Vertex2DColor), vertices, GL_STATIC_DRAW);
	
	// Débinding du VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Création du VAO
	GLuint vao;
	glGenVertexArrays(1, &vao);

	// Binding du VAO
	glBindVertexArray(vao);
	// Activation de l'attribut de sommet 0 (la position)
	const GLuint VERTEX_ATTR_POSITION = 0;
	const GLuint VERTEX_ATTR_COLOR = 1;
	glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
	glEnableVertexAttribArray(VERTEX_ATTR_COLOR);

	// Spécification de l'attribut de sommet 0
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), (const GLvoid*) offsetof(Vertex2DColor, position));
	glVertexAttribPointer(VERTEX_ATTR_COLOR, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2DColor), (const GLvoid*) offsetof(Vertex2DColor, color));
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

		// Drawing Code
		glClear(GL_COLOR_BUFFER_BIT);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		// Update the display
		windowManager.swapBuffers();
	}

	// Libérations des ressources
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);

	return EXIT_SUCCESS;
}
