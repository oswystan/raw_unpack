/*
 **************************************************************************************
 *       Filename:  unpack.c
 *    Description:   source file
 *
 *        Version:  1.0
 *        Created:  2016-08-25 15:17:05
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main(int argc, const char *argv[]) {
    if (argc != 4) {
        printf("usage: <filename> <width> <height>\n");
        return -1;
    }

    int width = atoi(argv[2]);
    int height = atoi(argv[3]);

    FILE* fp = fopen(argv[1], "rb");
    if (!fp) {
        printf("Fail to open file <%s>\n", argv[1]);
        return -1;
    }

    char fn[128];
    sprintf(fn, "unpack_%s", argv[1]);
    FILE* fo = fopen(fn, "wb");
    if (!fo) {
        printf("Fail to open file <%s>\n", fn);
        fclose(fp);
        return -1;
    }

    unsigned char buf[1024*8];
    int stride = ceil(width*1.25/8)*8;
    int i = 0;
    int j = 0;
    int n = 0;
    while(!feof(fp)) {
        for (n = 0; n < height; n++) {
            int ret = fread(buf, 1, stride, fp);
            if (!ret) {
                break;
            }
            for (j = 0; j < width/4; j++) {
                unsigned char * p = buf + j*5;
                for (i = 0; i < 4; i++) {
                    unsigned short d = p[i];
                    d = d << 2;
                    d = d | ((p[4]>>(i*2))&0x3);
                    fwrite(&d, 2, 1, fo);
                }
            }
        }
    }
    fclose(fo);
    fclose(fp);
    return 0;
}

/********************************** END **********************************************/

