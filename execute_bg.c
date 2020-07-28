#include"headers.h"
void execute_bg(char ** parsed_commands,int no){
    if(no==2){
        int jobno=atoi(parsed_commands[1]);
        int c=0;char executable[1024];
        for(int i=0;i<=process_count;++i){
            sprintf(executable,"/proc/%d/stat",process_pid[i]);
            FILE *fd =fopen(executable,"r");
            if(fd==NULL)
                continue;
            c++;
            fclose(fd);
        }
        if(jobno>c||jobno<0)
            printf("Invalid job no , run jobs command and correct yourself \n");
        else{
            int i;c=0;
            for(i=0;i<=process_count;++i){
                sprintf(executable,"/proc/%d/stat",process_pid[i]);
                FILE *fd =fopen(executable,"r");
                if(fd==NULL)
                    continue;
                if(c==jobno)
                    break;
                ++c;
                fclose(fd);
            }
            if(i>process_count)
                printf("Invalid job no , run jobs command and correct yourself \n");
            else
                kill(process_pid[i],SIGCONT);
            //strcpy(process_status[i],"killed");
        }
    }
    else 
        printf("Invalid Syntax\n Syntax bg job_no\n");
}
