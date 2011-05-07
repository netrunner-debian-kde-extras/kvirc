#ifndef _kvi_sysconfig_h_
#define _kvi_sysconfig_h_
//=============================================================================
//
// System dependant configuration for KVIrc
// This file is automatically generated: do not edit
//
//=============================================================================

#define SYSTEM_SIZE_OF_SHORT_INT ${CMAKE_SYSTEM_SIZE_OF_SHORT_INT}
#define SYSTEM_SIZE_OF_INT ${CMAKE_SYSTEM_SIZE_OF_INT}
#define SYSTEM_SIZE_OF_LONG_INT ${CMAKE_SYSTEM_SIZE_OF_LONG_INT}
#define SYSTEM_SIZE_OF_LONG_LONG_INT ${CMAKE_SYSTEM_SIZE_OF_LONG_LONG_INT}

#cmakedefine SYSTEM_HAS_SYS_TYPES_H 1
#cmakedefine SYSTEM_HAS_STRINGS_H 1
#cmakedefine HAVE_SETENV 1
#cmakedefine HAVE_PUTENV 1

#cmakedefine COMPILE_THREADS_USE_POSIX 1
#cmakedefine COMPILE_THREADS_USE_WIN32 1
#cmakedefine COMPILE_THREADS_USE_SOLARIS_LIBTHREAD 1
#cmakedefine COMPILE_IGNORE_SIGALARM 1

#cmakedefine COMPILE_MEMORY_PROFILE 1
#cmakedefine COMPILE_MEMORY_CHECKS 1

#cmakedefine COMPILE_CRYPT_SUPPORT 1
#cmakedefine COMPILE_SSL_SUPPORT 1
#cmakedefine COMPILE_CRYPTOPP_SUPPORT 1
#cmakedefine COMPILE_X11_SUPPORT 1
#cmakedefine COMPILE_XSS_SUPPORT 1
#cmakedefine COMPILE_IPV6_SUPPORT 1
#cmakedefine COMPILE_PSEUDO_TRANSPARENCY 1
#cmakedefine COMPILE_KDE_SUPPORT 1
#cmakedefine COMPILE_WEBKIT_SUPPORT 1
#cmakedefine COMPILE_DBUS_SUPPORT 1
#cmakedefine COMPILE_ZLIB_SUPPORT 1

#cmakedefine COMPILE_PHONON_SUPPORT 1
#cmakedefine COMPILE_ESD_SUPPORT 1
#cmakedefine COMPILE_OSS_SUPPORT 1
#cmakedefine HAVE_LINUX_SOUNDCARD_H 1
#cmakedefine HAVE_SYS_SOUNDCARD_H 1
#cmakedefine HAVE_MACHINE_SOUNDCARD_H 1
#cmakedefine COMPILE_DCC_CANVAS 1
#cmakedefine COMPILE_AUDIOFILE_SUPPORT 1
#cmakedefine COMPILE_DISABLE_DCC_VOICE 1
#cmakedefine HAVE_LINUX_SOUNDCARD_H 1
#cmakedefine HAVE_SYS_SOUNDCARD_H 1
#cmakedefine HAVE_SOUNDCARD_H 1

#cmakedefine COMPILE_DISABLE_DCC_VIDEO 1
#cmakedefine COMPILE_DISABLE_AVDEVICE 1
#cmakedefine COMPILE_DISABLE_OGG_THEORA 1
#cmakedefine HAVE_LIBV4L2 1
#cmakedefine V4L2_CAP_VIDEO_CAPTURE 1
#cmakedefine COMPILE_V4L1_CODE 1

#cmakedefine COMPILE_DEBUG_MODE 1

#cmakedefine COMPILE_PERL_SUPPORT 1
#cmakedefine COMPILE_PYTHON_SUPPORT 1

#if !(defined(MINGW))
#cmakedefine COMPILE_ix86_ASM 1
#cmakedefine COMPILE_WITH_SYSTEM_MEMMOVE 1
#endif
#cmakedefine COMPILE_USE_DYNAMIC_LABELS 1
#cmakedefine COMPILE_GET_INTERFACE_ADDRESS 1
#cmakedefine HAVE_INET_ATON 1
#cmakedefine HAVE_INET_NTOA 1

#define COMPILE_USE_STANDALONE_MOC_SOURCES 1

#define KVIRC_VERSION_RELEASE "${CMAKE_KVIRC_VERSION_RELEASE}"
#define KVIRC_VERSION_BRANCH "${CMAKE_KVIRC_VERSION_BRANCH}"

// KVIrc detects the modules directory on macs/win32 by itself
// this seems to be used on linux only
#if !(defined(Q_OS_MACX) || defined(MINGW))
#define KVIRC_RESOURCES_DIR "${CMAKE_KVIRC_RESOURCES_DIR}"
#define KVIRC_MODULES_DIR "${CMAKE_KVIRC_MODULES_DIR}"
#endif

#endif //!_kvi_sysconfig_h_
