//
//  main.c
//  c-gl-lib
//
//  Created by Jack Armstrong on 7/14/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#define glshader_CHECK_FOR_ERRORS

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "glwin.h"
#include "glutil.h"
#include "glshader.h"
#include "glarr.h"
#include "glbuf.h"

int main(int argc, const char * argv[]) {
    glwin_init();
    glwin_default_hints();
    glwin_hint_version(4,1);
    glwin_hint_profile(CORE);
    glwin_hint_forward_compat(true);
    
    glwin*win=glwin_create();
    glwin_set_title(win, "c-gl-lib");
    glwin_set_size(win, 500, 500);
    glwin_show(win);
    glwin_init_gl(win);
    
    glutil_print_ext();
    printf("\n");
    glutil_print_info();
    printf("\n");

    const_glstr_c vertCode=util_load_file("shader.vert");
    const_glstr_c fragCode=util_load_file("shader.frag");
    
//    printf("fragCode: %s\n",fragCode);
    
    glshader vertShader=glshader_compile(vertCode, VERTEX);
    glshader fragShader=glshader_compile(fragCode, FRAGMENT);
    
    if(!glshader_compiled(vertShader))printf("Vertex shader failed: %s\n",glshader_error_log(vertShader));
    if(!glshader_compiled(fragShader))printf("Fragment shader failed: %s\n",glshader_error_log(fragShader));
    
    glshader_program sp=glshader_program_gen();
    glshader_program_attach(sp, vertShader);
    glshader_program_attach(sp, fragShader);
    glshader_program_link(sp);
    
    printf("Shader program id: %i\n",sp);
    
    glarr arr=glarr_gen();
    glarr_bind(arr);
    
    float*fdata=(float*)malloc(sizeof(float)*9);
    fdata[0]=0;fdata[1]=0;fdata[2]=0;
    fdata[3]=1;fdata[4]=0;fdata[5]=0;
    fdata[6]=0;fdata[7]=1;fdata[8]=0;
    
    glbuf buf=glbuf_gen(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    glbuf_bind(buf);
    glbuf_set_data(buf, fdata, 9);
    glbuf_add_attrib(buf, 0, 9*sizeof(float), GL_FLOAT, false, 3*sizeof(float), 0*sizeof(float));
    glbuf_unbind(buf);
    
    glarr_unbind();
    
    printf("VAO id: %i\n",arr);
    printf("VBO id: %i\n",buf.buf);
    
    while(!glwin_should_close(win)){
        float time=glutil_get_time();
        float gray=0.5*cos(time)+0.5;
        glutil_clear_screen(gray,gray,gray);
        
        glshader_program_bind(sp);
        
        glarr_bind(arr);
        
        glbuf_bind(buf);
        glbuf_render_array(buf, 0, 3);
        glbuf_unbind(buf);
        
        glarr_unbind();
        
        glshader_program_unbind();
        
        glwin_swap_buffers(win);
        glwin_poll_events();
    }
    
    glarr_delete(arr);
    
    glwin_delete(win);
    glwin_end();
    
    //glvertarr
    //glvertbuf
    //gledgebuf
    //glframebuf
    //gltex
    //stb_image
    
    return 0;
}
