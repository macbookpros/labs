#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#include "pi.h"

void print_usage();

int main(int argc, char *argv[])
{
        int opt;
        int world_rank;int size;
        int count = 0, flip = 10000, seed = 1;
        double pi = 0.0;
        char *filename = NULL;
       MPI_File fh;
        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
       MPI_Comm_size(MPI_COMM_WORLD, &size);
        while ((opt = getopt(argc, argv, "s:f:o:")) != -1) {
                switch (opt) {
                        case 's':
                                seed = atoi(optarg);
                                break;
                        case 'f':
                                flip = atoi(optarg);
                                break;
                        case 'o':
                                filename = optarg;
                                break;
                        default:
                                if (world_rank == 0) print_usage(argv[0]);
                }
        }

        init_pi(seed, filename,world_rank,size,fh);
        srand(seed*world_rank);
        compute_pi(flip/size, &count, &pi);
        printf("rank %d: %d / %d = %f\n", world_rank, count, flip, (double)count / (double)flip);
        if (world_rank == 0) {
                printf("pi: %f\n", pi);
        }
        
        cleanup_pi();
        MPI_Finalize(); 
      
        return 0;
}
    
void print_usage(char *program)
{   
        fprintf(stderr, "Usage: %s [-s seed] [-r trials]\n", program);
        exit(1);
}  