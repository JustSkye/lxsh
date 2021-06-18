#ifndef EXECUTOR_H
#define EXECUTOR_H
#include <string>
#include <vector>

#include "../logger/logger.h"

namespace lxsh {
    class executor {
    public:
        executor(lxsh::logger logger);
        ~executor();

        std::string search_path(std::string program_name);
        int execute_command(std::vector<std::string> args);
    
    private:
        lxsh::logger logger;
    };
}

#endif
