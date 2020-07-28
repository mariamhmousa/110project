#ifndef INCLUDES_H
#define INCLUDES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>  
#include <math.h>
#include <inttypes.h>
#include <time.h>
#include <sys/timeb.h>
#include <thread>
#include <errno.h>
#include "defines.h"


static int print_u128_u(uint128_t u128)
{
    int rc;
    if (u128 > UINT64_MAX)
    {
        uint128_t leading  = u128 / P10_UINT64;
        uint64_t  trailing = u128 % P10_UINT64;
        rc = print_u128_u(leading);
        rc += printf("%." TO_STRING(E10_UINT64) PRIu64, trailing);
    }
    else
    {
        uint64_t u64 = u128;
        rc = printf("%" PRIu64, u64);
    }
    return rc;
}


#endif
