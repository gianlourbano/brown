#include <vector>

namespace brown::graphics
{
    using fb = std::vector<std::vector<char>>;

    class frame_buffer
    {
    public:
        void init(int width, int height);

        void add(fb _fb);

        void dump();

    private:
        fb m_fb;
    };
}