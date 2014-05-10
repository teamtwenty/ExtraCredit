//
//  Keith.cpp
//  ExtraCreditLab
//
//  Created by Maxx Rodriguez on 5/9/14.
//  Copyright (c) 2014 Maxx Rodriguez. All rights reserved.
//

#include "Keith.hpp"
#include <iostream>
#include <stdio.h>
#include "Main.hpp"
#include "Thread.hpp"
#include "Types.hpp"

using std::cout;
using std::endl;

static bool IsKeith(ulong pNum);

void FindKeiths(ulong pLimit)
{
    if (GetVerbose()) cout << "FindKeith() Begin" << endl;
    ulong num = pLimit;
    int arr[10], i =0, sum = 0, flag = 0;
    for(i=len(pLimit)-1;i>=0;i--)
    {
        {
            arr[i]=pLimit%10;
            pLimit/=10;
        }
    }
    while(flag==0)
    {
        for(i=0;i<len(num);i++)
            sum+=arr[i];
        if(sum==num)
        {
            flag=1;
        }
        if(sum>num)
        {
            flag=1;
        }
        for(i=0;i<len(num);i++)
        {
            if(i!=len(num)-1)
                arr[i]=arr[i+1];
            else
                arr[i]=sum;
        }
        sum=0;
        IsKeith((ulong)flag);
    }
    if (GetVerbose()) cout << "FindKeith() End" << endl;


}

void *FindKeithsThread
(
 void *pState
 )
{
    // If running in verbose mode, then tell the user that the thread is beginning.
    if (GetVerbose()) cout << "FindKeithsThread() Begin" << endl;
    
    // We know that pState is really a pointer to a ThreadState structure, so type cast it.
    ThreadState *state = static_cast<ThreadState *>(pState);
    
    // Find all the primes from 2 to state->mLimit.
    FindKeiths(state->mLimit);
    
    // The thread exit code is 0 (success).
    state->mExitCode = 0;
    
    // If running verbose mode, then tell the user that the thread is ending.
    if (GetVerbose()) cout << "FindKiethsThread() End" << endl;
    
    // Exit (terminate) the thread and return pState as the return variable.
    pthread_exit(pState);
}


static bool IsKeith(ulong pNum)
{
    if(pNum==1)
        return true;
    else
        return false;
    return true;
}



