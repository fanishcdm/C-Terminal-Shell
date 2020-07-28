#include<string.h>
#include<stdio.h>
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <errno.h>
#include<dirent.h>
#include<grp.h>
#include<time.h>
#include<pwd.h>
#include<signal.h>
extern int globalcurpid;
extern char globalcurprocess[1024];
extern int fanshellpid;
extern char process_list[100][200];
extern int process_pid[100];
extern int process_count;
extern char process_status[100][200];
extern char history[20][256];
extern int history_latest;
extern char home[1024];
void up_arrow(char **);
void execute_overkill();
void sigint_handler(int sig_num);
void sigtstp_handler(int sig_num);
void execute_redirection(char **);
void prompt(char * home);
void execute_setenv(char ** parsed_commands,int );
void execute_jobs(char ** parsed_commands);
void execute_kjob(char ** parsed_commands,int );
void execute_bg(char ** parsed_commands,int);
void execute_fg(char ** parsed_commands,int);
void execute_unsetenv(char ** parsed_commands,int );
void execute(char ** ,int input,int output);
char ** removesemicolon(char * input);
char ** parse_command(char * command);
void execute_ls(char ** parsed_commands);
void execute_cd(char *,char *);
void execute_pwd();
void execute_echo(char **);
void execute_pinfo(int);
void execute_process(char **);
void execute_history(char **);
char ** parse_pipe(char *);
void execute_pipe(char *);

