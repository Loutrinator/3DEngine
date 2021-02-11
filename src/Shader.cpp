//
// Created by Marine on 11/01/2021.
//

#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Helpers/FileHelper.h"
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const std::string &name) {
	_id = glCreateProgram();
	GLuint vertex = loadShader(name + ".vert", GL_VERTEX_SHADER);
	GLuint fragment = loadShader(name + ".frag", GL_FRAGMENT_SHADER);
	glAttachShader(_id, vertex);
	glAttachShader(_id, fragment);
	glLinkProgram(_id);

	glDetachShader(_id, vertex);
	glDetachShader(_id, fragment);

	glDeleteShader(vertex);

	glDeleteShader(fragment);

	GLint linkSuccess;
	glGetProgramiv(_id, GL_LINK_STATUS, &linkSuccess);

	if (linkSuccess == GL_FALSE) {
		int length;
		glGetProgramiv(_id, GL_INFO_LOG_LENGTH, &length);

		std::string error;
		error.resize(length - 1);
		glGetProgramInfoLog(_id, length, nullptr, (char*)error.data());

		throw std::runtime_error("Error while linking shaders to program: " + error);
	}
}

Shader::~Shader() {
	glDeleteProgram(_id);
}

GLuint Shader::loadShader(const std::string &path, GLenum type) {

	std::string source;
	GLuint shader = glCreateShader(type);
	try {
		source = FileHelper::readAllText("resources/shaders/" + path);
	}
	catch (const std::ios_base::failure &e) {
		std::cout << "Unable to open shader file \"" << path << "\"" << std::endl;
		throw e;
	}

	const char *source_c = source.c_str();
	glShaderSource(shader, 1, &source_c, nullptr);
	glCompileShader(shader);

	GLint compileSuccess;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileSuccess);
	if (compileSuccess == GL_FALSE) {
		int length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);

		std::string error;
		error.resize(length - 1);
		glGetShaderInfoLog(shader, length, nullptr, (char*)error.data());

		throw std::runtime_error("Error while compiling shader: " + error);
	}
	return shader;
}

void Shader::bind() const {
	glUseProgram(_id);
}

GLuint Shader::getId() const {
	return _id;
}


void Shader::setBool(const std::string &name, bool value) const {
	glUniform1i(glGetUniformLocation(_id, name.c_str()), (int) value);
}

void Shader::setInt(const std::string &name, int value) const {
	glUniform1i(glGetUniformLocation(_id, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const {
	glUniform1f(glGetUniformLocation(_id, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, glm::vec3 value) const {
    auto toto = glGetUniformLocation(_id, name.c_str());
	glUniform3fv(toto, 1, glm::value_ptr(value));
}
void Shader::setMat4(const std::string& name, glm::mat4 value) const {
	glUniformMatrix4fv(glGetUniformLocation(_id, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

