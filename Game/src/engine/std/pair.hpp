#pragma once
#include <unistd.h>

namespace brown::dt
{
    template <typename A, typename B>
    class pair
    {
    public:
        A first;
        B second;

        pair() {}
        constexpr pair(const A &a, const B &b) : first(a), second(b) {}
        pair(const pair &other) : first(other.first), second(other.second) {}
        pair(pair &&other) noexcept = default;
        ~pair() = default;

        bool operator==(const pair &other) const
        {
            return first == other.first && second == other.second;
        }

        bool operator!=(const pair &other) const
        {
            return !(*this == other);
        }

        pair<A, B> &operator=(const pair<A, B> &other)
        {
            if (this == &other)
                return *this;

            this->first = other.first;
            this->second = other.second;
            return *this;
        }

        pair<A, B> &operator=(pair<A, B> &&other)
        {
            if (this == &other)
                return *this;

            this->first = std::move(other.first);
            this->second = std::move(other.second);
            return *this;
        }
    };

    template <typename A, typename B>
    pair<A, B> make_pair(const A &a, const B &b)
    {
        return pair<A, B>(static_cast<A>(a), static_cast<B>(b));
    }
}