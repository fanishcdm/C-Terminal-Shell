#include"headers.h"
char ** parse_command(char * command){
    char * token;
    token=strtok(command," \t\n");
    char ** temp=(char **)malloc(100*sizeof(char *));
    int i=0;
    while(token!=NULL){
        temp[i]=(char *)malloc(strlen(token)+1);
        strcpy(temp[i],token);
        i++;
        token=strtok(NULL," \t\n");
    }
    temp[i]=NULL;
    return temp;
}
