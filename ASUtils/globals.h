#ifndef AS_GLOBALS_H
#define AS_GLOBALS_H

#include <QtCore/qglobal.h>

#ifdef ASUTILS_LIBRARY
#  define ASUTILS_EXPORT Q_DECL_EXPORT
#else
#  define ASUTILS_EXPORT Q_DECL_IMPORT
#endif

namespace AS {

using sample_t = float;

} // AS

#endif // AS_GLOBALS_H
