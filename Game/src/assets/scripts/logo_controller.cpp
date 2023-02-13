#include "assets/scripts/logo_controller.hpp"

    void logo_controller::on_create() {
        ts = &get_component<transform>();
    }

    void logo_controller::on_update()
    {
        if (m_counter < 10)
        {
            if(m_timer.elapsed() >= 0.05)
            {
                m_counter++;
                m_timer.start();
                ts->position.y++;
            }
        }
    }