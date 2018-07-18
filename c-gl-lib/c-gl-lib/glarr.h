//
//  glarr.h
//  c-gl-lib
//
//  Created by Jack Armstrong on 7/15/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef glarr_h
#define glarr_h

#include <stdio.h>
#include <stdbool.h>
#include "util.h"
#include "glutil.h"
#include <OpenGL/gl3.h>

typedef GLuint glarr;

glarr glarr_gen(void);
void glarr_bind(glarr arr);
void glarr_unbind(void);
void glarr_delete(glarr arr);


#endif /* glarr_h */
