/*
 * Copyright (C) the libgit2 contributors. All rights reserved.
 *
 * This file is part of libgit2, distributed under the GNU GPL v2 with
 * a Linking Exception. For full terms see the included COPYING file.
 */
#ifndef INCLUDE_unix_posix_h__
#define INCLUDE_unix_posix_h__

#ifndef LIBGIT2_NO_FEATURES_H
# include "git2/sys/features.h"
#endif

#include <stdio.h>
#include <dirent.h>
#include <sys/param.h>
#include <sys/time.h>
#include <sys/stat.h>

#if (defined(_WIN32)) && !defined(__CYGWIN__)
typedef SOCKET GIT_SOCKET;
#else
typedef int GIT_SOCKET;
#endif
#ifndef INVALID_SOCKET
# define INVALID_SOCKET -1
#endif

#define p_lseek(f,n,w) vfspp_lseek(f, n, w)
#define p_fstat(f,b) vfspp_fstat(f, b)
#define p_lstat(p,b) vfspp_lstat(p,b)
#define p_stat(p,b) vfspp_stat(p, b)

#if defined(GIT_USE_STAT_MTIMESPEC)
# define st_atime_nsec st_atimespec.tv_nsec
# define st_mtime_nsec st_mtimespec.tv_nsec
# define st_ctime_nsec st_ctimespec.tv_nsec
#elif defined(GIT_USE_STAT_MTIM)
# define st_atime_nsec st_atim.tv_nsec
# define st_mtime_nsec st_mtim.tv_nsec
# define st_ctime_nsec st_ctim.tv_nsec
#elif !defined(GIT_USE_STAT_MTIME_NSEC) && defined(GIT_USE_NSEC)
# error GIT_USE_NSEC defined but unknown struct stat nanosecond type
#endif

#define p_utimes(f, t) vfspp_utimes(f, t)

#define p_readlink(a, b, c) vfspp_readlink(a, b, c)
#define p_symlink(o,n) vfspp_symlink(o, n)
#define p_link(o,n) vfspp_link(o, n)
#define p_unlink(p) vfspp_unlink(p)
#define p_mkdir(p,m) vfspp_mkdir(p, m)
extern char *p_realpath(const char *, char *);

GIT_INLINE(int) p_fsync(int fd)
{
	p_fsync__cnt++;
	return vfspp_fsync(fd);
}

#define p_recv(s,b,l,f) recv(s,b,l,f)
#define p_send(s,b,l,f) send(s,b,l,f)
#define p_inet_pton(a, b, c) inet_pton(a, b, c)

#define p_strcasecmp(s1, s2) strcasecmp(s1, s2)
#define p_strncasecmp(s1, s2, c) strncasecmp(s1, s2, c)
#define p_vsnprintf(b, c, f, a) vsnprintf(b, c, f, a)
#define p_snprintf snprintf
#define p_mkstemp(p) vfspp_mkstemp(p)
#define p_chdir(p) vfspp_chdir(p)
#define p_chmod(p,m) vfspp_chmod(p, m)
#define p_rmdir(p) vfspp_rmdir(p)
#define p_access(p,m) vfspp_access(p,m)
#define p_ftruncate(fd, sz) vfspp_ftruncate(fd, sz)

/* see win32/posix.h for explanation about why this exists */
#define p_lstat_posixly(p,b) vfspp_lstat(p,b)

#define p_localtime_r(c, r) vfspp_localtime_r(c, r)
#define p_gmtime_r(c, r) vfspp_gmtime_r(c, r)

#define p_timeval vfspp_timeval

#ifdef GIT_USE_FUTIMENS
GIT_INLINE(int) p_futimes(int f, const struct p_timeval t[2])
{
	struct timespec s[2];
	s[0].tv_sec = t[0].tv_sec;
	s[0].tv_nsec = t[0].tv_usec * 1000;
	s[1].tv_sec = t[1].tv_sec;
	s[1].tv_nsec = t[1].tv_usec * 1000;
	return futimens(f, s);
}
#else
# define p_futimes vfspp_futimes
#endif

#endif
