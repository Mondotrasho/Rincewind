#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shaders.h"
#include "Shader.h"

#include "glm/glm.hpp"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window,float deltaTime);

const char *vertexShaderSource = thirdvert;
const char *fragmentShaderSource = fourthfrag;

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {

	//tell GLFW what version of OpenGL we are using
	glfwInit(); //version 4.6
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	//create window
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Rincewind", NULL, NULL);
	//error checking stop if failed to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//make window active
	glfwMakeContextCurrent(window);
	//calls if the window is ever resized so that gl gets the new size
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	//check if glad loaded
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// build and compile our shader program
	// ------------------------------------
	Shader ourShader("../bin/shaders/vertex/vert3.vs", "../bin/shaders/fragment/frag4.fs"); // you can name your shader files however you like
	//Shader ourShader(thirdvert, fourthfrag,true);
	
	//write version info to console
	printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;



	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
		 0.0f,  0.5f, 0.5f,  0.0f, 0.0f, 1.0f    // top 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};


	unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
	// 2. copy our vertices array in a vertex buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3. copy our index array in a element buffer for OpenGL to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 4. then set the vertex attributes pointers
	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    //glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    //glBindVertexArray(0); 

	  
	//set up deltatime
	double prevTime = glfwGetTime();
	double currTime = 0;
	double deltaTime = 0;
	//keeps window open
	while (!glfwWindowShouldClose(window))
	{// update delta time
		currTime = glfwGetTime();
		deltaTime = currTime - prevTime;
		prevTime = currTime;
		// input
		processInput(window, deltaTime);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// draw our first triangle
		ourShader.use();
		//render tri or whatever
		glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

	glfwTerminate();
	return 0;
}

float delay = 0.1f;
//this is out input
void processInput(GLFWwindow *window, float deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);


	//toggle polygonmode between wire frame and filled
	if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS && delay <= 0)
	{
		GLint polygonMode;
		glGetIntegerv(GL_POLYGON_MODE, &polygonMode);
		if (polygonMode == GL_LINE) 
		{ glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
		else 
		{glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); }
		delay = 0.1f;
	}
	if(delay > 0)
	delay -= deltaTime;
}

//this is our callback to resize
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

struct Vertex
{
	glm::vec4 position;
	glm::vec4 colour;
	glm::vec2 textcord;
	glm::vec4 normal;
};

void initialize(unsigned i, Vertex* vertex, unsigned i1, unsigned* indices)
{
	return;
};

//rows, number of quads
//columns, number of quads
void initializeGrid(int quad_rows,int quad_columns,float width,float height)
{

	const unsigned int num_vert_per_row = quad_columns + 1;
	const unsigned int num_vert_per_col = quad_rows + 1;

	const float gap_along_rows = width / quad_rows;
	const float gap_along_cols = width / quad_columns;

	Vertex* verticies = new Vertex[num_vert_per_row * num_vert_per_col];

	for (int y = 0; y < num_vert_per_col; ++y)
	{
		for (int x = 0; x < num_vert_per_row; ++x)
		{
			glm::vec4 position{ x * gap_along_rows,0,y * gap_along_cols,1 };
			verticies[x + y * num_vert_per_row].position = position;
		}
	}

	unsigned int num_triangles = quad_rows * quad_columns * 2;
	unsigned int* indices = new unsigned int[num_triangles * 3];

	int base = 0;
	for (int x = 0; x < quad_rows * 2; ++x)
	{
		for (int y = 0; y < quad_columns * 2; ++x)
		{
			indices[base] = (x + y * num_vert_per_row);
			indices[base+1] = (x + y * num_vert_per_row) + 1;
			indices[base + 2] = x + 1 + (y + 1) * num_vert_per_row;

			indices[base+3] = (x + y * num_vert_per_row) + 1;
			indices[base+4] = x + 1 + (y + 1) * num_vert_per_row;
			indices[base + 5] = x + (y + 1) * num_vert_per_row;
		}
	}

	initialize(num_vert_per_col*num_vert_per_row, verticies, num_triangles * 3, indices);

	delete[] indices;
	delete[] verticies;
}
