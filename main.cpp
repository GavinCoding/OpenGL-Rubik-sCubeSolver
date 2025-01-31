#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>

const char *vertexShaderSource = 
	"#version 330 core\n"
    	"layout (location = 0) in vec3 aPos;\n"
    	"void main()\n"
    	"{\n"
    	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    	"}\0";
const char *fragmentShaderSource = 
	"#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
	"}\n";
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

int main()
{
	//Initialization for window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800,800,"gavin's window", NULL, NULL);

	//checks
	if(window == NULL)
	{
		std::cout << "Window failed to init" << std::endl;
		glfwTerminate();
		return -1;
	}
	//set Context to window. 
	glfwMakeContextCurrent(window);

	//Glad Init
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Glad failed to init" << std::endl;
		return -1;
	}
	//window viewport set
	glViewport(0,0,800,800);
	glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
	//Initializing window done
	
	//Render section
	float vertices[] = {
		-0.5f,-0.5f,0.0f,
		0.5f,-0.5f,0.0f,
		0.0f,0.5f,0.0f
	};

	//init buffers with VBO then bind VAO after
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	unsigned int VAO; //used to store VAO id, VAO is used to store link settings basically
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	
	//Vertex Shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	
	//vertex shader compile check and log
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
   		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//fragment shader(color)
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		glGetShaderInfoLog(fragmentShader,  512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRGMNT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	//link shaders with Shader Program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if(!success)
	{
    		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADERPRGRM\n" << infoLog << std::endl;
	}
			
	//delete Shader Object, no longer needed
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//connect vertex data to vertex shader attributes. WIll be in VAO
	glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE,3*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);

	while(!glfwWindowShouldClose(window))
	{
		//Process User Input
		processInput(window);


		//Render commands
		glClearColor(0.2f,0.3f,0.3f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		//check and call events and swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
void processInput(GLFWwindow* window)
{
	if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0,0,width,height);
}
