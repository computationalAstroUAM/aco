#include "orbit.h"
#include <vector>
#include <valarray>
#include <cstdlib> // for atoi
#include <iostream>
#include <chrono> // for time measurement

int main(int argc, char* argv[]) {
#ifdef USE_OPENMP
    std::cout << "Using OpenMP\n";
    if(argc < 3) {
        std::cout << "Usage: " << argv[0] << " Nsteps num_threads\n";
        return 1;
    }

    int Nsteps = std::atoi(argv[1]);
    std::string num_threads = argv[2];
    setenv("OMP_NUM_THREADS", num_threads.c_str(), 1);
#else
    if(argc < 2) {
        std::cout << "Usage: " << argv[0] << " Nsteps\n";
        return 1;
    }

    int Nsteps = std::atoi(argv[1]);
#endif

    std::vector<Orbit> lfrog(Nsteps), rk4(Nsteps);

    lfrog[0].x  = Dse;
    lfrog[0].y  = 0.;
    lfrog[0].vx = 0.;
    lfrog[0].vy = sqrt(Grav*Msun/Dse);

    rk4[0].x    = Dse;
    rk4[0].y    = 0.;
    rk4[0].vx   = 0.;
    rk4[0].vy   = sqrt(Grav*Msun/Dse);

    double dt = Tend/(double)(Nsteps-1);
    std::chrono::duration<double> elapsed_leapfrog = std::chrono::duration<double>::zero();
    std::chrono::duration<double> elapsed_rungekutta4 = std::chrono::duration<double>::zero();

    for(uint64_t istep=0; istep<Nsteps-1; istep++) {
        auto start = std::chrono::high_resolution_clock::now();
        leapfrog(lfrog, dt, istep);
        auto end = std::chrono::high_resolution_clock::now();
        elapsed_leapfrog += end - start;

        start = std::chrono::high_resolution_clock::now();
        rungekutta4(rk4, dt, istep);
        end = std::chrono::high_resolution_clock::now();
        elapsed_rungekutta4 += end - start;
    }

    std::cout << "Total time elapsed for leapfrog: " << elapsed_leapfrog.count() << " seconds\n";
    std::cout << "Total time elapsed for rungekutta4: " << elapsed_rungekutta4.count() << " seconds\n";

    output(lfrog, "lfrog.dat", Nsteps);
    output(rk4, "rk4.dat", Nsteps);

    return 0;
}