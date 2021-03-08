#!/bin/bash

# Rsyncs the files to the class01 RHL machine in DSL152, then compile and run for a range of n processors, with 20 reps for each n.
# Resulting times are returned via ssh and piped to file.
# To change the maximum integer to consider, directly modify the '#define LIMIT' line at the top of the source file.

# Note: This script relies on my personal .ssh/config, so if you're trying to run this and you aren't me, it won't work directly -- but I'll probably leave a separate script commented out at the bottom of this file to compile and run on your local machine (I'll assume you're on a DSC machine using the MPI 'module'.

set -euo pipefail

# average TOTAL wallclock time for twin-prime search over range of # processors
for np in {1,2,4,8,16}; do
	for rep in {1..20}; do
		echo "NP = $np Rep $rep" >&2
		sshpass -p "$DSCPASS" rsync MPIPrimes.cpp class01:~/
		sshpass -p "$DSCPASS" ssh -tq class01 'source /etc/profile && module load mpi && mpic++ -std=c++11 MPIPrimes.cpp && mpirun -np '"$np"' a.out'
	done | awk 'BEGIN{sum=0}{sum+=$0}END{print sum / NR}'
done | tee times

# load balancing: each thread's wallclock time (only considering time spent in parallel, not waiting).  One rep should suffice.
sshpass -p "$DSCPASS" rsync MPIPrimes_LoadBalance.cpp class01:~/
sshpass -p "$DSCPASS" ssh -tq class01 'source /etc/profile && module load mpi && mpic++ -std=c++11 MPIPrimes_LoadBalance.cpp && mpirun -np 16 a.out' | tee balance

### example of compiling and running on local machine w/ 8 threads
#module load mpi
#mpic++ -std=c++11 MPIPrimes.cpp
#mpirun -np 8 a.out
