#pragma once

typedef struct Filter {
  float x;
  float a;
  float b;
  float z;
  float rate;
} Filter;

void applyFilter(Filter *);
void setFilter(Filter *, float);
Filter filter(float); 
