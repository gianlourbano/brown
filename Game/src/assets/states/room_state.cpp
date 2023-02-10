#include "room_state.hpp"
#include "assets/scripts/door_controller.hpp"

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
    animation closed_horizontal = {
        "animated_horizontal_door_c",
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

    animation closed_vertical = {
        "animated_vertical_door_c",
        {0, 0},
        4,
        20,
        false,
        true};

    if (fp[data.id - 10])
    {
        auto door = create_entity("door_1");
        door.add_component<transform>({offset + vec2{8 * TILE_SIZE, 0}});
        door.add_component<sprite>({{3, 2}, "door2"});
        door.add_component<animator_controller>({});

        animator_controller *anim = &door.get_component<animator_controller>();
        anim->add_anim("close", closed_horizontal);
        anim->add_anim("open", opened_horizontal);

        door.add_component<native_script>({}).bind<door_controller>(door_data(data.world_gen->get_room_for_current_world(data.id - 10),this, data.id - 10, false, dir==1, 3));

        tm.set_tile(3, 0, 8);
    }

    if (fp[data.id + 1])
    {
        auto door = create_entity("door_2");
        door.add_component<transform>({offset + vec2{16 * TILE_SIZE + 3, 2 * TILE_SIZE + 2}});
        door.add_component<sprite>({{3, 2}, "door1"});
        door.add_component<animator_controller>({});

        animator_controller *anim = &door.get_component<animator_controller>();
        anim->add_anim("close", closed_vertical);
        anim->add_anim("open", opened_vertical);

        door.add_component<native_script>({}).bind<door_controller>(door_data(data.world_gen->get_room_for_current_world(data.id + 1),this, data.id + 1, true, dir==2, 4));

        tm.m_data.at(16, 2) = 12;
    }

    if (fp[data.id + 10])
    {
        auto door = create_entity("door_3");
        door.add_component<transform>({offset + vec2{8 * TILE_SIZE, 6 * TILE_SIZE - 1}});
        door.add_component<sprite>({{3, 2}, "door3"});
        door.add_component<animator_controller>({});

        animator_controller *anim = &door.get_component<animator_controller>();
        anim->add_anim("close", closed_horizontal);
        anim->add_anim("open", opened_horizontal);

        door.add_component<native_script>({}).bind<door_controller>(door_data(data.world_gen->get_room_for_current_world(data.id + 10),this, data.id + 10, false, dir==3, 1));

        tm.m_data.at(8, 5) = 3;
    }

    if (fp[data.id - 1])
    {
        auto door = create_entity("door_4");
        door.add_component<transform>({offset + vec2{0, 2 * TILE_SIZE + 2}});
        door.add_component<sprite>({{3, 2}, "door1"});
        door.add_component<animator_controller>({});

        animator_controller *anim = &door.get_component<animator_controller>();
        anim->add_anim("close", closed_vertical);
        anim->add_anim("open", opened_vertical);

        door.add_component<native_script>({}).bind<door_controller>(door_data(data.world_gen->get_room_for_current_world(data.id - 1),this, data.id - 1, true, dir==4, 2));

        tm.m_data.at(0, 2) = 14;
    }
}