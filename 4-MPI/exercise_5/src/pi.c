#include "pi.h"
#include<math.h>
#include<mpi.h>
void init_pi(int set_seed, char *outfile,int rank,int numranks, MPI_File fhtemp)
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
      fh=fhtemp;
      MPI_File_open(MPI_COMM_WORLD,filename,MPI_MODE_CREATE|MPI_MODE_WRONLY,MPI_INFO_NULL, &fh);
}

void cleanup_pi()
{
        if (filename != NULL)
                free(filename);
}

void compute_pi(int flip, int *local_count, double *answer)
{
MPI_Offset offset;
int i;
double x,y,z;int count=0;int localpi=0;
 for(i=0;i<flip;i++)
 {
      x = (double)rand()/RAND_MAX;
      y = (double)rand()/RAND_MAX;
      z = sqrt((x*x)+(y*y));
      if (z<=1.0) count++;
 }
double tempvalue=(double)(count)/(flip*size);
char msg[80];int msgsize;
sprintf(msg,"%d %f\n",world_rank,tempvalue);
msgsize=strlen(msg);
offset = world_rank*msgsize;
 *local_count=count;
MPI_File_write_at(fh,offset,msg,msgsize, MPI_CHAR, MPI_STATUS_IGNORE);
  MPI_Reduce(&count,&localpi,1, MPI_INT,MPI_SUM,0, MPI_COMM_WORLD);
if(world_rank==0)
{
char newmsg[50];int newmsgsize;char buf[80];
*answer=((double)localpi/(flip*size))*4;
sprintf(newmsg,"pi is %f\n",*answer);
newmsgsize=strlen(newmsg);
sprintf(buf,"%d",size);
 MPI_Offset newoffset=(size)*msgsize+(strlen(buf)-1)*size;
 MPI_File_write_at(fh,newoffset,newmsg,newmsgsize, MPI_CHAR, MPI_STATUS_IGNORE);
   MPI_File_close(&fh);
}
}