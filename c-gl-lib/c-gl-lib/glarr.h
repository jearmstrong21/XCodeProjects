//
//  glarr.h
//  c-gl-lib
//
//  Created by Jack Armstrong on 9/1/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef glarr_h
#define glarr_h

#include <stdio.h>
#include <OpenGL/gl3.h>

typedef int glarr;

glarr glarr_create(void);

void glarr_bind(glarr gla);
void glarr_unbind(void);

void glarr_delete(glarr gla);

#endif /* glarr_h */
