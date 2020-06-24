#include <stdio.h>
#include <stdlib.h>

void usage(const char *cmd)
{
    printf("Usage %s <input file name> <var name>\n",cmd);
    exit(1);
}

int main(int argc, char *argv[]){
    if(argc != 3) usage(argv[1]);
    char *fname = argv[1];
    FILE *fl = fopen(fname,"rb");
    if(!fl) {
        printf("File %s not found\n",fname);
        exit(1);
    }
    printf("const uint8_t %s[] = {",argv[2]);
    int first = 1;
    while(!feof(fl)){
        unsigned char c = fgetc(fl);
        if(first) first = 0;
        else putchar(',');
        printf(" 0x%02x",c);
    }
    fclose(fl);
    printf("};\n");
    exit(0);
}