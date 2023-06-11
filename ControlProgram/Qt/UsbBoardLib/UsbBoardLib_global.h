#pragma once

#include <QtCore/qglobal.h>

#ifndef QT_STATIC
# if defined(LIBHWKEY_LIB)
#  define UsbBoardLib_EXPORT Q_DECL_EXPORT
# else
#  define UsbBoardLib_EXPORT Q_DECL_IMPORT
# endif
#else
# define UsbBoardLib_EXPORT
#endif
