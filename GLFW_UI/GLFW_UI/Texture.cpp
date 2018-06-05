//
//  Texture.cpp
//  GLFW_UI
//
//  Created by Jack Armstrong on 5/30/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "Texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(){
    
}

Texture::Texture(string fn){
    fileName=fn;
}

void Texture::genTexture(GLenum minFilter,GLenum magFilter){
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(fileName.c_str(), &width, &height, &nrChannels, 0);
    if(!data){
        std::cout<<"Bad texture load for file \""<<fileName<<"\"\n";
        return;
    }
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    std::cout<<"Texture gen for file \""<<fileName<<"\", "<<width<<"x"<<height<<": "<<id<<std::endl;
}

void Texture::bindTexture(){
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::delTexture(){
    glDeleteTextures(1, &id);
}
