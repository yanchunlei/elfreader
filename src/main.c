#include <stdlib.h>
#include "dbg.h"

int main(int argc, char *argv[])
{
    FILE *target;
    if(argc < 2)
    {
        log_err("no file specified.");
    }

    target = fopen(argv[1], "r");
    check(target, "can not open file.");

    return 0;
error:
    if(target) fclose(target);
    return -1;
}
