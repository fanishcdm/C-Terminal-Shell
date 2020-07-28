#include"headers.h"
void execute_kjob(char ** parsed_commands,int no){
    if(no==3){
        int jobno=atoi(parsed_commands[1]);
        int c=0;
        for(int i=0;i<=process_count;++i){
            if(process_status[i][0]=='k')
                continue;
            c++;
        }
        if(jobno>c||jobno<0)
            printf("Invalid job no , run jobs command and correct yourself \n");
        else{
            int i;c=0;
            for(i=0;i<=process_count;++i){
                if(process_status[i][0]=='k')
                    continue;
                if(c==jobno)
                    break;
                ++c;
            }
            if(i>process_count)
                printf("Invalid job no , run jobs command and correct yourself \n");
            else 
                kill(process_pid[i],atoi(parsed_commands[2]));
            //strcpy(process_status[i],"killed");
        }
    }
    else 
        printf("Invalid Syntax\n Syntax kjob job_no signal_no\n");
}
