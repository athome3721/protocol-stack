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

#include <arch_helpers.h>
#include <plat_marvell.h>
#include <psci.h>
#include <debug.h>


/*******************************************************************************
 * A3700 handler called to check the validity of the power state
 * parameter.
 ******************************************************************************/
int a3700_validate_power_state(unsigned int power_state,
			     psci_power_state_t *req_state)
{
	ERROR("a3700_validate_power_state needs to be implemented\n");
	panic();
}

/*******************************************************************************
 * A3700 handler called when a CPU is about to enter standby.
 ******************************************************************************/
void a3700_cpu_standby(plat_local_state_t cpu_state)
{
	ERROR("a3700_cpu_standby needs to be implemented\n");
	panic();
}

/*******************************************************************************
 * A3700 handler called when a power domain is about to be turned on. The
 * mpidr determines the CPU to be turned on.
 ******************************************************************************/
int a3700_pwr_domain_on(u_register_t mpidr)
{
	psci_0_2_cpu_on_64(mpidr);
	return 0;
}

/*******************************************************************************
 * A3700 handler called to save the entry point which will be later on used
 * when performing CPU on process.
 ******************************************************************************/
int a3700_validate_ns_entrypoint(uintptr_t entrypoint)
{
	psci_save_cpu_entrypoint(entrypoint);
	return PSCI_E_SUCCESS;
}


/*******************************************************************************
 * A3700 handler called when a power domain is about to be turned off. The
 * target_state encodes the power state that each level should transition to.
 ******************************************************************************/
void a3700_pwr_domain_off(const psci_power_state_t *target_state)
{
	ERROR("a3700_pwr_domain_off needs to be implemented\n");
	panic();
}

/*******************************************************************************
 * A3700 handler called when a power domain is about to be suspended. The
 * target_state encodes the power state that each level should transition to.
 ******************************************************************************/
void a3700_pwr_domain_suspend(const psci_power_state_t *target_state)
{
	ERROR("a3700_pwr_domain_suspend needs to be implemented\n");
	panic();
}

/*******************************************************************************
 * A3700 handler called when a power domain has just been powered on after
 * being turned off earlier. The target_state encodes the low power state that
 * each level has woken up from.
 ******************************************************************************/
void a3700_pwr_domain_on_finish(const psci_power_state_t *target_state)
{
	ERROR("a3700_pwr_domain_on_finish needs to be implemented\n");
	panic();
}

/*******************************************************************************
 * A3700 handler called when a power domain has just been powered on after
 * having been suspended earlier. The target_state encodes the low power state
 * that each level has woken up from.
 * TODO: At the moment we reuse the on finisher and reinitialize the secure
 * context. Need to implement a separate suspend finisher.
 ******************************************************************************/
void a3700_pwr_domain_suspend_finish(const psci_power_state_t *target_state)
{
	ERROR("a3700_pwr_domain_suspend_finish needs to be implemented\n");
	panic();
}

/*******************************************************************************
 * A3700 handlers to shutdown/reboot the system
 ******************************************************************************/
static void __dead2 a3700_system_off(void)
{
	ERROR("a3700_system_off needs to be implemented\n");
	panic();
	wfi();
	ERROR("A3700 System Off: operation not handled.\n");
	panic();
}

static void __dead2 a3700_system_reset(void)
{
	psci_0_2_system_reset();
	/* we shouldn't get to this point */
	panic();
}

/*******************************************************************************
 * Export the platform handlers via plat_arm_psci_pm_ops. The ARM Standard
 * platform layer will take care of registering the handlers with PSCI.
 ******************************************************************************/
const plat_psci_ops_t plat_arm_psci_pm_ops = {
	.cpu_standby = a3700_cpu_standby,
	.pwr_domain_on = a3700_pwr_domain_on,
	.pwr_domain_off = a3700_pwr_domain_off,
	.pwr_domain_suspend = a3700_pwr_domain_suspend,
	.pwr_domain_on_finish = a3700_pwr_domain_on_finish,
	.pwr_domain_suspend_finish = a3700_pwr_domain_suspend_finish,
	.system_off = a3700_system_off,
	.system_reset = a3700_system_reset,
	.validate_power_state = a3700_validate_power_state,
	.validate_ns_entrypoint = a3700_validate_ns_entrypoint
};
