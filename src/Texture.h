//
// Created by Marine on 14/01/2021.
//

#ifndef PROJETPHONG_TEXTURE_H
#define PROJETPHONG_TEXTURE_H


#include <string>
#include "glad/glad.h"

class Texture {
public:
	Texture();
	explicit Texture(const std::string& path);
	~Texture();
	GLuint getId() const;
private:
	GLuint _id;
};


#endif //PROJETPHONG_TEXTURE_H
