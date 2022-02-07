// Auto-generated file. Do not edit!
//   Template: src/f32-vrnd/vrndd-sse2.c.in
//   Generator: tools/xngen
//
// Copyright 2020 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <emmintrin.h>

#include <xnnpack/common.h>
#include <xnnpack/math.h>
#include <xnnpack/vunary.h>


void xnn_f32_vrndd_ukernel__sse2_x4(
    size_t n,
    const float* x,
    float* y,
    const union xnn_f32_rnd_params params[restrict XNN_MIN_ELEMENTS(1)]) XNN_OOB_READS
{
  assert(n != 0);
  assert(n % sizeof(float) == 0);

  const __m128i vmagic = _mm_load_si128((const __m128i*) params->sse2.sign_mask);
  const __m128 vone = _mm_load_ps(params->sse2.one);
  for (; n >= 4 * sizeof(float); n -= 4 * sizeof(float)) {
    const __m128 vx0123 = _mm_loadu_ps(x);
    x += 4;

    const __m128i vintx0123 = _mm_cvttps_epi32(vx0123);

    const __m128 vrndmask0123 = _mm_castsi128_ps(_mm_or_si128(vmagic, _mm_cmpeq_epi32(vintx0123, vmagic)));

    const __m128 vprerndx0123 = _mm_cvtepi32_ps(vintx0123);

    const __m128 vrndx0123 = _mm_or_ps(_mm_and_ps(vx0123, vrndmask0123), _mm_andnot_ps(vrndmask0123, vprerndx0123));

    const __m128 vy0123 = _mm_sub_ps(vrndx0123, _mm_and_ps(_mm_cmpgt_ps(vrndx0123, vx0123), vone));

    _mm_storeu_ps(y, vy0123);
    y += 4;
  }
  if XNN_UNLIKELY(n != 0) {
    const __m128 vx = _mm_loadu_ps(x);
    const __m128i vintx = _mm_cvttps_epi32(vx);
    const __m128 vrndmask = _mm_castsi128_ps(_mm_or_si128(vmagic, _mm_cmpeq_epi32(vintx, vmagic)));
    const __m128 vprerndx = _mm_cvtepi32_ps(vintx);
    const __m128 vrndx = _mm_or_ps(_mm_and_ps(vx, vrndmask), _mm_andnot_ps(vrndmask, vprerndx));
    __m128 vy = _mm_sub_ps(vrndx, _mm_and_ps(_mm_cmpgt_ps(vrndx, vx), vone));
    if (n & (2 * sizeof(float))) {
      _mm_storel_pi((__m64*) y, vy);
      vy = _mm_movehl_ps(vy, vy);
      y += 2;
    }
    if (n & (1 * sizeof(float))) {
      _mm_store_ss(y, vy);
    }
  }
}
