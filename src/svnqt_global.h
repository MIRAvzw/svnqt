#include <QtCore/QtGlobal>

 #if defined(SVNQT_LIBRARY)
 #  define SVNQT_EXPORT Q_DECL_EXPORT
 #else
 #  define SVNQT_EXPORT Q_DECL_IMPORT
 #endif

#define SVNQT_SIZE_UNKNOWN qlonglong(-1)

