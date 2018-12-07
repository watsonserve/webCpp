#ifndef _STDAFX_H_
#define _STDAFX_H_

#if defined(__linux__) || defined(__linux)
#define __LINUX__
#endif

#if defined(__APPLE__) || defined(__MACOSX__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__bsdi__)
#define __BSD__
#endif

#endif /* _STDAFX_H_ */
