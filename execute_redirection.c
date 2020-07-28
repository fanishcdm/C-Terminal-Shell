#include"headers.h"
void execute_redirection(char ** parsed_commands ){
    int input=0,output=0,append=0;
    char inputfile[1024],outputfile[1024],appendfile[1024];
    int i;
    for( i=0;parsed_commands[i]!=NULL;++i){
        if(strcmp(parsed_commands[i],">")==0){
            output=1;
            parsed_commands[i]=NULL;
            strcpy(outputfile,parsed_commands[i+1]);
        }
        else if(strcmp(parsed_commands[i],"<")==0){
            input=1;
            parsed_commands[i]=NULL;
            strcpy(inputfile,parsed_commands[i+1]);
        }
        else if(strcmp(parsed_commands[i],">>")==0){
            append=1;
            parsed_commands[i+1]=NULL;
            strcpy(outputfile,parsed_commands[i+1]);
        }
    }
    if(input){
        int fd=open(inputfile,O_RDONLY);
        if(fd<0){  
            perror("Error opening file ");
        //    return ;
        }
        dup2(fd,0);
        close(fd);
    }
    if(output){
        int fd=open(outputfile, O_WRONLY | O_TRUNC | O_CREAT , 0644);
        if(fd<0){  
            perror("Error opening file ");
        //    return ;
        }
        dup2(fd,1);
        close(fd);
    }
    if(append){
        int fd= open(appendfile, O_WRONLY | O_APPEND);
        if(fd<0){  
            perror("Error opening file ");
        //    return ;
        }
        dup2(fd,1);
        close(fd);
    }
}
