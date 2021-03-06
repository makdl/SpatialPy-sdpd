/* SSA-SDPD model file, automatically generated by SpatialPy */
#include <math.h>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "count_cores.h"
#include "particle.h"
#include "propensities.h"
#include "simulate.h"

/* Species names */
__DEFINE_SPECIES__

/* Number of reactions */
#define NR __NUMBER_OF_REACTIONS__  // Depricated, will remove in future version.
#define NUM_REACTIONS __NUMBER_OF_REACTIONS__
#define NUM_SPECIES __NUMBER_OF_SPECIES__
#define NUM_VOXELS __NUMBER_OF_VOXELS__

__DATA_FUNCTION_DEFINITIONS__


/* Parameter definitions */
__DEFINE_PARAMETERS__

/* Reaction definitions */
__DEFINE_REACTIONS__

PropensityFun *ALLOC_propensities(void)
{
    PropensityFun *ptr = (PropensityFun *)malloc(sizeof(PropensityFun)*NUM_REACTIONS);
    
__DEFINE_PROPFUNS__
    return ptr;
}

void FREE_propensities(PropensityFun* ptr)
{
    free(ptr);
}

ChemRxnFun* ALLOC_ChemRxnFun(void){
    ChemRxnFun*ptr = (ChemRxnFun*)malloc(sizeof(ChemRxnFun)*NUM_REACTIONS);
__DEFINE_CHEM_FUNS__
    return ptr;
}
void FREE_ChemRxnFun(ChemRxnFun* ptr){
    free(ptr);
}


__INPUT_CONSTANTS__

int debug_flag;

void init_create_particle(system_t* sys, int id, double x, double y, double z, int type){
    particle_t* p = create_particle(id);
    p->x[0] = x;
    p->x[1] = y;
    p->x[2] = z;
    p->id = id;
    p->type = type;
    p->rho = sys->rho0;
    p->mass = input_vol[id];
    add_particle(p, sys);
}


int init_all_particles(system_t* sys){
    int id=0;
    __INIT_PARTICLES__
    return id;
}


int main(int argc, char**argv){
    debug_flag = 0;
    //system_t* system = create_system();
    // Fix particles in space
    //system->static_domain = 1;
    //CONFIG = 
    //system->dt = 1;
    //system->nt = 101;
    //system->output_freq = 1;
    //system->h = 0.5;
    //system->rho0 = 1.0;
    //system->c0 = 10;
    //system->P0 = 10;
    // bounding box
    //system->xlo = -5.1;
    //system->xhi = 5.1;
    //system->ylo = -1.1;
    //system->yhi = 1.1;
    //system->zlo = -1.1;
    //system->zhi = 1.1;
    __SYSTEM_CONFIG__
    // create all particles in system
    init_all_particles(system);
    // Setup chemical reaction system
    initialize_rdme(system, NUM_VOXELS, NUM_SPECIES, NUM_REACTIONS, input_vol, input_sd,
                    input_data, input_dsize, input_irN, input_jcN, input_prN, input_irG,
                    input_jcG, input_species_names, input_u0, input_num_subdomain,
                    input_subdomain_diffusion_matrix);

    if(argc>1){
        srand48(atol(argv[1]));
    }else{
        srand48((long int)time(NULL)+(long int)(1e9*clock()));
    }
    int num_threads = get_num_processors();
    if(num_threads>8){ num_threads=8; }
    run_simulation(num_threads, system);
    exit(0);
}

