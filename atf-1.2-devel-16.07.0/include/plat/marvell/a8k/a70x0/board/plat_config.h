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
#ifndef __BOARD_CONFIG_H__
#define __BOARD_CONFIG_H__

#include <amb_adec.h>
#include <rfu.h>
#include <iob.h>
#include <ccu.h>


uintptr_t marvell_get_amb_reg_offs(int cp_index);
uintptr_t marvell_get_rfu_reg_offs(void);
uintptr_t marvell_get_iob_reg_offs(int cp_index);
int marvell_get_iob_max_win(void);
uintptr_t marvell_get_ccu_reg_offs(void);
int marvell_get_ccu_max_win(void);


/* The functions below are defined as Weak and may be overridden in specific Marvell
   standard platform */
int marvell_get_amb_memory_map(struct amb_win **win, uint32_t *size);
int marvell_get_rfu_memory_map(struct rfu_win **win, uint32_t *size);
int marvell_get_iob_memory_map(struct iob_win **win, uint32_t *size, int cp_index);
int marvell_get_ccu_memory_map(struct ccu_win **win, uint32_t *size);

#endif /* __BOARD_CONFIG_H__ */
