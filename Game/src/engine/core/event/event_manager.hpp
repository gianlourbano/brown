#pragma once
#include "event.hpp"
#include "../types.hpp"
#include <functional>
#include <list>
#include <unordered_map>
#include <string>

namespace brown
{
    struct event_listener
    {
        std::string m_name;
        std::function<void(event &)> listener;

        bool operator==(event_listener& e1) {
            return this->m_name == e1.m_name;
        }

        bool operator!=(event_listener& e1) {
            return this->m_name != e1.m_name;
        }
    };

    class event_manager
    {
    public:
        void add_listener(event_id id, std::string name, std::function<void(event &)> const &listener)
        {
            listeners[id].push_back({name, listener});
        }

        void remove_event_listener(event_id id, std::string name)
        {
            listeners[id].remove_if([name](event_listener l) {return l.m_name == name;});
        }

        void send_event(event &ev)
        {
            uint32_t type_ = ev.get_type();

            for (auto const &listener : listeners[type_])
            {
                listener.listener(ev);
            }
        }

        void send_event(event_id &id)
        {
            event ev(id);

            for (auto const &listener : listeners[id])
            {
                listener.listener(ev);
            }
        }

    private:
        std::unordered_map<event_id, std::list<event_listener>> listeners;
    };
}