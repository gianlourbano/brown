#include "core/ECS/system.hpp"
#include "core/brain.hpp"
#include "core/ECS/components/native_script.hpp"

namespace brown
{
    class scripts_system : public brown::system
    {
    public:
        void on_destroy();
        void on_create();
        void update(brain *br);
    };
}