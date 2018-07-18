//
//  glshader.c
//  c-gl-lib
//
//  Created by Jack Armstrong on 7/14/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "glshader.h"

glshader glshader_compile(const_glstr_c source,glshader_type type){
    glshader s=glCreateShader(type);
    glShaderSource(s, 1, &source, NULL);
    glCompileShader(s);
#ifdef glshader_CHECK_FOR_ERRORS
    int success;
    char infoLog[1024];
    glGetShaderiv(s, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(s, 512, NULL, infoLog);
        const char*str_type=(type==VERTEX?"vertex": (type==FRAGMENT?"fragment":"other")  );
        printf("Shader compilation error for %s:\n%s\n",str_type,infoLog);
        return -1;
    }
#endif
    return s;
}

int glshader_compiled(glshader s){
    int success;
    glGetShaderiv(s, GL_COMPILE_STATUS, &success);
    return success;
}

char* glshader_error_log(glshader s){
    char*infoLog=(char*)malloc(sizeof(char)*512);
    glGetShaderInfoLog(s, 512, NULL, infoLog);
    return infoLog;
}

glshader_program glshader_program_gen(void){
    glshader_program sp=glCreateProgram();
    return sp;
}

glshader_program glshader_program_attach(glshader_program p,glshader s){
    glAttachShader(p, s);
    return p;
}

glshader_program glshader_program_link(glshader_program p){
    glLinkProgram(p);
    return p;
}

void glshader_program_bind(glshader_program sp){
    glUseProgram(sp);
}
void glshader_program_unbind(){
    glUseProgram(0);
}

void glshader_program_delete(glshader_program p){
    glDeleteProgram(p);
}
