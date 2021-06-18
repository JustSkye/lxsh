#ifndef LOGGER_H
#define LOGGER_H
#include <string>

namespace lxsh {
    class logger {
    public:
        enum log_level {
            debug,
            error
        };

        logger();
        ~logger();

        void log(log_level level, std::string log_text);
    };
}

#endif
