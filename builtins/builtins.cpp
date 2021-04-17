#include "builtins.h"
#include <stdio.h>
#include <string>
#include <unistd.h>
#include <vector>

std::string builtins[] = {
    "help",
    "exit",
    "cd",
    "pwd",
    "echo",
};

int (*builtins_f[]) (std::vector<std::string>) = {
    &lxsh_help,
    &lxsh_exit,
    &lxsh_cd,
    &lxsh_pwd,
    &lxsh_echo,
};

int lxsh_help(std::vector<std::string> args) {
    printf("lxsh builtins:\n");
    for(std::string arg : builtins)
        printf("%s\n", arg.c_str());
    return 1;
}

int lxsh_exit(std::vector<std::string> args) {
    return 0;
}

int lxsh_cd(std::vector<std::string> args) {
    if (args.size() <= 1)
        printf("lxsh: 'cd' expects an argument\n"); // TODO: this shouldn't actually be the case. If no directory is given, it should default to the users home
    else if (args.size() > 2)
        printf("lxsh: 'cd' only expects one argument\n");
    return 1;
}

int lxsh_pwd(std::vector<std::string> args) {
    printf("%s\n", get_current_dir_name());
    return 1;
}

int lxsh_echo(std::vector<std::string> args) {
    if (args.size() <= 1) {
        return 1;
    } else {
        args.erase(args.begin());
        for(std::string arg : args)
            printf("%s ", arg.c_str());
        printf("\n");
        return 1;
    }
}
