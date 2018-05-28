//
//  BoxVO.hpp
//  ShaderFunGLFW
//
//  Created by Jack Armstrong on 5/20/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef BoxVO_hpp
#define BoxVO_hpp

#include "VO.hpp"

class BoxVO:public VO{
public:
    BoxVO();
    ~BoxVO();
    void genBuffersBox(float x,float y,float w,float h);
};

#endif /* BoxVO_hpp */
