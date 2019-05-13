#include<stdio.h>
#include<mpi.h>
int main()
{
    int rank,num_ranks,prev_rank,next_rank,recv_rank;
    MPI_Init( NULL,NULL);
    MPI_Status status;
    int token=0;
    MPI_Comm_rank( MPI_COMM_WORLD, &rank );
    MPI_Comm_size( MPI_COMM_WORLD, &num_ranks );
   prev_rank=(rank+(num_ranks-1))%num_ranks;
  next_rank=(rank+1) % num_ranks;
if(rank==0) {
MPI_Send(&token,1,MPI_INT,next_rank,rank,MPI_COMM_WORLD);
 MPI_Recv(&token,1,MPI_INT,prev_rank,prev_rank,MPI_COMM_WORLD,&status);
 printf(" Rank %d received %d from rank=%d\n",rank,token,prev_rank);
}
 else
{
 MPI_Recv(&token,1,MPI_INT,prev_rank,prev_rank,MPI_COMM_WORLD,&status);
 printf(" Rank %d received %d from rank=%d\n",rank,token,prev_rank);
 token=token+1;
 MPI_Send(&token,1,MPI_INT,next_rank,rank,MPI_COMM_WORLD);
}
MPI_Finalize();
  return 0;
}