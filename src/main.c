#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"

typedef struct {
    unsigned char magicbytes[4];
    unsigned char architecture_format;
    unsigned char architecture_endian;

}Elfheader;

Elfheader *read_elfheader(FILE *target)
{
    Elfheader *target_header = malloc(sizeof(Elfheader));
    check(target_header, "can not allocate memory for Elfheader");
    fread(target_header, sizeof(Elfheader), 1, target);

    return target_header;
error:
    if(target_header) free(target_header);
    return NULL;
};

int is_valid_elf(Elfheader *target_header)
{
    unsigned char temp[4];
    temp[0] = 0x7F; temp[1] = 'E';
    temp[2] = 'L'; temp[3] = 'F';

    int result = memcmp(target_header->magicbytes, temp, 4);

    if(result == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void header_info(Elfheader *target_header)
{
    printf("INFO_ARCHITECTURE: \n");
    printf("format[32bit(1)/64bit(2)]: %d\n", (int)target_header->architecture_format);
    printf("endian[lil(1)/big(2)]: %d\n", (int)target_header->architecture_endian);
}

int main(int argc, char *argv[])
{
    FILE *target;
    if(argc < 2)
    {
        log_err("no file specified.");
    }

    target = fopen(argv[1], "r");
    check(target, "can not open file.");

    Elfheader *target_header = read_elfheader(target);

    if(is_valid_elf(target_header)) sentinel("invalid elf header.");
    header_info(target_header);

    free(target_header);
    fclose(target);
    return 0;

error:
    if(target_header) free(target_header);
    if(target) fclose(target);
    return -1;
}
