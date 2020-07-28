#include"headers.h"
void sigint_handler(int signum){
    if(getpid()!=fanshellpid)
        return;
    if(globalcurpid!=-1){
        kill(globalcurpid,SIGINT);
    /*    for(int i=0;i<=process_count;++i){
            if(process_pid[i]==globalcurpid){
                strcpy(process_status[i],"killed");
                break;
            }
        }*/
    }
    fflush(stdout);
}
