//
// Created by admin on 15/09/18.
//

#include "../algo.h"

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
    fftwf_complex out[512] = {0};
    fftwf_complex ou2[512] = {0};

    for (unsigned char &i : inp) {
        i = (uint8_t)(random() & 0b1);
    }

    for(size_t i = 0; i < 512; i++) {
        inp[i] = cR[i/2];
        inp[i+1] = cR[i/2];
        i++;
    }

    for(size_t i = 0; i < 512; i++) {
        rnd[i] = static_cast<uint8_t>((i / 2) % 2);
    }

    puts("-- Input --");
    for (unsigned char i : inp) {
        printf("%d, ", i);
    }

    precompute(inp, out);

    puts("\n-- Output --");
    for(size_t i = 0; i < 512; i++) {
        printf("%f + %fi, ", out[i][0], out[i][1]);
    }

    // ^ works

    puts("\n-- Input --");
    for (unsigned char i : rnd) {
        printf("%d, ", i);
    }

    float f = cor(out, rnd, ou2);
    printf("\nCor: [%f]\n", f);

    f = cor(out, inp, ou2);
    printf("\nCor: [%f]\n", f);
}
