#include"headers.h"
void execute_overkill(){
    for(int i=0;i<=process_count;++i){
        kill(process_pid[i],9);
    }
}
