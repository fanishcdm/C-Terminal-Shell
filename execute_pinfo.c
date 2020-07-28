#include"headers.h"
void execute_pinfo(int epid){
    char process_path[1024],process_executable[1024],cd[1024],temp1[1024],epid_str[256],c;
    unsigned long mem;int temp2;
    sprintf(process_path,"/proc/%d/stat",epid);
    FILE * fd = fopen(process_path,"r");// "r" for read only
    if(fd == NULL){
        printf("Process with pid %d doesn't exist\n",epid); // error handling
        return ;
    }
    if(fd){
        // c == third word of stat file contains current status of process
        fscanf(fd,"%d %s %c %lu",&temp2,temp1,&c,&mem);
        printf("pid -- %d\n",epid);
        printf("Process Status -- %c\n",c);
        printf("memory -- %lu {Virtural Memory}\n",mem*1024);
        fclose(fd);
    }
    else perror("ERROR : Process doesn't exist\n");
    sprintf(process_executable,"/proc/%d/exe",epid);
    unsigned long characters_written;
    // readlink reads the symlink exe which is pointed to executable path of process
    if((characters_written=readlink(process_executable,cd,sizeof(cd)))>=0){
        cd[characters_written]='\0';
        char dir[1024];
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

        printf("Executable Path -- %s\n",dir);
    }
    else perror("Error: Process doesn't exists\n");
}
