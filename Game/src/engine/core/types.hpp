#pragma once
#include <bitset>
#include <cstdint>

// Source: https://gist.github.com/Lee-R/3839813
inline constexpr std::uint32_t fnv1a_32(char const *s, std::size_t count)
{
    return count ? (fnv1a_32(s, count - 1) ^ s[count - 1]) * 16777619u : 2166136261u;
}

constexpr std::uint32_t operator"" _hash(char const *s, std::size_t count)
{
    return fnv1a_32(s, count);
}

using entity_id = std::uint32_t;
const entity_id MAX_ENTITIES = 5000;
using component_type = std::uint8_t;
const component_type MAX_COMPONENTS = 32;
using signature = std::bitset<MAX_COMPONENTS>;

enum class input_buttons
{
    W,
    A,
    S,
    D,
    H,
    J,
    K,
    U,
};

// Events
using event_id = std::uint32_t;
using param_id = std::uint32_t;

#define METHOD_LISTENER(EventType,name, Listener) EventType,name, std::bind(&Listener, this, std::placeholders::_1)
#define FUNCTION_LISTENER(EventType,name, Listener) EventType,name, std::bind(&Listener, std::placeholders::_1)

namespace Events::Window
{
    const event_id QUIT = "Events::Window::QUIT"_hash;
    const event_id INPUT = "Events::Window::INPUT"_hash;
}

namespace Events::Window::Input
{
    const param_id INPUT = "Events::Window::Input::INPUT"_hash;
}

#define EVENT_ID(category, name) const event_id name = "Events::##category::##name"_hash;
#define EVENT_PARAM_ID(category, name) const param_id name = "Events::##category::##name"_hash;

