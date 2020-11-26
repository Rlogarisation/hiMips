// silly program which creates a 1000-deep directory hierarchy

/*
z5206267@corelli:~/COMP1521/LectureFiles$ ./nest_directories 

Current directory now: /tmp_amd/reed/export/reed/1/z5206267/COMP1521/LectureFiles/d0

Current directory now: /tmp_amd/reed/export/reed/1/z5206267/COMP1521/LectureFiles/d0/d1

Current directory now: /tmp_amd/reed/export/reed/1/z5206267/COMP1521/LectureFiles/d0/d1/d2

Current directory now: /tmp_amd/reed/export/reed/1/z5206267/COMP1521/LectureFiles/d0/d1/d2/d3

Current directory now: /tmp_amd/reed/export/reed/1/z5206267/COMP1521/LectureFiles/d0/d1/d2/d3/d4

Current directory now: /tmp_amd/reed/export/reed/1/z5206267/COMP1521/LectureFiles/d0/d1/d2/d3/d4/d5

Current directory now: /tmp_amd/reed/export/reed/1/z5206267/COMP1521/LectureFiles/d0/d1/d2/d3/d4/d5/d6

Current directory now: /tmp_amd/reed/export/reed/1/z5206267/COMP1521/LectureFiles/d0/d1/d2/d3/d4/d5/d6/d7

Current directory now: /tmp_amd/reed/export/reed/1/z5206267/COMP1521/LectureFiles/d0/d1/d2/d3/d4/d5/d6/d7/d8

Current directory now: /tmp_amd/reed/export/reed/1/z5206267/COMP1521/LectureFiles/d0/d1/d2/d3/d4/d5/d6/d7/d8/d9
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>


int main(int argc, char *argv[]) {

    for (int i = 0; i < 10;i++) {
        char dirname[256];
        snprintf(dirname, sizeof dirname, "d%d", i);
        // Create a directory.
        if (mkdir(dirname, 0755) != 0) {
            perror(dirname);
            return 1;
        }
        // Move the current directory into new created directory.
        if (chdir(dirname) != 0) {
            perror(dirname);
            return 1;
        }
        // Access the information in the current directory.
        char pathname[1000000];
        if (getcwd(pathname, sizeof pathname) == NULL) {
            perror("getcwd");
            return 1;
        }
        // And print out the current directory.
        printf("\nCurrent directory now: %s\n", pathname);
    }

    return 0;
}