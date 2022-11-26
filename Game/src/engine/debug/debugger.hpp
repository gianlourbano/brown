#pragma once
#include <string>
#include <iostream>
#include <fstream>

#define LOG(msg) brown::debug::log(msg, __FILE__)
#define ASSERT(check, msg) brown::debug::assert(check, msg, __FILE__, __LINE__, #check)
#define ERROR(msg) brown::debug::error(msg, __FILE__, __LINE__)

namespace brown::debug
{
    template <typename T>
    void log(T to_log, const char *file)
    {
        std::ofstream log_file("LOG.txt", std::ios::app);
        log_file << "[LOG] FILE: " << file << ": " << to_log << std::endl;
        log_file.close();
    }
    void assert(bool check, const std::string &message, const char *file, int line, const char *assertion);
    void error(const std::string &message, const char *file, int line);
}