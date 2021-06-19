#include <fstream>
#include <sys/stat.h>
#include <unistd.h>

#include "history.h"

namespace lxsh {
    history::history(lxsh::logger logger) { 
        this->logger = logger;
    }
    history::~history() { }

    void history::save_line_to_session_history(std::string line) {
        session_history.push_back(line);
    }

    void history::save_session_history_to_file() { 
        logger.log(logger.debug, "attempting to save session history to file");
       
        std::string HOME = getenv("HOME");
        std::string lxsh_history_location = HOME + "/.lxsh_history";

        struct stat buffer;   
        if (stat (lxsh_history_location.c_str(), &buffer) == 0) {
            logger.log(logger.debug, "~/.lxsh_history exists");
        } else {
            logger.log(logger.debug, "~/.lxsh_history does not exsist, will be created");
        }

        std::ofstream lxsh_history(lxsh_history_location, std::fstream::app);

        for (std::string entry : session_history) {
            lxsh_history << entry << "\n";
        }

        lxsh_history.close();
    }

    std::string history::get_line_at(int index) { 
        if (session_history.size() >= index) {
            return session_history[index];
        } else {
            return nullptr;
        }
    }
 
    int history::get_history_length() {
        std::string HOME = getenv("HOME");
        std::string lxsh_history_location = HOME + "/.lxsh_history";
        
        std::string line;
        int history_length = 0;
        
        std::ifstream lxsh_history(lxsh_history_location);

        while (getline (lxsh_history, line)) { 
            history_length++;
        }

        lxsh_history.close();

        history_length += get_session_history_length();

        logger.log(logger.debug, "history length = '" + std::to_string(history_length) + "'");
        return history_length;
    }

    int history::get_session_history_length() {
        int session_history_length = session_history.size();
        logger.log(logger.debug, "session history length = '" + std::to_string(session_history_length) + "'");
        return session_history_length;
    }
}

