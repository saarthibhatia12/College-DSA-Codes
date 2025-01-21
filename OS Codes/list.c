#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <wait.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>

int main(){
    DIR*d;
    struct dirent *de;
    struct stat buf;
    struct passwd *p;
    struct group *g;
    int i,j;
    char P[10]="rwxrwxrwx", AP[10];
    d=opendir(".");
    readdir(d);
    readdir(d);
    while((de=readdir(d))!=NULL){
        stat(de->d_name,&buf);
        if(S_ISDIR(buf.st_mode))
            printf("d");
        else if(S_ISREG(buf.st_mode))
            printf("-");
        else if(S_ISLNK(buf.st_mode))
            printf("l");

        else if(S_ISCHR(buf.st_mode))
            printf("c");
        else if(S_ISBLK(buf.st_mode))
            printf("b");
        else if(S_ISFIFO(buf.st_mode))
            printf("p");
        else if(S_ISSOCK(buf.st_mode))
            printf("s");
    }
    for(i=0,j=1<<8;i<9;i++,j>>=1)
        AP[i]=buf.st_mode&j?P[i]:'-';
    AP[i]='\0';
    printf("%s",AP);
    printf("%d",buf.st_nlink);
    p=getpwuid(buf.st_uid);
    printf("%s",p->pw_name);
    g=getgrgid(buf.st_gid);
    printf("%s",g->gr_name);
    printf("%d",buf.st_size);

    printf("%s",de->d_name);
    return 0;
}
