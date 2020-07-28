#include"headers.h"
void sigtstp_handler(int signum){
    if(getpid()!=fanshellpid)
        return;
    if(globalcurpid!=-1){
        kill(globalcurpid,SIGTSTP);
/*        int i;
        for(i=0;i<=process_count;++i)
            if(process_pid[i]==globalcurpid)
                break;
        if(i==process_count+1){
            process_count++;
            process_pid[process_count]=globalcurpid;
            strcpy(process_list[process_count],globalcurprocess);
            strcpy(process_status[process_count],"stopped");
        }*/
    }
    //globalcurpid=-1;
    fflush(stdout);
}
