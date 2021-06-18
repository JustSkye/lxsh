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
        // TODO: Check if ~/.lxsh_history exists, if not, create it.
        // TODO: Write each line in session_history to file.
    }

    std::string history::get_line_at(int index) { 
        if (session_history.size() >= index) {
            return session_history[index];
        } else {
            return nullptr;
        }
    }
 
    int history::get_history_length() {
        // TODO: Length of session history PLUS file history
    }

    int history::get_session_history_length() { 
        return session_history.size();
    }
}

