#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
int main(){
        int pid_arr[1000],count=0;
        DIR *dir;
        struct dirent *entry;
        char p_name[100],p_status[100];
        char for_name[100],line[100];
        char for_state[100];
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
                        snprintf(for_name,sizeof(for_name),"/proc/%d/comm",pid_arr[i]);
                        snprintf(for_state,sizeof(for_state),"/proc/%d/status",pid_arr[i]);
                        FILE *fp=fopen(for_name,"r");
                        FILE *fp2=fopen(for_state,"r");
                        if(fp==NULL || fp2==NULL){
                                if(fp) fclose(fp);
                                if(fp2) fclose(fp2);
                                continue;
                        }
                        p_name[0]='\0';
                        p_status[0]='\0';
                        while(fgets(line,sizeof(line),fp2)!=NULL){
                             if(strncmp(line,"State:",6)==0){
                                strcpy(p_status,line);
                                p_status[strcspn(p_status,"\n")] = '\0';
                                break;
                                }
                        }
                        if (p_status[0] == '\0')
                                strcpy(p_status, "State: Unknown");
                        if (fgets(p_name, sizeof(p_name), fp) != NULL) {
                                p_name[strcspn(p_name,"\n")] ='\0';
                                printf("%-35s %-8d %s\n", p_name, pid_arr[i], p_status);
                        }
                        fclose(fp);
                        fclose(fp2);
                }
          closedir(dir);
        }
        return 0;
}


                 																																																																																																																											                                                                                                                                                                                            
