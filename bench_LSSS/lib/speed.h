
#ifndef __SPEED_H__
#define __SPEED_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

long long cpucycles(void);                                      
unsigned long long average(unsigned long long *t, size_t tlen);
void print_results(const char *s, unsigned long long *t, size_t     tlen);

#endif
