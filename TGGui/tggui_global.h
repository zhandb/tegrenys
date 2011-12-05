#ifndef TGGUI_GLOBAL_H
#define TGGUI_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef TGGUI_LIB
# define TGGUI_EXPORT Q_DECL_EXPORT
#else
# define TGGUI_EXPORT Q_DECL_IMPORT
#endif

#endif // TGGUI_GLOBAL_H
