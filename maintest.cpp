#include "sstd_stack_log.hpp"
#include <iostream>

template<std::size_t N>
std::size_t xxx(const char (&)[N]) {
    return N;
}

int main() {

    sstd_mark_function_stack();
    sstd_mark_function_stack();
    sstd_mark_function_stack();
    sstd_mark_function_stack();

    std::cout << xxx(__func__) << std::endl;

    std::array< sstd::StackInformation, sstd::StackInformation::maxStackLength > test;

    auto varE =
        sstd_get_function_stack(test);

    for (auto p = test.data(); p != varE; ++p) {
        std::cout << p->file << std::endl;
        std::cout << p->func << std::endl;
        std::cout << p->line << std::endl;
    }

    system("pause");

}





















