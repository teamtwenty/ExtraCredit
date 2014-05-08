//**************************************************************************************************************
// FILE: Main.cpp
//**************************************************************************************************************
#include <cstdlib>
#include <iostream>
#include <string>
#include "Amicable.hpp"
#include "Keith.hpp"
#include "Prime.hpp"
#include "Thread.hpp"

using std::cout;
using std::endl;
using std::string;

//==============================================================================================================
// Type Definitions
//==============================================================================================================
typedef enum { parallel, serial } RunMode;

//==============================================================================================================
// Static Global Variable Definitions
//==============================================================================================================
static struct MainGlobals {
    ulong   mAmicableLimit;
    ulong   mKeithLimit;
    ulong   mPrimeLimit;
    RunMode mRunMode;
    bool    mVerbose;
} gGlobals;

//==============================================================================================================
// Static Function Declarations
//==============================================================================================================
static void Help
    (
    );

static void Parallel
    (
    );

static void ParseCmdLine
    (
    int   pArgc,
    char *pArgv[]
    );

static void Serial
    (
    );

//==============================================================================================================
// Public Function Declarations
//==============================================================================================================

//--------------------------------------------------------------------------------------------------------------
// Error()
//
// Called when an error occurs. Displays the error message pMsg and then terminates the program by calling
// exit(). Note that if exit() is called, any running threads will be terminated.
//--------------------------------------------------------------------------------------------------------------
void Error
    (
    std::string const pMsg
    )
{
    if (pMsg != "") cout << pMsg << endl;
    exit(-1);
}

//--------------------------------------------------------------------------------------------------------------
// main()
//
// Parses the command line to get the arguments and options. Then runs the tests in either serial or parallel
// mode. Calls pthread_exit() to wait on all threads to terminate before main() terminates.
//--------------------------------------------------------------------------------------------------------------
int main
    (
    int   pArgc,
    char *pArgv[]
    )
{
    ParseCmdLine(pArgc, pArgv);
    gGlobals.mRunMode == serial ? Serial() : Parallel();
    pthread_exit(NULL);
}

//--------------------------------------------------------------------------------------------------------------
// GetVerbose()
//
// Returns the mVerbose flag from the gGlobals structure.
//--------------------------------------------------------------------------------------------------------------
bool GetVerbose
    (
    )
{
    return gGlobals.mVerbose;
}

//--------------------------------------------------------------------------------------------------------------
// Help()
//
// Displays information about the command line arguments and options.
//--------------------------------------------------------------------------------------------------------------
static void Help
    (
    )
{
    cout << "usage: thread mode prime-limit amicable-limit keith-limit [--verbose]" << endl << endl;
    cout << "mode is:" << endl << endl;
    cout << "    --serial    Run the program in serial mode." << endl;
    cout << "    --parallel  Run the program in parallel mode." << endl;
    cout << endl;
    cout << "prime-limit is the largest number to test for the prime test." << endl;
    cout << "amicable-limit is the largest number to test for the amicable test." << endl;
    cout << "keith-limit is the largest number to test for the keith test." << endl;
}

//--------------------------------------------------------------------------------------------------------------
// Parallel()
//
// Starts the three threads to find the primes from 2 up to gGlobals.mPrimeLimit, all the amicable numbers
// from 2 up to gGlobals.mAmicableLimit, and all the Keith numbers from 10 up to gGlobals.mKeithLimit. If any
// thread fails to start, the we terminate by calling Error().
//--------------------------------------------------------------------------------------------------------------
static void Parallel
    (
    )
{
    ThreadState *primesState = StartThread(FindPrimesThread, gGlobals.mPrimeLimit);
    if (primesState->mStarted != 0) Error("Failed to start FindPrimes thread");

    ThreadState *amicableState = StartThread(FindAmicableThread, gGlobals.mAmicableLimit);
    if (amicableState->mStarted != 0) Error("Failed to start FindAmicable thread");

    // Start the thread to find the Keith numbers.
    ???
}

//--------------------------------------------------------------------------------------------------------------
// ParseCmdLine()
//
// See Help() for what is expected on the command line.
//--------------------------------------------------------------------------------------------------------------
static void ParseCmdLine
    (
    int         pArgc,
    char       *pArgv[]
    )
{
    gGlobals.mVerbose = false;
    if (pArgc < 6) { Help(); Error(""); }
    string mode(pArgv[1]);
    if (mode == "--serial") gGlobals.mRunMode = serial;
    else if (mode == "--parallel") gGlobals.mRunMode = parallel;
    else { Help(); Error(""); }
    gGlobals.mPrimeLimit = atol(pArgv[2]);
    gGlobals.mAmicableLimit = atol(pArgv[3]);   
    gGlobals.mKeithLimit = atol(pArgv[4]);  
    if (pArgc == 6) {
        string verbose(pArgv[5]);
        if (verbose == "--verbose") gGlobals.mVerbose = true;
        else { Help(); Error(""); }
    }
}

//--------------------------------------------------------------------------------------------------------------
// Serial()
//
// See Parallel(). Finds all the primes first, then all the amicable numbers, then all the Keith numbers.
//
// PSEUDOCODE:
// Call FindPrimes()
// Call FindAmicable()
// Call FindKeiths()
//--------------------------------------------------------------------------------------------------------------
???
