#pragma once

namespace brown::dt {
    template<typename T>
    class set {
         public:
            void insert(T& element);
            void erase(T& element);
    };
}