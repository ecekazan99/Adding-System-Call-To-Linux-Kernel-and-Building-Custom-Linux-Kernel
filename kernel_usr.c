/*
syscall_64.tbl (335	common	sys_my_syscall0	__x64_sys_my_syscall0
		336	common	sys_my_syscall1	__x64_sys_my_syscall1
		337	common	sys_my_syscall2	__x64_sys_my_syscall2
		338	common	sys_my_syscall3	__x64_sys_my_syscall3)

syscalls.h (asmlinkage long sys_my_syscall_0(char __user *, char __user *);
	    asmlinkage long sys_my_syscall_1(char __user *, char __user *);
	    asmlinkage long sys_my_syscall_2(char __user *, char __user *);
	    asmlinkage long sys_my_syscall_3(char __user *, char __user *);)
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/syscall.h>
#include <unistd.h>

#define DEST_SIZE 1000

int main(char argc, char *argv[]){
	char *dest=NULL;
	dest=(char*)malloc(2000);

	if(argc==1 &&strncmp(argv[0],"./2017510049.out",strlen("./2017510049.out"))==0){
		char *src="\nRight Usage:\n\t-all prints some information (process id and itsargument/s) about all processes\n\t-p takes process id and prints the details of it\n\t-k takes process id\n";
		long int return_val = syscall(335,src,dest);
		printf("%s\n",dest);
	}
	else if(argc==2 && strncmp(argv[1],"-all",strlen("-all"))==0){
		char *parameter=argv[1];
		char *src=NULL;
		printf("Process id and the argument list for the processes:\n");
		long int return_val = syscall(336,src,dest);
		printf("%s\n",dest);
	}
	else if(argc==3 && strncmp(argv[1],"-p",strlen("-p"))==0){
		char *parameter=argv[1];
		char *id=argv[2];
		printf("Argument# [");
		printf(parameter);
		printf("] -Process Information:\n");
		long int return_val = syscall(337,id,dest);
		printf("%s -> %s\n",id,dest);
	}
	else if(argc==3 && strncmp(argv[1],"-k",strlen("-k"))==0){
		char *src="\nProcess was killed...\n";
		long int return_val = syscall(338,src,dest);
		printf("%s\n",dest);
	}
	else{
		char *src="\nRight Usage:\n./2017510049.out\n\t-all prints some information (process id and itsargument/s) about all processes\n\t-p takes process id and prints the details of it\n\t-k takes process id\n";
		long int return_val = syscall(335,src,dest);
		printf("%s\n",dest);
	}
	return 0;
}