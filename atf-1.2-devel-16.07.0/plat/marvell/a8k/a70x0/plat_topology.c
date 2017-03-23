/*
* ***************************************************************************
* Copyright (C) 2016 Marvell International Ltd.
* ***************************************************************************
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* Redistributions of source code must retain the above copyright notice, this
* list of conditions and the following disclaimer.
*
* Redistributions in binary form must reproduce the above copyright notice,
* this list of conditions and the following disclaimer in the documentation
* and/or other materials provided with the distribution.
*
* Neither the name of Marvell nor the names of its contributors may be used
* to endorse or promote products derived from this software without specific
* prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
* OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
***************************************************************************
*/

#include <plat_marvell.h>
#include <assert.h>

#define MPIDR_CLUSTER_ID_OFFEST		8
#define MPIDR_CLUSTER_ID_MASK		0xF
#define MPIDR_CPU_ID_MASK		0x3


const unsigned char arm_power_domain_tree_desc[] = {
	/* No of root nodes */
	PLAT_MARVELL_CLUSTER_COUNT,
	/* No of children for the first node */
	PLAT_MARVELL_CLUSTER_CORE_COUNT,
	/* No of children for the second node */
	PLAT_MARVELL_CLUSTER_CORE_COUNT,
#ifdef PLAT_MARVELL_APN_806_Z /* there are 4 clusters in Z1 */
	/* No of children for the third node */
	PLAT_MARVELL_CLUSTER_CORE_COUNT,
	/* No of children for the fourth node */
	PLAT_MARVELL_CLUSTER_CORE_COUNT
#endif
};


/*******************************************************************************
 * This function implements a part of the critical interface between the psci
 * generic layer and the platform that allows the former to query the platform
 * to convert an MPIDR to a unique linear index. An error code (-1) is returned
 * in case the MPIDR is invalid.
 ******************************************************************************/
int plat_core_pos_by_mpidr(u_register_t mpidr)
{
	int target_id;
	int cluster, cpu;

	cluster = (mpidr >> MPIDR_CLUSTER_ID_OFFEST) & MPIDR_CLUSTER_ID_MASK;
	cpu = mpidr & MPIDR_CPU_ID_MASK;

	assert(cpu < PLAT_MARVELL_CLUSTER_CORE_COUNT);

	target_id = (cluster * PLAT_MARVELL_CLUSTER_CORE_COUNT) + cpu;

	return target_id;
}

