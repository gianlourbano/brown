#include "scriptable_AI.hpp"
#include "player_controller.hpp"


void scriptable_AI::on_create() {
    ts = &get_component<transform>();
    m_player = static_cast<player_controller *>(m_state->find_entity("player").get_component<native_script>().instance);
}

bool scriptable_AI::check_collision(int dir)
{
    chtype chars[4] = {
        mvwinch(m_state->get_win(), ts->position.y-1, ts->position.x) & A_CHARTEXT,
        mvwinch(m_state->get_win(), ts->position.y, ts->position.x + 1) & A_CHARTEXT,
        mvwinch(m_state->get_win(), ts->position.y + 1, ts->position.x) & A_CHARTEXT,
        mvwinch(m_state->get_win(), ts->position.y, ts->position.x - 1) & A_CHARTEXT};

    // return !(chars[dir - 1] == ' ' || (chars[dir - 1] <= 'z' && chars[dir - 1] >= 'a'));
    return chars[dir - 1] == '#' || chars[dir - 1] == '%' || chars[dir - 1] == 'x' || chars[dir - 1] == 'a' || chars[dir - 1] == '6' || chars[dir - 1] == '7'|| chars[dir - 1] == 'b';
}

void scriptable_AI::move(int dir) 
{
    switch (dir) {
        case 1:
            ts->direction = 1;
            if (!check_collision(1))
                ts->position.y--;
            break;
        case 2:
            ts->direction = 2;
            if (!check_collision(2))
                ts->position.x++;
            break;
        case 3:
            ts->direction = 3;
            if (!check_collision(3))
                ts->position.y++;
            break;
        case 4:
            ts->direction = 4;
            if (!check_collision(4))
                ts->position.x--;
            break;
    }
}