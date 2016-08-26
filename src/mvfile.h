/* mvfile.h */

#ifndef MVFILE_H
#define MVFILE_H

// set path separator depending on environment
const char kPathSeparator;

// moves file given input file and output file
int moveFile(char* infile, char* outdir);

#endif
