/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */


#ifndef CONFIG_H
#define CONFIG_H	1


/* define this to include support for RSA SecurID */
/* #undef ACECLNT */

/* define this to include ACL support */
#define ACLS 1

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* define this if your o/s is AIX */
/* #undef AIX */

/* Define this if you have DES routines you can link to for ARAP (See the user
   guide for more details) */
/* #undef ARAP_DES */

/* define this to include debugging support */
/* #undef DBG */

/* define this if your o/s is FreeBSD */
/* #undef FREEBSD */

/* Define to 1 if you have the <crypt.h> header file. */
#define HAVE_CRYPT_H 1

/* Define to 1 if you have the <ctype.h> header file. */
#define HAVE_CTYPE_H 1

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the <errno.h> header file. */
#define HAVE_ERRNO_H 1

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define to 1 if you have the `getdtablesize' function. */
#define HAVE_GETDTABLESIZE 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* */
#define HAVE_LIBWRAP 1

/* Define to 1 if you have the <malloc.h> header file. */
#define HAVE_MALLOC_H 1

/* Define to 1 if you have the `memcpy' function. */
#define HAVE_MEMCPY 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `memset' function. */
#define HAVE_MEMSET 1

/* define if your system has libpam */
/* #undef HAVE_PAM */

/* Define to 1 if the system has the type `pid_t'. */
#define HAVE_PID_T 1

/* Define if you have POSIX threads libraries and header files. */
#define HAVE_PTHREAD 1

/* Define to 1 if you have the `random' function. */
#define HAVE_RANDOM 1

/* Define to 1 if you have the <shadow.h> header file. */
#define HAVE_SHADOW_H 1

/* Define to 1 if the system has the type `socklen_t'. */
#define HAVE_SOCKLEN_T 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strchr' function. */
#define HAVE_STRCHR 1

/* Define to 1 if you have the `strcspn' function. */
#define HAVE_STRCSPN 1

/* Define to 1 if you have the `strerror' function. */
#define HAVE_STRERROR 1

/* Define to 1 if cpp supports the ANSI # stringizing operator. */
#define HAVE_STRINGIZE 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strrchr' function. */
#define HAVE_STRRCHR 1

/* Define to 1 if you have the <sysexits.h> header file. */
#define HAVE_SYSEXITS_H 1

/* Define to 1 if you have the <syslog.h> header file. */
#define HAVE_SYSLOG_H 1

/* Define to 1 if you have the <sys/resource.h> header file. */
#define HAVE_SYS_RESOURCE_H 1

/* Define to 1 if you have the <sys/socket.h> header file. */
#define HAVE_SYS_SOCKET_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/wait.h> header file. */
#define HAVE_SYS_WAIT_H 1

/* Define to 1 if you have the <termios.h> header file. */
#define HAVE_TERMIOS_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the <utmpx.h> header file. */
#define HAVE_UTMPX_H 1

/* Define to 1 if you have the <utmp.h> header file. */
#define HAVE_UTMP_H 1

/* Define to 1 if you have the `wait3' function. */
#define HAVE_WAIT3 1

/* Define to 1 if you have the `wait4' function. */
#define HAVE_WAIT4 1

/* Define to 1 if you have the `waitpid' function. */
#define HAVE_WAITPID 1

/* Define to 1 if you have the <wait.h> header file. */
#define HAVE_WAIT_H 1

/* define this if your o/s is HPux */
/* #undef HPUX */

/* define this to include libwrap (tcp_wrappers) support */
#define LIBWRAP 1

/* define this if your o/s is Linux */
#define LINUX 1

/* Define to 1 if `sizeof (long int)' = 8. Obsolete, use `SIZEOF_LONG_INT'. */
/* #undef LONG_64_BITS */

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* define this to include MAXSESS support to enforce a limit on maximum
   sessions per user */
/* #undef MAXSESS */

/* define this to include support to finger NASes for the number of sessions a
   user is using */
/* #undef MAXSESS_FINGER */

/* define this if your o/s is MIPS */
/* #undef MIPS */

