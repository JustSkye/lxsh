#include <iostream>
#include <sstream>

#include "logger/logger.h"
#include "prompt/prompt.h"
#include "builtins/builtins.h"
#include "executor/executor.h"

#include "config.h"

// TODO: Start alias system
std::map<std::string, std::string> aliases;

std::string read_line();
std::vector<std::string> split_line(std::string const& line);
int parse_and_execute(std::vector<std::string> args, lxsh::executor& executor, lxsh::builtins& builtins);

std::string read_line() {
    std::string line;
    getline(std::cin, line);

    return line;
}

std::vector<std::string> split_line(std::string const& line) {
    std::vector<std::string> args;

    std::stringstream ln(line);
    std::string arg;
    while (ln >> arg) {
        if (arg == "~") {
            arg = getenv("HOME");
        }
        args.push_back(arg);
    }

    return args;
}

int parse_and_execute(std::vector<std::string> args, lxsh::executor& executor, lxsh::builtins& builtins) {
    if (args.empty()) {
        return 1;
    }
    
    if (builtins.check_if_builtin(args[0])) {
        return builtins.execute_builtin(args);
    }

    return executor.execute_command(args);
}

int main(int argc, char **argv) {
    lxsh::logger logger;
    lxsh::prompt prompt;
    lxsh::executor executor(logger);
    lxsh::builtins builtins(logger);

    std::string line;
    std::vector<std::string> args;
    int status = 1;
    
    logger.log(logger.debug, "initialized");

    do {
        /* Print PS1 */
        prompt.print_ps1();

        /* Read user input, the 'line' */
        line = read_line();
        logger.log(logger.debug, "line = '" + line + "'");

        /* Assign the values that split_line() returns to 'args' */
        split_line(line).swap(args);

        /* Give 'args' to the parser, which will give them to the executor */
        status = parse_and_execute(args, executor, builtins);

        /* Clear 'line' */
        line = "";

        /* Clear 'args' */
        args.clear();
    } while (status);

	return EXIT_SUCCESS;
}

