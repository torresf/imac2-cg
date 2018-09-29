#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/glm.hpp>
#include <cstddef>

using namespace glimac;

class Vertex2DColor {
	public:
		glm::vec2 position;
		glm::vec3 color;
		Vertex2DColor();
		Vertex2DColor(const glm::vec2 &position, const glm::vec3 &color):position(position), color(color){}
};

Vertex2DColor::Vertex2DColor() {
	position = glm::vec2(0.f, 0.f);
	color = glm::vec3(0.f, 0.f, 0.f);
}

int main(int argc, char** argv) {
	const int nb_triangles = 12; 

	// Initialize SDL and open a window
	SDLWindowManager windowManager(600, 600, "GLImac");

	// Initialize glew for OpenGL3+ support
	GLenum glewInitError = glewInit();
	if(GLEW_OK != glewInitError) {
		std::cerr << glewGetErrorString(glewInitError) << std::endl;
		return EXIT_FAILURE;
	}

	FilePath applicationPath(argv[0]);
	Program program = loadProgram(applicationPath.dirPath() + "shaders/triangle.vs.glsl",
	                              applicationPath.dirPath() + "shaders/triangle.fs.glsl");
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
	std::vector<Vertex2DColor> vertices;
	
	float angle1 = 0;
	float angle2 = 0;
	for (int i = 0; i < nb_triangles; ++i)
	{
		angle1 = i * (2 * glm::pi<float>()) / nb_triangles;
		angle2 = (i+1) * (2 * glm::pi<float>()) / nb_triangles;
		vertices.push_back(Vertex2DColor(glm::vec2(0, 0), glm::vec3(1, i%2, 0)));
		vertices.push_back(Vertex2DColor(glm::vec2(glm::cos(angle1) * .5f, glm::sin(angle1) * .5f), glm::vec3(1, i%2, 0)));
		vertices.push_back(Vertex2DColor(glm::vec2(glm::cos(angle2) * .5f, glm::sin(angle2) * .5f), glm::vec3(1, i%2, 0)));
	}

	glBufferData(GL_ARRAY_BUFFER, 3 * nb_triangles * sizeof(Vertex2DColor), vertices.data(), GL_STATIC_DRAW);
	
	// Débinding du VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Création du VAO
	GLuint vao;
	glGenVertexArrays(1, &vao);

	// Binding du VAO
	glBindVertexArray(vao);
	// Activation de l'attribut de sommet 0 (la position)
	const GLuint VERTEX_ATTR_POSITION = 3;
	const GLuint VERTEX_ATTR_COLOR = 8;
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
		glDrawArrays(GL_TRIANGLES, 0, 3 * nb_triangles);
		glBindVertexArray(0);

		// Update the display
		windowManager.swapBuffers();
	}

	// Libérations des ressources
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);

	return EXIT_SUCCESS;
}
