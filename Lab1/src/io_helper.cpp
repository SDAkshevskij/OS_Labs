#include "../include/io_helper.h"
#include <ctype.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

char read_char(int &status) {
    char buffer[1];
    status = read(STDIN_FILENO, buffer, sizeof(char));
    return buffer[0];
}
std::string read_word(int *is_last) {
    std::string word = "";
    int status;
    char c;
    while((c = read_char(status)) != ' ' && c != '\n' && status == 1){
        word += c;
    }
    if(c == '\n' || status != 1) {
        *is_last = 1;
    }
    else{
        *is_last = 0;
    }
    return word;
}
std::string read_word(){
    int status;
    return read_word(&status);
}
double read_double(int *is_last) {
    std::string word;
    word = read_word(is_last);
    return atof(word.c_str());
}

void write_char(const char c) {
    char buffer[1] = {c};
    write(STDOUT_FILENO, buffer, sizeof(char));
}
void write_string(const std::string &str) {
    write(STDOUT_FILENO, str.c_str(), str.length() * sizeof(char));
}
void write_line(const std::string &line) {
    write_string(line);
    write_char('\n');
}
void reverse_string(std::string &str){
    for(int i = 0; i < str.length() / 2; i++){
        char buffer = str[i];
        str[i] = str[str.length() - i - 1];
        str[str.length() - i - 1] = buffer;
    }
}

std::string double_to_string(const double num){
    int intNum = (int)num;
    std::string intPart = "";
    if(num < 0){
        intNum = -intNum;
        intPart += '-';
    }
    while(intNum != 0){
        intPart += (intNum % 10) + '0';
        intNum /= 10;
    }
    reverse_string(intPart);
    int accuracy = 4;
    if(intPart == ""){
        intPart += '0';
    }
    double fractNum = abs(num) - (int)num;
    if(fractNum == 0) return intPart;
    intPart += '.';
    std::string fractPart = "";
    for(int i = 0; i < accuracy; i++){
        if(fractNum - (int)fractNum == 0){
            break;
        }
        fractNum *= 10;
        fractPart += (int)fractNum % 10 + '0';
    }
    return intPart + fractPart;
}
