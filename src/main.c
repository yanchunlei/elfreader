#include <stdlib.h>
#include "dbg.h"

typedef struct {
    unsigned char magicbytes[3];

}Elfheader;

Elfheader *Read_elfheader(FILE *target)
{
    Elfheader *target_header = malloc(sizeof(Elfheader));
    check(target_header, "can not allocate memory for Elfheader");
    fread(target_header, sizeof(Elfheader), 1, target);

    return target_header;
error:
    if(target_header) free(target_header);
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
