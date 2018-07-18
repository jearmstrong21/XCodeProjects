//
//  util.h
//  c-gl-lib
//
//  Created by Jack Armstrong on 7/14/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef util_h
#define util_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <OpenGL/GL3.h>
#include <GLFW/glfw3.h>

typedef char* cstr;
typedef GLubyte* glstr_b;
typedef GLchar* glstr_c;

typedef const char* const_cstr;
typedef const GLubyte* const_glstr_b;
typedef const GLchar* const_glstr_c;

long slurp(char const* path, char **buf, bool add_nul);
const_glstr_c util_load_file(const_glstr_c fn);

#endif /* util_h */
