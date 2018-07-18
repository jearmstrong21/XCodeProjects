//
//  glwin.h
//  c-gl-lib
//
//  Created by Jack Armstrong on 7/14/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef glwin_h
#define glwin_h

#include <stdio.h>
#include <stdbool.h>
#include <GLFW/glfw3.h>

typedef GLFWwindow glwin;

#define CORE GLFW_OPENGL_CORE_PROFILE

void glwin_init(void);

void glwin_default_hints(void);
void glwin_hint_version(int major,int minor);
void glwin_hint_profile(int profile);
void glwin_hint_forward_compat(bool forward_compat);

glwin* glwin_create(void);

void glwin_set_size(glwin* win,const int w,const int h);
void glwin_set_title(glwin* win,const char* title);

void glwin_init_gl(glwin*win);

void glwin_set_visible(glwin*win, bool visible);
void glwin_show(glwin*win);
void glwin_hide(glwin*win);

bool glwin_should_close(glwin*win);

void glwin_swap_buffers(glwin*win);
void glwin_poll_events(void);

void glwin_delete(glwin*win);

void glwin_end(void);

#endif /* glwin_h */
