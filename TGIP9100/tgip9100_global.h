#ifndef TGIP9100_GLOBAL_H
#define TGIP9100_GLOBAL_H

#include <Qt/qglobal.h>

#ifdef TGIP9100_LIB
# define TGIP9100_EXPORT Q_DECL_EXPORT
#else
# define TGIP9100_EXPORT Q_DECL_IMPORT
#endif

#endif // TGIP9100_GLOBAL_H
