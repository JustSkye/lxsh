#include <stdio.h>
#include <string>
#include <unistd.h>

#include "prompt.h"

namespace lxsh {
    prompt::prompt() { }
    prompt::~prompt() { }

    void prompt::print_ps1() {
        std::string current_dir(get_current_dir_name());
        std::string HOME(getenv("HOME"));

        size_t found_index = current_dir.find(HOME);
        if (found_index != std::string::npos) {
            current_dir.replace(found_index, std::string(HOME).size(), "~");
        }

        printf("[%s] > ", current_dir.c_str());
    }

    void prompt::print_ps2() {
        printf(">> ");
    }

    void prompt::print_ps3() {
        printf(">>> ");
    }

    void prompt::print_ps4() {
        printf(">>>> ");
    }
}

