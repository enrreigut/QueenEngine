#pragma once

#include "../Vendor/ImGUI/imgui.h"

#include "../Utils/Singleton.h"

namespace Queen
{
    namespace GUI
    {
        class Logger : public Utils::Singleton<Logger>
        {
            friend class Utils::Singleton<Logger>;

        public:

            Logger();

            void Clear();
            void AddLog(const char* fmt, ...) IM_FMTARGS(2);
            void Draw(const char* title, bool* p_open);

            ImGuiTextBuffer     Buf;
            ImGuiTextFilter     Filter;
            ImVector<int>       LineOffsets; // Index to lines offset. We maintain this with AddLog() calls.
            bool                AutoScroll;  // Keep scrolling if already at the bottom.
        };
    }
}