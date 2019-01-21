//
//  Filters.cpp
//  smem
//
//  Created by Jule Schatz on 1/7/19.
//  Copyright © 2019 Jule Schatz. All rights reserved.
//

#include "filters.h"

bool AlwaysTrue::operator()(int weight_in){
    return true;
}

Thresh::Thresh(int threshIn){
    threshold = threshIn;
}
    
bool Thresh::operator()(int weight_in){
    if(weight_in >= threshold){
        return true;
    }
    return false;
}
