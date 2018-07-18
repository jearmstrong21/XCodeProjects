//
//  glutil.h
//  c-gl-lib
//
//  Created by Jack Armstrong on 7/14/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef glutil_h
#define glutil_h

#include <stdio.h>
#include <stdbool.h>
#include "util.h"
#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>

void glutil_clear_screen(float r,float g,float b);
float glutil_get_time(void);
void glutil_print_info(void);
void glutil_print_ext(void);
int glutil_get_major_version(void);
int glutil_get_minor_version(void);

#endif /* glutil_h */
