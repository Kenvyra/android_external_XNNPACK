// Auto-generated file. Do not edit!
//   Template: src/qs8-gemm/scalar.c.in
//   Generator: tools/xngen
//
// Copyright 2021 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <xnnpack/scalar-utils.h>
#include <xnnpack/gemm.h>


void xnn_qs8_gemm_minmax_ukernel_1x4__scalar(
    size_t mr,
    size_t nc,
    size_t kc,
    const int8_t* restrict a,
    size_t a_stride,
    const void* restrict w,
    int8_t* restrict c,
    size_t cm_stride,
    size_t cn_stride,
    const union xnn_qs8_gemm_params params[restrict XNN_MIN_ELEMENTS(1)])
{
  assert(mr != 0);
  assert(mr <= 1);
  assert(nc != 0);
  assert(kc != 0);

  const int8_t* a0 = a;
  int8_t* c0 = c;

  do {
    int32_t vacc0x0 = ((const int32_t*) w)[0];
    int32_t vacc0x1 = ((const int32_t*) w)[1];
    int32_t vacc0x2 = ((const int32_t*) w)[2];
    int32_t vacc0x3 = ((const int32_t*) w)[3];
    w = (const void*) ((uintptr_t) w + 4 * sizeof(int32_t));

    size_t k = kc;
    do {
      const int32_t va0 = (int32_t) *a0++;

      const int32_t vb0 = ((const int8_t*) w)[0];
      const int32_t vb1 = ((const int8_t*) w)[1];
      const int32_t vb2 = ((const int8_t*) w)[2];
      const int32_t vb3 = ((const int8_t*) w)[3];
      w = (const void*) ((uintptr_t) w + 4 * sizeof(int8_t));

      vacc0x0 += va0 * vb0;
      vacc0x1 += va0 * vb1;
      vacc0x2 += va0 * vb2;
      vacc0x3 += va0 * vb3;

      k -= sizeof(int8_t);
    } while (k != 0);

    const int32_t vmultiplier = params->scalar.multiplier;
    const int64_t vproduct0x0 = (int64_t) vacc0x0 * (int64_t) vmultiplier;
    const int64_t vproduct0x1 = (int64_t) vacc0x1 * (int64_t) vmultiplier;
    const int64_t vproduct0x2 = (int64_t) vacc0x2 * (int64_t) vmultiplier;
    const int64_t vproduct0x3 = (int64_t) vacc0x3 * (int64_t) vmultiplier;

    const int64_t vq31rounding = INT64_C(0x40000000);
    const int32_t vq31product0x0 = (int32_t) (uint32_t) ((uint64_t) (vproduct0x0 + vq31rounding) >> 31);
    const int32_t vq31product0x1 = (int32_t) (uint32_t) ((uint64_t) (vproduct0x1 + vq31rounding) >> 31);
    const int32_t vq31product0x2 = (int32_t) (uint32_t) ((uint64_t) (vproduct0x2 + vq31rounding) >> 31);
    const int32_t vq31product0x3 = (int32_t) (uint32_t) ((uint64_t) (vproduct0x3 + vq31rounding) >> 31);

    const int32_t vremainder_mask = params->scalar.remainder_mask;
    const int32_t vremainder0x0 = (vq31product0x0 & vremainder_mask) - (int32_t) (vq31product0x0 < 0);
    const int32_t vremainder0x1 = (vq31product0x1 & vremainder_mask) - (int32_t) (vq31product0x1 < 0);
    const int32_t vremainder0x2 = (vq31product0x2 & vremainder_mask) - (int32_t) (vq31product0x2 < 0);
    const int32_t vremainder0x3 = (vq31product0x3 & vremainder_mask) - (int32_t) (vq31product0x3 < 0);

    const uint32_t vshift = params->scalar.shift;
    const int32_t vremainder_threshold = params->scalar.remainder_threshold;
    int32_t vout0x0 = asr_s32(vq31product0x0, vshift) + (int32_t) (vremainder0x0 > vremainder_threshold);
    int32_t vout0x1 = asr_s32(vq31product0x1, vshift) + (int32_t) (vremainder0x1 > vremainder_threshold);
    int32_t vout0x2 = asr_s32(vq31product0x2, vshift) + (int32_t) (vremainder0x2 > vremainder_threshold);
    int32_t vout0x3 = asr_s32(vq31product0x3, vshift) + (int32_t) (vremainder0x3 > vremainder_threshold);

    const int32_t vout_min = params->scalar.output_min_less_zero_point;
    vout0x0 = XNN_UNPREDICTABLE(vout0x0 < vout_min) ? vout_min : vout0x0;
    vout0x1 = XNN_UNPREDICTABLE(vout0x1 < vout_min) ? vout_min : vout0x1;
    vout0x2 = XNN_UNPREDICTABLE(vout0x2 < vout_min) ? vout_min : vout0x2;
    vout0x3 = XNN_UNPREDICTABLE(vout0x3 < vout_min) ? vout_min : vout0x3;

    const int32_t vout_max = params->scalar.output_max_less_zero_point;
    vout0x0 = XNN_UNPREDICTABLE(vout0x0 > vout_max) ? vout_max : vout0x0;
    vout0x1 = XNN_UNPREDICTABLE(vout0x1 > vout_max) ? vout_max : vout0x1;
    vout0x2 = XNN_UNPREDICTABLE(vout0x2 > vout_max) ? vout_max : vout0x2;
    vout0x3 = XNN_UNPREDICTABLE(vout0x3 > vout_max) ? vout_max : vout0x3;

    const int32_t voutput_zero_point = params->scalar.output_zero_point;
    vout0x0 += voutput_zero_point;
    vout0x1 += voutput_zero_point;
    vout0x2 += voutput_zero_point;
    vout0x3 += voutput_zero_point;

    if XNN_LIKELY(nc >= 4) {
      c0[0] = (int8_t) vout0x0;
      c0[1] = (int8_t) vout0x1;
      c0[2] = (int8_t) vout0x2;
      c0[3] = (int8_t) vout0x3;

      a0 = (const int8_t*) ((uintptr_t) a0 - kc);

      c0 = (int8_t*) ((uintptr_t) c0 + cn_stride);

      nc -= 4;
    } else {
      if (nc & 2) {
        c0[0] = (int8_t) vout0x0;
        c0[1] = (int8_t) vout0x1;
        vout0x0 = vout0x2;
        c0 += 2;
      }
      if (nc & 1) {
        c0[0] = (int8_t) vout0x0;
      }

      nc = 0;
    }
  } while (nc != 0);
}
