#include "headers.h"
char home[1024];
char globalcurprocess[1024];
char process_list[100][200];
int process_pid[100];
char process_status[100][200];
int process_count=-1;
char history[20][256];
int history_latest=0;
int globalcurpid;
int fanshellpid;

void execute_pipe(char * command){
    if(command==NULL)return;
    char ** piped_commands=parse_pipe(command);
    char ** temp;
    int i; // no of piped commands
    for( i=0;piped_commands[i]!=NULL;++i);
    int fd[2],input=0,a,b;
    for(int j=0;j<i-1;++j){
        a=dup(0);b=dup(1);
        pipe(fd);
        temp = parse_command(piped_commands[j]);
        execute_redirection(temp);
        execute(temp,input,fd[1]); // important
        close(fd[1]);
        dup2(a,0);
        dup2(b,1);
        input=fd[0];
    }

    int c=dup(0),d=dup(1);
    temp = parse_command(piped_commands[i-1]);
    execute_redirection(temp);
    execute(temp,input,1);
    close(input);
    dup2(c,0);
    dup2(d,1);
}

void letsgo(){
    while(1){
        prompt(home); // display 
        char input[1024];
        fgets(input,1024,stdin); // input commands
        int status;
        pid_t pid;
        while((pid=waitpid(-1,&status,WNOHANG))>0){ // checking the status of processes
            for(int i=0;i<=process_count;++i){
                if(process_pid[i]==pid/*&&strcmp(process_status[i],"killed")!=0*/){
                    //strcpy(process_status[i],"killed");
                    printf("process %s with pid %d exited with status %d\n",process_list[i],pid,WEXITSTATUS(status));
                }
            }
        }
        //if(strstr(input, ";") != NULL) // if semicolon in query
        //printf("in main  %s\n",input);
        char ** commands = removesemicolon(input);
        char ** args;
        for(int i=0;commands[i]!=NULL;++i){
            if(strstr(commands[i],"|")!=NULL){
                execute_pipe(commands[i]);
            }
            else {
                int a=dup(0),b=dup(1);
                args=parse_command(commands[i]);
                if(args==NULL||args[0]==NULL)continue;
                execute_redirection(args);

                execute(args,0,1);

                dup2(a,0);
                dup2(b,1);
            }
            free(commands[i]);
        }
        free(commands);
    }
}

int main(int argc, char * argv[]){
    globalcurpid=-1;
    fanshellpid=getpid();
    signal(SIGINT,sigint_handler);   // ctrl C
    signal(SIGTSTP,sigtstp_handler); // ctrl Z
    char cd[1024];//curr_dir
    getcwd(cd,sizeof(cd));
    // home is where the file resides
    int i=strlen(argv[0])-1;
    while(argv[0][i]!='/'){
        i--;
    }
    char temp[i];
    for(int j=0;j<i;++j)temp[j]=argv[0][j];
    temp[i]='\0';
    chdir(temp);
    getcwd(home,sizeof(home));
    chdir(cd);
    for(int i=0;i<20;++i)strcpy(history[i],"\0");
    FILE *fd=fopen("history.txt","r");
    if(fd!=NULL){
        fread(history,sizeof(char),sizeof(history),fd);
        fclose(fd);
    }
    for( i=0;i<20;++i){
        if(strcmp(history[i],"\0")==0){history_latest=i-1;break;}
    }
    if(i==20) history_latest=i-1;
    letsgo(); // main loop
    return 0;
}
