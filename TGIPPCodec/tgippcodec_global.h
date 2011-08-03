#ifndef TGIPPCODEC_GLOBAL_H
#define TGIPPCODEC_GLOBAL_H

#include <Qt/qglobal.h>

#ifdef TGIPPCODEC_LIB
# define TGIPPCODEC_EXPORT Q_DECL_EXPORT
#else
# define TGIPPCODEC_EXPORT Q_DECL_IMPORT
#endif

#endif // TGIPPCODEC_GLOBAL_H
