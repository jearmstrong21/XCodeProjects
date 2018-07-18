//
//  glbuf.c
//  c-gl-lib
//
//  Created by Jack Armstrong on 7/15/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "glbuf.h"

glbuf glbuf_gen(glbuf_target target,glbuf_usage usage){
    glbuf buf;
    glGenBuffers(1, &buf.buf);
    buf.target=target;
    buf.usage=usage;
    buf.size=0;
    buf.fdata=NULL;
    buf.idata=NULL;
    return buf;
}

void glbuf_bind(glbuf buf){
    glBindBuffer(buf.target, buf.buf);
}

void glbuf_unbind(glbuf buf){
    glBindBuffer(buf.target, 0);
}

void glbuf_set_data(glbuf buf,float*fdata,glbuf_size num){
    buf.fdata=fdata;
    buf.size=num;
    glBufferData(buf.target, num*sizeof(float), fdata, buf.usage);
}

void glbuf_add_attrib(glbuf buf,int attrib,int size,int attribType,bool norm,int stride,int start){
    glEnableVertexAttribArray(attrib);
    glVertexAttribPointer(attrib, size, attribType, norm, stride, 0);
}

void glbuf_render_array(glbuf buf,GLuint first,GLuint count){
    glDrawArrays(GL_TRIANGLES, first, count);
}

void glbuf_delete(glbuf buf){
    glDeleteBuffers(1, &buf.buf);
}
