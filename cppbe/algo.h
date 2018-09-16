//
// Created by admin on 15/09/18.
//

#ifndef CPPBE_ALGO_H
#define CPPBE_ALGO_H

#include <cstdint>
#include <cstddef>
#include <cstring>
#include <fftw3.h>

#define RES_X   480
#define RES_Y   270
#define SEQ_LEN (256 * 2)

class algo {
    int16_t state[RES_X][RES_Y][3][SEQ_LEN] = {{{0}}};
    uint8_t last_frame[RES_X][RES_Y][3] = {{{0}}};
    size_t idx = 0;

    void loadState(uint8_t state[RES_X][RES_Y][3]);

public:
    algo(const algo &a2) {
        memcpy(state, a2.state, sizeof(state));
        memcpy(last_frame, a2.last_frame, sizeof(last_frame));
        this->idx = a2.idx;
    }

    algo();
    void run();
    void loadState(uint8_t *state);
};
#include <vector>
#include <complex>

void  precompute(uint8_t *inp, fftwf_complex out[510]);
float cor(fftwf_complex af[512], uint8_t pixData[512], fftwf_complex out[512]);
#endif //CPPBE_ALGO_H