/* Define this if you need MSCHAP support */
/* #undef MSCHAP */

/* Define this if you have DES routines you can link to for MSCHAP (See the
   user guide for more details) */
/* #undef MSCHAP_DES */

/* define this if your o/s is NetBSD */
/* #undef NETBSD */

/* Name of package */
#define PACKAGE "tacacs"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME "tacacs"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "tacacs F4.0.4.28"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "tacacs"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "F4.0.4.28"

/* define this to include profiling */
/* #undef PROFILE */

/* Define to necessary symbol if this constant uses a non-standard name on
   your system. */
/* #undef PTHREAD_CREATE_JOINABLE */

/* define this if your o/s needs children reaped even though the SIGCHLD
   default is SIG_IGN */
#define REAPCHILD 1

/* define this if your o/s needs children reaped even with an explicit SIG_IGN
   */
#define REAPSIGIGN 1

/* define this if you find that your daemon quits after being sent more than
   one SIGUSR1. Some systems need to explicitly re-arm signals after they've
   been used once */
/* #undef REARMSIGNAL */

/* Define as the return type of signal handlers (`int' or `void'). */
#define RETSIGTYPE void

/* Define to 1 if the `setpgrp' function takes no argument. */
#define SETPGRP_VOID 1

/* define if your system has a shadow password file */
#define SHADOW_PASSWORDS 1

/* The size of `long int', as computed by sizeof. */
#define SIZEOF_LONG_INT 4

/* define this to include support for skey */
/* #undef SKEY */

/* define this if your o/s is Solaris */
/* #undef SOLARIS */

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* define this to a GID for setgid() at run-time */
/* #undef TACPLUS_GROUPID */

/* define this to a UID for setuid() at run-time */
/* #undef TACPLUS_USERID */

/* Define to 1 if you can safely include both <sys/time.h> and <time.h>. */
#define TIME_WITH_SYS_TIME 1

/* define this to include user-specific enable password support */
#define UENABLE 1

/* define this if your waitpid() takes an union wait status pointer */
/* #undef UNIONWAIT */

/* Version number of package */
#define VERSION "F4.0.4.28"

/* define this to set pedantic gcc warnings */
#define WARN 1

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
/* #  undef WORDS_BIGENDIAN */
# endif
#endif

/* Define to 1 if `lex' declares `yytext' as a `char *' by default, not a
   `char[]'. */
#define YYTEXT_POINTER 1

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
/* #undef inline */
#endif


/* UENABLE requires ACLS */
#ifdef UENABLE
# ifndef ACLS
#  define ACLS 1
# endif
#endif

/* MAXSESS_FINGER requires MAXSESS */
#ifdef MAXSESS_FINGER
# ifndef MAXSESS
#  define MAXSESS	1
# endif
#endif

/* Some, eg: solaris 2.6, dont have socklen_t */
#ifndef HAVE_SOCKLEN_T
# define socklen_t	int
#endif

/* host specifics */
/* Define this if your password file does not contain age and comment fields. */
#define NO_PWAGE

#if AIX
/*
 * The only way to properly compile BSD stuff on AIX is to define a
 * "bsdcc" compiler on your system.  See /usr/lpp/bos/bsdport on your
 * system for details. People who do NOT do this tell me that the code
 * still compiles but that it then doesn't behave correctly e.g. child
 * processes are not reaped correctly.  Don't expect much sympathy if
 * you do this.
 */
# define _BSD 1
# define _BSD_INCLUDES
# define NO_PWAGE
#endif	/* AIX */

#if LINUX
# define NO_PWAGE
# include <unistd.h>
# ifdef GLIBC
#  define CONST_SYSERRLIST
# endif
#endif	/* LINUX */

#if NETBSD
# define NO_PWAGE
# define CONST_SYSERRLIST
#endif

#if FREEBSD
# define CONST_SYSERRLIST
# define NO_PWAGE
#endif

#if BSDI
# define NO_PWAGE
#endif
#endif /* CONFIG_H */

