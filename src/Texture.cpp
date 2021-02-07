//
// Created by Marine on 14/01/2021.
//

#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string& path) {

	int width, height, nrChannels;
	unsigned char* data = stbi_load(("resources/textures/" + path).c_str(), &width, &height, &nrChannels, 0);
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);
	_id = texture;
}

GLuint Texture::getId() const {
	return _id;
}

Texture::~Texture() {
	glDeleteTextures(1,&_id);
}

Texture::Texture() {

}
