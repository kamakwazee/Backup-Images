/* mvfile.c
 *
 * Moves file given input file and output directory
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "mvfile.h"

const char kPathSeparator =
#ifdef _WIN32
  '\\';
#else
  '/';
#endif

// max buffer size = 512 bytes
#define BUFFERSIZE 512

typedef uint8_t BYTE;

// moves file given input file and output file
int moveFile(char* infile, char* outfile)
{

  /* attempt to open input file
   * if it fails, return error 1
   */
  FILE* inptr = fopen(infile, "rb");
  if(inptr == NULL)
  {

    printf("Could not open %s.\n",infile);
    return 1;

  }

  /* attempt to open output file
   * if it fails, return error 3
   */
  FILE* outptr = fopen(outfile,"wb");
  if(outptr == NULL)
  {

    fclose(inptr);
    fprintf(stderr, "Could not create %s.\n",outfile);
    return 2;

  }

  // get size of input file
  fseek(inptr, 0L, SEEK_END);
  int fs = ftell(inptr);
  rewind(inptr);

  // buffer for reading data
  BYTE buffer[BUFFERSIZE];

  // loop through input file
  for(int i = 0; i < fs; i += BUFFERSIZE)
  {

    size_t bs = 0; // current buffer size

    // read a block into buffer
    bs = fread(&buffer, sizeof(BYTE), BUFFERSIZE, inptr);

    // write buffer to file
    fwrite(&buffer, sizeof(BYTE), bs, outptr);

  }

  // close files
  fclose(inptr);
  fclose(outptr);

  // attempt to remove input file
  if(remove(infile) != 0)
    printf("Couldn't remove %s\n",infile);

  // SUCCESS!!!!!
  return 0;
}
