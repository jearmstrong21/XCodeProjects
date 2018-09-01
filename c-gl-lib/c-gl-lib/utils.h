//
//  utils.h
//  c-gl-lib
//
//  Created by Jack Armstrong on 8/31/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef utils_h
#define utils_h

#include <stdio.h>
#include <stdlib.h>

typedef char* char_str;
typedef const char* const_char_str;

char_str utils_readfile(const_char_str filename);

#endif /* utils_h */
