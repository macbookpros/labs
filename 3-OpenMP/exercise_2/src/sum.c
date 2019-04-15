#include "sum.h"
#define CLS (64/sizeof(double))

void omp_sum(double *sum_ret)
{
  double sum=0;
#pragma omp parallel for
  for(int i=0;i<size;i++)
{
  sum+=x[i];
 }
  *sum_ret=sum;
}

void omp_critical_sum(double *sum_ret)
{
double sum=0;
#pragma omp parallel for
  for(int i=0;i<size;i++)
{
  #pragma omp critical
  sum+=x[i];
 }
  *sum_ret=sum;
}

void omp_atomic_sum(double *sum_ret)
{
double sum=0;
#pragma omp parallel for
  for(int i=0;i<size;i++)
{
  #pragma omp atomic
  sum+=x[i];
 }
  *sum_ret=sum;
}

void omp_local_sum(double *sum_ret)
{
 int MAX_THREADS=32;
//printf("MAXTHREADS IS - %d"+MAX_THREADS);
double sum[MAX_THREADS];
for(int i=0;i<MAX_THREADS;i++)
sum[i]=0;
double localsum=0;int i;
int stripSize = size/MAX_THREADS;
#pragma omp parallel private(i)
{
  int id=omp_get_thread_num();
 // printf ("id is \n %d ",id);
  int first = id*stripSize;
  int last = (id == MAX_THREADS - 1) ? (size - 1) : (first + stripSize - 1);
  for(i=first;i<=last;i++)
{
  sum[id]+=x[i];
 }
}
//printf("num threads is %d",num_threads2);
for(int i=0;i<MAX_THREADS;i++)
{
   localsum+=sum[i];
}
  *sum_ret=localsum;
}

void omp_padded_sum(double *sum_ret)
{
 int MAX_THREADS=32;
//printf("MAXTHREADS IS - %d"+MAX_THREADS);
double sum[MAX_THREADS*CLS];
for(int i=0;i<MAX_THREADS;i++)
sum[i*CLS]=0;
double localsum=0;int i;
int stripSize = size/MAX_THREADS;
#pragma omp parallel private(i)
{
  int id=omp_get_thread_num();
 // printf ("id is \n %d ",id);
  int first = id*stripSize;
  int last = (id == MAX_THREADS - 1) ? (size - 1) : (first + stripSize - 1);
  for(i=first;i<=last;i++)
{
  sum[id*CLS]+=x[i];
 }
}
//printf("num threads is %d",num_threads2);
for(int i=0;i<MAX_THREADS;i++)
{
   localsum+=sum[i*CLS];
}
  *sum_ret=localsum;
}

void omp_private_sum(double *sum_ret)
{
 int MAX_THREADS=32;
//printf("MAXTHREADS IS - %d"+MAX_THREADS);
double localsum=0;int i;
int stripSize = size/MAX_THREADS;
double mysum=0;
#pragma omp parallel private(i,mysum)
{
  int id=omp_get_thread_num();
 // printf ("id is \n %d ",id);
  int first = id*stripSize;
  int last = (id == MAX_THREADS - 1) ? (size - 1) : (first + stripSize - 1);
  for(i=first;i<=last;i++)
{
  mysum+=x[i];
 }
  #pragma omp critical
 localsum+=mysum;
}
  *sum_ret=localsum;

}

void omp_reduction_sum(double *sum_ret)
{
   double sum=0;
   #pragma omp parallel for reduction(+:sum)
  for(int i=0;i<size;i++)
{
  sum+=x[i];
 }
  *sum_ret=sum;
}
