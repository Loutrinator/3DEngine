//
// Created by Marine on 13/01/2021.
//

#ifndef PROJETPHONG_ENGINE_H
#define PROJETPHONG_ENGINE_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>
#include "Camera.h"
#include "Texture.h"


class Engine {
public:
	void setup(int width, int height, bool debug);
	GLFWwindow* window{};
	void processInput();
	void run();
	Camera mainCamera;
	float deltaTime{};
	static std::unique_ptr<Engine> instance;

	Engine();


private:
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
	static void messageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *message, const void *userParam);
	static void activateDebugMode();
	int initWindow(int width, int height, bool debug);
	float lastFrame{};

	bool firstMouse;
	double lastX;
	double lastY;

	Texture textureLoader;
};


#endif //PROJETPHONG_ENGINE_H
