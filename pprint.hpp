/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *  PPRINT.HPP -- pretty printter declarations                         *
 *                                                                     *
 *  Operations:                                                        *
 *  - Accepts filename patterns from command line, expanding           *
 *    wildcard characters, {*,?}, if encountered.                      *
 *  - Accepts parameter changes from the command line, e.g.:           *
 *      -?    displays usage message                                   *
 *      -i<n> sets tab width to n (default 2)                          *
 *  - If the command line is empty, queries user for filename.         *
 *  - Attempts to open all files, named on the command line.           *
 *  - Reads and indents each file to stdout.                           *
 *  Assumptions:                                                       *
 *  - Each file contains correct C or C++ source code.                 *
 *                                                                     *
 *  History:                                                           *
 *  - V0.0 - 10 Jun 1993                                               *
 *                                                                     *
 *  Language:        Borland C++, ver 3.1                              *
 *  Platform:        i386, DOS 5.0                                     *
 *  Author:          Jordon Lin                                        *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef PPRINT_HPP
#define PPRINT_HPP

#include <stdlib.h>        // ANSI:     exit()
#include <ctype.h>         // ANSI:     isspace()
#include <stdio.h>                                      
#include <string.h>
#include <conio.h>         // ANSI:     getch()
#include "tokens.hpp"      // FAWCETT:  prototypes for tokens
#include "cmdline.hpp"     // FAWCETT:  prototypes for command line function
#include "files.hpp"       // FAWCETT:  prototypes for file pattern
#include "getline.hpp"

string indent_line(token &fp, pparm &pptr, int keyword);
string indent_keyword(token &fp, pparm &pptr);
string indent_next(token &fp, pparm &pptr, string &comment);

#endif
