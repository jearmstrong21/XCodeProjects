//
//  glarr.c
//  c-gl-lib
//
//  Created by Jack Armstrong on 9/1/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "glarr.h"

glarr glarr_create(void){
    glarr gla;
    glGenVertexArrays(1,&gla);
    return gla;
}

void glarr_bind(glarr gla){
    glBindVertexArray(gla);
}
void glarr_unbind(void){
    glBindVertexArray(0);
}

void glarr_delete(glarr gla){
    glDeleteVertexArrays(1, &gla);
}
