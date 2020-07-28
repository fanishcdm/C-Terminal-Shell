#include"headers.h"
void execute_fg(char ** parsed_commands,int no){
    if(no==2){
        int jobno=atoi(parsed_commands[1]);
        int c=0;char executable[1024];
        for(int i=0;i<=process_count;++i){
            sprintf(executable,"/proc/%d/stat",process_pid[i]);
            FILE * fd =fopen(executable,"r");
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
                FILE * fd =fopen(executable,"r");
                if(fd==NULL)
                    continue;
                if(c==jobno)
                    break;
                ++c;
                fclose(fd);
            }
            if(i>process_count)
                printf("Invalid job no , run jobs command and correct yourself \n");
            else {

                int shellpid=getpid(),status;
                if(globalcurpid==-1)globalcurpid=process_pid[i];
                pid_t pidnumber;
                pidnumber= process_pid[i];
                signal(SIGTTOU,SIG_IGN);
                signal(SIGTTIN,SIG_IGN);
                tcsetpgrp(0,getpgid(pidnumber));
                kill(pidnumber,SIGCONT);
                //signal(SIGTTOU,SIG_DFL);
                waitpid(pidnumber,&status,WUNTRACED);
                tcsetpgrp(0,shellpid);
                signal(SIGTTOU,SIG_DFL);
                signal(SIGTTIN,SIG_DFL);

                //for(int j=0;j<=process_count;++j)printf("%d %s %d\n",j,process_list[j],process_pid[j]);
                /*       globalcurpid=process_pid[i];
                         kill(process_pid[i],SIGTSTP);
                         kill(process_pid[i],SIGCONT);
                         int status;
                         waitpid(process_pid[i],&status,WUNTRACED);
                         */ } 

        }
    }
    else 
        printf("Invalid Syntax\n Syntax fg job_no\n");
}
