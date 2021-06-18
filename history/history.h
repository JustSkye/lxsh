#ifndef HISTORY_H
#define HISTORY_H
#include <string>
#include <vector>

#include "../logger/logger.h"

namespace lxsh {
    class history {
    public:
        history(lxsh::logger logger);
        ~history();

        void save_line_to_session_history(std::string line);

        void save_session_history_to_file();

        std::string get_line_at(int index); 

        int get_history_length();
        int get_session_history_length();

    private:
        lxsh::logger logger;

        std::vector<std::string> session_history;
    };
}

#endif
