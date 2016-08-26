/* backup.c
 *
 * Move all media files from input directory
 * to output directory ignoring important folders
 *
 * May need to be hard coded to ignore certain folders
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>

#include "mvfile.h"

char* types[] = {"jpg", "png", "zip", "mov", "3gp", "mpg", "modd", "gif", "mp4", "wmv"};
int tlength = 10; // length of types array

char* ignore[] = {".gimp-2.6",".oracle_jre_usage","AppData","Downloads"};
int ilength = 4;

int loopFiles(char* indir, char* outdir);

// gets file extension
// taken from http://stackoverflow.com/questions/5309471/getting-file-extension-in-c
char *get_filename_ext(char *filename);

char *get_dirname(char *filename);

// Determines if the extension is a media type
bool extInList(char* ext);

bool ignInList(char* ign);

int main(int argc, char* argv[])
{

  if(argc < 3)
  {

    printf("Usage: backup indir outdir\n");
    return 1;

  }

  char *indir;
  indir = argv[1];
  char *outdir;
  outdir = argv[2];

  return loopFiles(indir, outdir);

}

int loopFiles(char* indir, char* outdir)
{

  struct dirent *dp;
  DIR *dfd;

  if ((dfd = opendir(indir)) == NULL)
  {
   fprintf(stderr, "Can't open %s\n", indir);
   return 1;
  }

  char *ifn;
  char *ofn;

  while((dp = readdir(dfd)) != NULL)
  {
    if(strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
      continue;

    ifn = (char*) malloc(sizeof(indir) + sizeof(dp->d_name) + 2);
    ofn = (char*) malloc(sizeof(outdir) + sizeof(dp->d_name) + 2);

    sprintf(ifn, "%s%c%s", indir, kPathSeparator, dp->d_name);
    sprintf(ofn, "%s%c%s", outdir, kPathSeparator, dp->d_name);

    if(dp->d_type == DT_DIR)
    {
      if(ignInList(get_dirname(ifn)))
        printf("Ignoring %s\n\n", ifn);
      else
      {
        mkdir(ofn);
        loopFiles(ifn, ofn);
        rmdir(ifn);
      }
    }
    else
    {

      if(extInList(get_filename_ext(dp->d_name)))
      {

        printf("%s\n%s\n\n",ifn,ofn);
        if(moveFile(ifn, ofn) != 0)
        {
          free(ifn);
          free(ofn);
          return 1;
        }

      }

    }

    free(ifn);
    free(ofn);

  }

  return 0;

}


// Gets file extension
char *get_filename_ext(char *filename){
   char *dot = strrchr(filename, '.');
   if(!dot || dot == filename) return "";
   return dot + 1;
}

char *get_dirname(char *filename){
   char *dir = strrchr(filename, kPathSeparator);
   if(!dir || dir == filename) return "";
   return dir + 1;
}

// Determines if the extension is a media type
bool extInList(char *ext)
{

  for(int i = 0; i < tlength; i++)
  {

    if(strcmp(ext, types[i]) == 0)
      return true;

  }

  return false;

}

bool ignInList(char *ign)
{

  for(int i = 0; i < ilength; i++)
  {

    if(strcmp(ign, ignore[i]) == 0)
      return true;

  }

  return false;

}
