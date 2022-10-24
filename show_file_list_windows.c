#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int main()
{
   // Get the current path
   char path[FILENAME_MAX];
   GetCurrentDirectory(FILENAME_MAX, path);

   ListDirectoryContents(path);
}

BOOL ListDirectoryContents(const char *sDir)
{
   WIN32_FIND_DATA fdFile;
   HANDLE hFind = NULL;

   char sPath[2048];
   char sSize[2048];

   // Specify a file mask. *.* = We want everything!
   sprintf(sPath, "%s\\*.*", sDir);

   if ((hFind = FindFirstFile(sPath, &fdFile)) == INVALID_HANDLE_VALUE)
   {
      printf("Path not found: [%s]\n", sDir);
      return FALSE;
   }

   do
   {
      // Find first file will always return "."
      //     and ".." as the first two directories.
      if (strcmp(fdFile.cFileName, ".") != 0 && strcmp(fdFile.cFileName, "..") != 0)
      {
         // Build up our file path using the passed in
         //   [sDir] and the file/foldername we just found:
         sprintf(sPath, "%s\\%s", sDir, fdFile.cFileName);

         // Is the entity a File or Folder?
         if (fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
         {
            printf("Directory: %s\n", sPath);
            ListDirectoryContents(sPath); // Recursion, I love it!
         }
         else
         {
            // Get the file size
            sprintf(sSize, "%d", fdFile.nFileSizeLow);
            // Get the file last access date
            SYSTEMTIME stUTC, stLocal;
            FileTimeToSystemTime(&fdFile.ftLastAccessTime, &stUTC);
            SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

            printf("File: %s\nBytes: %s\nLast Access Date: %02d/%02d/%d %02d:%02d\n\n", sPath, sSize, stLocal.wDay, stLocal.wMonth, stLocal.wYear);
         }
      }
   } while (FindNextFile(hFind, &fdFile)); // Find the next file.

   FindClose(hFind); // Always, Always, clean things up!

   return TRUE;
}