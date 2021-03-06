/* *****************************************************************************
SSA-SDPD simulation engine
Copyright 2018 Brian Drawert (UNCA)

This program is distributed under the terms of the GNU General Public License.
See the file LICENSE.txt for details.
***************************************************************************** */
#ifndef simulate_h
#define simulate_h
#include "particle.h"

void run_simulation(int num_threads, system_t* system);

void take_step1(particle_t* me, system_t*system, unsigned int step);
void take_step2(particle_t* me, system_t*system, unsigned int step);
void compute_forces(particle_t* me, system_t*system, unsigned int step);
//void compute_bond_forces(bond_t* this_bond, system_t*system, unsigned int step);

#endif // simulate_h
