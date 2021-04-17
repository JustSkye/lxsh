#ifndef BUILTINS_H
#define BUILTINS_H
#include <string>
#include <vector>

extern std::string builtins[];
extern int (*builtins_f[]) (std::vector<std::string>);

int lxsh_help(std::vector<std::string> args);
int lxsh_exit(std::vector<std::string> args);
int lxsh_cd(std::vector<std::string> args);
int lxsh_pwd(std::vector<std::string> args);
int lxsh_echo(std::vector<std::string> args);

#endif
