#pragma once
#include <string>
#include <iostream>
#include <fstream>

#define LOG(msg) brown::debug::log(msg, __FILE__)
#define ASSERT(check, msg) brown::debug::assert(check, msg, __FILE__, __LINE__, #check)
#define ERROR(msg) brown::debug::error(msg, __FILE__, __LINE__)

namespace brown::debug {
    void log(const std::string &message, const char *file);
    void assert(bool check, const std::string &message, const char *file, int line, const char *assertion);
    void error(const std::string &message, const char *file, int line);
}