#ifndef AUDIOSCRIPT_GLOBAL_H
#define AUDIOSCRIPT_GLOBAL_H

#include <QtCore/QtGlobal>

#if defined(AUDIOSCRIPT_LIBRARY)
#  define AUDIOSCRIPT_EXPORT Q_DECL_EXPORT
#else
#  define AUDIOSCRIPT_EXPORT Q_DECL_IMPORT
#endif

#endif // AUDIOSCRIPT_GLOBAL_H
