#include "include/file.h"

class File;

File::File(char * enname){
			name = enname;
}

File::File(char * enname,FileAccessMode ftc) {
			name = enname;
			ft = ftc; 
}


		void File::Open(char * fname,FileAccessMode fom,FileShareMode fsm,FileAttributes fa,FileCreationMode fcm) {
			name = fname;
			DWORD Access,Share,CreateMode;
			switch(fom) {
				case READ :
					Access = GENERIC_READ;
					break;
				case WRITE :
					Access = GENERIC_WRITE;
					break;
				case READWRITE:
					Access = GENERIC_READ | GENERIC_WRITE;
					break;
				default:
					clog<<"Undefined file access mode "<<endl;
					break;
			}
			
			switch(fsm) {
				case NO_SHARE:
					Share = 0;
					break;
				case READ_SHARE :
					Share = FILE_SHARE_READ;
					break;
				case WRITE_SHARE:
					Share = FILE_SHARE_WRITE;
					break;
				default :
					clog<<"Undefined file share mode "<<endl;
					break;
			}
			
			switch(fcm) {
				case NEW:
					CreateMode = CREATE_NEW;
					break;
				case CREATE_OVERWRITE:
					CreateMode = CREATE_ALWAYS;
					break;
				case OPEN:
					CreateMode = OPEN_EXISTING;
					break;
				case OPEN_CREATE:
					CreateMode = OPEN_ALWAYS;
					break;
				case TRUNC:
					CreateMode = TRUNCATE_EXISTING;
					break;
				default:
					clog<<"Undefined file creation mode "<<endl;
					break;
			}
			
			if(fcm==TRUNC && (fom==WRITE_SHARE || fom==0)) {
				clog<<"Truncating a file requires at lease a READ_SHARE access, you will get in trouble :\(";
			}
			
			fhnd =  CreateFileA(fname,Access,Share,NULL,CreateMode,fa,NULL);
			if(fhnd==INVALID_HANDLE_VALUE) {
				clog<<"An error occurred during opening the file";
			}
			ft = (fom==READ)?READ:WRITE;
		}
		void File::Open(FileAccessMode fom,FileShareMode fsm,FileAttributes fa,FileCreationMode fcm) {
			return Open(name,fom,fsm,fa,fcm);
		}
		void File::Open(FileShareMode fsm,FileAttributes fa,FileCreationMode fcm) {
			 Open(name,ft,fsm,fa,fcm);
		}
		void File::Close() {
			CloseHandle(fhnd);
		}
		
		DWORD File::Write(const void* data,DWORD bytestowrite) {
			DWORD *written = (DWORD *) malloc(sizeof(DWORD));
			if(ft==READ) {
				clog<<"You have opened the file for reading, but you want to write, you will face a trouble :(";
			}
			WriteFile(fhnd,data,bytestowrite,written,NULL);
			if (*written!=bytestowrite) {
				clog<<"An error occurred during writing to the output file";
			}
			return *written;
		}
		
		DWORD File::Read(void *data,DWORD bytestoread) {
			DWORD* read = (DWORD *) malloc(sizeof(DWORD));
			if(ft==WRITE) {
				clog<<"You have opened the file for writing, but you want to read, you will face a trouble :(";
			}
			ReadFile(fhnd,data,bytestoread,read,NULL);
			if (*read!=bytestoread) {
				FILE * flog = fopen("libfile.log","w");
				fprintf(flog,"Reached end of file or invalid file handle. :\(");
				fclose(flog);
			}
			return *read;
		}
		
		DWORD File::WriteAll(const char *buffer) {
			return Write(buffer,strlen(buffer));
		}
		
		DWORD File::ReadAll(char *buffer) {
			int i = 0;
			while (Read(buffer+i,BUFFER_SIZE)==BUFFER_SIZE) {
				++i;
			}
			return i+1;
		}
		
		bool File::Delete() {
			return (DeleteFileA(name)!=0):true?false;
		}
		
		char * File::getName() {
			return name;
		}
		
		void File::setName(char * sname) {
			name = sname;
		}
		
		FileAccessMode File::getAccess(){
			return ft;
		}
		
		void File::setAccess(FileAccessMode sft) {
			ft = sft;
		}
