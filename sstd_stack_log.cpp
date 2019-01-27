#include "sstd_stack_log.hpp"
#include <mutex>
#include <shared_mutex>
#include <list>

namespace sstd {

    namespace this_file {

        inline bool constexpr isNull(const StackInformation & arg) {
            return
                (arg.func.empty()) ||
                (arg.line < 1);
        }

        class CurrentStackList {
            std::list< StackInformation > dataPrivate;
            mutable std::shared_mutex dataMutexPrivate;
            static_assert(StackInformation::maxStackLength > 16u);
        public:

            inline CurrentStackList() {
                dataPrivate.resize(StackInformation::maxStackLength);
            }

            inline void push(const StackInformation & arg) {
                std::unique_lock varWriteLock{ dataMutexPrivate };
                auto varPos = --dataPrivate.end();
                dataPrivate.splice(
                    dataPrivate.cbegin(),
                    dataPrivate,
                    varPos);
                *varPos = arg;
            }

            inline StackInformation * getCurrentStack(StackInformation *b, StackInformation *e) const {
                std::shared_lock varReadLock{ dataMutexPrivate };
                const auto varLast = dataPrivate.cend();
                auto varPos = dataPrivate.cbegin();
                auto p = b;
                for (; p != e; ++p) {
                    if ((varLast != varPos) && (!isNull(*varPos))) {
                        *p = *varPos;
                        ++varPos;
                        continue;
                    } else {
                        return p;
                    }
                }
                return p;
            }

        };

        inline CurrentStackList & getStackList() {
            static auto * varAns = new CurrentStackList;
            return *varAns;
        }

    }/*this_file*/

    StackInformation * getCurrentStack(StackInformation *b, StackInformation *e) {
        return
            this_file::getStackList().getCurrentStack(b, e);
    }

    extern void pushStack(const StackInformation & arg) {
        this_file::getStackList().push(arg);
    }

}/*namespace sstd*/



