#ifndef APR_PRIVATE_H
#define APR_PRIVATE_H

/* So that we can use inline on some critical functions, and use
 * GNUC attributes (such as to get -Wall warnings for printf-like
 * functions).  Only do this in gcc 2.7 or later ... it may work
 * on earlier stuff, but why chance it.
 *
 * We've since discovered that the gcc shipped with NeXT systems
 * as "cc" is completely broken.  It claims to be __GNUC__ and so
 * on, but it doesn't implement half of the things that __GNUC__
 * means.  In particular it's missing inline and the __attribute__
 * stuff.  So we hack around it.  PR#1613. -djg
 */
#if !defined(__GNUC__) || __GNUC__ < 2 || \
    (__GNUC__ == 2 && __GNUC_MINOR__ < 7) ||\
    defined(NEXT)
#define ap_inline
#define __attribute__(__x)
#define ENUM_BITFIELD(e,n,w)  signed int n : w
#else
#define ap_inline __inline__
#define USE_GNU_INLINE
#define ENUM_BITFIELD(e,n,w)  e n : w
#endif

@TOP@

/* Various #defines we need to know about */
#undef HAVE_LOCK_EX
#undef HAVE_F_SETLK
#undef HAVE_CODESET
#undef HAVE_PTHREAD_PROCESS_SHARED
#undef DEV_RANDOM
#undef HAVE_TRUERAND
#undef HAVE_POLLIN
#undef HAVE_isascii

/* Cross process serialization techniques */
#undef USE_FLOCK_SERIALIZE
#undef USE_SYSVSEM_SERIALIZE
#undef USE_FCNTL_SERIALIZE
#undef USE_PROC_PTHREAD_SERIALIZE
#undef USE_PTHREAD_SERIALIZE

#undef READDIR_IS_THREAD_SAFE

#undef NEED_RLIM_T
#undef USEBCOPY

#undef HAVE_GMTOFF
#undef USE_THREADS

#undef SIZEOF_SSIZE_T
#undef SIZEOF_OFF_T

#undef HAVE_MM_SHMT_MMFILE

/* BeOS specific flag */
#undef HAVE_BONE_VERSION

@BOTTOM@

/* Make sure we have ssize_t defined to be something */
#undef ssize_t

#if !defined(HAVE_STRCASECMP) && defined(HAVE_STRICMP)
#define strcasecmp(s1,s2) stricmp(s1,s2)
#endif

#if !defined(HAVE_SOCKLEN_T)
typedef int socklen_t;
#endif

/* switch this on if we have a BeOS version below BONE */
#if BEOS && !HAVE_BONE_VERSION
#define BEOS_R5 1
#else
#define BEOS_BONE 1
#endif

#endif /* APR_PRIVATE_H */
