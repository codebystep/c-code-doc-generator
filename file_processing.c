/**
 * Module file_processing.c
 * This module handles the parsing and processing of C source and header files to generate documentation. 
 * It includes functions for reading files, processing included headers, and keeping track of already processed files.
 */

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "file_processing.h"
#include "global.h"
#include "constants.h"
#include "documentation_processing.h"

/**
 * Checks if a file has already been processed to avoid duplicate processing.
 * @param filename Name of the file to check.
 * @return true if the file has been processed, false otherwise.
 */
bool fileAlreadyProcessed(const char *filename) {
        /* Loop through all processed files */
        for (int i = 0; i < processedCount; i++) {
        if (strcmp(processedFiles[i], filename) == 0) {
            return true;
        }
    }
    return false;
}

/**
 * Adds a filename to the list of processed files.
 * This function is called after a file is successfully processed to mark it as done.
 * @param filename Name of the file to add to the processed list.
 */
void addFileToProcessed(const char *filename) {
        /* Check if the maximum file count has not been reached */
        if (processedCount < MAX_FILES) {
        strcpy(processedFiles[processedCount], filename);
        processedCount++;
        } 
        else {
        fprintf(stderr, "Error: Limit of processed files exceeded\n");
        }
}

/**
 * Main function to process a single C source or header file.
 * This function reads the file, extracts documentation comments, and processes them.
 * It also handles included files recursively.
 * @param filename Name of the file to process.
 * @param outputFile File pointer to the output file for documentation.
 */
void processFile(const char *filename, FILE *outputFile) {
    /* Check if the file has already been processed */
    if (fileAlreadyProcessed(filename)) {
        return;
    }
    /* Open the file for reading */
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error: Unable to open file %s\n", filename);
        return;
    }

    /* Add the file to the processed list */
    addFileToProcessed(filename);

    /* Define and initialize variables for processing */
    DocComment comment;
    char line[1024];
    bool inComment = false;
    bool commentReady = false;
    char prototypeBuffer[1024] = {0}; /* Buffer to store the function prototype */
    char *functionStart;
    char *functionEnd;
    char fileType = (strstr(filename, ".h") != NULL) ? 'H' : 'C'; 

    /* Process the file line by line */
    while (fgets(line, sizeof(line), file)) {
        /* Process includes, comments and function prototypes */
        if (strstr(line, "#include")) {
            char includedFileName[256];
            if (sscanf(line, "#include \"%255[^\"]\"", includedFileName) == 1) {
                processFile(includedFileName, outputFile); 
            }
        } 
        else if (strstr(line, "/**") || strstr(line, "/*!")) {
            /* Start of a comment block */
            inComment = true;
            initDocComment(&comment);
            memset(prototypeBuffer, 0, sizeof(prototypeBuffer));
        } 
        else if (inComment && strstr(line, "*/")) {
            /* End of a comment block */
            inComment = false;
            commentReady = true;
        } 
        else if (inComment) {
            /* Inside a comment block, process the current line */
            processComment(line, &comment);
        } 
        else if (commentReady) {

            /* After a complete comment block, look for the function prototype */
            if (strchr(line, '{') || strstr(line, ";")) {
                strncat(prototypeBuffer, line, sizeof(prototypeBuffer) - strlen(prototypeBuffer) - 1);
                if (strchr(prototypeBuffer, '{') || strstr(prototypeBuffer, ";")) {
                    /* Process the function prototype */
                    char *start = prototypeBuffer;
                    while (*start && isspace((unsigned char)*start)) {
                        start++;
                    }

                    functionStart = strchr(start, ' ');
                    functionEnd = strchr(start, ')');

                    if (functionStart && functionEnd && (functionEnd > functionStart)) {                        
                        /* Extract return type and function name */
                        char returnType[256];
                        strncpy(returnType, start, functionStart - start);
                        returnType[functionStart - start] = '\0';

                        while (isspace((unsigned char)*functionStart)) {
                            functionStart++;
                        }

                        char functionName[1024];
                        strncpy(functionName, functionStart, functionEnd - functionStart + 1);
                        functionName[functionEnd - functionStart + 1] = '\0';

                        /* Create a FunctionDoc object and add it to the global array */
                        FunctionDoc funcDoc;
                        strncpy(funcDoc.returnType, returnType, sizeof(funcDoc.returnType));
                        strncpy(funcDoc.functionName, functionName, sizeof(funcDoc.functionName));
                        strncpy(funcDoc.moduleName, filename, sizeof(funcDoc.moduleName));
                        funcDoc.fileTypes[0] = fileType;
                        funcDoc.fileTypes[1] = '\0';
                        funcDoc.comment = comment;

                        /* Reset flags and initialize a new DocComment for the next function */
                        addFunctionDoc(&funcDoc);
                        commentReady = false;
                        initDocComment(&comment);
                    }
                }
            }
            else {
                /* Accumulate lines until the complete prototype is read */
                strncat(prototypeBuffer, line, sizeof(prototypeBuffer) - strlen(prototypeBuffer) - 1);
                }
        }
    }

    /* If the file is a header file, attempt to find the corresponding source file */
    if (fileType == 'H') {
        char cFilename[256];
        strcpy(cFilename, filename);
        char *dot = strrchr(cFilename, '.');
        if (dot) {
            strcpy(dot, ".c");  /* Replace .h with .c */
            FILE *testFile = fopen(cFilename, "r");
            if (testFile != NULL) {
                fclose(testFile);
                processFile(cFilename, outputFile);
            }
        }
    }

    fclose(file);
}
