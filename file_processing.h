/**
 * Module file_processing.h
 * This module contains function prototypes for processing files during documentation generation.
 */

#ifndef FILE_PROCESSING_H
#define FILE_PROCESSING_H

#include "data_structures.h"
#include <stdio.h>
#include <stdbool.h>

/* ____________________________________________________________________________

    Function Prototypes
   ____________________________________________________________________________
*/

/**
 * Processes the specified source file and outputs formatted documentation to the provided output file.
 * @param filename The name of the file to process.
 * @param outputFile The file where the formatted documentation will be written.
 */
void processFile(const char *filename, FILE *outputFile);

/**
 * Checks if the specified file has already been processed.
 * @param filename The name of the file to check.
 * @return true if the file has already been processed, false otherwise.
 */
bool fileAlreadyProcessed(const char *filename);

/**
 * Records a file as processed to prevent duplicate processing.
 * @param filename The name of the file to mark as processed.
 */
void addFileToProcessed(const char *filename);

#endif 