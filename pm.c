#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
int main(){
        int pid_arr[1000],count=0;
        DIR *dir;
        struct dirent *entry;
        char p_name[100];
        char path[100];
        dir=opendir("/proc");
        if(dir==NULL)
                perror("opendir");
        else{
                while((entry=readdir(dir))!=NULL){
                        if(isdigit(entry->d_name[0])){
                                if(count<1000){
                                pid_arr[count]=atoi(entry->d_name);
                                count++;
                                }
                        }
                }
                printf("The PIDs are %d.\n",count);
                printf("The PIDs are the following:\n");
                for(int i=0;i<count;i++){
                        snprintf(path,sizeof(path),"/proc/%d/comm",pid_arr[i]);
                        FILE *fp=fopen(path,"r");
                        if(fp==NULL)
                                perror(path);
                        else{
                        fgets(p_name,100,fp);
                        p_name[strcspn(p_name,"\n")] ='\0';
                        printf("%35s:   ",p_name);
                        printf("%d      \n",pid_arr[i]);
                        fclose(fp);
                        }
                }
			closedir(dir);
        }
        return 0;

}