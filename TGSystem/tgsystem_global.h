#ifndef TGSYSTEM_GLOBAL_H
#define TGSYSTEM_GLOBAL_H

#include <Qt/qglobal.h>

#ifdef TGSYSTEM_LIB
# define TGSYSTEM_EXPORT Q_DECL_EXPORT
#else
# define TGSYSTEM_EXPORT Q_DECL_IMPORT
#endif

#endif // TGSYSTEM_GLOBAL_H
