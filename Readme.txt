PROBLEM STATEMENT:-
Write a MPI code to implement a simple Jacobi iteration to solve the Laplace equation in two dimensions with finite differences. 
xnew[i][j] = (x[i+1][j] + x[i-1][j] + x[i][j+1] + x[i][j-1])/4;

Algorithm

•	We have used 4X4 matrix which is divided for 2 processes.
•	Here each element  is updated w.r.t to its surrounding elements and also value is computed based on whether it is border ,corner or 
•	In order to find border points we compute the sum and divide the result by 3.
•	Similarly for corner points we divide it by 2 
•	Rest of the matrix elements is divided by 4.





MPI Functions used:
•	MPI_Init : 
Initialize the MPI execution environment 
Synopsis
int MPI_Init( int *argc, char ***argv )
Input Parameters
argc  : Pointer to the number of arguments 
argv : Pointer to the argument vector 
•	MPI_Finalize:
 Terminates MPI execution environment 
Synopsis
int MPI_Finalize( void )
•	MPI_Send :
 Performs a blocking send 
Synopsis
int MPI_Send(void *buf, int count, MPI_Datatype datatype, int dest, int tag,MPI_Comm comm)
Input Parameters
buf  : initial address of send buffer (choice) 
count : number of elements in send buffer (nonnegative integer) 
datatype : datatype of each send buffer element (handle) 
dest : rank of destination (integer) 
tag : message tag (integer) 
comm : communicator (handle) 

•	MPI_Recv :
 Blocking receive for a message 
Synopsis
int MPI_Recv(void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status)
Output Parameters
buf :initial address of receive buffer (choice) 
status : status object (Status) 
Input Parameters
count : maximum number of elements in receive buffer (integer) 
datatype : datatype of each receive buffer element (handle) 
source : rank of source (integer) 
tag : message tag (integer) 
comm : communicator (handle) 

•	MPI_Allreduce :
 Combines values from all processes and distributes the result back to all processes 
Synopsis
int MPI_Allreduce ( void *sendbuf, void *recvbuf, int count, 
                   MPI_Datatype datatype, MPI_Op op, MPI_Comm comm )
Input Parameters
sendbuf : starting address of send buffer (choice) 
count : number of elements in send buffer (integer) 
datatype : data type of elements of send buffer (handle) 
op : operation (handle) 
comm : communicator (handle) 
Output Parameter
recvbuf : starting address of receive buffer (choice) 
•	MPI_Comm_size : 
Determines the size of the group associated with a communicator 
Synopsis
int MPI_Comm_size( MPI_Comm comm, int *size ) 
Input Parameter
comm : communicator (handle) 
Output Parameter
size : number of processes in the group of comm (integer) 


•	MPI_Comm_rank :
 Determines the rank of the calling process in the communicator 
Synopsis
int MPI_Comm_rank( MPI_Comm comm, int *rank ) 
Input Argument
comm : communicator (handle) 
Output Argument
rank : rank of the calling process in the group of comm (integer).
