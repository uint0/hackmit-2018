//
// Created by admin on 15/09/18.
//

#include <iostream>
#include "algo.h"


uint8_t cR[] = {1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,0,1,1,1,1,0,0,0,1,1,0,1,0,1,1,1,0,0,1,0,0,0,0,1,1,1,1,0,1,1,1,0,1,1,1,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,1,0,1,1,1,1,1,0,0,1,1,0,1,1,1,0,0,0,1,0,1,1,1,0,1,0,0,1,1,0,0,1,0,1,0,1,0,1,0,0,1,0,0,1,0,0,0,1,0,1,0,0,0,0,1,0,0,1,1,0,1,0,0,0,1,1,1,1,1,0,1,0,1,1,0,1,0,0,1,0,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,1,0,1,0,0,0,1,0,0,1,0,1,1,1,1,0,0,1,0,1,1,0,0,0,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1,1,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,1,1,0,0,0,0,1,0,1,0,1,1,0,0,1,0,0,1,1,1,0,0,1,1,1,0,1,0,1,0,0};
uint8_t cG[] = {1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,0,1,1,1,1,0,0,0,1,1,0,1,0,1,1,1,0,0,1,0,0,0,0,1,1,1,1,0,1,1,1,0,1,1,1,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,1,0,1,1,1,1,1,0,0,1,1,0,1,1,1,0,0,0,1,0,1,1,1,0,1,0,0,1,1,0,0,1,0,1,0,1,0,1,0,0,1,0,0,1,0,0,0,1,0,1,0,0,0,0,1,0,0,1,1,0,1,0,0,0,1,1,1,1,1,0,1,0,1,1,0,1,0,0,1,0,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,1,0,1,0,0,0,1,0,0,1,0,1,1,1,1,0,0,1,0,1,1,0,0,0,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1,1,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,1,1,0,0,0,0,1,0,1,0,1,1,0,0,1,0,0,1,1,1,0,0,1,1,1,0,1,0,1,0,0};
uint8_t cB[] = {1,1,1,1,1,1,1,1,0,1,1,0,1,1,0,0,1,1,1,1,0,0,0,1,1,0,1,0,1,1,1,0,0,1,0,0,0,0,1,1,1,1,0,1,1,1,0,1,1,1,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,1,0,1,1,1,1,1,0,0,1,1,0,1,1,1,0,0,0,1,0,1,1,1,0,1,0,0,1,1,0,0,1,0,1,0,1,0,1,0,0,1,0,0,1,0,0,0,1,0,1,0,0,0,0,1,0,0,1,1,0,1,0,0,0,1,1,1,1,1,0,1,0,1,1,0,1,0,0,1,0,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,1,1,0,1,0,1,0,0,0,1,0,0,1,0,1,1,1,1,0,0,1,0,1,1,0,0,0,1,0,0,0,1,1,0,0,1,1,0,0,0,1,1,1,0,0,0,0,1,1,0,0,0,0,0,1,1,1,0,1,1,0,0,0,0,1,0,1,0,1,1,0,0,1,0,0,1,1,1,0,0,1,1,1,0,1,0,1,0,0};


void algo::loadState(uint8_t *input) {
    for (int i = 0; i < 1080; i+=4) {
        for (int j = 0; j < 1920; j+=4) {
            int pxindex = (i*1920 + j);
            int b = input[pxindex*4];
            this->state[i/4][j/4][0][this->idx] = ((b - this->last_frame[i/4][j/4][0]) / 2);
            this->last_frame[i/4][j/4][0] = (b / 2);
            int g = input[pxindex*4+1];
            this->state[i/4][j/4][1][this->idx] = ((g - this->last_frame[i/4][j/4][1]) / 2);
            this->last_frame[i/4][j/4][1] = (g / 2);
            int r = input[pxindex*4+2];
            this->state[i/4][j/4][2][this->idx] = ((r - this->last_frame[i/4][j/4][2]) / 2);
            this->last_frame[i/4][j/4][2] = (r / 2);

            /*
            int pxindex = (i*1920 + j);
            int b = input[pxindex*4] + input[(pxindex+1)*4] + input[(pxindex+1920)*4] + input[(pxindex+1921)*4];
            this->state[i/2][j/2][0][this->idx] = ((b / 4 - this->last_frame[i / 2][j / 2][0]) / 2);
            this->last_frame[i/2][j/2][0] = (b / 8);
            int g = input[pxindex*4+1] + input[(pxindex+1)*4+1] + input[(pxindex+1920)*4+1] + input[(pxindex+1921)*4+1];
            this->state[i/2][j/2][1][this->idx] = ((g / 4 - this->last_frame[i / 2][j / 2][1]) / 2);
            this->last_frame[i/2][j/2][1] = (g / 8);
            int r = input[pxindex*4+2] + input[(pxindex+1)*4+2] + input[(pxindex+1920)*4+2] + input[(pxindex+1921)*4+2];
            this->state[i/2][j/2][2][this->idx] = ((r / 4 - this->last_frame[i / 2][j / 2][2]) / 2);
            this->last_frame[i/2][j/2][2] = (r / 8);
             */
        }
    }
    this->idx++;
    if (this->idx == 512) {
        this->idx = 0;
    }
}

