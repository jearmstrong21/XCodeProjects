//
//  glbuf.h
//  c-gl-lib
//
//  Created by Jack Armstrong on 9/1/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef glbuf_h
#define glbuf_h

#include <stdio.h>
#include <OpenGL/gl3.h>
#include <stdbool.h>

typedef int glbuf_usage;
typedef int glbuf_target;

#define glbuf_target_ARRAY GL_ARRAY_BUFFER
#define glbuf_target_ATOMIC_COUNTER GL_ATOMIC_COUNTER_BUFFER
#define glbuf_target_COPY_READ GL_COPY_READ_BUFFER
#define glbuf_target_COPY_WRITE GL_COPY_WRITE_BUFFER
#define glbuf_target_DISPATCH_INDIRECT GL_DISPATCH_INDIRECT_BUFFER
#define glbuf_target_DRAW_INDIRECT GL_DRAW_INDIRECT_BUFFER
#define glbuf_target_ELEMENT_ARRAY GL_ELEMENT_ARRAY_BUFFER
#define glbuf_target_PIXEL_PACK GL_PIXEL_PACK_BUFFER
#define glbuf_target_PIXEL_UNPACK GL_PIXEL_UNPACK_BUFFER
#define glbuf_target_QUERY GL_QUERY_BUFFER
#define glbuf_target_SHADER_STORAGE GL_SHADER_STORAGE_BUFFER
#define glbuf_target_TEXTURE GL_TEXTURE_BUFFER
#define glbuf_target_TRANSFORM_FEEDBACK GL_TRANSFORM_FEEDBACK_BUFFER
#define glbuf_target_UNIFORM GL_UNIFORM_BUFFER

#define glbuf_usage_STREAM_DRAW GL_STREAM_DRAW
#define glbuf_usage_STREAM_READ GL_STREAM_READ
#define glbuf_usage_STREAM_COPY GL_STREAM_COPY
#define glbuf_usage_STATIC_DRAW GL_STATIC_DRAW
#define glbuf_usage_STATIC_READ GL_STATIC_READ
#define glbuf_usage_STATIC_COPY GL_STATIC_COPY
#define glbuf_usage_DYNAMIC_DRAW GL_DYNAMIC_DRAW
#define glbuf_usage_DYNAMIC_READ GL_DYNAMIC_READ
#define glbuf_usage_DYNAMIC_COPY GL_DYNAMIC_COPY

#define glbuf_type_BYTE GL_BYTE
#define glbuf_type_UNSIGNED_BYTE GL_UNSIGNED_BYTE
#define glbuf_type_SHORT GL_SHORT
#define glbuf_type_UNSIGNED_SHORT GL_UNSIGNED_SHORT
#define glbuf_type_INT GL_INT
#define glbuf_type_UNSIGNED_INT GL_UNSIGNED_INT
#define glbuf_type_HALF_FLOAT GL_HALF_FLOAT
#define glbuf_type_FLOAT GL_FLOAT
#define glbuf_type_DOUBLE GL_DOUBLE
#define glbuf_type_FIXED GL_FIXED
#define glbuf_type_INT_2_10_10_10_REV GL_INT_2_10_10_10_REV
#define glbuf_type_UNSIGNED_INT_2_10_10_10_REV GL_UNSIGNED_INT_2_10_10_10_REV
#define glbuf_type_UNSIGNED_INT_10f_11f_11f_REV GL_UNSIGNED_INT_10F_11F_11F_REV

typedef struct {
    GLuint internal;
    glbuf_usage usage;
    glbuf_target target;
} glbuf;


glbuf glbuf_create(glbuf_usage usage,glbuf_target target);

void glbuf_bind(glbuf glb);
void glbuf_unbind(glbuf glb);

void glbuf_add_attrib(int attrib,int size,int type,bool norm,int stride,int start);
void glbuf_set_data(glbuf glb,size_t size,const void*data);
void glbuf_modify_data(glbuf glb,const void*data,int start,int dist);
void glbuf_delete(glbuf glb);

#endif /* glbuf_h */
