//
// Created by Marine on 13/01/2021.
//

#ifndef PROJETPHONG_ENGINE_H
#define PROJETPHONG_ENGINE_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Camera.h"


class Engine {
public:
	Engine(int width, int height, bool debug);
	GLFWwindow* window;
	void processInput();
	void run();
	Camera mainCamera;
private:
	static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
	static void messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);
	static void activateDebugMode();
	int initWindow(int width, int height, bool debug);
};


#endif //PROJETPHONG_ENGINE_H
