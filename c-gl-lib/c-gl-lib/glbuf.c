//
//  glbuf.c
//  c-gl-lib
//
//  Created by Jack Armstrong on 9/1/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "glbuf.h"

glbuf glbuf_create(glbuf_usage usage,glbuf_target target){
    glbuf glb;
    glb.usage=usage;
    glb.target=target;
    glGenBuffers(1, &glb.internal);
    return glb;
}

void glbuf_bind(glbuf glb){
    glBindBuffer(glb.target, glb.internal);
}
void glbuf_unbind(glbuf glb){
    glBindBuffer(glb.target, 0);
}

void glbuf_add_attrib(int attrib,int size,int type,bool norm,int stride,int start){
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, size, type, norm, stride, (const GLvoid*)start);
}

void glbuf_set_data(glbuf glb,const void*data,size_t length){
    glBufferData(glb.target, length, data, glb.usage);
}

void glbuf_delete(glbuf glb){
    glDeleteBuffers(1, &glb.internal);
}
