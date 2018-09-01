//
//  glshader.h
//  c-gl-lib
//
//  Created by Jack Armstrong on 9/1/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef glshader_h
#define glshader_h

#include <stdio.h>
#include <OpenGL/gl3.h>
#include "utils.h"
#include <stdbool.h>

//glshader_DEBUG_ERR_LOG

#define SHADER_VERTEX GL_VERTEX_SHADER
#define SHADER_FRAGMENT GL_FRAGMENT_SHADER

typedef int glshader;
typedef int glshader_type;

glshader glshader_create(void);
void glshader_attach_file(glshader gls,const_char_str filename,glshader_type type);
void glshader_attach_code(glshader gls,const_char_str code,glshader_type type);
void glshader_link(glshader gls);

void glshader_bind(glshader gls);
void glshader_unbind(void);

void glshader_delete(glshader gls);

#endif /* glshader_h */
