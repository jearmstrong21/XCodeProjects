//
//  main.cpp
//  HelloChlorine
//
//  Created by Jack Armstrong on 7/24/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#include <stdlib.h>
#include "chlorine.hpp"
#include <vector>

typedef std::vector<float> flist;
typedef std::vector<int> ilist;

const float NANO_IN_SECOND=1000000000.0f;

int main(int argc, const char * argv[]) {
    ilist list;
    for(int i=0;i<5;i++){
        list.push_back(i);
    }
    ch::Worker worker("square.cl");
    printf("Started\n");
    worker.call("square", list);
    worker.call("square", list);
    worker.call("square", list);
    for(int i=0;i<5;i++){
        printf("%i\n",list[i]);
    }
    return 0;
}
