#pragma once
#include <cstddef>

namespace brown::mem
{

    template <typename T>
    class allocator;

    template <>
    class allocator<void>;

    template <>
    class allocator<void>
    {
    public:
        typedef void *pointer;
        typedef const void *const_pointer;
        typedef void value_type;
        template <typename U>
        struct rebind
        {
            using other = allocator<U>;
        };
    };

    template <typename T>
    class allocator
    {
    public:
        using value_type = T;
        using pointer = T *;
        using const_pointer = const T *;
        using reference = T &;
        using const_reference = const T &;
        using size_type = size_t;
        using difference_type = ptrdiff_t;

        template <typename U>
        using other = allocator<U>;

        allocator() noexcept = default;
        allocator(const allocator &) noexcept = default;
        template <typename U>
        allocator(const allocator<U> &) noexcept;
        ~allocator() noexcept = default;

        pointer address(reference) const noexcept;
        const_pointer address(const_reference) const noexcept;

        pointer allocate(size_type, allocator<void>::const_pointer = 0);
        void deallocate(pointer, size_type);

        size_type max_size() const noexcept;

        template <typename U, typename... Args>
        void construct(U *, Args &&...);
        template <typename U>
        void destroy(U *);
    };
}