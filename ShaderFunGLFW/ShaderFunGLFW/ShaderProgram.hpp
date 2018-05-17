//
//  ShaderProgram.hpp
//  ShaderFunGLFW
//
//  Created by Jack Armstrong on 5/15/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef ShaderProgram_hpp
#define ShaderProgram_hpp

#include <string>
#include <cstdio>
#include <cmath>
#include "shaders.hpp"

using std::string;

class ShaderProgram{
public:
    
    string fragFileName;
    string vertFileName;
    
    int fragID;
    int vertID;
    int progID;
    
    ShaderProgram();
    
    
    void compile();
    void glAssignParams();
    void glBind();
    void unBind();
};

#endif /* ShaderProgram_hpp */
