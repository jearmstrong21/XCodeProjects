//
//  glshader.h
//  c-gl-lib
//
//  Created by Jack Armstrong on 7/14/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef glshader_h
#define glshader_h

#include <stdio.h>
#include <stdbool.h>
#include <OpenGL/gl3.h>
#include "glutil.h"

typedef GLuint glshader;
typedef GLuint glshader_program;

typedef GLuint glshader_type;

#define VERTEX GL_VERTEX_SHADER
#define FRAGMENT GL_FRAGMENT_SHADER

glshader glshader_compile(const_glstr_c source,glshader_type type);

glshader_program glshader_program_gen(void);

int glshader_compiled(glshader s);
cstr glshader_error_log(glshader s);

glshader_program glshader_program_attach(glshader_program p,glshader s);

glshader_program glshader_program_link(glshader_program p);

void glshader_program_bind(glshader_program sp);
void glshader_program_unbind(void);

void glshader_program_delete(glshader_program p);

#endif /* glshader_h */
