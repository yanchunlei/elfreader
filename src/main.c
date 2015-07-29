#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"

typedef struct {
    unsigned char magicbytes[4];
    unsigned char architecture_format;
    unsigned char architecture_endian;

    unsigned char elf_version;

    unsigned char target_os;

    unsigned char abi_version;
    unsigned char elf_pad[7];

    unsigned short elf_type;
    unsigned short architecture_instructions;
    unsigned short elf_version2;

    unsigned long elf_entrypoint64;
    unsigned long elf_startheadertable;
    unsigned long elf_startsectiontable;

    unsigned int elf_flags;

    unsigned short elf_headersize;
    unsigned short elf_pentryheadersize;
    unsigned short elf_tableentrys;
    unsigned short elf_sizesection;
    unsigned short elf_sectioncount;
    unsigned short elf_sectionnames;



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
    printf("arch format[32bit(1)/64bit(2)]: %d\n", (int)target_header->architecture_format);
    printf("arch endian[lil(1)/big(2)]: %d\n", (int)target_header->architecture_endian);
    printf("arch instructionset: %#02x\n", target_header->architecture_instructions);
    printf("\n");
    printf("ELF_VARIOUS_INFO: \n");
    printf("ELF version[orig(1)]: %d\n", (int)target_header->elf_version);
    printf("ELF type[reloc(1)/exec(2)/shared(3)/core(4)]: %d\n", target_header->elf_type);
    printf("ELF Entrypoint: %#016x\n", target_header->elf_entrypoint64);
    printf("ELF program header table: %#016x\n", target_header->elf_startheadertable);
    printf("ELF section header table: %#016x\n", target_header->elf_startsectiontable);
    printf("ELF header size: %d\n", target_header->elf_headersize);
    printf("ELF table header size: %d\n", target_header->elf_pentryheadersize);
    printf("ELF table entrys: %d\n", target_header->elf_tableentrys);
    printf("ELF section size: %d\n", target_header->elf_sizesection);
    printf("ELF section count: %d\n", target_header->elf_sectioncount);
    printf("ELF section contain names: %#04x", target_header->elf_sectionnames);
    printf("\n");
    printf("INFO_OS: \n");
    printf("target os: %d", (int)target_header->target_os);
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
