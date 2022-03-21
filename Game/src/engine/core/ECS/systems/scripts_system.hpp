#include "core/ECS/system.hpp"
#include "core/brain.hpp"
#include "core/ECS/components/native_script.hpp"
#include "core/ECS/entity/scriptable_entity.hpp"

namespace brown
{
    class state;
    
    class scripts_system : public brown::system
    {
    public:
        static std::shared_ptr<scripts_system> register_system(brown::brain* br);

        void on_destroy(state *);
        void on_create();
        void update(state *);
    };
}