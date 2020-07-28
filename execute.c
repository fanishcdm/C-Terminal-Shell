#include"headers.h"

void execute(char ** parsed_commands,int input ,int output){

    //printf("%s\n",commands);

    if(input!=0){
        dup2(input,0);
        close(input);
    }
    if(output!=1){
        dup2(output,1);
        close(output);
    }
    if(strcmp(parsed_commands[0],"\n")==0|strcmp(parsed_commands[0],"\0")==0) return;
    
    //for(int i=0;parsed_commands[i]!=NULL;++i)printf("%s\n",parsed_commands[i]);

    if(parsed_commands[0]==NULL) return ;
    
    // no of arguments
    int no_of_parsed =0;
    for(;parsed_commands[no_of_parsed]!=NULL;no_of_parsed++);
    strcpy(globalcurprocess,parsed_commands[0]);

    //printf("%s\n",parsed_commands[0]);
    if(strcmp(history[19],"\0")!=0&&strncmp(history[history_latest],parsed_commands[0],strlen(parsed_commands[0]))!=0){
        for(int i=1;i<20;++i)strcpy(history[i-1],history[i]);
        strcpy(history[19],parsed_commands[0]);
        strcat(history[19],"\n");
    } 
    else if(strncmp(history[history_latest],parsed_commands[0],strlen(parsed_commands[0]))!=0){
        strcpy(history[++history_latest],parsed_commands[0]);
        strcat(history[history_latest],"\n");
    }

    //for(int i=0;i<=history_latest;++i)printf("%s",history[i]);printf("\n\n");

    if(strcmp(parsed_commands[0],"cd")==0){
        if(parsed_commands[1]==NULL)
            execute_cd(home,home);
        else 
            execute_cd(parsed_commands[1],home);
    }
    else if(strcmp(parsed_commands[0],"pwd")==0){
        execute_pwd();
    }
    else if(strcmp(parsed_commands[0],"echo")==0){
        execute_echo(parsed_commands);
    }
    else if(strcmp(parsed_commands[0],"pinfo")==0){
        if(parsed_commands[1]==NULL) execute_pinfo(getpid());
        else execute_pinfo(atoi(parsed_commands[1]));
    }
    else if(strcmp(parsed_commands[0],"ls")==0){
        execute_ls(parsed_commands);
    }
    else if(strcmp(parsed_commands[0],"history")==0){
        /*        if(strcmp(history[history_latest],parsed_commands[0])){
                  strcpy(history[++history_latest],parsed_commands[0]);
                  strcat(history[history_latest],"\n");
                  }*/
        execute_history(parsed_commands);
    }
    else if(strcmp(parsed_commands[0],"setenv")==0){
        execute_setenv(parsed_commands,no_of_parsed);
    }
    else if(strcmp(parsed_commands[0],"unsetenv")==0){
        execute_unsetenv(parsed_commands,no_of_parsed);
    }
    else if(strcmp(parsed_commands[0],"jobs")==0){
        execute_jobs(parsed_commands);
    }
    else if(strcmp(parsed_commands[0],"kjob")==0){
        execute_kjob(parsed_commands,no_of_parsed);
    }
    else if(strcmp(parsed_commands[0],"bg")==0){
        execute_bg(parsed_commands,no_of_parsed);
    }
    else if(strcmp(parsed_commands[0],"fg")==0){
        execute_fg(parsed_commands,no_of_parsed);
    }
    else if(strcmp(parsed_commands[0],"overkill")==0){
        execute_overkill();
    }
    else if(parsed_commands[0][0]==27&&parsed_commands[0][1]==91&&(parsed_commands[0][2]==65)&&strlen(parsed_commands[0]>2)){
    up_arrow(parsed_commands);
    }
    else if(strcmp(parsed_commands[0],"quit")==0||strcmp(parsed_commands[0],"exit")==0){
        FILE *f=fopen("history.txt","w+");
        int size=0;
        //for(int i=0;i<=history_latest;++i)size+=strlen(history[i]);
        fwrite(history,sizeof(char),sizeof(history),f);
        fclose(f);
        exit(0);
    }
    else {
        //for(int i=0;parsed_commands[i]!=NULL;++i)printf("%s\n",parsed_commands[i]);
        execute_process(parsed_commands);
    }

    for(int i=0;parsed_commands[i]!=NULL;++i)free(parsed_commands[i]);
    free(parsed_commands);


}
