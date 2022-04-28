#pragma once

namespace brown::std
{
    template <typename A, typename B>
    class pair
    {
        A first;
        B second;

        pair() = delete;

        pair(A a, B b) : first(a), second(b){};

        bool operator==(pair<A, B> cmp) const
        {
            return cmp.first == this->first && cmp.second == this->second;
        }

        bool operator!=(pair<A, B> cmp) const { return !operator==(cmp); }

        pair<A, B> &operator=(const pair<A, B> &other)
        {
            if (this == &other)
                return *this;
            this->first = other.first;
            this->second = other.second;
            return *this;
        }

        friend std::ostream &operator<<(std::ostream &os, const pair<A, B> &pair)
        {
            return os << '(' << pair.first << ',' << pair.second << ')';
        }
    };
};
