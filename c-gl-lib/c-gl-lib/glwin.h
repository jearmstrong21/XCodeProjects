//
//  glwin.h
//  c-gl-lib
//
//  Created by Jack Armstrong on 8/31/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef glwin_h
#define glwin_h

#include <stdio.h>

#include <GLFW/glfw3.h>
#include "utils.h"
#include <stdbool.h>

typedef GLFWwindow* glwin;

#define PROFILE_CORE GLFW_OPENGL_CORE_PROFILE
#define PROFILE_COMPAT GLFW_OPENGL_COMPAT_PROFILE
#define PROFILE_ANY GLFW_OPENGL_ANY_PROFILE

void glwin_init(void);

glwin glwin_create(void);

float glwin_get_time(void);

void glwin_set_size(glwin win,int w,int h);
void glwin_set_title(glwin win,char*title);

void glwin_hints_version(int major,int minor);
void glwin_hints_forward_compat(bool forwardCompat);
void glwin_hints_profile(int profile);

void glwin_default_error_func(int i,const_char_str str);
void glwin_set_error_func(GLFWerrorfun ef);

void glwin_default_hints(void);

void glwin_destroy(glwin win);

bool glwin_is_open(glwin win);

void glwin_bind(glwin win);

void glwin_swap_buffers(glwin win);
void glwin_poll_events(void);

void glwin_end(void);

#endif /* glwin_h */
