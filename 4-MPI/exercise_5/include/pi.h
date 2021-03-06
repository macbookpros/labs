#ifndef __PI_H__
#define __PI_H__
#include <mpi.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
char *filename;
int seed;
int world_rank,size;
MPI_File fh;
void init_pi(int, char*,int,int,MPI_File);
void cleanup_pi();
void compute_pi(int, int*, double*);

#endif