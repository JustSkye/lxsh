#ifndef EXECUTOR_H
#define EXECUTOR_H
#include <string>
#include <vector>

std::string search_path(std::string program_name);
int execute_command(std::vector<std::string> args);

#endif
