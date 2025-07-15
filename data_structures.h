/**
 * Module data_structures.h
 * This module contains function prototypes and defines data structures used for documentation processing.
 */

#ifndef DATA_STRUCTURES_H
#define DATA_STRUCTURES_H

#include "constants.h"

/* ____________________________________________________________________________

    Structures and Datatypes
   ____________________________________________________________________________
*/

/**
 * @struct DocComment
 * @brief Represents a documentation comment associated with a function.
 */
typedef struct {
    char brief[1024];                  /* Brief description of the function. */
    char details[4096];                /* Detailed description of the function. */
    char freeText[MAX_TEXT_LENGTH];    /* Additional text or notes. */
    char lastLineHadText;              /* Indicates if the last line had text (for formatting purposes). */
    char paramName[MAX_PARAMS][256];   /* Array of parameter names. */
    char paramDesc[MAX_PARAMS][1024];  /* Array of parameter descriptions. */
    int paramCount;                    /* Count of parameters. */
    char returnVal[256];               /* Return value description. */
    char author[256];                  /* Author of the function. */
    char version[256];                 /* Version information. */
} DocComment;

/**
 * @struct FunctionDoc
 * @brief Represents documentation for a function.
 */
typedef struct {
    char returnType[256];             /* Return type of the function. */
    char functionName[256];           /* Name of the function. */
    char moduleName[256];             /* Module in which the function resides. */
    char prototype[1024];             /* Prototype of the function. */
    char fileTypes[2];                /* Types of files (header/source). */
    DocComment comment;               /* Associated documentation comment. */
} FunctionDoc;

/* ____________________________________________________________________________

    Function Prototypes
   ____________________________________________________________________________
*/

/**
 * Initializes a DocComment structure.
 * @param comment Pointer to a DocComment structure.
 */
void initDocComment(DocComment *comment);

/**
 * Merges two DocComment structures.
 * @param dest Destination DocComment structure.
 * @param src Source DocComment structure.
 */
void mergeDocComments(DocComment *dest, const DocComment *src);

#endif 
