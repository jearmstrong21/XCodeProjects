//
//  main.c
//  c-gl-lib
//
//  Created by Jack Armstrong on 7/14/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#include "glconfig.h"

#include "glwin.h"
#include "glutils.h"
#include "glshader.h"
#include "glarr.h"
#include "glbuf.h"
#include "utils.h"

void error_func(int i,const_char_str str){
    printf("ERROR\n");
    switch(i){
        case GLFW_NOT_INITIALIZED:
            printf("Not initialized: %s\n",str);
            break;
        case GLFW_NO_CURRENT_CONTEXT:
            printf("No current context: %s\n",str);
            break;
        case GLFW_INVALID_ENUM:
            printf("Invalid enum: %s\n",str);
            break;
        case GLFW_INVALID_VALUE:
            printf("Invalid value: %s\n",str);
            break;
        case GLFW_OUT_OF_MEMORY:
            printf("Out of memory: %s\n",str);
            break;
        case GLFW_API_UNAVAILABLE:
            printf("API Unavailable: %s\n",str);
            break;
        case GLFW_VERSION_UNAVAILABLE:
            printf("Version unavailable: %s\n",str);
            break;
        case GLFW_PLATFORM_ERROR:
            printf("Platform error: %s\n",str);
            break;
        case GLFW_FORMAT_UNAVAILABLE:
            printf("Format unavailable: %s\n",str);
            break;
    }
    printf("Press any key to continue\n");
    getchar();
}

int main(int argc, const char * argv[]) {
    
    glwin_init();
    glfwSetErrorCallback(error_func);
    
    glwin_default_hints();
    glwin_hints_version(4,1);
    glwin_hints_forward_compat(true);
    glwin_hints_profile(PROFILE_CORE);
    glwin win=glwin_create();
    glwin_set_size(win, 500,500);
    glwin_set_title(win, "Title");
    glwin_bind(win);
    
    const_byte_str version=glutils_get_string(GL_VERSION);
    int major=glutils_get_integer(GL_MAJOR_VERSION);
    int minor=glutils_get_integer(GL_MINOR_VERSION);
    
    printf("Version: %s\n",version);
    printf("Major version: %i\nMinor version: %i\n",major,minor);
    
    glshader shader=glshader_create();
    glshader_attach_file(shader, "shader.vert", SHADER_VERTEX);
    glshader_attach_file(shader, "shader.frag", SHADER_FRAGMENT);
    glshader_link(shader);
    
    glarr array=glarr_create();
    
    glarr_bind(array);
    
    float posData[]={
        0,0,0,
        1,0,0,
        0,1,0
    };
    glbuf bufPos=glbuf_create(glbuf_usage_STATIC_DRAW, glbuf_target_ARRAY);
    glbuf_bind(bufPos);
    glbuf_set_data(bufPos, posData, sizeof(posData));
    glbuf_add_attrib(0, 3, glbuf_type_FLOAT, false, 3*sizeof(float), 0);
    glbuf_unbind(bufPos);
    
    float colData[]={
        1,0,0,
        0,1,0,
        0,0,1
    };
    glbuf bufCol=glbuf_create(glbuf_usage_STATIC_DRAW,glbuf_target_ARRAY);
    glbuf_bind(bufCol);
    glbuf_set_data(bufCol,colData,sizeof(colData));
    glbuf_add_attrib(1,3,glbuf_type_FLOAT,false,3*sizeof(float),0);
    glbuf_unbind(bufCol);
    
    glarr_unbind();
    
    printf("Shader id: %i\n",shader);
    printf("Array id: %i\n",array);
    
    while(glwin_is_open(win)){
        glwin_bind(win);
//        float gray=0.5+0.5*cos(glwin_get_time());
//        glutils_set_clear_color(gray,gray,gray);
        glutils_set_clear_color(1,1,1);
        glutils_clear_screen();
        
        glshader_bind(shader);
        
        glarr_bind(array);
        
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glarr_unbind();
        
        glshader_unbind();
        
        glwin_swap_buffers(win);
        glwin_poll_events();
    }
//    while(true){}
    
    glwin_end();
    
    return 0;
}
