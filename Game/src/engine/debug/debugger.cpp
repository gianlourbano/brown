#include "debugger.hpp"

namespace brown::debug
{
    void log(const std::string &message, const char *file)
    {
        std::ofstream log_file("LOG.txt", std::ios::app);
        log_file << "[LOG] FILE: " << file << ": " << message << std::endl;
        log_file.close();
    }

    void assert(bool check, const std::string &message, const char *file, int line, const char *assertion)
    {
        if (!check)
        {
            std::ofstream log_file("LOG.txt", std::ios::app);
            log_file << "[ASSERT] FILE: " << file << ", at line: " << line << ": " << message << " (" << assertion << ")" <<std::endl;
            log_file.close();
            exit(1);
        }
    }

    void error(const std::string &message, const char *file, int line)
    {
        std::ofstream log_file("LOG.txt", std::ios::app);
        log_file << "[ERROR] FILE: " << file << ", at line: " << line << ": " << message << std::endl;
        log_file.close();
        exit(1);
    }
}