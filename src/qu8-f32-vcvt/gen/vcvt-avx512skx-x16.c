// Auto-generated file. Do not edit!
//   Template: src/qs8-f32-vcvt/avx512skx.c.in
//   Generator: tools/xngen
//
// Copyright 2021 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <immintrin.h>

#include <xnnpack/common.h>
#include <xnnpack/intrinsics-polyfill.h>
#include <xnnpack/vcvt.h>


void xnn_qu8_f32_vcvt_ukernel__avx512skx_x16(
    size_t n,
    const uint8_t* x,
    float* y,
    const union xnn_qu8_f32_cvt_params params[restrict XNN_MIN_ELEMENTS(1)]) XNN_OOB_READS
{
  assert(n != 0);
  assert(n % sizeof(uint8_t) == 0);
  assert(x != NULL);
  assert(y != NULL);

  const __m512i vminus_zero_point = _mm512_load_si512(params->avx512.minus_zero_point);
  const __m512 vscale = _mm512_load_ps(params->avx512.scale);
  for (; n >= 16 * sizeof(uint8_t); n -= 16 * sizeof(uint8_t)) {
    __m512i vx = _mm512_cvtepu8_epi32(_mm_loadu_si128((const __m128i*) x));
    vx = _mm512_add_epi32(vx, vminus_zero_point);
    x += 16;

    __m512 vy = _mm512_cvtepi32_ps(vx);
    vy = _mm512_mul_ps(vy, vscale);

    _mm512_storeu_ps(y, vy);
    y += 16;
  }
  if XNN_UNLIKELY(n != 0) {
    assert(n >= 1 * sizeof(uint8_t));
    assert(n <= 15 * sizeof(uint8_t));

    // Prepare mask for valid elements (depends on n).
    const __mmask16 vmask = _cvtu32_mask16((uint16_t) ((uint32_t) (UINT32_C(1) << n) - UINT32_C(1)));

    __m512i vx = _mm512_cvtepu8_epi32(_mm_maskz_loadu_epi8(vmask, x));
    vx = _mm512_add_epi32(vx, vminus_zero_point);

    __m512 vy = _mm512_cvtepi32_ps(vx);
    vy = _mm512_mul_ps(vy, vscale);

    _mm512_mask_storeu_ps(y, vmask, vy);
  }
}
