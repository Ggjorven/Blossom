#include "blpch.h"
#include "Profiler.hpp"

#if !defined(BL_DIST)
void* operator new(std::size_t size) {
    auto ptr = std::malloc(size);
    if (!ptr) throw std::bad_alloc{};
    TracyAlloc(ptr, size);
    return ptr;
}

void operator delete(void* ptr) noexcept {
    TracyFree(ptr);
    std::free(ptr);
}

void operator delete(void* ptr, std::size_t size) noexcept {
    TracyFree(ptr);
    std::free(ptr);
}
#endif