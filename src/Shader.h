//
// Created by Antoine on 11/01/2021.
//

#ifndef PROJETPHONG_SHADER_H
#define PROJETPHONG_SHADER_H


#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader {
public:
	Shader(const std::string& name);
	~Shader();
	void bind() const;
	GLuint getId() const;
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;
	void setVec3(const std::string& name, glm::vec3 value) const;
	void setMat4(const std::string& name, glm::mat4 value) const;

private:
	GLuint _id;
	static GLuint loadShader(const std::string& path, GLenum type);
};


#endif //PROJETPHONG_SHADER_H
