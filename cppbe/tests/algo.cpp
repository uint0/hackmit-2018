//
// Created by admin on 15/09/18.
//

#include "../algo.h"
#include <cstdlib>
#include <cstring>

uint8_t cR[] = {
        1,1,1,1,1,1,1,1,
        0,1,1,0,1,1,0,0,
        1,1,1,1,0,0,0,1,
        1,0,1,0,1,1,1,0,
        0,1,0,0,0,0,1,1,
        1,1,0,1,1,1,0,1,
        1,1,1,0,1,0,0,0,
        0,0,1,0,0,0,0,0,
        0,1,0,1,1,0,1,1,
        1,1,1,0,0,1,1,0,
        1,1,1,0,0,0,1,0,
        1,1,1,0,1,0,0,1,
        1,0,0,1,0,1,0,1,
        0,1,0,0,1,0,0,1,
        0,0,0,1,0,1,0,0,
        0,0,1,0,0,1,1,0,
        1,0,0,0,1,1,1,1,
        1,0,1,0,1,1,0,1,
        0,0,1,0,1,0,0,1,
        1,1,1,1,1,0,0,0,
        0,0,0,0,1,1,0,1,
        1,0,1,0,1,0,0,0,
        1,0,0,1,0,1,1,1,
        1,0,0,1,0,1,1,0,
        0,0,1,0,0,0,1,1,
        0,0,1,1,0,0,0,1,
        1,1,0,0,0,0,1,1,
        0,0,0,0,0,1,1,1,
        0,1,1,0,0,0,0,1,
        0,1,0,1,1,0,0,1,
        0,0,1,1,1,0,0,1,
        1,1,0,1,0,1,0
};

int main(void) {
    srand(0xdeadbeef);

    uint8_t       inp[512] = {0};
    uint8_t       rnd[512] = {0};
    fftwf_complex out[512];

    for (unsigned char &i : inp) {
        i = (uint8_t)(random() & 0b1);
    }

    for(size_t i = 0; i < 255; i++) {
        inp[i] = cR[i/2];
        inp[i+1] = cR[i/2];
        i++;
    }

    for (unsigned char &i : rnd) {
        i = (uint8_t)(random() & 0b11111111);
    }

    puts("-- Input --");
    for (unsigned char i : inp) {
        printf("%d, ", i);
    }

    precompute(inp, out);

    puts("\n-- Output --");
    for(size_t i = 0; i < 511; i++) {
        printf("%f + %fi, ", out[i][0], out[i][1]);
    }

    puts("\n-- Input --");
    for (unsigned char i : rnd) {
        printf("%d, ", i);
    }


    float f = cor(out, 512, rnd);
    printf("\nCor: [%f]\n", f);

    f = cor(out, 512, inp);
    printf("\nCor: [%f]\n", f);
}
