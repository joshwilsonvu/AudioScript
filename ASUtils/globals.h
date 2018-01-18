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
    _32,
    _64,
    _128,
    _256,
    _512,
    _1024
};

size_t to_size_t(BufferSize size);

}

#endif // GLOBALS_H
