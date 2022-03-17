#include "engine.hpp"

namespace brown::debug
{
    class debug_state : public state
    {
    public:
    
        void init(brown::engine *game);
        void cleanup();

        void pause();
        void resume();

        void handle_events(brown::engine *game);
        void update(brown::engine *game);
        void draw(brown::engine *game);

        static debug_state *instance()
        {
            return &m_debug_state;
        }

    protected:
        debug_state() {}

    private:
        static debug_state m_debug_state;
    };
}