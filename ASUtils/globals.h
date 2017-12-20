#ifndef GLOBALS_H
#define GLOBALS_H

#include <QtCore/qglobal.h>

#ifdef ASUTILS_LIBRARY
#  define ASUTILS_EXPORT Q_DECL_EXPORT
#else
#  define ASUTILS_EXPORT Q_DECL_IMPORT
#endif

typedef float sample_t;

#endif // GLOBALS_H
