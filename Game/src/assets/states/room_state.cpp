#include "room_state.hpp"
#include "assets/scripts/door_controller.hpp"
#include "assets/scripts/boss_door_controller.hpp"

void room_state::generate_doors(tilemap &tm)
{
    world_generator::floorplan fp = data.world_gen->get_current_floorplan();

    int dir = data.direction;

    animation opened_horizontal = {
        "animated_horizontal_door",
        {0, 0},
        6,
        10,
        false,
        true};

    animation opened_vertical = {
        "animated_vertical_door",
        {0, 0},
        4,
        20,
        false,
        true};

    vec2 positions[4] = {
        {8 * TILE_SIZE, 0 },
        {0, 4 * TILE_SIZE},
        {8 * TILE_SIZE, 4 * TILE_SIZE},
        {4 * TILE_SIZE, 0}};

    int fps[4] = {
        fp[data.id - 10],
        fp[data.id - 1],
        fp[data.id + 1],
        fp[data.id + 10]
        };
        
    vec2 tiles[4] = {
        {3, 0},
        {16, 2},
        {8, 5},
        {0, 2}
    };

    int tiles_ids[4] = {
        8, 12, 3, 13
    };
    
    // for(int i = 0; i < 4; i++) {
    //     if(fps[i]) {
    //         auto door = create_entity("door_" + std::to_string(i));
    //         door.add_component<transform>({offset + positions[i]});
    //         door.add_component<sprite>({{3, 2}, "door1"});
    //         door.add_component<animator_controller>({});

    //         animator_controller *anim = &door.get_component<animator_controller>();
    //         anim->add_anim("open", opened_vertical);

    //         if (fps[i] == ROOM_TYPE::BOSS || fps[i] == ROOM_TYPE::BOSS_UNDISCOVERED)
    //             door.add_component<native_script>({}).bind<boss_door_controller>(door_data(data.world_gen->get_room_for_current_world(data.id + 1), this, data.id + 1, i % 2 == 1, dir == i+1, (i+1)%4 + 2) % 4));
    //         else
    //             door.add_component<native_script>({}).bind<door_controller>(door_data(data.world_gen->get_room_for_current_world(data.id + 1), this, data.id + 1, i % 2 == 1, dir == i+1, (i+1)%4 + 2) % 4);

    //         tm.m_data.at(tiles[i].x, tiles[i].y) = tiles_ids[i];
    //     }
    // }

    if (fp[data.id - 10])
    {
        auto door = create_entity("door_1");
        door.add_component<transform>({offset + vec2{8 * TILE_SIZE, 0}});
        door.add_component<sprite>({{3, 2}, "door2"});
        door.add_component<animator_controller>({});

        animator_controller *anim = &door.get_component<animator_controller>();
        anim->add_anim("open", opened_horizontal);

        if (fp[data.id - 10] == ROOM_TYPE::BOSS || fp[data.id - 10] == ROOM_TYPE::BOSS_UNDISCOVERED)
            door.add_component<native_script>({}).bind<boss_door_controller>(door_data(data.world_gen->get_room_for_current_world(data.id - 10), this, data.id - 10, false, dir == 1, 3));
        else
            door.add_component<native_script>({}).bind<door_controller>(door_data(data.world_gen->get_room_for_current_world(data.id - 10), this, data.id - 10, false, dir == 1, 3));

        tm.set_tile(3, 0, 8);
    }

    if (fp[data.id + 1])
    {
        auto door = create_entity("door_2");
        door.add_component<transform>({offset + vec2{16 * TILE_SIZE + 3, 2 * TILE_SIZE + 2}});
        door.add_component<sprite>({{3, 2}, "door1"});
        door.add_component<animator_controller>({});

        animator_controller *anim = &door.get_component<animator_controller>();
        anim->add_anim("open", opened_vertical);

        if (fp[data.id + 1] == ROOM_TYPE::BOSS || fp[data.id + 1] == ROOM_TYPE::BOSS_UNDISCOVERED)
            door.add_component<native_script>({}).bind<boss_door_controller>(door_data(data.world_gen->get_room_for_current_world(data.id + 1), this, data.id + 1, true, dir == 2, 4));
        else
            door.add_component<native_script>({}).bind<door_controller>(door_data(data.world_gen->get_room_for_current_world(data.id + 1), this, data.id + 1, true, dir == 2, 4));

        tm.m_data.at(16, 2) = 12;
    }

    if (fp[data.id + 10])
    {
        auto door = create_entity("door_3");
        door.add_component<transform>({offset + vec2{8 * TILE_SIZE, 6 * TILE_SIZE - 1}});
        door.add_component<sprite>({{3, 2}, "door3"});
        door.add_component<animator_controller>({});

        animator_controller *anim = &door.get_component<animator_controller>();
        anim->add_anim("open", opened_horizontal);

        if (fp[data.id + 10] == ROOM_TYPE::BOSS || fp[data.id + 10] == ROOM_TYPE::BOSS_UNDISCOVERED)
            door.add_component<native_script>({}).bind<boss_door_controller>(door_data(data.world_gen->get_room_for_current_world(data.id + 10), this, data.id + 10, false, dir == 3, 1));
        else
            door.add_component<native_script>({}).bind<door_controller>(door_data(data.world_gen->get_room_for_current_world(data.id + 10), this, data.id + 10, false, dir == 3, 1));

        tm.m_data.at(8, 5) = 3;
    }

    if (fp[data.id - 1])
    {
        auto door = create_entity("door_4");
        door.add_component<transform>({offset + vec2{0, 2 * TILE_SIZE + 2}});
        door.add_component<sprite>({{3, 2}, "door1"});
        door.add_component<animator_controller>({});

        animator_controller *anim = &door.get_component<animator_controller>();
        anim->add_anim("open", opened_vertical);

        if (fp[data.id - 1] == ROOM_TYPE::BOSS || fp[data.id - 1] == ROOM_TYPE::BOSS_UNDISCOVERED)
            door.add_component<native_script>({}).bind<boss_door_controller>(door_data(data.world_gen->get_room_for_current_world(data.id - 1), this, data.id - 1, true, dir == 4, 2));
        else
            door.add_component<native_script>({}).bind<door_controller>(door_data(data.world_gen->get_room_for_current_world(data.id - 1), this, data.id - 1, true, dir == 4, 2));

        tm.m_data.at(0, 2) = 13;
    }
}

