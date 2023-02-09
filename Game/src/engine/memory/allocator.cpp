#include "allocator.hpp"
#include <limits>
#include <type_traits>
#include <utility>

namespace brown::mem {

    template<typename T>
    template<typename U>
    allocator<T>::allocator(const allocator<U>&) noexcept
    {
    }

    template<typename T>
    auto allocator<T>::address(reference x) const noexcept -> pointer
    {
        return &x;
    }

    template<typename T>
    auto allocator<T>::address(const_reference x) const noexcept -> const_pointer
    {
        return &x;
    }

    template<typename T>
    auto allocator<T>::allocate(size_type n, allocator<void>::const_pointer) -> pointer
    {
        return reinterpret_cast<pointer>(::operator new(n * sizeof(value_type)));
    }

    template<typename T>
    void allocator<T>::deallocate(pointer p, size_type)
    {
        ::operator delete(p);
    }

    template<typename T>
    auto allocator<T>::max_size() const noexcept -> size_type
    {
        return std::numeric_limits<size_type>::max() / sizeof(value_type);
    }
    
    template<typename T>
    template<typename U, typename... Args>
    void allocator<T>::construct(U* p, Args&&... args)
    {
        static_assert(std::is_constructible<U, Args...>::value, "Cannot construct type");
        ::new(reinterpret_cast<void*>(p)) U(std::forward<Args>(args)...);
    }

    template<typename T>
    template<typename U>
    void allocator<T>::destroy(U* p)
    {
        static_assert(std::is_destructible<U>(), "Cannot destroy type");
        p->~U();
    }

}