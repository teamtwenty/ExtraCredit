//
//  Keith.hpp
//  ExtraCreditLab
//
//  Created by Maxx Rodriguez on 5/9/14.
//  Copyright (c) 2014 Maxx Rodriguez. All rights reserved.
//

#ifndef ExtraCreditLab_Keith_hpp
#define ExtraCreditLab_Keith_hpp

#include <iostream>
#include "Types.hpp"
#include <math.h>


extern void FindKeiths
(
 ulong pLimit
 );

extern void *FindKeithsThread
(
 void *pState
 );


int len(ulong num)
{
    int count=0;
    while(num>0)
    {
        num=num/10;
        count++;
    }
    return count;
}

#endif
