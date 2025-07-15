/**
 * Module documentation_processing.c
 * This module implements functions for processing and managing documentation comments.
 */

#include "documentation_processing.h"
#include <stdbool.h>
#include "global.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "utility.h"

/**
 * Processes a single line of a documentation comment.
 * This function parses special tags (like @brief, @details, etc.) from a given line and stores
 * the information in the provided DocComment structure. It also handles the formatting
 * and validation of the line.
 * @param line The line of text to be processed.
 * @param comment Pointer to the DocComment structure where the processed information is stored.
 */
void processComment(const char *line, DocComment *comment) {
    /* Check for null pointers to prevent crashes */ 
    if (line == NULL || comment == NULL) {
        fprintf(stderr, "Error: Null pointer in processComment function\n");
        return;
    }

    /* Skip leading spaces and asterisks (common in comment blocks) */
    const char *start = line;
    while (*start && (isspace((unsigned char)*start) || *start == '*')) {
        start++;
    }

    /* Initialize trimmedLine to an empty string */
    char trimmedLine[1024] = {0}; 
    trimLine(start, trimmedLine);

    /* Process different documentation tags like @brief, @details, etc.
       The function checks if the line starts with a specific tag and then processes it accordingly. */
    if (strncmp(trimmedLine, "@brief", 6) == 0) {
        if (strlen(trimmedLine) > 7) {
            strncpy(comment->brief, trimmedLine + 7, sizeof(comment->brief) - 1);
            comment->brief[sizeof(comment->brief) - 1] = '\0'; /* Ensure null-termination */
        }
    } 
    else if (strncmp(trimmedLine, "@details", 8) == 0) {
            if (strlen(trimmedLine) > 9) {
            strncpy(comment->details, trimmedLine + 9, sizeof(comment->details) - 1);
            comment->details[sizeof(comment->details) - 1] = '\0'; 
            }
    } 
    else if (strncmp(trimmedLine, "@param", 6) == 0) {
            if (comment->paramCount < MAX_PARAMS) { /* Check that the limit is not exceeded */
            char *restOfLine = trimmedLine + 7;
            char *spaceAfterType = strchr(restOfLine, ' ');
                if (spaceAfterType) {
                    *spaceAfterType = '\0';
                    char *nameStart = spaceAfterType + 1;

                    /* Check for special chars */
                    char *specialChar = strpbrk(nameStart, "*[]");
                    while (specialChar) {
                        nameStart = specialChar + 1;
                        specialChar = strpbrk(nameStart, "*[]");
                    }

                    char *descStart = strchr(nameStart, ' ');
                    if (descStart) {
                        *descStart = '\0';
                        descStart += 1;

                        snprintf(comment->paramName[comment->paramCount], sizeof(comment->paramName[comment->paramCount]), "%s %s", restOfLine, spaceAfterType + 1);
                        snprintf(comment->paramDesc[comment->paramCount], sizeof(comment->paramDesc[comment->paramCount]), "%s", descStart);
                        comment->paramCount++;
                    }
                }
            }
    } 
    else if (strncmp(trimmedLine, "@return", 7) == 0) {
        if (strlen(trimmedLine) > 8) {
            strncpy(comment->returnVal, trimmedLine + 8, sizeof(comment->returnVal) - 1);
            comment->returnVal[sizeof(comment->returnVal) - 1] = '\0'; /* Ensure null-termination */
        } 
        else {
            invalidCommentFormat = 1;
            comment->returnVal[0] = '\0';
        }
    } 
    else if (strncmp(trimmedLine, "@author", 7) == 0) {
            if (strlen(trimmedLine) > 8) {
            strncpy(comment->author, trimmedLine + 8, sizeof(comment->author) - 1);
            comment->author[sizeof(comment->author) - 1] = '\0'; 
            }
    } 
    else if (strncmp(trimmedLine, "@version", 8) == 0) {
            if (strlen(trimmedLine) > 9) {
            strncpy(comment->version, trimmedLine + 9, sizeof(comment->version) - 1);
            comment->version[sizeof(comment->version) - 1] = '\0'; 
            }
    } else {
            /* The else clause handles lines that do not start with any recognized tag
               It treats them as free text and appends them to the 'freeText' field of the DocComment structure */
            if (strlen(trimmedLine) > 0) {
                size_t freeTextLength = strlen(comment->freeText);
                if (freeTextLength + strlen(trimmedLine) + 1 < MAX_TEXT_LENGTH) {
                    if (comment->lastLineHadText) {
                        strncat(comment->freeText, "\n", MAX_TEXT_LENGTH - freeTextLength - 1);
                        freeTextLength++;
                    }
                    strncat(comment->freeText, trimmedLine, MAX_TEXT_LENGTH - freeTextLength - 1);
                }
                comment->lastLineHadText = 1;
            } 

        else {
            comment->lastLineHadText = 0;
        }
    }
}

/**
 * Adds a function's documentation to the global collection.
 * Compares and updates documentation if already exists.
 * @param funcDoc The documentation details to add.
 * @return true if successfully added or updated, false otherwise.
 */
bool addFunctionDoc(FunctionDoc *funcDoc) {
    for (int i = 0; i < functionCount; i++) {
        /* Compare return type and function name */
        if (strcmp(functionDocs[i].returnType, funcDoc->returnType) == 0 &&
            strcmp(functionDocs[i].functionName, funcDoc->functionName) == 0) {
            /* Update file types if new */
            if (strchr(functionDocs[i].fileTypes, funcDoc->fileTypes[0]) == NULL) {
                int len = strlen(functionDocs[i].fileTypes);
                functionDocs[i].fileTypes[len] = funcDoc->fileTypes[0];
                functionDocs[i].fileTypes[len + 1] = '\0';
            }

            /* Merge comments */
            mergeDocComments(&functionDocs[i].comment, &funcDoc->comment);
            return true;
        }
    }

    /* Add new function documentation */
    if (functionCount < MAX_FUNCTIONS) {
        functionDocs[functionCount] = *funcDoc;
        functionCount++;
        return true;
    }

    return false;
}