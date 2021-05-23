#include "G/assert.h"

int main()
{
    log_print(2, "foobar %d", 6);
    null_assert(0);
    return 0;
}
