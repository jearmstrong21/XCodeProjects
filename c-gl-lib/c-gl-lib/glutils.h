//
//  glutils.h
//  c-gl-lib
//
//  Created by Jack Armstrong on 8/31/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef glutils_h
#define glutils_h

#include <stdio.h>

#include <OpenGL/gl3.h>

typedef GLubyte* byte_str;
typedef const GLubyte* const_byte_str;

void glutils_set_clear_color(float r,float g,float b);
void glutils_clear_screen(void);

int glutils_get_integer(int prop);
const_byte_str glutils_get_string(int prop);

#endif /* glutils_h */
