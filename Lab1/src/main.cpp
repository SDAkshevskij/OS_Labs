#include <vector>
#include <string>
#include "../include/io_helper.h"
#include <ctype.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    std::string inputFileName;
    inputFileName = read_word();
    
    int pipe1[2]; //Child -> parent
        if(pipe(pipe1) == -1){
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    int processId = fork();
    if(processId == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if(processId > 0){ //parent
        close(pipe1[1]);
        char buf[4096];
        int bytes;
        while(bytes = read(pipe1[0], buf, sizeof(buf))){
            if(bytes < 0){
                char er[] = "failed to read from pipe1!\n";
                write(STDERR_FILENO, er, sizeof(er));
                exit(EXIT_FAILURE);
            }
            // char test[] = "parent output\n";
            // write(STDOUT_FILENO, test, sizeof(test));
            write(STDOUT_FILENO, buf, bytes);
        }
        close(pipe1[0]);
        wait(NULL);
    }
    else { // child
        close(pipe1[0]);
        dup2(pipe1[1], STDOUT_FILENO);
        execl("child", "child", inputFileName.c_str(), NULL);
        char er[] = "execl call failed!\n";
        write(STDERR_FILENO, er, sizeof(er));
        exit(EXIT_FAILURE);
    }
}
