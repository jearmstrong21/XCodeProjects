//
//  glutils.c
//  c-gl-lib
//
//  Created by Jack Armstrong on 8/31/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "glutils.h"

void glutils_set_clear_color(float r,float g,float b){
    glClearColor(r,g,b,1);
}
void glutils_clear_screen(void){
    glClear(GL_COLOR_BUFFER_BIT);
}

int glutils_get_integer(int prop){
    int i;
    glGetIntegerv(prop,&i);
    return i;
}

const_byte_str glutils_get_string(int prop){
    return glGetString(prop);
}
