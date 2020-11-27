// print all environment variables

// Environ is array of strings which contain the system information 
// for process.
// Some process wish to have all system information but we cannot input them all
// one by one, so that is what environ does.
// Environ can be set up by setenv(), and retrieve information by getenv().
#include <stdio.h>

int main(void) {
    // print all environment variables
    extern char **environ;

    for (int i = 0; environ[i] != NULL; i++) {
        printf("%s\n", environ[i]);
    }
}


/*
z5206267@corelli:~/COMP1521/LectureProcess$ ./environ 
cadPATH=/usr/local/cad/bin:/usr/local/cad/other/bin:/usr/local/cad/ucb/bin
MANPATH=/import/reed/1/z5206267/man:/usr/local/man:/usr/local/X11/man:/usr/man:/usr/share/man
TERM_PROGRAM=vscode
localPATH=/usr/local/bin
gnuMANPATH=/usr/local/gnu/man
TERM=xterm-256color
SHELL=/usr/local/bin/bash
AMD_ENTRYPOINT=vs/server/remoteExtensionHostProcess
SSH_CLIENT=125.209.159.146 59253 22
TERM_PROGRAM_VERSION=1.51.1
etcPATH=/usr/local/etc:/usr/etc:/etc:/sbin:/usr/sbin
USER=z5206267
shareMANPATH=/usr/local/share/man
sharePATH=/usr/local/share/bin-pc.amd64.linux:/usr/local/share/bin
sysMANPATH=/usr/man:/usr/share/man
x11PATH=/usr/local/X11/bin:/usr/bin/X11
PATH=/tmp_amd/reed/export/reed/1/z5206267/.vscode-server/bin/e5a624b788d92b8d34d1392e4c4d9789406efe8f/bin:/import/reed/1/z5206267/bin-pc.amd64.linux:/import/reed/1/z5206267/bin:/usr/local/bin:/usr/bin:/bin
MAIL=/import/reed/1/z5206267/.incoming-mail
LC_COLLATE=POSIX
PWD=/import/reed/1/z5206267/COMP1521/LectureProcess
localMANPATH=/usr/local/man
LANG=en_AU.UTF-8
USES_VSCODE_SERVER_SPAWN=true
PS1=${debian_chroot:+($debian_chroot)}\u@\h:\w\$ 
gnuPATH=/usr/local/gnu/bin
MAILDROP=/import/reed/1/z5206267/.incoming-mail
PS2=> 
HOME=/import/reed/1/z5206267
SHLVL=5
VSCODE_GIT_ASKPASS_MAIN=/tmp_amd/reed/export/reed/1/z5206267/.vscode-server/bin/e5a624b788d92b8d34d1392e4c4d9789406efe8f/extensions/git/dist/askpass-main.js
PIPE_LOGGING=true
XDG_CACHE_HOME=/var/tmp/cache-42487-8UMl7U
LOGNAME=z5206267
VSCODE_GIT_IPC_HANDLE=/tmp/vscode-git-5d95c85282.sock
SSH_CONNECTION=125.209.159.146 59253 129.94.242.48 22
VSCODE_IPC_HOOK_CLI=/tmp/vscode-ipc-ae8f4bb8-b527-404e-8a2d-171a0f1de4a1.sock
sysPATH=/usr/ucb:/usr/bin:/bin:/usr/ccs/bin
ARCH=pc.amd64.linux
VSCODE_GIT_ASKPASS_NODE=/tmp_amd/reed/export/reed/1/z5206267/.vscode-server/bin/e5a624b788d92b8d34d1392e4c4d9789406efe8f/node
GIT_ASKPASS=/tmp_amd/reed/export/reed/1/z5206267/.vscode-server/bin/e5a624b788d92b8d34d1392e4c4d9789406efe8f/extensions/git/dist/askpass.sh
x11MANPATH=/usr/local/X11/man:/usr/X11R6/man
VERBOSE_LOGGING=true
COLORTERM=truecolor
_=./environ
OLDPWD=/import/reed/1/z5206267/COMP1521
DCC_SANITIZER=ADDRESS
DCC_PATH=/tmp_amd/adams/export/adams/1/cs1911/bin/dcc
DCC_PID=108081
DCC_BINARY=/tmp_amd/reed/export/reed/1/z5206267/COMP1521/LectureProcess/environ
DCC_UNLINK=/tmp/dcc-iCbTw5
DCC_SANITIZER1_PID=108081
DCC_SANITIZER2_PID=108082
*/