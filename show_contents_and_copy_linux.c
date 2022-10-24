#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main( int argc, char *argv[] )
{

  FILE *fp;
  char path[1035];

  // we ask the user for the file to oṕen and copy
  printf("Ingrese el nombre del archivo que desea abrir y copiar: ");
  char fileName[30];
  scanf("%[^\n]s",fileName);
  char openCommand[100] = "cat ";
  strcat(openCommand, fileName);

  /* Open the command for reading. */
  fp = popen(openCommand, "r");
  if (fp == NULL) {
    printf("Failed to run command\n" );
    exit(1);
  }


  /* Read the output a line at a time - output it. */
  while (fgets(path, sizeof(path), fp) != NULL) {
    printf("%s", path);
  }
  /* close */
  pclose(fp);

  // Copy the file to copy_dir folder 
  char copyCommand[100] = "cp ";
  strcat(copyCommand, fileName);
  strcat(copyCommand, " copy_dir/");
  system(copyCommand);

  return 0;
}
