#include "string.hpp"
#include <cstring>

namespace brown::dt
{

    string::string(const char *str)
    {
        size_t i = 0;
        while (str[i] != '\0')
            i++;
        this->resize(i + 1);
        for (size_t j = 0; j < i; j++)
            this->push_back(str[j]);
    }

    string::string(const string &str)
    {
        this->resize(str.size());
        for (size_t i = 0; i < str.size(); i++)
            this->push_back(str[i]);
    }

    string::string(string &&str)
    {
        this->resize(str.size());
        for (size_t i = 0; i < str.size(); i++)
            this->push_back(str[i]);
    }

    string::string(std::string str)
    {
        this->resize(str.size());
        for (size_t i = 0; i < str.size(); i++)
            this->push_back(str[i]);
    }

    string::~string()
    {
        this->clear();
    }

    string string::operator=(const string &str)
    {
        if (this == &str)
            return *this;
        this->clear();
        this->resize(str.size());
        for (size_t i = 0; i < str.size(); i++)
            this->push_back(str[i]);
        return *this;
    }

    string string::operator=(string &&str)
    {
        if (this == &str)
            return *this;
        this->clear();
        this->resize(str.size());
        for (size_t i = 0; i < str.size(); i++)
            this->push_back(str[i]);
        return *this;
    }

    string string::operator+(const string &str)
    {
        string ret;
        ret.resize(this->size() + str.size());
        for (size_t i = 0; i < this->size(); i++)
            ret.push_back((*this)[i]);
        for (size_t i = 0; i < str.size(); i++)
            ret.push_back(str[i]);
        return ret;
    }

    string string::operator+(const char *str)
    {
        string ret;
        size_t i = 0;
        while (str[i] != '\0')
            i++;
        ret.resize(this->size() + i);
        for (size_t j = 0; j < this->size(); j++)
            ret.push_back((*this)[j]);
        for (size_t j = 0; j < i; j++)
            ret.push_back(str[j]);
        return ret;
    }

    std::ostream &operator<<(std::ostream &os, const string &str)
    {
        for (size_t i = 0; i < str.size(); i++)
            os << str[i];
        return os;
    }

    std::istream &operator>>(std::istream &is, string &str)
    {
        char c;
        while (is >> c)
            str.push_back(c);
        return is;
    }

    bool string::operator==(const string &str) const
    {
        if (this->size() != str.size())
            return false;
        for (size_t i = 0; i < this->size(); i++)
            if ((*this)[i] != str[i])
                return false;
        return true;
    }

    string string::operator+=(const string &str)
    {
        this->resize(this->size() + str.size());
        for (size_t i = 0; i < str.size(); i++)
            this->push_back(str[i]);
        return *this;
    }

    string string::operator+=(const char *str)
    {
        size_t i = 0;
        while (str[i] != '\0')
            i++;
        this->resize(this->size() + i);
        for (size_t j = 0; j < i; j++)
            this->push_back(str[j]);
        return *this;
    }

    string string::operator+=(const char c)
    {
        this->push_back(c);
        return *this;
    }

    string string::operator+=(const std::string &str)
    {
        this->resize(this->size() + str.size());
        for (size_t i = 0; i < str.size(); i++)
            this->push_back(str[i]);
        return *this;
    }

    char *string::c_str()
    {
        char *ret = new char[this->size() + 1];
        strncpy(ret, this->data(), this->size());
        ret[this->size()] = '\0';
        return ret;
    }
}