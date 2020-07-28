#include"headers.h"
char ** parse_pipe(char * input){
    int i;
    char * token;
    token=strtok(input,"|\n");
    char ** temp=(char **)malloc(100*sizeof(char *));
    for(i=0;token!=NULL;++i){    
        temp[i]=(char *)malloc(strlen(token)+1);
        strcpy(temp[i],token);
        token=strtok(NULL,"|\n");
    }
    temp[i]=NULL;
    return temp;
}
