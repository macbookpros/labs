#include <stdio.h>
#include <sys/time.h>
#define N 100000
double mysecond();

int main(){
  int i, j;
  double t1, t2; // timers                                                         
  double a[N], b[N], c[N]; // arrays  
                                             
  // init arrays                                                                   
  for (i = 0; i < N; i++){
    a[i] = 47.0;
    b[i] = 3.1415;
  }

  //to avoid coldstart          

for(i = 0; i < N; i++){ 
 c[i]=a[i]*b[i];
        }             
  //meaure performance                                    
  t1 = mysecond();
// to avoid clock granularity
  for(j = 0; j < 10; j++)
{
  for(i = 0; i < N; i++)
    c[i] = a[i]*b[i];
}
  t2 = mysecond();
//to use the result
 printf("first value is %f",c[0]);
  printf("Execution time: %11.8f s\n", (t2 - t1)/10);
  return 0;
}

// function with timer                                                             
double mysecond(){
  struct timeval tp;
  struct timezone tzp;
  int i;

  i = gettimeofday(&tp,&tzp);
  return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}
