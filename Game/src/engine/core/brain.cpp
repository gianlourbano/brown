#include "brain.hpp"

#include "core/ECS/components/animation.hpp"
#include "core/ECS/components/sprite.hpp"
#include "core/ECS/components/native_script.hpp"
#include "core/ECS/components/transform.hpp"
#include "core/ECS/components/rigid_body.hpp"
#include "core/ECS/components/animator_controller.hpp"
#include "core/ECS/components/ui.hpp"

namespace brown {
    void brain::register_basic_components()
        {
            this->register_component<transform>();
            this->register_component<sprite>();
            this->register_component<animator_controller>();
            this->register_component<native_script>();
            this->register_component<ui>();
        }
}