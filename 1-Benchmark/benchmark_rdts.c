#define N 5000
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdint.h>

// Use the preprocessor so we know definitively that these are placed inline
#define RDTSC_START()            \
        __asm__ volatile("CPUID\n\t" \
                         "RDTSC\n\t" \
                         "mov %%edx, %0\n\t" \
                         "mov %%eax, %1\n\t" \
                         : "=r" (start_hi), "=r" (start_lo) \
                         :: "%rax", "%rbx", "%rcx", "%rdx");

#define RDTSC_STOP()              \
        __asm__ volatile("RDTSCP\n\t" \
                         "mov %%edx, %0\n\t" \
                         "mov %%eax, %1\n\t" \
                         "CPUID\n\t" \
                         : "=r" (end_hi), "=r" (end_lo) \
                         :: "%rax", "%rbx", "%rcx", "%rdx");

// Returns the elapsed time given the high and low bits of the start and stop time.
uint64_t elapsed(uint32_t start_hi, uint32_t start_lo,
                 uint32_t end_hi,   uint32_t end_lo)
{
        uint64_t start = (((uint64_t)start_hi) << 32) | start_lo;
        uint64_t end   = (((uint64_t)end_hi)   << 32) | end_lo;
        return end-start;
}


int main()
{
uint32_t start_hi=0, start_lo=0;
        uint32_t end_hi=0,end_lo=0;
  int i, j;
  double a[N], b[N], c[N]; // arrays  
                                             
  // init arrays                                                                   
  for (i = 0; i < N; i++){
    a[i] = 47.0;
    b[i] = 3.1415;
  }
RDTSC_START();
  // measure performance                                                           

  for(i = 0; i < N; i++)
    c[i] = a[i]*b[i];
 RDTSC_STOP();
printf("first value is %f",c[0]);
                uint64_t e = elapsed(start_hi, start_lo, end_hi, end_lo);
                printf("Time elapsed is %ld \n", e);
  return 0;
}

