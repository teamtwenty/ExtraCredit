//**************************************************************************************************************
// FILE: Prime.cpp
//**************************************************************************************************************
#include <iostream>
#include <cmath>
#include "Main.hpp"
#include "Prime.hpp"
#include "Thread.hpp"

using std::cout;
using std::endl;

//==============================================================================================================
// Static Function Declarations
//==============================================================================================================
static bool IsPrime
    (
    ulong const pNum
    );

//==============================================================================================================
// Function Definitions
//==============================================================================================================

//--------------------------------------------------------------------------------------------------------------
// FindPrimes()
//
// Finds all prime numbers from 2 to pLimit. We do nothing with the numbers we find.
//--------------------------------------------------------------------------------------------------------------
void FindPrimes
    (
    ulong pLimit
    )
{
    if (GetVerbose()) cout << "FindPrimes() Begin" << endl;
    for (ulong n = 2L; n <= pLimit; n += 2L) {
        if (IsPrime(n))
            ;
    }
    if (GetVerbose()) cout << "FindPrimes() End" << endl;
}

//--------------------------------------------------------------------------------------------------------------
// FindPrimesThread()
//
// A thread which finds all prime numbers from 2 to pState->mLimit.
//--------------------------------------------------------------------------------------------------------------
void *FindPrimesThread
    (
    void *pState
    )
{
    // If running in verbose mode, then tell the user that the thread is beginning.
    if (GetVerbose()) cout << "FindPrimesThread() Begin" << endl;

    // We know that pState is really a pointer to a ThreadState structure, so type cast it.
    ThreadState *state = static_cast<ThreadState *>(pState);

    // Find all the primes from 2 to state->mLimit.
    FindPrimes(state->mLimit);

    // The thread exit code is 0 (success).
    state->mExitCode = 0;

    // If running verbose mode, then tell the user that the thread is ending.
    if (GetVerbose()) cout << "FindPrimesThread() End" << endl;

    // Exit (terminate) the thread and return pState as the return variable.
    pthread_exit(pState);
}

//--------------------------------------------------------------------------------------------------------------
// IsPrime()
//
// Returns true if pNum is prime. Note: I know this is an extremely inefficient way to test for primality, but
// that's not the point of this project.
//--------------------------------------------------------------------------------------------------------------
static bool IsPrime
    (
    ulong const pNum
    )
{
    if (pNum < 2L) return false;
    if (pNum == 2L) return true;
    for (ulong div = 3L; div <= sqrt(pNum); div += 2L) {
        if (pNum % div == 0L) return false;
    }
    return true;
}
