#pragma once

#include <stdint.h>

#define CLIP(X) (X > 1.0f ? 1.0f : X < -1.0f ? -1.0f : X)
#define WET(X, M, W) (((1.0f - W) * X) + ((1.0f - (1.0f - W)) * M))
#define TRUNC(X, M) (((float)(X > M) * M) + (((float)!(X > M)) * X))
#define PAN_L(X, P) TRUNC(((1.0f - (2.0f * (P - 0.5f))) * X), 1.0f)
#define PAN_R(X, P) TRUNC(((1.0f - (2.0f * (0.5f - P))) * X), 1.0f)
#define FROM_I16(X) ((float)X / (float)32768)

int16_t fromFloat(float);
