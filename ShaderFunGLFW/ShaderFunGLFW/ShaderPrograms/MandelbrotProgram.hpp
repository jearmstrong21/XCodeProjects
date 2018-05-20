//
//  MandelbrotProgram.hpp
//  ShaderFunGLFW
//
//  Created by Jack Armstrong on 5/15/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef MandelbrotProgram_hpp
#define MandelbrotProgram_hpp

#include <string>
#include <stdio.h>
#include "shaders.hpp"
#include "ShaderProgram.hpp"


class MandelbrotProgram:public ShaderProgram{
public:
    MandelbrotProgram();
    
    void glAssignParams();
};



#endif /* MandelbrotProgram_hpp */
