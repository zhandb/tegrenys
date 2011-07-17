#ifndef TGNETWORK_GLOBAL_H
#define TGNETWORK_GLOBAL_H

#include <Qt/qglobal.h>

#ifdef TGNETWORK_LIB
# define TGNETWORK_EXPORT Q_DECL_EXPORT
#else
# define TGNETWORK_EXPORT Q_DECL_IMPORT
#endif

#endif // TGNETWORK_GLOBAL_H
