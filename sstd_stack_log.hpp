#pragma once

#include <array>
#include <vector>
#include <string_view>
using namespace std::string_view_literals;

namespace sstd {

    class StackInformation {
    public:
        constexpr const static unsigned int maxStackLength = 512;
        std::string_view func;
        std::string_view file;
        int line;

        template<std::size_t N1, std::size_t N2>
        inline constexpr StackInformation(
            const char(&v1)[N1],
            const char(&v2)[N2],
            int v3) :
            func(v1, N1 - 1),
            file(v2, N2 - 1),
            line(v3) {
            static_assert(N1 > 0);
            static_assert(N2 > 0);
        }

        inline constexpr StackInformation() :
            func(""sv),
            file(""sv),
            line(0) {
        }

        constexpr StackInformation(const StackInformation &) = default;
        constexpr StackInformation(StackInformation &&) = default;
        constexpr StackInformation&operator=(const StackInformation &) = default;
        constexpr StackInformation&operator=(StackInformation &&) = default;
    };

    extern StackInformation * getCurrentStack(StackInformation *, StackInformation *);
    extern void pushStack(const StackInformation &);

    template<std::size_t N>
    extern StackInformation * getCurrentStack(std::array<StackInformation, N> & v) {
        return getCurrentStack(v.data(), v.data() + v.size());
    }

}/*namespace sstd*/

#ifndef sstd_mark_function_stack
#define sstd_mark_function_stack() sstd::pushStack( { __func__ , __FILE__ , __LINE__ } ) 
#endif

#ifndef sstd_get_function_stack
#define sstd_get_function_stack(...) sstd::getCurrentStack(__VA_ARGS__)
#endif


















