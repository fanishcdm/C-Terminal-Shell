#include"headers.h"
void execute_jobs(char ** parsed_commands){
    //for(int j=0;j<=process_count;++j)printf("%d %s %d\n",j,process_list[j],process_pid[j]);
    printf("NUMBER  PID   NAME   STATUS\n");
    char executable[1024];
    for(int i=0,number=0;i<=process_count;++i){
        /*if(strcmp(process_status[i],"killed")==0)
            continue;*/
        int temp2;char temp1[1024];char c; unsigned long mem;
        sprintf(executable,"/proc/%d/stat",process_pid[i]);
      //  printf("%s\n",executable);
        FILE * fd = fopen(executable,"r");// "r" for read only
        if(fd==NULL)continue;
        fscanf(fd,"%d %s %c %lu",&temp2,temp1,&c,&mem);
        fclose(fd);
        if(c=='R')
            strcpy(executable,"running");
        else if(c=='S')
            strcpy(executable,"running/sleeping in an interruptible wait");
        else if(c=='D')
            strcpy(executable,"un-sleeping in an uninterruptible disk sleep");
        else if(c=='Z')
            strcpy(executable,"zombie");
        else if(c=='T')
            strcpy(executable,"stopped on a signal");
    //    printf("%d %d\n",i,process_count);
        printf("[%d]  %d    %s    %s\n",number++,process_pid[i],process_list[i],executable);
    }
}
