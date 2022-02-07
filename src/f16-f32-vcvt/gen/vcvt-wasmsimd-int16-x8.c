// Auto-generated file. Do not edit!
//   Template: src/f16-f32-vcvt/wasmsimd-int16.c.in
//   Generator: tools/xngen
//
// Copyright 2021 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <wasm_simd128.h>

#include <xnnpack/common.h>
#include <xnnpack/vcvt.h>


void xnn_f16_f32_vcvt_ukernel__wasmsimd_int16_x8(
    size_t n,
    const void* input,
    float* output,
    const union xnn_f16_f32_cvt_params params[restrict XNN_MIN_ELEMENTS(1)]) XNN_OOB_READS
{
  assert(n != 0);
  assert(n % sizeof(uint16_t) == 0);
  assert(input != NULL);
  assert(output != NULL);

  const v128_t vsign_mask = wasm_v128_load64_splat(params->wasmsimd_int16.sign_mask);
  const v128_t vexp_offset = wasm_v128_load64_splat(params->wasmsimd_int16.exp_offset);
  const v128_t vexp_scale = wasm_v128_load64_splat(params->wasmsimd_int16.exp_scale);
  const v128_t vmagic_mask = wasm_v128_load64_splat(params->wasmsimd_int16.magic_mask);
  const v128_t vmagic_bias = wasm_v128_load64_splat(params->wasmsimd_int16.magic_bias);
  const v128_t vdenorm_cutoff = wasm_v128_load64_splat(params->wasmsimd_int16.denorm_cutoff);

  const uint16_t* i = (const uint16_t*) input;
  for (; n >= 8 * sizeof(uint16_t); n -= 8 * sizeof(uint16_t)) {
    const v128_t vh = wasm_v128_load(i);
    i += 8;

    const v128_t vsign = wasm_v128_and(vh, vsign_mask);

    const v128_t vnonsign = wasm_v128_xor(vh, vsign);

    const v128_t vprenorm_lo = wasm_i16x8_shl(vnonsign, 13);
    const v128_t vprenorm_hi = wasm_i16x8_add(wasm_u16x8_shr(vnonsign, 3), vexp_offset);

    const v128_t vnorm_lo = wasm_f32x4_mul(wasm_v16x8_shuffle(vprenorm_lo, vprenorm_hi, 0,  8, 1,  9, 2, 10, 3, 11), vexp_scale);
    const v128_t vnorm_hi = wasm_f32x4_mul(wasm_v16x8_shuffle(vprenorm_lo, vprenorm_hi, 4, 12, 5, 13, 6, 14, 7, 15), vexp_scale);

    const v128_t vdenorm_lo = wasm_f32x4_sub(wasm_v16x8_shuffle(vnonsign, vmagic_mask, 0,  8, 1,  9, 2, 10, 3, 11), vmagic_bias);
    const v128_t vdenorm_hi = wasm_f32x4_sub(wasm_v16x8_shuffle(vnonsign, vmagic_mask, 4, 12, 5, 13, 6, 14, 7, 15), vmagic_bias);

    const v128_t vmask = wasm_i16x8_gt(vnonsign, vdenorm_cutoff);
    const v128_t vzero = wasm_i16x8_const_splat(0);

    const v128_t vxmask_lo = wasm_i32x4_extend_low_i16x8(vmask);
    const v128_t vf_lo = wasm_v128_or(wasm_v16x8_shuffle(vzero, vsign, 0,  8, 1,  9, 2, 10, 3, 11),
      wasm_v128_bitselect(vnorm_lo, vdenorm_lo, vxmask_lo));

    const v128_t vxmask_hi = wasm_i32x4_extend_high_i16x8(vmask);
    const v128_t vf_hi = wasm_v128_or(wasm_v16x8_shuffle(vzero, vsign, 4, 12, 5, 13, 6, 14, 7, 15),
      wasm_v128_bitselect(vnorm_hi, vdenorm_hi, vxmask_hi));

    wasm_v128_store(output, vf_lo);
    wasm_v128_store(output + 4, vf_hi);
    output += 8;
  }
  if XNN_UNLIKELY(n != 0) {
    assert(n >= 1 * sizeof(uint16_t));
    assert(n <= 7 * sizeof(uint16_t));
    const v128_t vh = wasm_v128_load(i);

    const v128_t vsign = wasm_v128_and(vh, vsign_mask);

    const v128_t vnonsign = wasm_v128_xor(vh, vsign);

    const v128_t vprenorm_lo = wasm_i16x8_shl(vnonsign, 13);
    const v128_t vprenorm_hi = wasm_i16x8_add(wasm_u16x8_shr(vnonsign, 3), vexp_offset);

    const v128_t vnorm_lo = wasm_f32x4_mul(wasm_v16x8_shuffle(vprenorm_lo, vprenorm_hi, 0,  8, 1,  9, 2, 10, 3, 11), vexp_scale);
    const v128_t vnorm_hi = wasm_f32x4_mul(wasm_v16x8_shuffle(vprenorm_lo, vprenorm_hi, 4, 12, 5, 13, 6, 14, 7, 15), vexp_scale);

    const v128_t vdenorm_lo = wasm_f32x4_sub(wasm_v16x8_shuffle(vnonsign, vmagic_mask, 0,  8, 1,  9, 2, 10, 3, 11), vmagic_bias);
    const v128_t vdenorm_hi = wasm_f32x4_sub(wasm_v16x8_shuffle(vnonsign, vmagic_mask, 4, 12, 5, 13, 6, 14, 7, 15), vmagic_bias);

    const v128_t vmask = wasm_i16x8_gt(vnonsign, vdenorm_cutoff);
    const v128_t vzero = wasm_i16x8_const_splat(0);

    const v128_t vxmask_lo = wasm_i32x4_extend_low_i16x8(vmask);
    v128_t vf = wasm_v128_or(wasm_v16x8_shuffle(vzero, vsign, 0, 8, 1, 9, 2, 10, 3, 11),
      wasm_v128_bitselect(vnorm_lo, vdenorm_lo, vxmask_lo));

    if (n & (4 * sizeof(uint16_t))) {
      wasm_v128_store(output, vf);
      output += 4;

      const v128_t vxmask_hi = wasm_i32x4_extend_high_i16x8(vmask);
      vf = wasm_v128_or(wasm_v16x8_shuffle(vzero, vsign, 4, 12, 5, 13, 6, 14, 7, 15),
        wasm_v128_bitselect(vnorm_hi, vdenorm_hi, vxmask_hi));
    }
    if (n & (2 * sizeof(uint16_t))) {
      *((double*) output) = wasm_f64x2_extract_lane(vf, 0);
      output += 2;

      vf = wasm_v64x2_shuffle(vf, vf, 1, 1);
    }
    if (n & (1 * sizeof(uint16_t))) {
      *((float*) output) = wasm_f32x4_extract_lane(vf, 0);
    }
  }
}
