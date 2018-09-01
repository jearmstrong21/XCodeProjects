//
//  glwin.c
//  c-gl-lib
//
//  Created by Jack Armstrong on 8/31/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "glwin.h"

void glwin_init(void){
    glfwInit();
}

glwin glwin_create(void){
    return glfwCreateWindow(100, 100, "Default Title", 0, 0);
}

float glwin_get_time(void){
    return glfwGetTime();
}

void glwin_hints_version(int major,int minor){
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
}

void glwin_hints_forward_compat(bool forwardCompat){
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, forwardCompat);
}

void glwin_hints_profile(int profile){
    glfwWindowHint(GLFW_OPENGL_PROFILE, profile);
}

void glwin_set_size(glwin win,int w,int h){
    glfwSetWindowSize(win, w, h);
}
void glwin_set_title(glwin win,char*title){
    glfwSetWindowTitle(win, title);
}

void glwin_default_hints(void){
    glfwDefaultWindowHints();
}

void glwin_destroy(glwin win){
    glfwDestroyWindow(win);
}

bool glwin_is_open(glwin win){
    return !glfwWindowShouldClose(win);
}

void glwin_bind(glwin win){
    glfwMakeContextCurrent(win);
}

void glwin_swap_buffers(glwin win){
    glfwSwapBuffers(win);
}
void glwin_poll_events(void){
    glfwPollEvents();
}

void glwin_end(void){
    glfwTerminate();
}
