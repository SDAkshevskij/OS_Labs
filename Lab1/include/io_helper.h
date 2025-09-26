#ifndef IO_HELPER_H
#define IO_HELPER_H

#include <string>

char read_char();
std::string read_word(int *is_last);
std::string read_word();
double read_double(int *is_last);

void write_char(const char c);
void write_string(const std::string &str);
void write_line(const std::string &line);

void reverse_string(std::string &str);
std::string double_to_string(const double num);


#endif