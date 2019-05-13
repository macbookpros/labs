#include "pi.h"
#include<math.h>
void init_pi(int set_seed, char *outfile,int rank,int numranks)
{
        if (filename != NULL) {
                free(filename);
                filename = NULL;
        }

        if (outfile != NULL) {
                filename = (char*)calloc(sizeof(char), strlen(outfile)+1);
                memcpy(filename, outfile, strlen(outfile));
                filename[strlen(outfile)] = 0;
        }
        seed = set_seed*rank;
        world_rank=rank;
       size=numranks;
}

void cleanup_pi()
{
        if (filename != NULL)
                free(filename);
}
void compute_pi(int flip, int *local_count, double *answer)
{
 double x,y,z;int i;int count=0;int value[size];int localpi=0;
 for(i=0;i<flip;i++)
 {
      x = (double)rand()/RAND_MAX;
      y = (double)rand()/RAND_MAX;
      z = sqrt((x*x)+(y*y));
      if (z<=1.0) count++;
 }
 *local_count=count;
MPI_Gather(&count, 1, MPI_INT, value, 1, MPI_INT,0, MPI_COMM_WORLD);
if(world_rank==0)
{
   int j;
  for(j=0;j<size;j++)
  localpi+=value[j];
*answer=((double)localpi/(flip*size))*4;
}
}