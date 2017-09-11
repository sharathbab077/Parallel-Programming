#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
int a[4][4],b[4][4],in[4];
int main(int argc,char *argv[])
{
	int rank,size,rc,i,j,m;
	MPI_Status stat[2];
	int *in=0,*out=0,*out1=0,*in1=0;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&size);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	if(rank==0)
	{
		printf("instilising elements of matrix \n");
		for(i=0;i<2;i++)
			for(j=0;j<4;j++)
				a[i][j]=2*(i+j);//scanf("%d",&a[i][j]);
		printf("\n First half  matrix is: \n");
		in=(int *)malloc(4*sizeof(int));
		out=(int *)malloc(4*sizeof(int));
		in1=(int *)malloc(4*sizeof(int));

		for(i=0;i<2;i++)
		{
			for(j=0;j<4;j++)
			{
				printf("%d \t",a[i][j]);
				if(i==1)
					in[j]=a[i][j];	
			}
			printf("\n");
		}

		rc=MPI_Send(in,4,MPI_INT,1,0,MPI_COMM_WORLD);

		if(rc==0)
			printf("Rank 0:Sent Successfully \n");

			     rc=MPI_Recv(out,4,MPI_INT,1,1,MPI_COMM_WORLD,&stat[1]);
				if(rc==0)
				printf("Received from rank 1 \n");
		for(i=0;i<4;i++)
		{
			printf(" %d \t",out[i]);
			in1[i]=out[i];
		}


		printf("\n");
		printf(" Content of in1 buf is \n");

for(i=0;i<4;i++)
				printf("%d \t",in1[i]);
			printf("\n");
    for(i=0;i<2;i++)
     {
	 for(j=0;j<4;j++)
	  {
		if(i==0 && j==0)
		 {
		  b[i][j]=(a[i][j+1]+a[i+1][j])/2;
		 }

		 else if(i==0 && j==3)
		  {
		   b[i][j]=(a[i][j-1]+a[i+1][j])/2;
		  }

		 else if(j==0 && i==1)
		  {
		   b[i][j]=(a[i-1][j]+in1[j]+a[i][j+1])/3;
		  }
			
            else if(j==3 && i==1)
		  {
		   b[i][j]=(a[i-1][j]+in1[j]+a[i][j-1])/3;
		  }
		  
            else if(i==0 && 0<j<3)
		  {
		   b[i][j]=(a[i][j-1]+a[i+1][j]+a[i][j+1])/3;
		  }
		 
            else
             {
              b[i][j]=(a[i][j-1]+a[i][j+1]+a[i-1][j]+in1[j])/4;
             }

	   }
}

printf("Updated first half is : \n");
	 for(i=0;i<2;i++)
	  {
	    for(j=0;j<4;j++)
	     {
		 printf("%d \t",b[i][j]);
		}
		 printf("\n");
	  }

		
}
	
else if(rank==1)
 {
	printf("\nRank 1\n");
	out=(int *)malloc(4*sizeof(int));
	in=(int *)malloc(4*sizeof(int));
	out1=(int *)malloc(4*sizeof(int));
	rc=MPI_Recv(out,4,MPI_INT,0,0,MPI_COMM_WORLD,&stat[0]);
	if(rc==0)
	printf("Rank 1 Received successful \n");
	for(i=0;i<4;i++)
	 {
	   printf("%d \t",out[i]);
	   out1[i]=out[i];
	 }
	   printf("\n");
	   printf("\n content of out1 buf is \n");
	   for(i=0;i<4;i++)
	   printf("%d \t",out1[i]);
	   printf("\n");
	   for(i=2;i<4;i++)
	   for(j=0;j<4;j++)
	   a[i][j]=(i+j)*2;
	   printf("Second half is: \n");
	   for(i=2;i<4;i++)
	    {
		for(j=0;j<4;j++)
		 {
		   printf("%d \t",a[i][j]);
		   if(i==2)
		    out[j]=a[i][j];
		 }
	printf("\n");
		}
		rc=MPI_Send(out,4,MPI_INT,0,1,MPI_COMM_WORLD);
	   if(rc==0)
	   printf(" Rank 1 sent successful \n");
	   for(i=2;i<4;i++)
         {
          for(j=0;j<4;j++)
            {
             if(i==3 && j==0)
             {
                                                                        b[i][j]=(a[i][j+1]+a[i-1][j])/2;
             }
             else if(i==3 && j==3)
              {
                b[i][j]=(a[i][j-1]+a[i-1][j])/2;
              }
            
             else if(i==3 && 0<j<3)
              {
                 b[i][j]=(a[i][j-1]+a[i-1][j]+a[i][j+1])/3;
              }
		  
             else if(j==0 && 1<i<3)
              {
                b[i][j]=(out1[j]+a[i+1][j]+a[i][j+1])/3;
              }
             else if(j==3 && i==2)
              {
                    b[i][j]=(out1[j]+a[i+1][j]+a[i][j-1])/3;
              }
		  else
		   {
			b[i][j]=(a[i][j-1]+a[i][j+1]+a[i+1][j]+out1[j])/4;
		   }
             }
            }
printf("Updated second matrix : \n");
    for(i=2;i<4;i++)
     {
	 for(j=0;j<4;j++)
	  {
		printf("%d \t",b[i][j]);
	  }
		printf("\n");
	  }

	}
		
	
	MPI_Finalize();
	return 0;
}
