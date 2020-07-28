#include"headers.h"
void execute_history(char ** parsed_commands){
    int num=10;
    if(history_latest!=19){num=history_latest+1;}
    if(parsed_commands[1]!=NULL)num=atoi(parsed_commands[1]);
    if(num>=11)num=10;
    for(int i=0;i<num;i++){
        printf("%s",history[history_latest-i]);
    }
}
