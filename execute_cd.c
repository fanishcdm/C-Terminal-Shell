#include"headers.h"
void execute_cd(char * dest , char * home ){
    if(strcmp(dest,"~")==0) execute_cd(home,home);
    else if(strstr(dest,"~")!=NULL){
        char newdest[1024];
        strcpy(newdest,home);
        strcat(newdest,dest+1);
        if(chdir(newdest)!=0)
            printf("%s directory not found\n",newdest);
    }
    else if(chdir(dest)!=0)
            printf("%s directory not found\n",dest);
}

