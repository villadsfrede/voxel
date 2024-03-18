#ifndef NOISE_H
#define NOISE_H

#include <math.h>

static constexpr unsigned char p[256] = {
    151, 160, 137, 91, 90, 15, 131, 13, 201, 95, 96, 53, 194, 233, 7, 225, 140, 36, 103, 30, 69, 142,
    8, 99, 37, 240, 21, 10, 23, 190, 6, 148, 247, 120, 234, 75, 0, 26, 197, 62, 94, 252, 219, 203,
    117, 35, 11, 32, 57, 177, 33, 88, 237, 149, 56, 87, 174, 20, 125, 136, 171, 168, 68, 175, 74,
    165, 71, 134, 139, 48, 27, 166, 77, 146, 158, 231, 83, 111, 229, 122, 60, 211, 133, 230, 220,
    105, 92, 41, 55, 46, 245, 40, 244, 102, 143, 54, 65, 25, 63, 161, 1, 216, 80, 73, 209, 76, 132,
    187, 208, 89, 18, 169, 200, 196, 135, 130, 116, 188, 159, 86, 164, 100, 109, 198, 173, 186,
    3, 64, 52, 217, 226, 250, 124, 123, 5, 202, 38, 147, 118, 126, 255, 82, 85, 212, 207, 206, 59,
    227, 47, 16, 58, 17, 182, 189, 28, 42, 223, 183, 170, 213, 119, 248, 152, 2, 44, 154, 163, 70,
    221, 153, 101, 155, 167, 43, 172, 9, 129, 22, 39, 253, 19, 98, 108, 110, 79, 113, 224, 232, 178,
    185, 112, 104, 218, 246, 97, 228, 251, 34, 242, 193, 238, 210, 144, 12, 191, 179, 162, 241,
    81, 51, 145, 235, 249, 14, 239, 107, 49, 192, 214, 31, 181, 199, 106, 157, 184, 84, 204, 176,
    115, 121, 50, 45, 127, 4, 150, 254, 138, 236, 205, 93, 222, 114, 67, 29, 24, 72, 243, 141, 128, 195,
    78, 66, 215, 61, 156, 180,
};

float fade(float t) {
    return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
}

float gradient(int hash, float xf, float yf) {
    switch (hash & 0x7) {
    case 0x0: return  xf + yf;
    case 0x1: return  xf;
    case 0x2: return  xf - yf;
    case 0x3: return -yf;
    case 0x4: return -xf - yf;
    case 0x5: return -xf;
    case 0x6: return -xf + yf;
    case 0x7: return  yf;
    default:  return  0.0f;
    }
}

float lerp(float a, float b, float t) {
    return a + t * (b - a);
}

float perlin(float x, float y) {
    float const f = 0.005;

    x = f * x;
    y = f * y;

    int xi0 = (int)floor(x) & 0xFF;
    int yi0 = (int)floor(y) & 0xFF;

    float xf0 = x - (float)xi0;
    float yf0 = y - (float)yi0;
    float xf1 = xf0 - 1.0f;
    float yf1 = yf0 - 1.0f;

    int xi = xi0 & 0xFF;
    int yi = yi0 & 0xFF;

    float u = fade(xf0);
    float v = fade(yf0);

    int h00 = p[p[xi + 0] + yi + 0];
    int h01 = p[p[xi + 0] + yi + 1];
    int h10 = p[p[xi + 1] + yi + 0];
    int h11 = p[p[xi + 1] + yi + 1];

    float x1 = lerp(gradient(h00, xf0, yf0), gradient(h10, xf1, yf0), u);
    float x2 = lerp(gradient(h01, xf0, yf1), gradient(h11, xf1, yf1), u);

    return lerp(x1, x2, v);
}

#endif