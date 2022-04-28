#pragma once

namespace brown::std
{

    template <class T>
    class tree
    {
    public:
        tree(T data, tree *parent) : m_data(data), parent(parent) {}

        tree *add_node(T data, int dir)
        {
            switch (dir)
            {
            case 0:
                right = new tree(data, this);
                break;
            case 1:
                down = new tree(data, this);
                break;
            case 2:
                left = new tree(data, this);
                break;
            default:
                break;
            }
        }

    private:
        T m_data;
        tree<T> *left = nullptr;
        tree<T> *right = nullptr;
        tree<T> *down = nullptr;
        tree<T> *parent = nullptr;
    };
}