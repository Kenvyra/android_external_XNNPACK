// Auto-generated file. Do not edit!
//   Template: src/f32-raddstoreexpminusmax/sse2-rr2-p5.c.in
//   Generator: tools/xngen
//
// Copyright 2019 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <emmintrin.h>

#include <xnnpack/common.h>
#include <xnnpack/raddstoreexpminusmax.h>


void xnn_f32_raddstoreexpminusmax_ukernel__sse2_rr2_p5_x4(
    size_t elements,
    const float* input,
    const float* max,
    float* output,
    float* sum,
    const union xnn_f32_expminus_params params[restrict XNN_MIN_ELEMENTS(1)]) XNN_OOB_READS
{
  assert(elements % sizeof(float) == 0);

  const __m128 vi_max = _mm_load1_ps(max);
  const __m128 vlog2e = _mm_load_ps(params->sse2_rr2_p5.log2e);
  const __m128 vmagic_bias = _mm_load_ps(params->sse2_rr2_p5.magic_bias);
  const __m128 vminus_ln2_hi = _mm_load_ps(params->sse2_rr2_p5.minus_ln2_hi);
  const __m128 vminus_ln2_lo = _mm_load_ps(params->sse2_rr2_p5.minus_ln2_lo);
  const __m128 vc5 = _mm_load_ps(params->sse2_rr2_p5.c5);
  const __m128 vc4 = _mm_load_ps(params->sse2_rr2_p5.c4);
  const __m128 vc3 = _mm_load_ps(params->sse2_rr2_p5.c3);
  const __m128 vc2 = _mm_load_ps(params->sse2_rr2_p5.c2);
  const __m128 vc1 = _mm_load_ps(params->sse2_rr2_p5.c1);
  const __m128 vdenorm_cutoff = _mm_load_ps(params->sse2_rr2_p5.denorm_cutoff);

  __m128 vacc0 = _mm_setzero_ps();
  for (; elements >= 4 * sizeof(float); elements -= 4 * sizeof(float)) {
    // Load 4 (1x4) inputs at a time.
    const __m128 vi0123 = _mm_loadu_ps(input);
    input += 4;

    // Subtract maximum input x := i - i_max. This implies x <= 0.
    const __m128 vx0123 = _mm_sub_ps(vi0123, vi_max);

    // Compute reduced argument elements := round(x / log(2)).
    __m128 vn0123 = _mm_add_ps(_mm_mul_ps(vx0123, vlog2e), vmagic_bias);

    // Create a floating-point number s (scale) such that s == 2**elements for inputs which don't cause underflow, i.e.
    // -87.33642 <= x <= 0.0, and -126 <= elements <= 0 accordingly.
    const __m128 vs0123 = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(vn0123), 23));

    // Subtract the large number back to get final elements := round(x / log(2)).
    vn0123 = _mm_sub_ps(vn0123, vmagic_bias);

    // Compute reduced argument t := x - elements * log(2).
    // Use Cody-Waite range reduction method (note two constants to represent log(2)) to improve accuracy.
    __m128 vt0123 = _mm_add_ps(_mm_mul_ps(vn0123, vminus_ln2_hi), vx0123);

    vt0123 = _mm_add_ps(_mm_mul_ps(vn0123, vminus_ln2_lo), vt0123);

    // Compute degree-5 polynomial approximation for exp(t) on [-log(2)/2, log(2)/2].
    __m128 vp0123 = _mm_add_ps(_mm_mul_ps(vc5, vt0123), vc4);

    vp0123 = _mm_add_ps(_mm_mul_ps(vp0123, vt0123), vc3);

    vp0123 = _mm_add_ps(_mm_mul_ps(vp0123, vt0123), vc2);

    vp0123 = _mm_add_ps(_mm_mul_ps(vp0123, vt0123), vc1);

    // Reconstruct the final f value:
    //   f = s * (1 + t * (c1 + t * (c2 + t * (c3 + t * (c4 + t * c5)))))
    //     = s + (t * s) * (c1 + t * (c2 + t * (c3 + t * (c4 + t * c5))))
    //     = s + (t * s) * p
    vt0123 = _mm_mul_ps(vt0123, vs0123);

    __m128 vf0123 = _mm_add_ps(_mm_mul_ps(vt0123, vp0123), vs0123);

    // For inputs below zero cutoff, replace output with +0.0f.
    // Note that for NaN inputs, comparison result is false, and outputs are left unchanged.
    vf0123 = _mm_andnot_ps(_mm_cmplt_ps(vx0123, vdenorm_cutoff), vf0123);

    // Store 4 (1x4) outputs at a time.
    _mm_storeu_ps(output, vf0123);
    output += 4;

    // Accumulate computed exponents.
    vacc0 = _mm_add_ps(vacc0, vf0123);
  }

  __m128 vacc = vacc0;
  for (; elements >= 4 * sizeof(float); elements -= 4 * sizeof(float)) {
    // Load 4 inputs at a time.
    const __m128 vi = _mm_loadu_ps(input);
    input += 4;

    // Subtract maximum input x := i - i_max. This implies x <= 0.
    const __m128 vx = _mm_sub_ps(vi, vi_max);

    // Compute reduced argument elements := round(x / log(2)).
    __m128 vn = _mm_add_ps(_mm_mul_ps(vx, vlog2e), vmagic_bias);

    // Create a floating-point number s (scale) such that s == 2**elements for inputs which don't cause underflow, i.e.
    // -87.33642 <= x <= 0.0, and -126 <= elements <= 0 accordingly.
    const __m128 vs = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(vn), 23));

    // Subtract the large number back to get final elements := round(x / log(2)).
    vn = _mm_sub_ps(vn, vmagic_bias);

    // Compute reduced argument t := x - elements * log(2).
    // Use Cody-Waite range reduction method (note two constants to represent log(2)) to improve accuracy.
    __m128 vt = _mm_add_ps(_mm_mul_ps(vn, vminus_ln2_hi), vx);
    vt = _mm_add_ps(_mm_mul_ps(vn, vminus_ln2_lo), vt);

    // Compute degree-5 polynomial approximation for exp(t) on [-log(2)/2, log(2)/2].
    __m128 vp = _mm_add_ps(_mm_mul_ps(vc5, vt), vc4);
    vp = _mm_add_ps(_mm_mul_ps(vp, vt), vc3);
    vp = _mm_add_ps(_mm_mul_ps(vp, vt), vc2);
    vp = _mm_add_ps(_mm_mul_ps(vp, vt), vc1);

    // Reconstruct the final f value:
    //   f = s * (1 + t * (c1 + t * (c2 + t * (c3 + t * (c4 + t * c5)))))
    //     = s + (t * s) * (c1 + t * (c2 + t * (c3 + t * (c4 + t * c5))))
    //     = s + (t * s) * p
    vt = _mm_mul_ps(vt, vs);
    __m128 vf = _mm_add_ps(_mm_mul_ps(vt, vp), vs);

    // For inputs below zero cutoff, replace output with +0.0f.
    // Note that for NaN inputs, comparison result is false, and outputs are left unchanged.
    vf = _mm_andnot_ps(_mm_cmplt_ps(vx, vdenorm_cutoff), vf);

    // Store 4 outputs at a time.
    _mm_storeu_ps(output, vf);
    output += 4;

    // Accumulate computed exponents.
    vacc = _mm_add_ps(vacc, vf);
  }
  if (elements != 0) {
    assert(elements >= 1 * sizeof(float));
    assert(elements <= 3 * sizeof(float));
    // Load 4 inputs at a time.
    const __m128 vi = _mm_loadu_ps(input);

    // Subtract maximum input x := i - i_max. This implies x <= 0.
    const __m128 vx = _mm_sub_ps(vi, vi_max);

    // Compute reduced argument elements := round(x / log(2)).
    __m128 vn = _mm_add_ps(_mm_mul_ps(vx, vlog2e), vmagic_bias);

    // Create a floating-point number s (scale) such that s == 2**elements for inputs which don't cause underflow, i.e.
    // -87.33642 <= x <= 0.0, and -126 <= elements <= 0 accordingly.
    const __m128 vs = _mm_castsi128_ps(_mm_slli_epi32(_mm_castps_si128(vn), 23));

    // Subtract the large number back to get final elements := round(x / log(2)).
    vn = _mm_sub_ps(vn, vmagic_bias);

    // Compute reduced argument t := x - elements * log(2).
    // Use Cody-Waite range reduction method (note two constants to represent log(2)) to improve accuracy.
    __m128 vt = _mm_add_ps(_mm_mul_ps(vn, vminus_ln2_hi), vx);
    vt = _mm_add_ps(_mm_mul_ps(vn, vminus_ln2_lo), vt);

    // Compute degree-5 polynomial approximation for exp(t) on [-log(2)/2, log(2)/2].
    __m128 vp = _mm_add_ps(_mm_mul_ps(vc5, vt), vc4);
    vp = _mm_add_ps(_mm_mul_ps(vp, vt), vc3);
    vp = _mm_add_ps(_mm_mul_ps(vp, vt), vc2);
    vp = _mm_add_ps(_mm_mul_ps(vp, vt), vc1);

    // Reconstruct the final f value:
    //   f = s * (1 + t * (c1 + t * (c2 + t * (c3 + t * (c4 + t * c5)))))
    //     = s + (t * s) * (c1 + t * (c2 + t * (c3 + t * (c4 + t * c5))))
    //     = s + (t * s) * p
    vt = _mm_mul_ps(vt, vs);
    __m128 vf = _mm_add_ps(_mm_mul_ps(vt, vp), vs);

    // For inputs below zero cutoff, replace output with +0.0f.
    // Note that for NaN inputs, comparison result is false, and outputs are left unchanged.
    vf = _mm_andnot_ps(_mm_cmplt_ps(vx, vdenorm_cutoff), vf);

    if (elements & (2 * sizeof(float))) {
      // Store 2 outputs at a time.
      _mm_storel_pi((__m64*) output, vf);
      output += 2;

      // Accumulate 2 computed exponents.
      vacc = _mm_add_ps(vacc, _mm_movelh_ps(vf, _mm_setzero_ps()));

      vf = _mm_movehl_ps(vf, vf);
    }
    if (elements & (1 * sizeof(float))) {
      // Store 1 output at a time.
      _mm_store_ss(output, vf);

      // Accumulate 1 computed exponent.
      vacc = _mm_add_ss(vacc, vf);
    }
  }
  // Reduce 4 elements in the SIMD register
  vacc = _mm_add_ps(vacc, _mm_movehl_ps(vacc, vacc));
  vacc = _mm_add_ss(vacc, _mm_shuffle_ps(vacc, vacc, _MM_SHUFFLE(2, 3, 0, 1)));
  _mm_store_ss(sum, vacc);
}