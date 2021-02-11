//
// Created by Marine on 14/01/2021.
//

#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(const std::string& path):_id(0)  {

	int width, height, nrChannels;
	unsigned char* data = stbi_load(("resources/textures/" + path).c_str(), &width, &height, &nrChannels, 0);

	glGenTextures(1, &_id);
	glBindTexture(GL_TEXTURE_2D, _id);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, width, height);
    glTexSubImage2D(GL_TEXTURE_2D,0,0,0,width,height,GL_RGB, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);
}
/*
 *
    glTextureStorage2D(_id, 1, GL_RGB, width, height);
    glTextureSubImage2D(_id,0,0,0,width,height,GL_RGB, GL_UNSIGNED_BYTE, data);
 * */
Texture::Texture(int width, int height, GLenum format):_id(0) {
    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexStorage2D(GL_TEXTURE_2D, 1, format, width, height);
    //glGenerateMipmap(GL_TEXTURE_2D); //faudra augmenter level pour calculer le nombre de mipmap necessaires
}

GLuint Texture::getId() const {
	return _id;
}

Texture::~Texture() {
	glDeleteTextures(1,&_id);
}

Texture::Texture() {

}
