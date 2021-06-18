#include <stdio.h>
#include <unistd.h>

#include "builtins.h"

namespace lxsh {
    builtins::builtins(lxsh::logger logger) {
        this->logger = logger;

        _builtins["help"] = lxsh_help;
        _builtins["exit"] = lxsh_exit;
        _builtins["cd"] = lxsh_cd;
        _builtins["pwd"] = lxsh_pwd;
    }

    builtins::~builtins() { }

    bool builtins::check_if_builtin(std::string command) {
        for (std::pair<std::string, _builtin_pointer> pair : _builtins) {
            if (command == pair.first) {
                return true;
            }
        }
        return false;
    }

    int builtins::execute_builtin(std::vector<std::string> args) {
        logger.log(logger.debug, "builtin command detected");
        return _builtins[args[0]](args);
    }

    int builtins::lxsh_help(std::vector<std::string> args) {
        if (args.size() <= 1) {
            printf("lxsh builtins:\n"
                   "help [command_name] : Show this help or help for a specific command\n"
                   "exit                : Exit the shell\n"
                   "cd [dir]            : Change directory\n"
                   "pwd                 : Print working directory\n");
        } else {
            std::string command_name = args[1];
            if (command_name == "exit") {
                printf("lxsh: exit: Exits the shell. Takes no arguments.\n");
            } else if (command_name == "cd") {
                printf("lxsh: cd: Changes directory. If no directory is given, default to users home (if available).\n");
            } else if (command_name == "pwd") {
                printf("lxsh pwd: Prints working directory. Takes no arguments.\n");
            } else {
                printf("lxsh: No help is available for the given command.\n");
            }
        }
        return 1;
    }

    int builtins::lxsh_exit(std::vector<std::string> args) {
        return 0;
    }

    int builtins::lxsh_cd(std::vector<std::string> args) {
        if (args.size() <= 1) {
            if (chdir(getenv("HOME")) != 0) {
                printf("lxsh: 'cd' apparently no home is set for the current user\n");
            }
        } else if (args.size() > 2) {
            printf("lxsh: 'cd' only expects one argument\n");
        } else {
            if (chdir(args[1].c_str()) != 0) {
                printf("lxsh: 'cd' didn't find the given directory\n");
            }
        }
        return 1;
    }

    int builtins::lxsh_pwd(std::vector<std::string> args) {
        printf("%s\n", get_current_dir_name());
        return 1;
    }
}

