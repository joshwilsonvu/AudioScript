#ifndef APPPUBLIC_GLOBAL_H
#define APPPUBLIC_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIBAUDIOSCRIPT_LIBRARY)
#  define LIBAUDIOSCRIPT_EXPORT Q_DECL_EXPORT
#else
#  define LIBAUDIOSCRIPT_EXPORT Q_DECL_IMPORT
#endif

typedef float sample_t;

#endif // APPPUBLIC_GLOBAL_H
