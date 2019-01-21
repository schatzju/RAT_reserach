//
//  Filters.hpp
//  smem
//
//  Created by Jule Schatz on 1/7/19.
//  Copyright © 2019 Jule Schatz. All rights reserved.
//

#ifndef Filters_hpp
#define Filters_hpp

#include <stdio.h>

#endif /* Filters_hpp */

class AlwaysTrue{
public:
    bool operator()(int weight_in);
};

//Returns true if the weight is greater than or equal to threshold
class Thresh{
private:
    int threshold;
public:
    
    Thresh(int threshIn);
    
    bool operator()(int weight_in);
};
