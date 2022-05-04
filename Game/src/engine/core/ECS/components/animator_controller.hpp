#pragma once
#include "animation.hpp"
#include <string>
#include <unordered_map>

struct animator_controller
{

    void set_anim(std::string anim_name)
    {
        ASSERT(anims.find(anim_name) != anims.end(), "Invalid animation!");
        current_anim = &anims[anim_name];
    }

    void play_current()
    {
        current_anim->playing = true;
    }

    void play(std::string anim_name, std::function<void()> callback)
    {
        if (!anims[anim_name].playing)
        {
            set_anim(anim_name);
            play_current();
        } else if(anims[anim_name].has_finished)
            callback();
    }

    void play(std::string anim_name)
    {
        if (!anims[anim_name].playing)
        {
            set_anim(anim_name);
            play_current();
        }
    }

    void add_anim(std::string anim_name, animation anim)
    {
        anims.insert(std::make_pair(anim_name, anim));
        if (current_anim == nullptr)
            current_anim = &anims[anim_name];
    }

    animation *current_anim = nullptr;
    std::unordered_map<std::string, animation> anims;
};