algo::algo() {
    this->idx = 0;
    memset(this->state, 0, RES_X*RES_Y*3*512);
}

float cor(fftwf_complex af[512], uint8_t pixData[512]) {
    float diffs[512] = {0.0f};
    fftwf_complex out[512];

    diffs[0]   = 0.0f;
    diffs[511] = 0.0f;

    for(size_t i = 1; i < 511; i++) {
        float delta = (pixData[i + 1] - pixData[i - 1]) / 2.0f;
        diffs[i] = delta > 1.0f ? 1.0f : (delta < -1.0f ? -1.0f : delta);
    }

    fftwf_complex cDiff[512] = {{0,0}};
    for(size_t i = 0; i < 512; i++) {
        cDiff[i][0] = diffs[i];
        cDiff[i][1] = 0.0f;
    }

    fftwf_plan planf = fftwf_plan_dft_1d(510, cDiff, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftwf_execute(planf);
    fftwf_destroy_plan(planf);

    for(size_t i = 0; i < 512; i++) {
        float t   = out[i][1] * af[i][1] - out[i][0] * af[i][0];
        out[i][1] = out[i][0] * af[i][1] + out[i][1] * af[i][0];
        out[i][0] = t;
    }

    fftwf_plan planb = fftwf_plan_dft_1d(510, out, cDiff, FFTW_BACKWARD, FFTW_ESTIMATE);
    fftwf_execute(planb);
    fftwf_destroy_plan(planb);

    for(size_t i = 0; i < 512; i++) {
        cDiff[i][0] = -cDiff[i][0]/509;
    }

    float max = -INFINITY;
    for (float *diff : cDiff) {
        if(diff[0] > max) { max = diff[0]; }
    }

    return max;
}

void precompute(uint8_t inp[512], fftwf_complex out[512]) {
    float diffs[512];

    diffs[0]   = 0;
    diffs[511] = 0;

    for(size_t i = 1; i < 511; i++) {
        float delta = (inp[i + 1] - inp[i - 1]) / 2.0f;
        diffs[i] = delta;
    }

    fftwf_complex cDiff[512];
    for(size_t i = 0; i < 512; i++) {
        cDiff[i][0] = diffs[i];
        cDiff[i][1] = 0;
    }

    fftwf_plan planf = fftwf_plan_dft_1d(510, cDiff, out, FFTW_FORWARD, FFTW_ESTIMATE);
    fftwf_execute(planf);
    fftwf_destroy_plan(planf);

    for(size_t i = 0; i < 512; i++) {
        out[i][1] *= -1;
    }
}

float calc(int16_t *input, fftwf_complex *af, uint16_t idx) {
    uint8_t inpR[512];
    for(size_t i = idx; i < 512 + idx; i++) {
        inpR[i-idx] = (uint8_t)input[i % (512)];
    }

    return cor(af, inpR);
}

void dupl(uint8_t *out, uint8_t *typ) {
    for(size_t i = 0; i < 512; i++) {
        out[i]   = typ[i/2];
        out[i+1] = typ[i/2];
        i++;
    }
}

void algo::run() {
    fftwf_complex oR[512];
    fftwf_complex oG[512];
    fftwf_complex oB[512];

    uint8_t duped[512];
    dupl(duped, cR);
    precompute(duped, oR);
    dupl(duped, cG);
    precompute(duped, oG);
    dupl(duped, cB);
    precompute(duped, oB);


    int index = this->idx;

    float frame[RES_X][RES_Y] = {0.0f};
    float max = 0.0f;
    for (int i = 0; i < RES_X; i++) {
        for (int j = 0; j < RES_Y; j++) {
            frame[i][j]  = calc((int16_t*)this->state[i][j][0], oR, index);
            //frame[i][j] += calc((int16_t*)this->state[i][j][1], oG, static_cast<uint8_t>(index));
            //frame[i][j] += calc((int16_t*)this->state[i][j][2], oB, static_cast<uint8_t>(index));

            if (index % 10 == 4) {
                // std::cout << frame[i][j] << std::endl;
            }
            if (frame[i][j] > max) {
                max = frame[i][j];
            };
        }
    }

    if (index %1 == 0) {
        if(!max) max = 1;
        std::cout << "/ing file" << std::endl;
        const int dimx = RES_X, dimy = RES_Y;
        int i, j;
        FILE *fp = fopen("/tmp/first.ppm", "wb"); /* b - binary mode */
        (void) fprintf(fp, "P6\n%d %d\n255\n", dimx, dimy);
        for (j = 0; j < dimy; ++j)
        {
            for (i = 0; i < dimx; ++i)
            {
                static unsigned char color[3];
                color[0] = (255 * frame[i][j]) / max;  /* red */
                color[1] = (255 * frame[i][j]) / max;  /* green */
                color[2] = (255 * frame[i][j]) / max;  /* blue */
                (void) fwrite(color, 1, 3, fp);
            }
        }
        (void) fclose(fp);
    }
}
