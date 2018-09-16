//
// Created by admin on 15/09/18.
//

#ifndef CPPBE_ALGO_H
#define CPPBE_ALGO_H

#include <cstdint>
#include <cstddef>
#include <fftw3.h>

#define RES_X   640
#define RES_Y   480
#define SEQ_LEN (256 * 2)

class algo {
    //uint8_t state[RES_X][RES_Y][3][SEQ_LEN];
    size_t idx;

    //void loadState(uint8_t state[RES_X][RES_Y][3]);
};
#include <vector>
#include <complex>

void  precompute(uint8_t *inp, fftwf_complex out[510]);
float cor(fftwf_complex af[512], uint8_t pixData[512], fftwf_complex out[512]);
std::vector<std::complex<double>> preprocess(std::vector<std::complex<double>> vec);
#endif //CPPBE_ALGO_H
