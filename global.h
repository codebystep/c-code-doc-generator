/**
 * Module global.h
 * @brief Global declarations and extern variables used throughout the program.
 */

#ifndef GLOBAL_H
#define GLOBAL_H

#include "constants.h"
#include "data_structures.h"

/* ____________________________________________________________________________

    Global variables
   ____________________________________________________________________________
*/

// Array of processed file names.
extern char processedFiles[MAX_FILES][256];

// Count of processed files.
extern int processedCount;

// Array of function documentation structures.
extern FunctionDoc functionDocs[MAX_FUNCTIONS];

// Count of documented functions.
extern int functionCount;

// Flag for invalid comment format detection.
extern int invalidCommentFormat;

#endif 
