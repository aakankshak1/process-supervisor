#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <stdlib.h>

int main(){
	int pid_arr[1000],count=0;
	DIR *dir;
	dir=opendir("proc");
	if(dir==NULL)
		prinf("The system failed");
	else{
		struct dirent *entry;
		while((entry=readdir(dir))!=NULL){
			if(isdigit(entry->d_name[0])){
				if(count<1000){
				pid_arr[count]=atoi(entry->d_name);
				count++;
				}
			}
		}
		printf("The PIDs are %d",count);
		printf("The PIDs are the following:");	
		for(int i=0;i<count;i++)
			printf("%d\n",pid_arr[i]);
		}
	closedir(dir)
	return 0;

}




