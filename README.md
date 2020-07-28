Fanish Jain - 2018101021

RUNNING:
> make ; make clean  // clean removes the .o files 
> ./fanshell

Shell function descriptions: ( BONUS CODED :)
1. Each .c file contains the corresponding function , for eg , execute_cd.c contains execute_cd() function.
2. Program flow :
    a. Display prompt
    b. Read input and parse on basis of ";" 
    c. Execute the command and check for any background process exited or not
    d. Go to a.
3. To quit, press : "quit" or "exit".


FUNCTIONS:
1. setenv var value : fanshell sets the value of var to value, or to the empty string if value is omitted. Initially, fanshell inherits environment variables from its parent. Your shell can modify the value of an existing environment variable or create a new environment variable via the setenv command.
2. unsetenv var : fanshell destroys the environment variable var.
3. jobs : prints a list of all currently running jobs along with their pid, in particular, background jobs, in order of their creation along with their state – Running or Stopped.
4. kjob : takes the job id of a running job and sends a signal value to that process.
5. fg : brings a running or a stopped background job with given job number to foreground.
6. bg : changes a stopped background job to a running background job.
7. overkill : kills all background process at once.
8. CTRL-Z : It changes the status of currently running job to stop, and pushes it in background process.
9. CTRL-C : It should cause a SIGINT signal to be sent to the current foreground job of your shell. If there is no foreground job, then the signal doesn't have any effect.


10. Some more features:
	    semi colon seprated commnads work;
    	& for background;
	    remove extra spaces in echo;
	    builtin of cd , echo , pwd;
	    show relative path in promt and user name and host name;
	    Show message when a background process stop;
	    pinfo to get a particular process information;

11. Input-Output Redirection:-
		-can take input from a file, use "< fileName" for input
		-can save output in a file, use "> fileName" for output or use ">> fileName" to append output in file

12. Piping along with Input-Output Redirection:-
	- support multiple pipes use "|" for piping
	- ASSUMPTION use input redirction only in 1st command in pipe and use output redirection in last command of pipe

13. Decision made:-
	- use input redirction only in 1st command in pipe and use output redirection in last command of pipe
