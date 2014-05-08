//**************************************************************************************************************
// FILE: Thread.hpp
//**************************************************************************************************************
#ifndef THREAD_HPP
#define THREAD_HPP

#include <pthread.h>
#include "Types.hpp"

//==============================================================================================================
// Typedefs
//==============================================================================================================
typedef struct {
    ulong       mLimit;     // Upper limit of numbers to test 
    int         mStarted;   // True if the thread started successfully
    int         mExitCode;  // Thread exit code
    pthread_t   mThreadId;  // Thread ID
} ThreadState;

// Defines a type named ThreadFunction which is a pointer to a function with void * as the parameter and
// void * as the return value.
typedef void *(*ThreadFunction)(void *);

//==============================================================================================================
// Public Function Declarations
//==============================================================================================================
ThreadState *StartThread
    (
    ThreadFunction const pFunction,  // Pointer to the thread function
    ulong const          pLimit      // Upper limit of numbers to test
    );

#endif
