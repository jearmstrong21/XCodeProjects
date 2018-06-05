//
//  Letter.hpp
//  GLFW_UI
//
//  Created by Jack Armstrong on 5/31/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef Letter_hpp
#define Letter_hpp

#include <glfw3.h>
#include <OpenGL/gl3.h>
#include <iostream>
#include "Texture.hpp"
#include "ShaderProgram.hpp"
#include <glm/glm.hpp>
#include "VO.hpp"

class Letter{
private:
    VO vo;
    ShaderProgram shader;
public:
    Texture tex;//needs assigning
    int atlasW;//needs assigning
    int atlasH;//needs assigning
    int atlasX;//needs assigning
    int atlasY;//needs assigning
    vec2 pos;//needs assigning
    vec2 size;
    vec2 uvoff;

    Letter();
    
    void init();
    void render();
    void del();//NOTE: DOES NOT DELETE TEXTURE
    
};

#endif /* Letter_hpp */
