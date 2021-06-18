#include "../config.h"
#include "logger.h"

namespace lxsh {
    logger::logger() { }
    logger::~logger() { }

    void logger::log(log_level level, std::string log_text) {
        switch (level) {
            case debug:
                #ifdef LXSH_DEBUG
                printf("lxsh debug: %s\n", log_text.c_str());
                #endif
                break;
            case error:
                printf("lxsh error: %s\n", log_text.c_str());
                break;
        }
    }
}

