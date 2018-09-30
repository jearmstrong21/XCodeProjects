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

void glbuf_set_data(glbuf glb,size_t size,const void*data){
    glBufferData(glb.target, size, data, glb.usage);
}

void glbuf_modify_data(glbuf glb,const void*data,int start,int dist){
    glBufferSubData(glb.target, start, dist, data);
}

void glbuf_delete(glbuf glb){
    glDeleteBuffers(1, &glb.internal);
}
