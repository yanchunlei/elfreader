#include <stdlib.h>
#include "dbg.h"

typedef struct {

}Elfheader;

Elfheader *Read_elfheader(FILE *target)
{
    return NULL;   
};

int main(int argc, char *argv[])
{
    FILE *target;
    if(argc < 2)
    {
        log_err("no file specified.");
    }

    target = fopen(argv[1], "r");
    check(target, "can not open file.");

    Elfheader *target_header = Read_elfheader(target);

    return 0;
error:
    if(target) fclose(target);
    return -1;
}
