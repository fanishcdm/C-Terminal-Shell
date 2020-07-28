#include"headers.h"
void execute_setenv(char ** parsed_commands,int no){
    if(no-1==1)
        printf("No arguments are given to SETENV \n");
    else if(no-1>2){
        printf("Extra arguments , syntax => setenv var [val]\n");
    }
    else {
        setenv(parsed_commands[1],parsed_commands[2],1);
    }
}
