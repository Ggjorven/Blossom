#pragma once

#include <tracy/Tracy.hpp>
#include <tracy/TracyC.h>

#include <new>
#include <cstdlib>

// TODO(Jorben): Set some default colours
#define BL_ZONE_RED 0xFF0000FF

#if !defined(BL_DIST)
#define BL_PROFILE_SCOPE(name) ZoneScopedN(name)

// TODO(Jorben): Fix
#define BL_PROFILE_SCOPE_COLOUR(name, colour) ZoneNamedC(name, colour, true) 

void* operator new(std::size_t size);
void operator delete(void* ptr) noexcept;
void operator delete(void* ptr, std::size_t size) noexcept;

#else
#define BL_PROFILE_SCOPE
#define BL_PROFILE_SCOPE_COLOUR(name, colour)

#endif
