#include"headers.h"
void execute_echo(char ** parsed_commands){
    for(int i=1;parsed_commands[i]!=NULL;++i){
        printf("%s ",parsed_commands[i]);
    }
    printf("\n");
}

