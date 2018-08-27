//
//  rm_modular.hpp
//  Raytracer
//
//  Created by Jack Armstrong on 8/27/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef rm_modular_hpp
#define rm_modular_hpp

#include <stdio.h>

#include "rm.hpp"

namespace rm {
    
    class modular {
        
    public:
        virtual float distance(vec3 pos) const = 0;
        
    };
    
//    namespace modular {
    
    class min : public modular {
        
    public:
        modular*a;
        modular*b;
        min(modular*_1,modular*_2);
        
        float distance(vec3 pos)const;
        
    };
    
    
    class sphere : public modular {
        
    public:
        vec3 pos;
        float size;
        
        sphere(vec3 p,float s);
        
        float distance(vec3 pos)const;
    };
    
    class plane : public modular {
        
    public:
        vec3 pos;
        vec3 normal;
        
        plane(vec3 p,vec3 n);
        
        float distance(vec3 pos)const;
        
    };
        
//    };
    
}

#endif /* rm_modular_hpp */
