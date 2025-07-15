/**
 * Module latex_formatting.c
 * This module contains functions for transforming documentation into LaTeX format. It includes
 * functions for escaping LaTeX special characters, formatting module names, and creating a 
 * structured LaTeX document.
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "latex_formatting.h"
#include "global.h"

/**
 * Formats a module name for LaTeX, changing .h to .c if necessary.
 * @param moduleName The module name to be formatted.
 */
void formatModuleName(char *moduleName) {
    char temp[256];
    int j = 0;
    for (int i = 0; moduleName[i] != '\0'; i++) {
        temp[j++] = moduleName[i];
        if (moduleName[i] == '.') {
            if (strcmp(moduleName + i, ".h") == 0) {
                strcpy(temp + j - 2, ".c"); /* Rewrites .h for .c */
                break;
            }
        }
    }
    temp[j] = '\0';
    strcpy(moduleName, temp);
}

/**
 * Escapes special characters in a string for LaTeX formatting.
 * @param str The string to be escaped.
 */
void escapeLaTeXChars(char *str) {
    char temp[512];
    int j = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        switch (str[i]) {
            case '_': temp[j++] = '\\'; temp[j++] = '_'; break;
            default: temp[j++] = str[i];
        }
    }
    temp[j] = '\0';
    strcpy(str, temp);
}

/**
 * Starts a LaTeX document, writing the preamble and section headers.
 * @param outputFile The output file for the LaTeX document.
 */
void startLaTeXDocument(FILE *outputFile) {
    fprintf(outputFile, "\\documentclass{article}\n");
    fprintf(outputFile, "\\begin{document}\n\n");
    fprintf(outputFile, "\\section{Programátorská dokumentace}\n\n");
}

/**
 * @brief Formats function documentation into LaTeX format.
 * @param funcDoc Pointer to the documentation of the function.
 * @param outputFile File pointer to the output file for LaTeX formatted documentation.
 * @param isNewModule Pointer to a flag indicating if the current module is a new module in the document.
 * @param lastModuleName String representing the last processed module name.
 * This function takes the function documentation and formats it into LaTeX syntax. It handles
 * the transformation of module names, function prototypes, and documentation comments into LaTeX
 * while also managing the structure of the document sections. It checks for corresponding .c files
 * for header files and formats module and function names with LaTeX special characters escaped.
 */
void formatToLaTeX(const FunctionDoc *funcDoc, FILE *outputFile, bool *isNewModule, char *lastModuleName) {
    const DocComment *comment = &funcDoc->comment;
    char formattedModuleName[256];
    char tempStr[1024];

    /* Checks if a corresponding .c file exists for a .h file */
    bool hasCVersion = false;
    for (int i = 0; i < functionCount; i++) {
        if (strcmp(functionDocs[i].moduleName, funcDoc->moduleName) == 0 && strchr(functionDocs[i].fileTypes, 'C')) {
            hasCVersion = true;
            break;
        }
    }

    /* Format module name */
    strcpy(formattedModuleName, funcDoc->moduleName);
    escapeLaTeXChars(formattedModuleName);
    char *dot = strrchr(formattedModuleName, '.');
    if (dot && (hasCVersion || strchr(funcDoc->fileTypes, 'C'))) {
        strcpy(dot, ".c");  /* Change the suffix to .c */
    }

    formatModuleName(formattedModuleName);

    /* Check, if the module is new */
    if (strcmp(lastModuleName, formattedModuleName) != 0) {
        strcpy(lastModuleName, formattedModuleName);
        *isNewModule = true;
    }

    if (*isNewModule) {
        fprintf(outputFile, "\\subsection{Modul \\texttt{%s}}\n", formattedModuleName);
        *isNewModule = false;
    }
    /* Formatting function prototype */
    char formattedPrototype[1024];
    sprintf(formattedPrototype, "%s %s", funcDoc->returnType, funcDoc->functionName);
    escapeLaTeXChars(formattedPrototype);
    fprintf(outputFile, "\\subsubsection{Funkce \\texttt{%s}}\n\n", formattedPrototype);

    /* Brief description */
    if (strlen(comment->brief) > 0) {
        strcpy(tempStr, comment->brief);
        escapeLaTeXChars(tempStr);
        fprintf(outputFile, "\\textbf{Stručný popis:} %s\n\\par \\noindent\n \\\\", tempStr);
    }

    /* Arguments */
    if (comment->paramCount > 0) {
        fprintf(outputFile, "\\textbf{Argumenty:}\n");
        for (int i = 0; i < comment->paramCount; i++) {
            fprintf(outputFile, "\\verb\"%s\" -- %s ", comment->paramName[i], comment->paramDesc[i]);
        }
        fprintf(outputFile, "\\par \\noindent\n \\\\");
    }

    /* Return */ 
    if (strlen(comment->returnVal) > 0) {
        fprintf(outputFile, "\\textbf{Návratová hodnota:} \\verb\"%s\" -- %s\\par \\noindent\n \\\\", funcDoc->returnType, comment->returnVal);
    }

    /* Description */
    if (strlen(comment->freeText) > 0) {
        strcpy(tempStr, comment->freeText);
        escapeLaTeXChars(tempStr);
        fprintf(outputFile, "\\textbf{Popis:} %s\n\\par \\noindent\n \\\\", tempStr);
    }

    /* Details */
    if (strlen(comment->details) > 0) {
        strcpy(tempStr, comment->details);
        escapeLaTeXChars(tempStr);
        fprintf(outputFile, "\\textbf{Méně stručný popis:} %s\n\\par \\noindent\n \\\\", tempStr);
    }

    /* Author */
    if (strlen(comment->author) > 0) {
        strcpy(tempStr, comment->author);
        escapeLaTeXChars(tempStr);
        fprintf(outputFile, "\\textbf{Autor:} %s\n\\par \\noindent\n \\\\", tempStr);
    }

    /* Version */
    if (strlen(comment->version) > 0) {
        strcpy(tempStr, comment->version);
        escapeLaTeXChars(tempStr);
        fprintf(outputFile, "\\textbf{Verze:} %s\n\\par \\noindent\n", tempStr);
    }

    fprintf(outputFile, "\n");
}

/**
 * Ends a LaTeX document, writing the end document tag.
 * @param outputFile The output file for the LaTeX document.
 */
void endLaTeXDocument(FILE *outputFile) {
    fprintf(outputFile, "\n\\end{document}\n");
}