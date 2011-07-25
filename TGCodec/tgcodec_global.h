#ifndef TGCODEC_GLOBAL_H
#define TGCODEC_GLOBAL_H

#include <Qt/qglobal.h>

#ifdef TGCODEC_LIB
# define TGCODEC_EXPORT Q_DECL_EXPORT
#else
# define TGCODEC_EXPORT Q_DECL_IMPORT
#endif

#endif // TGCODEC_GLOBAL_H
