//
// Created by Marine on 13/01/2021.
//

#include "Engine.h"
#include <iostream>
#include "Shader.h"
#include "Object.h"
#include "Dragon.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>

void Engine::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

int Engine::initWindow(const int width, const int height) {

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, "ProjetPhong", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, width, height); //set la zone sur laquelle tu fais ton rendu

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);//resize

	glEnable(GL_DEPTH_TEST);
	return 1;
}

Engine::Engine(int width, int height, bool debug) {
	glfwInit();
	initWindow(width, height);
	if(debug){
		activateDebugMode();
	}
	mainCamera.setPosition(glm::vec3(-10,0,0));
}

void Engine::messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam)
{
	switch (severity)
	{
		case GL_DEBUG_SEVERITY_HIGH:
			std::cout << "ERROR " << id << ": " << message << std::endl;
			//if (IsDebuggerPresent())
			//	__debugbreak();
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			std::cout << "WARNING " << id << ": " << message << std::endl;
			break;
		case GL_DEBUG_SEVERITY_LOW:
			std::cout << "INFO " << id << ": " << message << std::endl;
			break;
	}
}

void Engine::activateDebugMode(){
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(messageCallback,nullptr);
	std::cout << "Driver: " << glGetString(GL_VERSION) << "\n";
	std::cout<< "GPU: " << glGetString(GL_RENDERER) << "\n";
}

void Engine::processInput() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void Engine::run() {
	std::cout << "run" << "\n";

	mainCamera.update();
	Shader myShader("phongLighting");

	//Object dragon(DragonVertices,DragonIndices);

	//creation objet
	Mesh dragon;
	dragon.setVertices(DragonVertices, sizeof(DragonVertices) / sizeof(float));
	dragon.setIndices(DragonIndices, sizeof(DragonIndices) / sizeof(uint16_t));

	while (!glfwWindowShouldClose(window)) {
		//events
		glfwPollEvents();// check les evenements qui ont eu lieu depuis le dernier appel de cette fonction
		//inputs
		processInput();

		//rendering

		glClearColor(0.4f, 0.4f, 0.4f, 0.4f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		myShader.bind();
		glm::vec3 dragonPosition = glm::vec3(0, -5, 0); //position de l'objet en world space

		glm::vec3 lightPos(10.0f, 10.0f, 10.0f);
		glm::vec3 lightColor(0.0f, 1.0f, 1.0f);
		glm::vec3 objectColor(0.5f, 0.5f, 0.5f);

		//                on construit le translate         on ajoute une rotation                          et un scale
		glm::mat4 model = glm::translate(dragonPosition) * glm::eulerAngleXYZ(0.0f, (float)glfwGetTime() * 0.75f, 0.0f) * glm::scale(glm::vec3(1.0f));


		glm::mat4 mvp = mainCamera.getProjection() * mainCamera.getView() * model;

		float ambientStrength = 0.4f;
		glm::vec3 ambientColor(1.0f,0.4f,1.0f);
		glm::vec3 specularColor(1.0f,0.0f,0.7f);

		myShader.setMat4("mvp",mvp);
		myShader.setMat4("model",model);
		myShader.setVec3("objectColor",objectColor);
		myShader.setVec3("camPos",mainCamera.getPosition());
		myShader.setVec3("lightPos",lightPos);
		myShader.setVec3("lightColor",lightColor);
		myShader.setFloat("ambientStrength",ambientStrength);
		myShader.setVec3("ambientColor",ambientColor);
		myShader.setFloat("specularStrength",2.0f);
		//myShader.setVec3("specularColor",specularColor);


		dragon.bind();
		glDrawElements(GL_TRIANGLES, sizeof(DragonIndices) / sizeof(uint16_t), GL_UNSIGNED_SHORT, nullptr);
		dragon.unbind();
		//dragon.draw();

		//swap
		glfwSwapBuffers(window); //échange les deux buffers (back buffer = tu fais ton rendu, front buffer = ton image affichée)
	}

	glfwTerminate();
}
