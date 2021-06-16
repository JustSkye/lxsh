#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <sstream>
#include <map>
#include <vector>
#include <unistd.h>

#include "prompt/prompt.h"
#include "builtins/builtins.h"
#include "executor/executor.h"

#include "config.h"

// TODO: Start alias system
std::map<std::string, std::string> aliases;

std::string read_line();
std::vector<std::string> split_line(std::string const& line);
int parse_and_execute(std::vector<std::string> args);

std::string read_line() {
    std::string line;
    getline(std::cin, line);

    #ifdef LXSH_DEBUG
	printf("lxsh debug: line = '%s'\n", line.c_str());
    #endif

    return line;
}

std::vector<std::string> split_line(std::string const& line) {
    u_int arg_count;
    if (line.empty() || line.back() == ' ')
        arg_count = 0;
    else
        arg_count = 1;

    for (u_int i = line.size(); i > 0; --i) {
        if (line[i] == ' ' && line[i - 1] != ' ') {
            ++arg_count;
        }
    }

    #ifdef LXSH_DEBUG
	printf("lxsh debug: arg_count = '%u'\n", arg_count);
    #endif

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

int parse_and_execute(std::vector<std::string> args) {
    if (args.empty()) {
        return 1;
    }

    /* This looks weird and feels wrong, but it works */
    for (u_int i = 0; i < (sizeof(*builtins) / sizeof(std::string*) + 1); i++) {
        if (strcmp(args[0].c_str(), builtins[i].c_str()) == 0) {
            #ifdef LXSH_DEBUG
            printf("lxsh debug: builtin function detected\n");
            #endif
            return (*builtins_f[i]) (args);
        }
    }

    #ifdef LXSH_DEBUG
    printf("lxsh debug: non-builtin command detected\n");
    #endif

    return execute_command(args);
}

int main(int argc, char **argv)
{
    std::string line;
    std::vector<std::string> args;
    int status = 1;

    #ifdef LXSH_DEBUG
	printf("lxsh debug: initialized\n");
    #endif

    do {
        /* Print PS1 */
        print_ps1();

        /* Read user input, the 'line' */
        line = read_line();

        /* Assign the values that split_line() returns to 'args' */
        split_line(line).swap(args);

        #ifdef LXSH_DEBUG
        if (!args.empty()) {
            printf("lxsh debug: args[0] = '%s'\n", args[0].c_str());
        } else {
            printf("lxsh debug: input was empty\n");
        }
        #endif

        /* Give 'args' to the parser, which will give them to the executor */
        status = parse_and_execute(args);

        /* Clear 'line' */
        line = "";

        /* Clear 'args' */
        args.clear();
    } while (status);

	return EXIT_SUCCESS;
}