void room_state::draw_minimap(vec2 pos, WINDOW *win)
{
    world_generator::floorplan floorplan = data.world_gen->get_current_floorplan();
    int y = pos.y, x = pos.x;

    for (int i = 0; i < 100; i++)
    {
        if (floorplan[i] == 4)
            brown::graphics::mvwprintwcolors(win, y, x, 15, "xx");
        else if (i == data.id)
            brown::graphics::mvwprintwcolors(win, y, x, 17, "oo");
        else if (floorplan[i] == 2)
            brown::graphics::mvwprintwcolors(win, y, x, 16, "xx");

        if (i % 10 == 0)
        {
            y++;
            x = pos.x;
        }

        x += 2;
    }

    y = pos.y;
    x = pos.x;

    for (int i = 0; i < 11; i++)
    {
        brown::graphics::mvwprintwcolors(win, y, x + 2 * i, 17, "--");
        brown::graphics::mvwprintwcolors(win, y + 10, x + 2 * i, 17, "--");
        brown::graphics::mvwprintwcolors(win, y + i, x, 17, "||");
        brown::graphics::mvwprintwcolors(win, y + i, x + 20, 17, "||");
    }
}

vec2 room_state::get_valid_position()
{
    vec2 pos = offset;

    chtype ch;
    do
    {
        ch = mvwinch(win, pos.y +1,  pos.x + 1) & A_CHARTEXT;
        pos = offset + vec2{rand() % (map_size.x - 1) * TILE_SIZE, rand() % (map_size.y - 1) * TILE_SIZE};
    } while (ch != ' ');

    return pos;
}