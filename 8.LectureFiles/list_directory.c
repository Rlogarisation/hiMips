
/*
z5206267@corelli:~/COMP1521/LectureFiles$ ./list_directory ..
10093142 .git
10109474 lab08
10109181 LectureMipsData
10092661 LectureFloatingPoint
10109248 lab05
10109140 LectureMipsControl
10095124 lab01
10093000 lab07
10109636 blobby
10109312 mips_sim
10109137 lab04
10092917 test06
10109196 test04
10093086 test07
10109091 .vscode
10092570 LectureInteger
10109515 test08
10084353 ..
10092565 COMP1521_Summary.pdf
10092710 lab03
10092646 lab02
10092613 LectureBitwiseOperation
10093098 LectureFiles
10100751 test03
10109337 test05
10093019 LectureMipsFunction
10095121 .
10100769 LectureMipsBasics
10092759 tempCodeRunnerFile
*/
#include <stdio.h>
#include <dirent.h>

// list the contents of directories specified as command-line arguments
int main(int argc, char *argv[]) {

    for (int arg = 1; arg < argc; arg++) {
        DIR *dirp = opendir(argv[arg]);
        if (dirp == NULL) {
            perror(argv[arg]);  // prints why the open failed
            return 1;
        }

        struct dirent *de;

        while ((de = readdir(dirp)) != NULL) {
            printf("%ld %s\n", de->d_ino, de->d_name);
        }

        closedir(dirp);
    }
    return 0;
}