//
//  glwin.c
//  c-gl-lib
//
//  Created by Jack Armstrong on 7/14/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "glwin.h"

void glwin_init(void){
    glfwInit();
}

glwin* glwin_create(void){
    return glfwCreateWindow(100, 100, "Default title", NULL, NULL);
}

void glwin_default_hints(void){
    glfwDefaultWindowHints();
}

void glwin_hint_version(int major,int minor){
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
}

void glwin_hint_profile(int profile){
    glfwWindowHint(GLFW_OPENGL_PROFILE,profile);
}

void glwin_hint_forward_compat(bool forward_compat){
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, forward_compat);
}

void glwin_set_size(glwin*win,const int w,const int h){
    glfwSetWindowSize(win, w, h);
}

void glwin_set_title(glwin*win,const char* title){
    glfwSetWindowTitle(win, title);
}

void glwin_init_gl(glwin*win){
    glfwMakeContextCurrent(win);
}

void glwin_set_visible(glwin*win,bool visible){
    if(visible)glwin_show(win);
    else glwin_hide(win);
}

void glwin_show(glwin*win){
    glfwShowWindow(win);
}

void glwin_hide(glwin*win){
    glfwHideWindow(win);
}

bool glwin_should_close(glwin*win){
    return glfwWindowShouldClose(win);
}

void glwin_swap_buffers(glwin* win){
    glfwSwapBuffers(win);
}

void glwin_poll_events(void){
    glfwPollEvents();
}

void glwin_delete(glwin*win){
    glfwDestroyWindow(win);
}

void glwin_end(void){
    glfwTerminate();
}
