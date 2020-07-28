#include"headers.h"
void execute_process(char ** parsed_commands){
	int background=0;
	for(int i=0;parsed_commands[i]!=NULL;++i)
		if(strcmp(parsed_commands[i],"&")==0)
        {background=1;parsed_commands[i]=NULL;}
	pid_t pid=fork();
	//globalcurpid=pid;
	if(pid<0){
		perror("pid<0");
		exit(0);
	}
	else if(pid==0){// child process
		/*if(background){
			close(STDOUT_FILENO);
			close(STDERR_FILENO);
		}*/
			setpgid(0, pid);
		execvp(parsed_commands[0],parsed_commands);
		printf("execvp error: %s not found\n",parsed_commands[0]);
		exit(0);
	}
	else {// parent process
		if(background){// add process to process_list
			strcpy(process_list[++process_count],parsed_commands[0]);
			process_pid[process_count]=pid;
			strcpy(process_status[process_count],"running");
			//process_status[process_count]=1;
		}
		else {
			if(globalcurpid==-1)globalcurpid=pid;
			int status, shell_pid = getpid();                                                                  
			signal(SIGTTOU, SIG_IGN);
			signal(SIGTTIN, SIG_IGN);
			tcsetpgrp(0, pid);
			waitpid(pid, &status, WUNTRACED);       // waits for child process
			tcsetpgrp(0, shell_pid);
			signal(SIGTTOU, SIG_DFL);
			signal(SIGTTIN, SIG_DFL);
            if(WIFSTOPPED(status)){
			    strcpy(process_list[++process_count],parsed_commands[0]);
			    process_pid[process_count]=pid;
                 
            }	
    /*        int status;
            waitpid(pid,&status,WUNTRACED);
      */      }
	}
}

