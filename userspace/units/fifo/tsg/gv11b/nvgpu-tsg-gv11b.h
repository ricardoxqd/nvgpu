/*
 * Copyright (c) 2019, NVIDIA CORPORATION.  All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#ifndef UNIT_NVGPU_TSG_GV11B_H
#define UNIT_NVGPU_TSG_GV11B_H

#include <nvgpu/types.h>

struct unit_module;
struct gk20a;

/** @addtogroup SWUTS-fifo-tsg-gv11b
 *  @{
 *
 * Software Unit Test Specification for fifo/tsg/gv11b
 */

/**
 * Test specification for: test_gv11b_tsg_init_eng_method_buffers
 *
 * Description: Branch coverage for gv11b_tsg_init_eng_method_buffers
 *
 * Test Type: Feature based
 *
 * Input: test_fifo_init_support() run for this GPU
 *
 * Steps:
 * - Check that engine method buffers can be allocated:
 *    - Build dummy TSG structure with tsg->eng_method_buffers = NULL.
 *    - Call g->ops.tsg.init_eng_method_buffers and check that
 *      eng_method_buffers have been allocated. Also check that
 *      buffer as been mapped (gpu_va must be non NULL).
 * - Check that engine method buffers can be deallocated
 *    - Call g->ops.tsg.init_eng_method_buffers and check that
 *      eng_method_buffers becomes NULL for TSG.
 * - Check engine method buffers initialization failure cases:
 *   - Failure to allocate eng_method_buffers descriptors (by using
 *     fault injection for kzalloc).
 *   - Failure to allocate/map first DMA buffer (by using fault injection
 *     for dma_alloc).
 *   - Failure to allocate/map second DMA buffer (by using fault injection
 *     for dma_alloc, with counter).
 *   In negative testing case, check that an error is returned, and
 *   that eng_method_buffers remains NULL for TSG.
 *
 * Output: Returns PASS if all branches gave expected results. FAIL otherwise.
 */
int test_gv11b_tsg_init_eng_method_buffers(struct unit_module *m,
		struct gk20a *g, void *args);

/**
 * Test specification for: test_gv11b_tsg_bind_channel_eng_method_buffers
 *
 * Description: Branch coverage for gv11b_tsg_bind_channel_eng_method_buffers
 *
 * Test Type: Feature based
 *
 * Input: test_fifo_init_support() run for this GPU
 *
 * Steps:
 * - Allocate TSG and channel.
 * - Bind channel to TSG
 * - Check that channel's method buffer is programmed as per TSG runlist:
 *    - Set TSG's runlist_id to ASYNC_CE and check that channel's ramin
 *      is programmed with gpu_va of ASYNC_CE's method buffer.
 *    - Set TSG's runlist_id to another value, and check that channels'
 *      ramin is programmed with gpu_va of GR_RUNQUE's method buffer.
 *    - Build dummy TSG structure with tsg->eng_method_buffers = NULL.
 * - Check engine method buffers bind failure cases:
 *   - Attempt to bind channel while tsg->eng_method_buffer is NULL.
 *     Check that channel's ramin entries are unchanged.
 *
 * Output: Returns PASS if all branches gave expected results. FAIL otherwise.
 */
int test_gv11b_tsg_bind_channel_eng_method_buffers(struct unit_module *m,
		struct gk20a *g, void *args);

/**
 * Test specification for: test_gv11b_tsg_unbind_channel_check_eng_faulted
 *
 * Description: Branch coverage for gv11b_tsg_unbind_channel_check_eng_faulted
 *
 * Test Type: Feature based
 *
 * Input: test_fifo_init_support() run for this GPU
 *
 * Steps:
 * - Allocate TSG and channel.
 * - Bind channel to TSG
 * - Check unbind channel when related engine is faulted:
 *    - Build fake hw_state with eng_faulted = true (currently, only
 *      CE engine would set this bit).
 *    - Call g->ops.tsg.unbind_channel_check_eng_faulted and check that:
 *      - Check that CE method count is reset if engine method buffer
 *        contains methods for this chid.
 *      - Check that CE method count is unchanged if engine method buffer
 *        does not contain methods for this chid.
 *
 * Output: Returns PASS if all branches gave expected results. FAIL otherwise.
 */
int test_gv11b_tsg_unbind_channel_check_eng_faulted(struct unit_module *m,
		struct gk20a *g, void *args);

/**
 * @}
 */

#endif /* UNIT_NVGPU_TSG_GV11B_H */