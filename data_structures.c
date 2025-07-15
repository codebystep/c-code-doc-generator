/**
 * Module data_structures.c
 * In this module is an implementation of functions for initializing and merging documentation comments.
 */

#include "data_structures.h"
#include <stdbool.h>
#include <string.h>

/**
 * Initializes a DocComment structure by setting all its fields to zero.
 * This function is essential to ensure that the DocComment structure starts with clean data.
 * @param comment Pointer to the DocComment structure to be initialized.
 */
void initDocComment(DocComment *comment) {
    memset(comment, 0, sizeof(DocComment));
    comment->lastLineHadText = 0;
}

/**
 * Merges two DocComment structures by combining their content.
 * This function is useful for consolidating documentation comments from multiple sources.
 * It carefully combines the contents of two DocComment structures into one.
 * @param dest The destination DocComment structure where the merged result is stored.
 * @param src The source DocComment structure from which data is taken.
 */
void mergeDocComments(DocComment *dest, const DocComment *src) {
    /* Merge 'brief' description */
    if (strlen(src->brief) > 0 && strlen(dest->brief) == 0) {
        strcpy(dest->brief, src->brief);
    }

    /* Merge 'details' description */
    if (strlen(src->details) > 0 && strlen(dest->details) == 0) {
        strcpy(dest->details, src->details);
    }

    /* Merge parameters */
    for (int i = 0; i < src->paramCount; i++) {
        bool found = false;
        for (int j = 0; j < dest->paramCount; j++) {
            if (strcmp(dest->paramName[j], src->paramName[i]) == 0) {
                found = true;
                break;
            }
        }
        /* If the parameter was not found, add it to the destination */
        if (!found) {
            strcpy(dest->paramName[dest->paramCount], src->paramName[i]);
            strcpy(dest->paramDesc[dest->paramCount], src->paramDesc[i]);
            dest->paramCount++;
        }
    }

    /* Merge 'returnVal' */
    if (strlen(src->returnVal) > 0 && strlen(dest->returnVal) == 0) {
        strcpy(dest->returnVal, src->returnVal);
    }

    /* Merge 'author' */
    if (strlen(src->author) > 0 && strlen(dest->author) == 0) {
        strcpy(dest->author, src->author);
    }

    /* Merge 'version' */
    if (strlen(src->version) > 0 && strlen(dest->version) == 0) {
        strcpy(dest->version, src->version);
    }

    /* Merge 'freeText' */
    if (strlen(src->freeText) > 0) {
        if (strlen(dest->freeText) > 0) {
            strcat(dest->freeText, "\n");
        }
        strcat(dest->freeText, src->freeText);
    }
}
