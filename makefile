CC=gcc
CFLAGS=-I ./
DEPS=headers.h
OBJ= execute.o execute_cd.o execute_pwd.o execute_echo.o execute_execvp.o main.o execute_pinfo.o parser.o prompt.o execute_ls.o removesemicolon.o execute_history.o  parse_pipe.o execute_redirection.o execute_setenv.o execute_unsetenv.o execute_fg.o execute_bg.o execute_kjob.o execute_jobs.o sigint_handler.o sigtstp_handler.o execute_overkill.o up_arrow.o
#all: clean
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
# 	here -o $@ denotes left side of (:) and $< is the first item on the right side of (:)

fanshell: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
# 	here $^ denotes all the items which are on the right side of (:)
	

.PHONY: clean

clean:
	rm -f *.o 
