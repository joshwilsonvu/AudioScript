#ifndef GLOBALS_H
#define GLOBALS_H

#include <QtCore/qglobal.h>

#ifdef ASUTILS_LIBRARY
#  define ASUTILS_EXPORT Q_DECL_EXPORT
#else
#  define ASUTILS_EXPORT Q_DECL_IMPORT
#endif

typedef float sample_t;

namespace AS {

enum class BufferSize : size_t {
    _32 = 32,
    _64 = 64,
    _128 = 128,
    _256 = 256,
    _512 = 512,
    _1024 = 1024
};

}

#endif // GLOBALS_H
