#pragma once

typedef struct Filter {
  float a;
  float b;
  float z;
  float rate;
  float slew;
  float target;
  float time;
} Filter;

void applyFilter(Filter *);
void setFilter(Filter *, float);
Filter filter(float, float, float, float, float);
