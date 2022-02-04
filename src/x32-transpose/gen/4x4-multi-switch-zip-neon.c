// Auto-generated file. Do not edit!
//   Template: src/x32-transpose/neon-zip.c.in
//   Generator: tools/xngen
//
// Copyright 2021 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <arm_neon.h>

#include <assert.h>

#include <xnnpack/common.h>
#include <xnnpack/math.h>
#include <xnnpack/transpose.h>

void xnn_x32_transpose_ukernel__4x4_multi_switch_zip_neon(
    const uint32_t* input,
    uint32_t* output,
    size_t input_stride,
    size_t output_stride,
    size_t block_width,
    size_t block_height)
{
  assert(output_stride >= block_height * sizeof(uint32_t));
  assert(input_stride >= block_width * sizeof(uint32_t));

  const size_t tile_height = 4;
  const size_t tile_width = 4;
  const size_t tile_hbytes = tile_height * sizeof(uint32_t);
  const size_t tile_wbytes = tile_width * sizeof(uint32_t);
  const size_t input_reset = tile_wbytes - round_down_po2(block_height, tile_height) * input_stride;
  const size_t input_offset = tile_height * input_stride;
  const size_t output_reset = tile_width * output_stride - round_down_po2(block_height, 2) * sizeof(uint32_t);

  const uint32_t* i0 = input;
  const uint32_t* i1 = (const uint32_t*) ((uintptr_t) i0 + input_stride);
  const uint32_t* i2 = (const uint32_t*) ((uintptr_t) i1 + input_stride);
  const uint32_t* i3 = (const uint32_t*) ((uintptr_t) i2 + input_stride);
  uint32_t* o = (uint32_t*) output;
  const size_t minus_output_stride = -output_stride;

  do {
    const size_t rem = min(block_width - 1, 3);
    const size_t oN_stride = rem * output_stride;
    size_t bh = block_height;
    for (; bh >= 4; bh -= 4) {
      const uint32x4_t v2_0 = vld1q_u32(i0); i0 = (uint32_t*) ((uintptr_t) i0 + input_offset);
      const uint32x4_t v2_1 = vld1q_u32(i1); i1 = (uint32_t*) ((uintptr_t) i1 + input_offset);
      const uint32x4_t v2_2 = vld1q_u32(i2); i2 = (uint32_t*) ((uintptr_t) i2 + input_offset);
      const uint32x4_t v2_3 = vld1q_u32(i3); i3 = (uint32_t*) ((uintptr_t) i3 + input_offset);

      const uint32x4x2_t v1_0 = vzipq_u32(v2_0, v2_2);
      const uint32x4x2_t v1_1 = vzipq_u32(v2_1, v2_3);

      const uint32x4x2_t v0_0 = vzipq_u32(v1_0.val[0], v1_1.val[0]);
      const uint32x4x2_t v0_1 = vzipq_u32(v1_0.val[1], v1_1.val[1]);

      uint32_t *oN = (uint32_t*) ((uintptr_t) o + oN_stride);
      switch (rem) {
        case 3:
          vst1q_u32(oN, v0_1.val[1]); oN = (uint32_t*) ((uintptr_t) oN + minus_output_stride);
        case 2:
          vst1q_u32(oN, v0_1.val[0]); oN = (uint32_t*) ((uintptr_t) oN + minus_output_stride);
        case 1:
          vst1q_u32(oN, v0_0.val[1]);
        case 0:
          vst1q_u32(o, v0_0.val[0]); o = (uint32_t*) ((uintptr_t) o + tile_hbytes);
          break;
        default:
          XNN_UNREACHABLE;
      }
    }

    if (bh != 0) {
      const uint32x4_t v2_0 = vld1q_u32(i0);
      if XNN_UNPREDICTABLE(bh < 2) {
        i1 = i0;
      }
      const uint32x4_t v2_1 = vld1q_u32(i1);
      if XNN_UNPREDICTABLE(bh <= 2) {
        i2 = i0;
      }
      const uint32x4_t v2_2 = vld1q_u32(i2);
      const uint32x4_t v2_3 = vmovq_n_u32(0);

      const uint32x4x2_t v1_0 = vzipq_u32(v2_0, v2_2);
      const uint32x4x2_t v1_1 = vzipq_u32(v2_1, v2_3);

      const uint32x4x2_t v0_0 = vzipq_u32(v1_0.val[0], v1_1.val[0]);
      const uint32x4x2_t v0_1 = vzipq_u32(v1_0.val[1], v1_1.val[1]);

      uint32x2_t v0_low = vget_low_u32(v0_0.val[0]);
      uint32x2_t v1_low = vget_low_u32(v0_0.val[1]);
      uint32x2_t v2_low = vget_low_u32(v0_1.val[0]);
      uint32x2_t v3_low = vget_low_u32(v0_1.val[1]);

      if (bh & 2) {
        uint32_t* oN = (uint32_t*) ((uintptr_t) o + oN_stride);
        switch (rem) {
          case 3:
            vst1_u32(oN, v3_low); oN = (uint32_t*) ((uintptr_t) oN + minus_output_stride);
          case 2:
            vst1_u32(oN, v2_low); oN = (uint32_t*) ((uintptr_t) oN + minus_output_stride);
          case 1:
            vst1_u32(oN, v1_low);
          case 0:
            vst1_u32(o, v0_low); o += 2;
            break;
          default:
            XNN_UNREACHABLE;
        }
        v0_low = vget_high_u32(v0_0.val[0]);
        v1_low = vget_high_u32(v0_0.val[1]);
        v2_low = vget_high_u32(v0_1.val[0]);
        v3_low = vget_high_u32(v0_1.val[1]);
      }

      if (bh & 1) {
        uint32_t* oN = (uint32_t*) ((uintptr_t) o + oN_stride);
        switch (rem) {
          case 3:
            vst1_lane_u32(oN, v3_low, 0); oN = (uint32_t*) ((uintptr_t) oN + minus_output_stride);
          case 2:
            vst1_lane_u32(oN, v2_low, 0); oN = (uint32_t*) ((uintptr_t) oN + minus_output_stride);
          case 1:
            vst1_lane_u32(oN, v1_low, 0);
          case 0:
            vst1_lane_u32(o, v0_low, 0);
            break;
          default:
            XNN_UNREACHABLE;
        }
      }
    }

    i0 = (const uint32_t*) ((uintptr_t) i0 + input_reset);
    i1 = (const uint32_t*) ((uintptr_t) i0 + input_stride);
    i2 = (const uint32_t*) ((uintptr_t) i1 + input_stride);
    i3 = (const uint32_t*) ((uintptr_t) i2 + input_stride);
    o = (uint32_t*) ((uintptr_t) o + output_reset);
    block_width = doz(block_width, tile_width);
  } while (block_width != 0);
}
