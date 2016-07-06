#ifndef FILE_H
#define FILE_H
#include <windows.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <tchar.h>

using namespace std;

/* To use more than one flag `or` the flags, like below

HIDDEN | READONLY

*/

#define HIDDEN FILE_ATTRIBUTE_HIDDEN
#define NORMAL FILE_ATTRIBUTE_NORMAL
#define DELETEONCLOSE FILE_FLAG_DELETE_ON_CLOSE
#define READONLY FILE_ATTRIBUTE_READONLY
#define OVERLAPPED FILE_FLAG_OVERLAPPED
#define RANDOMACCESS FILE_FLAG_RANDOM_ACCESS
#define SEQUENTIAL FILE_FLAG_SEQUENTIAL_SCAN 
#define BUFFER_SIZE 1 /* You may change it anytime you wanted:) */

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

typedef enum FileAccessMode {
	READ = 1,
	WRITE,
	READWRITE
} FileOpenMode;

typedef enum FileShareMode {
	NO_SHARE = 1,
	READ_SHARE,
	WRITE_SHARE
} FileShareMode;

typedef int FileAttributes;

typedef enum FileCreationMode {
	NEW=1,
	CREATE_OVERWRITE,
	OPEN,
	OPEN_CREATE,
	TRUNC
} FileCreationMode;



class File {
	public : 
		File(char *); /* Constructors */
		File(char *,FileAccessMode); /*Constructors*/
		void Open(char *,FileAccessMode,FileShareMode,FileAttributes,FileCreationMode); /* The complete function for opening files */
		void Open(FileAccessMode,FileShareMode,FileAttributes,FileCreationMode);/* The function for opening files if you have specified the name of file when you initialized the file object*/
		void Open(FileShareMode,FileAttributes,FileCreationMode); /* Another version of Open function :)*/ 
		void Close(); /* Function for closing the file after it is  used */
		DWORD Write(const void*,DWORD); /* General function for writing data to file */
		DWORD ReadAll(char *); /* Utilized function for reading string buffer from input file */
		DWORD WriteAll(const char*);/* Utilized function for writing string to buffer */
		DWORD Read(void *,DWORD);/* General function for reading data from file */
		bool Delete();/* Deletes the file */
		char *getName();
		void setName(char *);
		FileAccessMode getAccess();
		void setAccess(FileAccessMode);
	private:
		HANDLE fhnd; /* File handle */
		char * name; /* Name of file */
		FileAccessMode ft;/* Access mode of file */
};
#endif
