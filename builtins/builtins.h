#ifndef BUILTINS_H
#define BUILTINS_H
#include <map>
#include <string>
#include <vector>

namespace lxsh {

    class builtins {
    public:
        builtins();
        ~builtins();

        bool check_if_builtin(std::string command);
        int execute_builtin(std::vector<std::string> args);

        static int lxsh_help(std::vector<std::string> args);
        static int lxsh_exit(std::vector<std::string> args);
        static int lxsh_cd(std::vector<std::string> args);
        static int lxsh_pwd(std::vector<std::string> args);
    
    private:
        typedef int (*_builtin_pointer) (std::vector<std::string>);
        std::map<std::string, _builtin_pointer> _builtins;
    };
}

#endif
