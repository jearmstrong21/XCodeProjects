//
//  Texture.hpp
//  GLFW_UI
//
//  Created by Jack Armstrong on 5/30/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef Texture_hpp
#define Texture_hpp

#include <string>
#include <glfw3.h>
#include <OpenGL/gl3.h>
#include <iostream>


using std::string;

class Texture{
public:
    unsigned int id;
    string uniformName;
    string fileName;
    int width;
    int height;
    int nrChannels;
    
    Texture();
    Texture(string fn);
    
    void genTexture(GLenum minFilter,GLenum magFilter);
    
    void bindTexture();
    
    void delTexture();
};

#endif /* Texture_hpp */
