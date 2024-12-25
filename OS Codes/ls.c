#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

int main() {
  DIR *d;             // Directory pointer
  struct dirent *de;  // Structure to hold directory entry
  struct stat buf;    // Structure to hold file metadata

  d = opendir(".");  // Open current directory
  if (d == NULL) {
    perror("opendir failed");  // Handle errors if directory can't be opened
    return 1;
  }

  readdir(d);  // Skip "." (current directory)
  readdir(d);  // Skip ".." (parent directory)

  while ((de = readdir(d)) != NULL) {  // Loop through directory entries
    stat(de->d_name, &buf);            // Get file details

    // 1. File Type
    if (S_ISDIR(buf.st_mode))
      printf("d");
    else if (S_ISREG(buf.st_mode))
      printf("-");
    else if (S_ISCHR(buf.st_mode))
      printf("c");
    else if (S_ISBLK(buf.st_mode))
      printf("b");
    else if (S_ISLNK(buf.st_mode))
      printf("l");
    else if (S_ISFIFO(buf.st_mode))
      printf("p");
    else if (S_ISSOCK(buf.st_mode))
      printf("s");

    // 2. Permissions (rwxrwxrwx)
    char rwx[] = "rwxrwxrwx";      // Full permission string
    char perms[10] = "---------";  // Default no permissions
    for (int i = 0; i < 9; i++) {
      if (buf.st_mode & (1 << (8 - i))) {  // Check permission bit
        perms[i] = rwx[i];                 // Set corresponding rwx
      }
    }
    printf("%s", perms);

    // 3. Number of Links
    printf(" %lu", buf.st_nlink);

    // 4. User and Group Names
    struct passwd *p = getpwuid(buf.st_uid);  // Get owner name
    struct group *g = getgrgid(buf.st_gid);   // Get group name
    printf(" %s %s", p->pw_name, g->gr_name);

    // 5. File Size
    printf(" %ld", buf.st_size);

    // 6. Last Modification Time
    char time[20];
    struct tm *t = localtime(&buf.st_mtime);         // Convert time
    strftime(time, sizeof(time), "%b %d %H:%M", t);  // Format time
    printf(" %s", time);

    // 7. File Name
    printf(" %s\n", de->d_name);
  }

  closedir(d);  // Close the directory
  return 0;
}
