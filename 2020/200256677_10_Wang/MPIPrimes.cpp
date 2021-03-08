#define LIMIT 10e5 // maximum integer (long) to consider

#include <iostream>
#include <mpi.h>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {

    long limit = LIMIT;

    // MPI initialization
    int npes,mype,ierr;
    ierr = MPI_Init(&argc, &argv);
    ierr = MPI_Comm_size(MPI_COMM_WORLD, &npes);
    ierr = MPI_Comm_rank(MPI_COMM_WORLD, &mype);

    // start the clock
    double start_time = MPI_Wtime();

    // each processor's start and stride
    int my_start = 3 + (mype * 2);
    long stride = npes * 2;
    
    // parallel search for primes
    vector<long> my_primes;
    for(long n = my_start; n < limit; n += stride) {
        
        long root = sqrt(n);
        bool is_prime = true;
        
        // search for factors
        for(int i = 3; i <= root; i += 2) {
        
            // if integer n is not prime
            if(n % i == 0) {

                is_prime = false;
                break;

            }
        
        }

        // append prime to this processor's vector
        if(is_prime) {

            my_primes.push_back(n);

        }

    }

    // wait for all processes to reach this point
    MPI_Barrier(MPI_COMM_WORLD);

    // collect number of primes found on each process
    // since each process hold variable length vector and each process must know the length of other processes' vectors before gathering the vectors
    int prime_counts[npes];
    prime_counts[mype] = my_primes.size();
    MPI_Allgather(&prime_counts[mype], 1, MPI_INT, &prime_counts, 1, MPI_INT, MPI_COMM_WORLD);

    // next, compute displacement (start position of each vector to be concatenated)
    int displacement[npes];
    int position = 0;
    for(int i = 0; i < npes; i++) {

        displacement[i] = position;
        position += prime_counts[i];
    
    }
    int total_primes_found = position;

    // convert vector to array so it can be safely sent
    long sendbuf[prime_counts[mype]];
    for(int i = 0; i < prime_counts[mype]; i++) {
    
        sendbuf[i] = my_primes[i];
    
    }

    // collect all primes and sync to all processes
    long all_primes[total_primes_found];
    MPI_Allgatherv(&sendbuf, prime_counts[mype], MPI_LONG, &all_primes, prime_counts, displacement, MPI_LONG, MPI_COMM_WORLD);

    // parallel search for twin primes
    int my_twin_count = 0;
    for(int i = mype; i < total_primes_found; i+=npes) {
        long candidate = all_primes[i];
        // check if candidate + 2 exists in (unsorted) array of primes
        long *twinpos = find(all_primes, all_primes + total_primes_found, candidate + 2);
        long twin = *twinpos;
        // find returns last element in array if search-element is not found, verify distance = 2
        if(twin - candidate == 2) {
            my_twin_count++;
        }
    }
    
    // wait for all processes to reach this point 
    MPI_Barrier(MPI_COMM_WORLD);

    // sum up twin prime count
    int twin_count = 0;
    MPI_Allreduce(&my_twin_count, &twin_count, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

    // safely exit mpi section
    MPI_Finalize();

    // output
    if(mype == 0) {
        // cerr << twin_count << endl;
        cout << MPI_Wtime() - start_time << endl;
    }

}