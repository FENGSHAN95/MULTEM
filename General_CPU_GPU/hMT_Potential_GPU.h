/*
 * This file is part of MULTEM.
 * Copyright 2014 Ivan Lobato <Ivanlh20@gmail.com>
 *
 * MULTEM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * MULTEM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with MULTEM. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef hMT_Potential_GPU_H
#define hMT_Potential_GPU_H

#include "hConstTypes.h"
#include "hQuadrature.h"
#include "hMT_General_CPU.h"
#include "hMT_General_GPU.h"
#include "hMT_MGP_CPU.h"
#include "hMT_Specimen_CPU.h"
#include "hMT_AtomTypes_GPU.h"

#include "math.h"
#include <cuda.h>
#include <cuda_runtime.h>
#include <device_functions.h>

class cMT_Potential_GPU: public cMT_Specimen_CPU{
	private:
		sQ1 Qz;

		void SetPotPar(int PotParh);
		void LinearProjAtomicPotentialGPU(dim3 grid, dim3 threads);
		void CubicPolyCoef(dim3 grid, dim3 threads);
		void CubicPolyEval(int nsatom, double *&V0g, double *&V1g);

		int CheckGridLimits(int i, int n);
		void getbn(sGP &GP, double x, double y, double Rmax, sbn &bnx, sbn &bny);
		void setcVp(int iSlice, int iatom, int nsatom, dim3 &BPot, dim3 &TPot, dim3 &BCoef, dim3 &TCoef);
	public:
		sGP GP;									// xy-Grid properties
		cMT_AtomTypes_GPU *MT_AtomTypes_GPU;	// Atom types

		double *V0;								// Zero moment of the potential
		double *V1;								// first moment of the potential
		double *V2;								// Second moment of the potential

		void freeMemory();	
		cMT_Potential_GPU();
		~cMT_Potential_GPU();

		void SetInputData(cMT_MGP_CPU *MT_MGP_CPU_io, int nAtomsM_i, double *AtomsM_i);
		void ProjectedPotential(int iSlice);
};

#endif