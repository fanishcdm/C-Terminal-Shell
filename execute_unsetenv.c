#include"headers.h"
void execute_unsetenv(char ** parsed_commands,int no){
    if(no==2)
        unsetenv(parsed_commands[1]);
    else{
        printf("Invalid Syntax :(  Syntax=> unsetenv var\n");
    }
}
