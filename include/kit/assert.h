#ifndef _G_ASSERT_H_
#define _G_ASSERT_H_

#include <stdlib.h>
#include "log.h"

#define null_assert(p) \
    do { \
        if (!(p)) \
        { \
            log_error("NullPointerException in %s, line %u", __FILE__, __LINE__); \
            exit(1); \
        } \
    } while(0)

#endif
