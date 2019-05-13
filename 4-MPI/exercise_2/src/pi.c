#include "pi.h"
#include <stdlib.h>
#include <math.h>
#include<mpi.h>
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
 double x,y,z;int i;int count=0;int value[size-1];int localpi=0;
 MPI_Request reqs[size-1]; MPI_Request reqs2[size];MPI_Status stats[size-1];
 for(i=0;i<flip;i++)
 {
      x = (double)rand()/RAND_MAX;
      y = (double)rand()/RAND_MAX;
      z =sqrt((x*x)+(y*y));
      if (z<=1.0) count++;
 }
 *local_count=count;
if(world_rank==0)
{
  int j;
  for(j=1;j<size;j++)
  MPI_Irecv(&value[j-1],1,MPI_INT,j,1,MPI_COMM_WORLD,&reqs[j-1]);
  MPI_Waitall(size-1,reqs,stats);
 for(j=1;j<size;j++)
  localpi+=value[j-1];
localpi+=count;
*answer=((double)localpi/(flip*size))*4;
}
else
{
  MPI_Isend(&count,1,MPI_INT,0,1,MPI_COMM_WORLD,&reqs2[world_rank]);
  MPI_Wait(&reqs2[world_rank],stats);
}
}
