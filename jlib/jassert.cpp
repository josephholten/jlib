#include <jlib/jassert.hpp>
#include <cstdlib>

namespace jlib {

// just dummy code to the link against the lib 'jassert' which forces linking against 'cpptrace::cpptrace'
void jassert_exit(int i) {
    exit(i);
}

}