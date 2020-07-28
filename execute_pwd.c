#include"headers.h"
void execute_pwd(){
    char temp[1024];
    printf("%s\n",getcwd(temp,sizeof(temp)));
}

