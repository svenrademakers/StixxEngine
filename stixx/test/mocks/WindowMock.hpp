#ifndef WINDOW_MOCK_HPP
#define WINDOW_MOCK_HPP

#include "Window.hpp"
#include <vector>

class WindowMock
        : public sx::Window
{
    MOCK_METHOD0(Name, const char*());
    MOCK_METHOD0(ShouldClose, bool());
    MOCK_METHOD0(Size, std::pair<uint32_t, uint32_t>());
    MOCK_METHOD0(InstanceExtensions, std::vector<const char*>());
    MOCK_METHOD0(Poll, void());
    MOCK_METHOD0(GetHandle,void*());
};
#endif