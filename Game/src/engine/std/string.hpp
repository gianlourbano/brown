#pragma once
#include "vector.hpp"
#include <iostream>

namespace brown::dt
{
    /**
     * @brief String class.
     *
     * String implementation using a dynamic array of characters
     *
     */
    class string : public vector<char>
    {
    public:
        static const size_t npos = -1;

        /**
         * @brief Construct a new string object
         *
         */
        string() = default;

        /**
         * @brief Construct a new string object
         *
         * @param str the string to copy
         */
        string(const char *str);

        /**
         * @brief Construct a new string object
         *
         * @param str the string to copy
         */
        string(const string &str);

        /**
         * @brief Construct a new string object
         *
         * @param str the string to copy
         */
        string(string &&str);

        /**
         * @brief Construct a new string object
         *
         * @param c++ std::string to copy
         */
        string(std::string);

        /**
         * @brief Destroy the string object
         *
         */
        ~string();

        friend string operator+(const char *str, string &s)
        {
            string ret(str);
            ret += s;
            return ret;
        }

        friend string operator+(const char *str, string &&s)
        {
            string ret(str);
            ret += s;
            return ret;
        }

        /**
         * @brief Copy assignment operator
         *
         * @param str the string to copy
         * @return string& the string
         */
        string operator=(const string &str);

        /**
         * @brief Move assignment operator
         *
         * @param str the string to move
         * @return string& the string
         */
        string operator=(string &&str);

        /**
         * @brief Concatenate a string
         *
         * @param str the string to concatenate
         * @return string& the string
         */
        string operator+=(const string &str);

        /**
         * @brief Concatenate a string
         *
         * @param str the string to concatenate
         * @return string the string
         */
        string operator+(const string &str);

        /**
         * @brief Concatenate a string
         *
         * @param str the string to concatenate
         * @return string& the string
         */
        string operator+=(const char *str);

        string operator+=(const std::string& str);

        /**
         * @brief Concatenate a string
         *
         * @param str the string to concatenate
         * @return string the string
         */
        string operator+(const char *str);

        /**
         * @brief Concatenate a string
         *
         * @param str the string to concatenate
         * @return string& the string
         */
        string operator+=(char c);

        bool operator==(const string &str) const;

        bool operator!=(const string &str) const { return !(*this == str); }

        friend std::ostream &operator<<(std::ostream &os, const string &str);
        friend std::istream& operator>>(std::istream& is, string& str);

        /**
         * @brief Transforms the string in a char
         *
         * @return The pointer to the c style string.
         */
        char *c_str();
    };

    template <typename T>
    string to_string(T &value)
    {
        string str;
        str += std::to_string(value);
        return str;
    }

    template <typename T>
    string to_string(T &&value)
    {
        string str;
        str += std::to_string(value);
        return str;
    }
}