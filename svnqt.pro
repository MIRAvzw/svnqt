TARGET = svnqt

QT += core sql

TEMPLATE = lib
DEFINES += SVNQT_LIBRARY

VERSION = 1.6.0

INCLUDEPATH += src
INCLUDEPATH += /usr/include/apr-1
SOURCES += \
	src/cache/ReposConfig.cpp \
	src/cache/LogCache.cpp \
	src/cache/ReposLog.cpp \
	src/cache/DatabaseException.cpp \
	src/conflictdescription.cpp \
	src/url.cpp \
	src/client_modify.cpp \
	src/commititem.cpp \
	src/wc.cpp \
	src/client_lock.cpp \
	src/version_check.cpp \
	src/pool.cpp \
	src/log_entry.cpp \
	src/revision.cpp \
	src/client_update_parameter.cpp \
	src/repositorylistener.cpp \
	src/client_ls.cpp \
	src/apr.cpp \
	src/path.cpp \
	src/repoparameter.cpp \
	src/exception.cpp \
	src/repository.cpp \
	src/svnfilestream.cpp \
	src/targets.cpp \
	src/diffoptions.cpp \
	src/client_property.cpp \
	src/datetime.cpp \
	src/repositorydata.cpp \
	src/client_diff.cpp \
	src/client_annotate_parameter.cpp \
	src/stringarray.cpp \
	src/client_cat.cpp \
	src/client_status.cpp \
	src/dirent.cpp \
	src/svnstream.cpp \
	src/client_merge.cpp \
	src/contextdata.cpp \
	src/client_parameter.cpp \
	src/client_annotate.cpp \
	src/entry.cpp \
	src/client.cpp \
	src/info_entry.cpp \
	src/lock_entry.cpp \
	src/client_impl.cpp \
	src/diff_data.cpp \
	src/status.cpp \
	src/client_commit_parameter.cpp \
	src/conflictresult.cpp \
	src/context.cpp

HEADERS += \
	src/cache/ReposLog.h \
        src/cache/ReposConfig.cpp \
	src/cache/LogCache.cpp \
        src/cache/DatabaseException.h \
	src/cache/ReposLog.cpp \
        src/cache/conversion_check.h \
        src/cache/LogCache.h \
	src/cache/ReposConfig.h \
        src/cache/DatabaseException.cpp \
	src/apr.h \
        src/entry.h \
	src/repositorydata.h \
	src/version_check.h \
	src/info_entry.h \
	src/lock_entry.h \
	src/repositorylistener.h \
	src/url.h \
        src/client_update_parameter.h \
	src/version_check.cpp \
	src/context.h \
	src/pool.h \
        src/shared_pointer.h \
	src/contextdata.h \
	src/revision.h \
        src/path.cpp \
        src/wc.h \
        src/annotate_line.h \
	src/path.h \
	src/dirent.h \
	src/repoparameter.h \
	src/conflictdescription.h \
        src/stringarray.h \
        src/client_parameter_macros.h \
        src/log_entry.h \
        src/exception.h \
	src/client_impl.h \
	src/svnqttypes.h \
        src/commititem.h \
	src/context_listener.h \
	src/datetime.h \
        src/diff_data.h \
        src/status.h \
        src/targets.h \
        src/svnfilestream.h \
        src/client_annotate_parameter.h \
        src/repository.h \
	src/check.h \
        src/client.h \
        src/client_parameter.h \
        src/svnstream.h \
        src/helper.h \
        src/diffoptions.h \
        src/smart_pointer.h \
	src/client_commit_parameter.h \
        src/conflictresult.h
