//
// Created by Marine on 13/01/2021.
//

#define TINYOBJLOADER_IMPLEMENTATION
#include "Engine.h"
#include <iostream>
#include "Shader.h"
#include "Object.h"
#include "Dragon.h"
#include "Light.h"
#include "LoadedObj.h"
#include <glm/gtx/transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <vector>

void Engine::setup(int width, int height, bool debug) {
	glfwInit();
	initWindow(width, height,debug);
    //glfwSwapInterval(0);

	std::cout << "Driver: " << glGetString(GL_VERSION) << "\n";
	std::cout<< "GPU: " << glGetString(GL_RENDERER) << "\n";

	if(debug){
		activateDebugMode();
	}

	mainCamera.setPosition(glm::vec3(-9.8f, 8.3f, -1.16f));
	mainCamera.FOV = 90.0f;
	mainCamera.speed = 0.1f;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetCursorPosCallback(window, mouse_callback);
}

void Engine::mouse_callback(GLFWwindow* window, double xpos, double ypos){
	if (Engine::instance->firstMouse)
	{
		Engine::instance->lastX = xpos;
		Engine::instance->lastY = ypos;
		Engine::instance->mainCamera.yaw   = 0;
		Engine::instance->mainCamera.pitch = 0;
		Engine::instance->firstMouse = false;
	}

	//inverser la formule ici pour inverser les axes
	float xoffset = (float)xpos - (float)Engine::instance->lastX;
	float yoffset = (float)Engine::instance->lastY - (float)ypos;
	Engine::instance->lastX = xpos;
	Engine::instance->lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	Engine::instance->mainCamera.yaw   += xoffset;
	Engine::instance->mainCamera.pitch += yoffset;
}

void Engine::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

int Engine::initWindow(int width, int height, bool debug) {

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	if(debug){
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	}

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

	return 1;
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
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(messageCallback,nullptr);
}

void Engine::processInput() {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	const float cameraSpeed = 0.05f; // adjust accordingly
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		mainCamera.moveLeft();
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		mainCamera.moveRight();
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		mainCamera.moveForward();
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		mainCamera.moveBackward();
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		mainCamera.moveUp();
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
		mainCamera.moveDown();
}

void Engine::run() {
	std::cout << "run" << "\n";

	//SHADER
    Shader shader("phongLighting");

    //POST PROCESSING SHADERS
    Shader negativeShader("Post Processing/negative");
    Shader baseShader("Post Processing/base");


    //LIGHT
    glm::vec3 lightPos(5.0f, 10.0f, 0);
    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
    glm::vec3 lightDiffuse = lightColor * 0.7f;
    glm::vec3 lightAmbient = lightDiffuse * 0.1f;
    glm::vec3 lightSpecular(1.0f);

    Light mainLight(lightPos,lightAmbient,lightDiffuse,lightSpecular,&shader);


    //MATERIALS
    Texture crystalTexture("lightSwirlMarble.jpg");
    glm::vec3 redDiffuse(1.0f, 0.0f, 0.0f);
    glm::vec3 redAmbient = redDiffuse;
    glm::vec3 redSpecular(0.5f);
    float redShininess = 256;

    Material redPlasticMaterial(&shader, redAmbient, redDiffuse, redSpecular, redShininess);

    glm::vec3 blueDiffuse(0.0f, 0.0f, 1.0f);
    glm::vec3 blueAmbient = blueDiffuse;
    glm::vec3 blueSpecular(0.8f);
    float blueShininess = 128;

    Material bluePlasticMaterial(&shader, blueAmbient,blueDiffuse,blueSpecular,blueShininess);


    //OBJECTS
    std::vector<Object> objects;

	Mesh dragonMesh;
	dragonMesh.setVertices(DragonVertices, sizeof(DragonVertices) / sizeof(float));
	dragonMesh.setIndices(DragonIndices, sizeof(DragonIndices) / sizeof(uint16_t));

	Object dragon(dragonMesh,redPlasticMaterial, glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0f, -45.0f, 0.0f), glm::vec3(1.0f));
    //objects.push_back(dragon);

	float planeVertices[] = {
			1.0f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f, // top right
			1.0f,  -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  1.0f, 0.0f,  // bottom right
			-1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  0.0f, 0.0f,  // bottom left
			-1.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,   // top left
	};
	uint16_t planeIndices[] = {  // note that we start from 0!
			0, 1, 3,   // first triangle
			1, 2, 3    // second triangle
	};

	Mesh planeMesh;
	planeMesh.setVertices(planeVertices,sizeof(planeVertices) / sizeof(float));
	planeMesh.setIndices(planeIndices,sizeof(planeIndices) / sizeof(uint16_t));

	Object plane(planeMesh, bluePlasticMaterial, glm::vec3(0.0f), glm::vec3(glm::radians(90.0f),0.0f,0.0f), glm::vec3(10.0f));
    objects.push_back(plane);

    // LOAD OBJ
    LoadedObj obj(&shader, "resources/obj/sphere_smooth.obj", "resources/obj/");

    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);//creation
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    int windowWidth;
    int windowHeight;
    glfwGetWindowSize(window,&windowWidth,&windowHeight);
    Texture colorTexture(windowWidth, windowHeight, GL_RGB8);
    Texture depthTexture(windowWidth, windowHeight, GL_DEPTH_COMPONENT32);
    //Texture stencilTexture(windowWidth, windowHeight, GL_STENCIL);//TODO
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture.getId(), 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture.getId(), 0);
    GLenum attachments[] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1,attachments);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE){
        std::cout << "Failed to link framebuffer" << std::endl;
    }

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	while (!glfwWindowShouldClose(window)) {

		//events
		glfwPollEvents();// check les evenements qui ont eu lieu depuis le dernier appel de cette fonction
		//inputs
		processInput();

		mainCamera.update();

		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//rendering

		const float radius = 20.0f;
        //lightPos.x = sin(glfwGetTime()) * radius;
        //lightPos.z = cos(glfwGetTime()) * radius;
        mainLight.setPosition(lightPos);

        glEnable(GL_DEPTH_TEST);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.bind();
        mainLight.bind();
        shader.setVec3("camPos", mainCamera.getPosition());


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, crystalTexture.getId());

		for(Object& object : objects){
            glm::mat4 model = object.getTransform().getLocalMatrix();
            glm::mat4 MVP = mainCamera.getProjection() * mainCamera.getView() * model;

            shader.setMat4("mvp", MVP);
            shader.setMat4("model", model);
            object.draw();
		}
		obj.draw(mainCamera);

        glDisable(GL_DEPTH_TEST);

		//POST PROCESSING

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        planeMesh.bind();

        baseShader.bind();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, colorTexture.getId());

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, planeMesh.getIndiceSize(), GL_UNSIGNED_SHORT, nullptr);


		//swap
		glfwSwapBuffers(window); //échange les deux buffers (back buffer = tu fais ton rendu, front buffer = ton image affichée)
	}

	glfwTerminate();
}

std::unique_ptr<Engine> Engine::instance = std::make_unique<Engine>();


Engine::Engine() {
	deltaTime = 0.0f;
	lastFrame = glfwGetTime();
}


/*
 * */

