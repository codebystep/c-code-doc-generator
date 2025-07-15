/**
 * Module main.c
 * This module contains the main function of the program.
 */

#include <stdio.h>
#include <stdbool.h>
#include "global.h"
#include <string.h>
#include "file_processing.h"
#include "latex_formatting.h"


//Global variables

char processedFiles[MAX_FILES][256];
int processedCount = 0;
FunctionDoc functionDocs[MAX_FUNCTIONS];
int functionCount = 0;
int invalidCommentFormat = 0;

/**
 * Main function of the program.
 * It processes an input C source file and generates LaTeX formatted documentation.
 * 
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return An integer indicating the status of program execution.
 */
int main(int argc, char *argv[]) {
    char outputFileName[256];  

    /* Check if the correct number of arguments is provided */
    if (argc < 2) {
        fprintf(stderr, "Error: No input file provided\nEnter an input file (obligatory) and an output file (optional)\nFor instance: test.c |or| test.c output.tex\n");
        return 1;  
    }

    /* Check if the correct number of arguments is provided */
    if (argc > 3){
        fprintf(stderr, "Error: Incorrect number of arguments\n");
        return 1;
    }

    /* Check if the input file can be opened */
    FILE *inputFile = fopen(argv[1], "r");
    if (inputFile == NULL) {
        fprintf(stderr, "Error: File %s does not exist or cannot be opened\n", argv[1]);
        return 2;  
    }
    fclose(inputFile);  
  
    /* Determine the output file name based on the arguments */
    if (argc == 3) {
        strcpy(outputFileName, argv[2]);  
    } else {
        snprintf(outputFileName, sizeof(outputFileName), "%s-doc.tex", argv[1]);  
    }

    /* Open the output file for writing */
    FILE *outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        fprintf(stderr, "Error: Unable to open output file %s\n", outputFileName);
        return 2;  
    }

    /* Start the LaTeX document */
    startLaTeXDocument(outputFile);

    /* Process the input file and write documentation to the output file */
    processFile(argv[1], outputFile);

    bool isNewModule = true;  
    char lastModuleName[256] = "";  

    /* Loop through all documented functions and format them for LaTeX */
    for (int i = 0; i < functionCount; i++) {
        formatToLaTeX(&functionDocs[i], outputFile, &isNewModule, lastModuleName);
    }

    /* Finalize the LaTeX document */
    endLaTeXDocument(outputFile);

    /* Check if there was an invalid comment format detected */
    if (invalidCommentFormat) {
        fprintf(stderr, "Error: Invalid comment format detected\n");
        fclose(outputFile);
        return 3;  
    }

    fclose(outputFile);  
    return 0;  
}