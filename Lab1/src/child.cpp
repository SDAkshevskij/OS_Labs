#include "../include/child.h"
#include "../include/io_helper.h"


int main(int argc, char* argv[]){
    if (argc != 2) {
        char er[] = "Usage: child <filename>\n";
        write(STDERR_FILENO, er, sizeof(er));
        exit(EXIT_FAILURE);
    }
    std::string inputFileName = std::string(argv[1]);
    int inputFileFD = open(inputFileName.c_str(), O_RDONLY);
    if(inputFileFD == -1){
        char er[] = "Cant open the file\n";
        write(STDERR_FILENO, er, sizeof(er));
        exit(EXIT_FAILURE);
    }
    dup2(inputFileFD, STDIN_FILENO);
    close(inputFileFD);
    int is_last = 0;
    double firstNum = read_double(&is_last);
    if(is_last) return 0;
    double secondNum;
    do {
        secondNum = read_double(&is_last);
        if(secondNum == 0){
            write_line("division by zero");
            return 0;
        }
        write_line(double_to_string(firstNum / secondNum));
    } while(!is_last);
    return 0;
}