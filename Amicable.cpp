//**************************************************************************************************************
// FILE: Amicable.cpp
//**************************************************************************************************************
#include <iostream>
#include "Amicable.hpp"
#include "Main.hpp"
#include "Thread.hpp"
#include "Types.hpp"

using std::cout;
using std::endl;

//==============================================================================================================
// Static Function Declarations
//==============================================================================================================
static bool AreAmicable
    (
    ulong const pNum1,
    ulong const pNum2
    );

static ulong SumProperDivisors
    (
    ulong const pNum
    );

//==============================================================================================================
// Function Definitions
//==============================================================================================================

//--------------------------------------------------------------------------------------------------------------
// AreAmicable()
//
// Returns true if pNum1 and pNum2 are amicable numbers.
//--------------------------------------------------------------------------------------------------------------
static bool AreAmicable
    (
    ulong const pNum1,
    ulong const pNum2
    )
{
    return SumProperDivisors(pNum1) == pNum2 && SumProperDivisors(pNum2) == pNum1;
}

//--------------------------------------------------------------------------------------------------------------
// FindAmicable()
//
// Finds all amicable numbers from 2 to pLimit. We do nothing with the numbers that we find.
//--------------------------------------------------------------------------------------------------------------
void FindAmicable
    (
    ulong pLimit
    )
{
    if (GetVerbose()) cout << "FindAmicable() Begin" << endl;
    for (ulong num1 = 2L; num1 <= pLimit; num1++) {
        for (ulong num2 = num1 + 1; num2 <= pLimit; num2++) {
            if (AreAmicable(num1, num2))
                ;
        }
    }
    if (GetVerbose()) cout << "FindAmicable() End" << endl;
}

//--------------------------------------------------------------------------------------------------------------
// FindAmicableThread()
//
// The starting function for the "find amicable numbers" thread.
//
// NOTE: See comments in FindPrimesThread().
//--------------------------------------------------------------------------------------------------------------
void *FindAmicableThread
    (
    void *pState
    )
{
    if (GetVerbose()) cout << "FindAmicableThread() Begin" << endl;
    ThreadState *state = static_cast<ThreadState *>(pState);
    FindAmicable(state->mLimit);
    state->mExitCode = 0;
    if (GetVerbose()) cout << "FindAmicableThread() End" << endl;
    pthread_exit(pState);
}

//--------------------------------------------------------------------------------------------------------------
// SumProperDivisors()
//
// Returns the sum of the proper divisors of pNum.
//--------------------------------------------------------------------------------------------------------------
static ulong SumProperDivisors
    (
    ulong const pNum
    )
{
    ulong sum = 1L;
    for (ulong div = 2L; div < pNum; div++) {
        if (pNum % div == 0L) sum += div;
    }
    return sum;
}
