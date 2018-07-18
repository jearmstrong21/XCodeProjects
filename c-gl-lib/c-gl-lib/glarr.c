//
//  glarr.c
//  c-gl-lib
//
//  Created by Jack Armstrong on 7/15/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "glarr.h"

glarr glarr_gen(void){
    glarr arr;
    glGenVertexArrays(1, &arr);
    return arr;
}

void glarr_bind(glarr arr){
    glBindVertexArray(arr);
}

void glarr_unbind(void){
    glBindVertexArray(0);
}

void glarr_delete(glarr arr){
    glDeleteVertexArrays(1, &arr);
}
