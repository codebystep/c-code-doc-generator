/**
 * Module documentation_processing.h
 * this module contains function prototypes for processing documentation comments.
 */

#ifndef DOCUMENTATION_PROCESSING_H
#define DOCUMENTATION_PROCESSING_H

#include "data_structures.h"
#include <stdbool.h>

/* ____________________________________________________________________________

    Function Prototypes
   ____________________________________________________________________________
*/

/**
 * Processes a single line of documentation comment.
 * @param line The line to process.
 * @param comment The documentation comment structure to update.
 */
void processComment(const char *line, DocComment *comment);

/**
 * Adds a function's documentation to the collection.
 * @param funcDoc Documentation details of the function.
 * @return true if addition is successful, false otherwise.
 */
bool addFunctionDoc(FunctionDoc *funcDoc);

#endif 
