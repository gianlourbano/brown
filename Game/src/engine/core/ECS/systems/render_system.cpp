#include "render_system.hpp"
#include "../components/transform.hpp"
#include "../components/animation.hpp"

#include "../../../graphics/window/window.hpp"
#include <dirent.h>
#include <cstring>
#include <unordered_map>

sprite_data GLOBAL_SPRITES_paths{};
std::unordered_map<std::string, sprite_data> GLOBAL_SPRITES{};
std::string sprites_path = "./src/assets/sprites/";

std::shared_ptr<brown::render_system> brown::render_system::register_system(brown::brain *br)
{
    std::shared_ptr<brown::render_system> sys = br->register_system<brown::render_system>();
    signature signature;
    signature.set(br->get_component_type<transform>());
    signature.set(br->get_component_type<animation>());
    signature.set(br->get_component_type<sprite>());
    br->set_system_signature<brown::render_system>(signature);
    return sys;
}

void brown::render_system::init()
{
    DIR *dir;
    struct dirent *ent;
    ASSERT((dir = opendir(sprites_path.c_str())) != NULL, "Could not open sprites folder!\n");
    while ((ent = readdir(dir)) != NULL)
    {
        if (strcmp(ent->d_name, ".") && strcmp(ent->d_name, ".."))
        {
            std::string name(ent->d_name);
            if (name.find(".spr") || name.find(".aspr"))
                GLOBAL_SPRITES_paths.push_back(name);
        }
    }
    closedir(dir);

    for (auto &spr : GLOBAL_SPRITES_paths)
    {
        if (spr.find(".spr") != std::string::npos)
        {
            sprite_data m_data = brown::load_sprite(spr);
            GLOBAL_SPRITES.insert({spr.substr(0, spr.find(".spr")), m_data});
        }
        else if (spr.find(".aspr") != std::string::npos)
        {
            std::vector<sprite_data> m_data = brown::load_animated_sprite(spr);
            std::string temp = spr;
            int j = 0;
            for (auto &d : m_data)
            {
                GLOBAL_SPRITES.insert({temp.substr(0, temp.find(".aspr")).append(std::to_string(j)), d});
                j++;
            }
        }
    }
}

void brown::render_system::draw(WINDOW *win, brown::brain *br)
{
    for (auto &entity : m_entities)
    {
        auto &trans = br->get_component<transform>(entity);
        auto &spr = br->get_component<sprite>(entity);
        auto &anim = br->get_component<animation>(entity);

        if (anim.clips != 0 && anim.playing)
            graphics::mvwprintvcolors(win, trans.position.y - anim.offset.y, trans.position.x - anim.offset.x, true, GLOBAL_SPRITES[anim.name + std::to_string(anim.current)]);
        else
            graphics::mvwprintvcolors(win, trans.position.y, trans.position.x, true, GLOBAL_SPRITES[spr.sprite_name]);
    }
}

std::vector<sprite_data> brown::load_animated_sprite(std::string name)
{
    std::ifstream asprite_(sprites_path + name);
    std::vector<sprite_data> m_data;
    std::string line1;
    sprite_data frame;
    while (std::getline(asprite_, line1))
    {
        if (line1.find("frame") != std::string::npos)
        {
            m_data.push_back(frame);
            frame.clear();
        }
        else
        {
            frame.push_back(line1);
        }
    }
    asprite_.close();
    return m_data;
}

sprite_data brown::load_sprite(std::string name)
{
    std::ifstream sprite_(sprites_path + name);
    sprite_data m_data;
    std::string line1;

    while (std::getline(sprite_, line1))
    {
        m_data.push_back(line1);
    }

    sprite_.close();
    return m_data;
}