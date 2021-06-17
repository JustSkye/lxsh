#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#include "executor.h"
#include "../config.h"

namespace lxsh {
    executor::executor() { }
    executor::~executor() { }

    std::string executor::search_path(std::string program_name) {
        char* PATH = getenv("PATH");
        if (PATH == NULL)
            return "";

        char* p = PATH;
        char* p2;

        while (p && *p) {
            p2 = p;
            while (*p2 && *p2 != ':')
                p2++;

            int plen = p2 - p;
            if (!plen)
                plen = 1;

            int alen = strlen(program_name.c_str());
            char path[plen + 1 + alen + 1];

            strncpy(path, p, p2 - p);
            path[p2 - p] = '\0';

            if (p2[-1] != '/')
                strcat(path, "/");

            strcat(path, program_name.c_str());

            struct stat st;
            if (stat(path, &st) == 0) {
                if (!S_ISREG(st.st_mode)) {
                    p = p2;
                    if (*p2 == ':')
                        p++;
                    continue;
                }

                p = static_cast<char*>(malloc(strlen(path) + 1));
                if (!p)
                    return "";

                strcpy(p, path);
                return p;
            } else {
                p = p2;
                if (*p2 == ':')
                    p++;
            }
        }
        return "";
    }

    int executor::execute_command(std::vector<std::string> args) {
        std::string program_path = search_path(args[0]);

        if (program_path.empty()) {
            printf("lxsh: could not find '%s'\n", args[0].c_str());
            return 1;
        } else {
            #ifdef LXSH_DEBUG
            printf("lxsh debug: progam path = '%s'\n", program_path.c_str());
            #endif

            const char **argv = new const char* [args.size() + 1];
            for (u_int i = 0; i < args.size() + 1; ++i)
                argv[i] = args[i].c_str();
            argv[args.size()] = NULL;

            int status;
            pid_t pid = fork();
            if (pid == 0) {
                if (execvp(args[0].c_str(), (char **)argv) == -1) {
                    printf("lxsh: something broke\n");
                }
            } else if (pid < 0) {
                printf("lxsh: fork failed\n");
            } else {
                do {
                    waitpid(pid, &status, WUNTRACED);
                } while (!WIFEXITED(status) && !WIFSIGNALED(status));
            }
            return 1;
        }
    }
}

