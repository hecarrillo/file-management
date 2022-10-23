#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int main()
{
   // Read the file path to open
   char file_name[FILENAME_MAX];
   printf("Enter the file name to open: ");
   scanf("%s", file_name);

   FILE *ptr;
   char ch;

   // Opening file in reading mode
   ptr = fopen(file_name, "r");

   if (NULL == ptr)
   {
      printf("file can't be opened \n");
   }

   printf("___CONTENTS OF %s:___ \n\n", file_name);

   // Printing what is written in file
   // character by character using loop.
   do
   {
      ch = fgetc(ptr);
      printf("%c", ch);

      // Checking if character is not EOF.
   } while (ch != EOF);

   // Closing the file
   fclose(ptr);

   // Get the directory from the user to copy the file to
   // NOTE: The directory needs to be already created

   char dir[FILENAME_MAX];
   printf("\nEnter the directory to copy the file to: ");
   scanf("%s", dir);

   // Create a new file in the specified directory
   char new_file_name[FILENAME_MAX];
   sprintf(new_file_name, "%s\\%s", dir, file_name);

   // Copy the file
   CopyFile(file_name, new_file_name, FALSE);

   // Print the new file path
   printf("\nFile copied to: %s", new_file_name);

   return 0;
}
