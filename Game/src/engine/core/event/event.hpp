#pragma once
#include "../types.hpp"
#include <any>
#include <unordered_map>

namespace brown
{
    class event
    {
    public:
        event() = delete;

        explicit event(event_id type) : m_type(type){};

        template <typename T>
        void set_param(event_id id, T value)
        {
            m_data[id] = value;
        }

        template <typename T>
        T get_param(event_id id)
        {
            return std::any_cast<T>(m_data[id]);
        }

        event_id get_type() const { return m_type; };

    private:
        event_id m_type{};
        std::unordered_map<event_id, std::any> m_data{};
    };
}