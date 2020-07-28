#include "headers.h"
void prompt(char * home){
    char cd[1024],dir[1024];
    getcwd(cd,sizeof(cd));
    strcat(cd,"/");
    char homecopy[1024];
    strcpy(homecopy,home);
    strcat(homecopy,"/");
    if(strncmp(homecopy,cd,strlen(homecopy))==0&&strcmp(homecopy,cd)<0){
        strcpy(dir,"~");
        int j=1;
        for(int i=strlen(home);i<(int)strlen(cd)-1;++i,++j){
            dir[j]=cd[i];
        }
        dir[j]='\0';
    }
    else if(strcmp(homecopy,cd)==0){
        strcpy(dir,"~");
    }
    else {
        cd[strlen(cd)-1]='\0';
        strcpy(dir,cd);
    }
    char machinename[1024];
    gethostname(machinename,sizeof(machinename));
    printf("%s%s@%s:%s%s %s$ ","\033[0;32m",getenv("USER"),machinename,"\033[1;34m",dir,"\033[1;32m");
}
