//
//  glshader.c
//  c-gl-lib
//
//  Created by Jack Armstrong on 9/1/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "glshader.h"

glshader glshader_create(void){
    return glCreateProgram();
}
void glshader_attach_file(glshader gls,const_char_str filename,glshader_type type){
    glshader_attach_code(gls, utils_readfile(filename), type);
}
void glshader_attach_code(glshader gls,const_char_str code,glshader_type type){
    int p=glCreateShader(type);
    glShaderSource(p,1,&code,NULL);
    glCompileShader(p);
    
#ifdef glshader_DEBUG_ERR_LOG
    bool success;
    glGetShaderiv(p,GL_COMPILE_STATUS,&success);
    if(!success){
        char log[1024];
        glGetShaderInfoLog(p,1024,NULL,log);
        printf("ERROR LOG for shader:\n%s\n",log);
        return;
    }
#endif
    glAttachShader(gls,p);
    glDeleteShader(p);
}
void glshader_link(glshader gls){
    glLinkProgram(gls);
}

void glshader_bind(glshader gls){
    glUseProgram(gls);
}
void glshader_unbind(void){
    glUseProgram(0);
}

void glshader_delete(glshader gls){
    glDeleteProgram(gls);
}
