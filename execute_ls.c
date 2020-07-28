#include"headers.h"
extern char home[1024];
int is_dir(char * dir_name){
    struct stat buff;
    stat(dir_name,&buff);
    return S_ISDIR (buff.st_mode);
}

void execute_l(char *file_path,char *file_name,int a){
    char file_permissions[64],time_mod[64];
    struct stat st;
    if(!stat(file_path,&st)&&((!a && file_name[0]!='.')||a)){
        mode_t tocheck=st.st_mode;
        if(S_ISDIR(tocheck))file_permissions[0]='d'; //directory
        else if(S_ISREG(tocheck)) file_permissions[0]='-'; //file
        else file_permissions[0]='l'; //link
        file_permissions[1] = (tocheck & S_IRUSR) ? 'r' : '-';
        file_permissions[2] = (tocheck & S_IWUSR) ? 'w' : '-';
        file_permissions[3] = (tocheck & S_IXUSR) ? 'x' : '-';
        file_permissions[4] = (tocheck & S_IRGRP) ? 'r' : '-';
        file_permissions[5] = (tocheck & S_IWGRP) ? 'w' : '-';
        file_permissions[6] = (tocheck & S_IXGRP) ? 'x' : '-';
        file_permissions[7] = (tocheck & S_IROTH) ? 'r' : '-';
        file_permissions[8] = (tocheck & S_IWOTH) ? 'w' : '-';
        file_permissions[9] = (tocheck & S_IXOTH) ? 'x' : '-';
        file_permissions[10] = '\0';
        // ls -l format
        printf("%s %lu",file_permissions,st.st_nlink);
        printf(" %s ",(getpwuid(st.st_uid)->pw_name)); // username
        printf("%s ",(getgrgid(st.st_gid))->gr_name); // grp name
        strftime(time_mod, sizeof(time_mod), "%b %d %H:%M", localtime(&st.st_mtime));  
        printf("%10ld %s ",st.st_size,time_mod); // bytes
        if(is_dir(file_name))
            printf("%s%s%s\n","\033[1;34m",file_name,"\033[0m");
        else 
            printf("%s%s%s\n","\033[0;32m",file_name,"\033[0m");
    }
}

void execute_ls(char ** parsed_commands){
    char dest[1024]="randf***";
    char newdest[1024];
    int a=0,l=0;
    for(int i=1;parsed_commands[i]!=NULL;++i){
        if(parsed_commands[i][0]=='-'){
            if(strcmp(parsed_commands[i],"-l")==0)l=1;
            else if(strcmp(parsed_commands[i],"-a")==0)a=1;
            else if(strcmp(parsed_commands[i],"-la")==0||strcmp(parsed_commands[i],"-al")==0){a=1;l=1;}
        }
        else strcpy(dest,parsed_commands[i]);
    }
    if(strcmp(dest,"randf***")==0) strcpy(dest,".");
    //printf("%s\n",dest);
    else if(strstr(dest,"~")!=NULL){
        strcpy(newdest,home);
        strcat(newdest,dest+1);
        strcpy(dest,newdest);
    }
    struct dirent *dir_struct;
    DIR* dir_stream;
    dir_stream=opendir(dest);
    if(dir_stream==NULL){
        printf("Cannot find directory\n");
        return ;
    }
    while(dir_struct=readdir(dir_stream)){
        if(!l){
            if(!a){
                if(is_dir(dir_struct->d_name)&&(dir_struct->d_name)[0]!='.')
                    printf("%s%s\n","\033[1;34m",dir_struct->d_name);
                else if((dir_struct->d_name)[0]!='.')
                    printf("%s%s\n","\033[0;32m",dir_struct->d_name);
            }
            else {
                if(is_dir(dir_struct->d_name))
                    printf("%s%s\n","\033[1;34m",dir_struct->d_name);
                else 
                    printf("%s%s\n","\033[0;32m",dir_struct->d_name);
            }
        }
        else {
            char temp[1024];
            strcpy(temp,dest);
            strcat(temp,"/");
            strcat(temp,dir_struct->d_name);
            execute_l(temp,dir_struct->d_name,a);
            // execute_l(temp,dir_struct->d_name,a);
        }
    }
    closedir(dir_stream);
}
