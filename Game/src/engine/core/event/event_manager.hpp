#pragma once
#include "event.hpp"
#include "../types.hpp"
#include <functional>
#include <list>
#include <unordered_map>

namespace brown
{
    class event_manager
    {
    public:
        void add_listener(event_id id, std::function<void(event &)> const &listener)
        {
            listeners[id].push_back(listener);
        }

        void send_event(event &ev)
        {
            uint32_t type_ = ev.get_type();

            for (auto const &listener : listeners[type_])
            {
                listener(ev);
            }
        }

        void send_event(event_id &id)
        {
            event ev(id);

            for (auto const &listener : listeners[id])
            {
                listener(ev);
            }
        }

    private:
        std::unordered_map<event_id, std::list<std::function<void(event &)>>> listeners;
    };
}