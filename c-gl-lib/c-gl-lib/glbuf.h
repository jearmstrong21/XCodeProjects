//
//  glbuf.h
//  c-gl-lib
//
//  Created by Jack Armstrong on 7/15/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef glbuf_h
#define glbuf_h

#include <stdio.h>
#include <stdbool.h>
#include <OpenGL/gl3.h>

typedef GLuint glbuf_target;
typedef GLuint glbuf_usage;
typedef GLuint glbuf_id;
typedef GLuint glbuf_size;

typedef struct {
    float*fdata;
    int*idata;
    glbuf_size size;
    glbuf_id buf;
    glbuf_target target;
    glbuf_usage usage;
} glbuf;

glbuf glbuf_gen(glbuf_target target,glbuf_usage usage);

void glbuf_bind(glbuf buf);
void glbuf_unbind(glbuf buf);

void glbuf_set_data(glbuf buf,float*fdata,glbuf_size size);

void glbuf_add_attrib(glbuf buf,int attrib,int size,int attribType,bool norm,int stride,int start);

void glbuf_render_array(glbuf buf,GLuint first,GLuint count);

void glbuf_delete(glbuf buf);

#endif /* glbuf_h */
