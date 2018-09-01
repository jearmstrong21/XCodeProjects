//
//  utils.c
//  c-gl-lib
//
//  Created by Jack Armstrong on 8/31/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include "utils.h"

//https://stackoverflow.com/questions/3381080/reading-all-content-from-a-text-file-c
char_str utils_readfile(const_char_str filename){
    char_str fcontent = NULL;
    int fsize = 0;
    FILE *fp;
    
    fp = fopen(filename, "r");
    if(fp) {
        fseek(fp, 0, SEEK_END);
        fsize = ftell(fp);
        rewind(fp);
        
        fcontent = (char_str) malloc(sizeof(char) * fsize);
        fread(fcontent, 1, fsize, fp);
        
        fclose(fp);
    }
    return fcontent;
}
