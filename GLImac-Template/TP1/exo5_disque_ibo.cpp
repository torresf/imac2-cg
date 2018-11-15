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
	const int nb_triangles = 16;

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
	
	float angle = 0;
	vertices.push_back(Vertex2DColor(glm::vec2(0, 0), glm::vec3(1, 1, 1))); // Centre du cercle
	for (int i = 0; i < nb_triangles; ++i)
	{
		angle = i * (2 * glm::pi<float>()) / nb_triangles;
		vertices.push_back(Vertex2DColor(glm::vec2(glm::cos(angle) * .5f, glm::sin(angle) * .5f), glm::vec3(1, i%2, 0)));
	}

	glBufferData(GL_ARRAY_BUFFER,  (1 + nb_triangles) * sizeof(Vertex2DColor), vertices.data(), GL_STATIC_DRAW);
	
	// Débinding du VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// => Creation du IBO
    GLuint ibo;
    glGenBuffers(1, &ibo);

    // => On bind sur GL_ELEMENT_ARRAY_BUFFER, cible reservée pour les IBOs
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    // => Tableau d'indices: ce sont les indices des sommets à dessiner
    // On en a 6 afin de former deux triangles
    // Chaque indice correspond au sommet correspondant dans le VBO
    // uint32_t indices[] = {
    //     0, 1, 2, 0, 2, 3
    // };
    std::vector<uint32_t> indices;

    for (int i = 1; i < nb_triangles; ++i)
    {
    	indices.push_back(0);
    	indices.push_back(i);
    	indices.push_back(i+1);
    }
    // Dernier triangle pour terminer le cercle
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(nb_triangles);

    // => On remplit l'IBO avec les indices:
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * nb_triangles * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);

    // => Comme d'habitude on debind avant de passer à autre chose
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Création du VAO
	GLuint vao;
	glGenVertexArrays(1, &vao);

	// Binding du VAO
	glBindVertexArray(vao);

	// => On bind l'IBO sur GL_ELEMENT_ARRAY_BUFFER; puisqu'un VAO est actuellement bindé,
	// cela a pour effet d'enregistrer l'IBO dans le VAO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	// Activation des attributs (position et couleur)
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
		// => On utilise glDrawElements à la place de glDrawArrays
		// Cela indique à OpenGL qu'il doit utiliser l'IBO enregistré dans le VAO
		glDrawElements(GL_TRIANGLES, 3 * nb_triangles, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Update the display
		windowManager.swapBuffers();
	}

	// Libération des ressources
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);

	return EXIT_SUCCESS;
}
