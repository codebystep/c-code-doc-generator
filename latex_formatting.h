/**
 * Module latex_formatting.h
 * This module contains Function prototypes for formatting documentation in LaTeX.
 */

#ifndef LATEX_FORMATTING_H
#define LATEX_FORMATTING_H

#include "data_structures.h"
#include <stdio.h>
#include <stdbool.h>

/* ____________________________________________________________________________

    Function Prototypes
   ____________________________________________________________________________
*/

/**
 * Formats a module name for LaTeX document.
 * @param moduleName The name of the module to format.
 */
void formatModuleName(char *moduleName);

/**
 * Escapes LaTeX special characters in a string.
 * @param str The string to be processed for LaTeX formatting.
 */
void escapeLaTeXChars(char *str);

/**
 * Starts a LaTeX document, writing the necessary headers.
 * @param outputFile The file where the LaTeX document is written.
 */
void startLaTeXDocument(FILE *outputFile);

/**
 * Formats the documentation of a function for LaTeX.
 * @param funcDoc Documentation of the function.
 * @param outputFile The file where the formatted documentation will be written.
 * @param isNewModule Pointer to a flag indicating if a new module is started.
 * @param lastModuleName The name of the last processed module.
 */
void formatToLaTeX(const FunctionDoc *funcDoc, FILE *outputFile, bool *isNewModule, char *lastModuleName);

/**
 * Ends a LaTeX document, writing the necessary footers.
 * @param outputFile The file where the LaTeX document is written.
 */
void endLaTeXDocument(FILE *outputFile);

#endif 
