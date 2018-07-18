//
//  glutil.c
//  c-gl-lib
//
//  Created by Jack Armstrong on 7/14/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "glutil.h"

void glutil_clear_screen(float r,float g,float b){
    glClearColor(r, g, b, 1.0);
    glClear(GL_DEPTH_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
}

float glutil_get_time(void){
    return glfwGetTime();
}

int glutil_get_major_version(void){
    int major;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    return major;
}

int glutil_get_minor_version(void){
    int minor;
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    return minor;
}

void glutil_print_ext(void){
    int num;
    glGetIntegerv(GL_NUM_EXTENSIONS, &num);
    for(int i=0;i<num;i++){
        const_glstr_b log=glGetStringi(GL_EXTENSIONS, i);
        printf("Extension %2i: %s\n",i,log);
    }
}

void glutil_print_info(void){
    const_glstr_b version=glGetString(GL_VERSION);
    const_glstr_b renderer=glGetString(GL_RENDERER);
    const_glstr_b vendor=glGetString(GL_VENDOR);
    const_glstr_b glslVersion=glGetString(GL_SHADING_LANGUAGE_VERSION);
    int major=glutil_get_major_version();
    int minor=glutil_get_minor_version();
    printf("Major version ... %i\n",major);
    printf("Minor version ... %i\n",minor);
    printf("Renderer ........ %s\n",renderer);
    printf("Vendor .......... %s\n",vendor);
    printf("Version ......... %s\n",version);
    printf("GLSL version .... %s\n",glslVersion);
}
