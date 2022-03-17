#pragma once

#include <ncurses.h>
#include <vector>
#include <unistd.h>
#include "debug/debugger.hpp"
#include "core/color/color.hpp"
#include "graphics/window/window.hpp"
#include "engine.hpp"
//////
#include "core/event/event_manager.hpp"
#include "core/ECS/entity_manager.hpp"
#include "core/ECS/component_manager.hpp"
#include "core/ECS/system_manager.hpp"
#include "core/brain.hpp"
//////
#include "debug/debug_state.hpp"
//////
#include "core/ECS/components/animation.hpp"
#include "core/ECS/components/transform.hpp"
#include "core/ECS/components/sprite.hpp"
#include "core/ECS/components/force.hpp"
#include "core/ECS/components/rigid_body.hpp"
#include "core/ECS/components/native_script.hpp"
#include "core/ECS/systems/scripts_system.hpp"
#include "core/ECS/systems/animation_system.hpp"
#include "core/ECS/systems/render_system.hpp"
#include "core/ECS/systems/physics_system.hpp"