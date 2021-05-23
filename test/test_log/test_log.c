#include "G/log.h"

int main()
{
    log_print(2, "foobar %d", 6);
    log_error("exception %d", 7);
    return 0;
}
