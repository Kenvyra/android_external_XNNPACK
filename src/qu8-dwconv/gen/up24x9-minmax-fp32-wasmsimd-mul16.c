// Auto-generated file. Do not edit!
//   Template: src/qs8-dwconv/unipass-wasmsimd-mul16.c.in
//   Generator: tools/xngen
//
// Copyright 2020 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <wasm_simd128.h>

#include <xnnpack/dwconv.h>


void xnn_qu8_dwconv_minmax_fp32_ukernel_up24x9__wasmsimd_mul16(
    size_t channels,
    size_t output_width,
    const uint8_t** input,
    const void* weights,
    uint8_t* output,
    size_t input_stride,
    size_t output_increment,
    size_t input_offset,
    const uint8_t* zero,
    const union xnn_qu8_conv_minmax_params params[restrict XNN_MIN_ELEMENTS(1)]) XNN_OOB_READS
{
  assert(channels != 0);
  assert(output_width != 0);

  const v128_t vkernel_zero_point = wasm_u32x4_load16x4(params->fp32_wasmsimd.kernel_zero_point);
  do {
    const uint8_t* i0 = input[0];
    assert(i0 != NULL);
    if XNN_UNPREDICTABLE(i0 != zero) {
      i0 = (const uint8_t*) ((uintptr_t) i0 + input_offset);
    }
    const uint8_t* i1 = input[1];
    assert(i1 != NULL);
    if XNN_UNPREDICTABLE(i1 != zero) {
      i1 = (const uint8_t*) ((uintptr_t) i1 + input_offset);
    }
    const uint8_t* i2 = input[2];
    assert(i2 != NULL);
    if XNN_UNPREDICTABLE(i2 != zero) {
      i2 = (const uint8_t*) ((uintptr_t) i2 + input_offset);
    }
    const uint8_t* i3 = input[3];
    assert(i3 != NULL);
    if XNN_UNPREDICTABLE(i3 != zero) {
      i3 = (const uint8_t*) ((uintptr_t) i3 + input_offset);
    }
    const uint8_t* i4 = input[4];
    assert(i4 != NULL);
    if XNN_UNPREDICTABLE(i4 != zero) {
      i4 = (const uint8_t*) ((uintptr_t) i4 + input_offset);
    }
    const uint8_t* i5 = input[5];
    assert(i5 != NULL);
    if XNN_UNPREDICTABLE(i5 != zero) {
      i5 = (const uint8_t*) ((uintptr_t) i5 + input_offset);
    }
    const uint8_t* i6 = input[6];
    assert(i6 != NULL);
    if XNN_UNPREDICTABLE(i6 != zero) {
      i6 = (const uint8_t*) ((uintptr_t) i6 + input_offset);
    }
    const uint8_t* i7 = input[7];
    assert(i7 != NULL);
    if XNN_UNPREDICTABLE(i7 != zero) {
      i7 = (const uint8_t*) ((uintptr_t) i7 + input_offset);
    }
    const uint8_t* i8 = input[8];
    assert(i8 != NULL);
    if XNN_UNPREDICTABLE(i8 != zero) {
      i8 = (const uint8_t*) ((uintptr_t) i8 + input_offset);
    }
    input = (const uint8_t**) ((uintptr_t) input + input_stride);

    size_t c = channels;
    const void* w = weights;
    for (; c >= 24; c -= 24) {
      v128_t vacc0123 = wasm_v128_load(w);
      v128_t vacc4567 = wasm_v128_load((const void*) ((uintptr_t) w + 4 * sizeof(int32_t)));
      v128_t vacc89AB = wasm_v128_load((const void*) ((uintptr_t) w + 8 * sizeof(int32_t)));
      v128_t vaccCDEF = wasm_v128_load((const void*) ((uintptr_t) w + 12 * sizeof(int32_t)));
      v128_t vaccGHIJ = wasm_v128_load((const void*) ((uintptr_t) w + 16 * sizeof(int32_t)));
      v128_t vaccKLMN = wasm_v128_load((const void*) ((uintptr_t) w + 20 * sizeof(int32_t)));


      const v128_t vi0x01234567 = wasm_u16x8_load8x8(i0);
      const v128_t vk0x01234567 = wasm_u16x8_load8x8((const void*) ((uintptr_t) w + 24 * sizeof(int32_t) + 0 * sizeof(uint8_t)));
      const v128_t vi0x89ABCDEF = wasm_u16x8_load8x8(i0 + 8);
      const v128_t vk0x89ABCDEF = wasm_u16x8_load8x8((const void*) ((uintptr_t) w + 24 * sizeof(int32_t) + 8 * sizeof(uint8_t)));
      const v128_t vi0xGHIJKLMN = wasm_u16x8_load8x8(i0 + 16);
      const v128_t vk0xGHIJKLMN = wasm_u16x8_load8x8((const void*) ((uintptr_t) w + 24 * sizeof(int32_t) + 16 * sizeof(uint8_t)));
      i0 += 24;

      v128_t vprod01234567 = wasm_i16x8_mul(vi0x01234567, vk0x01234567);
      v128_t vprod89ABCDEF = wasm_i16x8_mul(vi0x89ABCDEF, vk0x89ABCDEF);
      v128_t vprodGHIJKLMN = wasm_i16x8_mul(vi0xGHIJKLMN, vk0xGHIJKLMN);

      vacc0123 = wasm_i32x4_add(vacc0123, wasm_u32x4_extend_low_u16x8(vprod01234567));
      vacc4567 = wasm_i32x4_add(vacc4567, wasm_u32x4_extend_high_u16x8(vprod01234567));
      vacc89AB = wasm_i32x4_add(vacc89AB, wasm_u32x4_extend_low_u16x8(vprod89ABCDEF));
      vaccCDEF = wasm_i32x4_add(vaccCDEF, wasm_u32x4_extend_high_u16x8(vprod89ABCDEF));
      vaccGHIJ = wasm_i32x4_add(vaccGHIJ, wasm_u32x4_extend_low_u16x8(vprodGHIJKLMN));
      vaccKLMN = wasm_i32x4_add(vaccKLMN, wasm_u32x4_extend_high_u16x8(vprodGHIJKLMN));

      const v128_t vi1x01234567 = wasm_u16x8_load8x8(i1);
      const v128_t vk1x01234567 = wasm_u16x8_load8x8((const void*) ((uintptr_t) w + 24 * sizeof(int32_t) + 24 * sizeof(uint8_t)));
      const v128_t vi1x89ABCDEF = wasm_u16x8_load8x8(i1 + 8);
      const v128_t vk1x89ABCDEF = wasm_u16x8_load8x8((const void*) ((uintptr_t) w + 24 * sizeof(int32_t) + 32 * sizeof(uint8_t)));
      const v128_t vi1xGHIJKLMN = wasm_u16x8_load8x8(i1 + 16);
      const v128_t vk1xGHIJKLMN = wasm_u16x8_load8x8((const void*) ((uintptr_t) w + 24 * sizeof(int32_t) + 40 * sizeof(uint8_t)));
      v128_t vsumx01234567 = wasm_i16x8_add(vi0x01234567, vi1x01234567);
      v128_t vsumx89ABCDEF = wasm_i16x8_add(vi0x89ABCDEF, vi1x89ABCDEF);
      v128_t vsumxGHIJKLMN = wasm_i16x8_add(vi0xGHIJKLMN, vi1xGHIJKLMN);
      i1 += 24;

      vprod01234567 = wasm_i16x8_mul(vi1x01234567, vk1x01234567);
      vprod89ABCDEF = wasm_i16x8_mul(vi1x89ABCDEF, vk1x89ABCDEF);
      vprodGHIJKLMN = wasm_i16x8_mul(vi1xGHIJKLMN, vk1xGHIJKLMN);

      vacc0123 = wasm_i32x4_add(vacc0123, wasm_u32x4_extend_low_u16x8(vprod01234567));
      vacc4567 = wasm_i32x4_add(vacc4567, wasm_u32x4_extend_high_u16x8(vprod01234567));
      vacc89AB = wasm_i32x4_add(vacc89AB, wasm_u32x4_extend_low_u16x8(vprod89ABCDEF));
      vaccCDEF = wasm_i32x4_add(vaccCDEF, wasm_u32x4_extend_high_u16x8(vprod89ABCDEF));
      vaccGHIJ = wasm_i32x4_add(vaccGHIJ, wasm_u32x4_extend_low_u16x8(vprodGHIJKLMN));
      vaccKLMN = wasm_i32x4_add(vaccKLMN, wasm_u32x4_extend_high_u16x8(vprodGHIJKLMN));

      const v128_t vi2x01234567 = wasm_u16x8_load8x8(i2);
      const v128_t vk2x01234567 = wasm_u16x8_load8x8((const void*) ((uintptr_t) w + 24 * sizeof(int32_t) + 48 * sizeof(uint8_t)));
      const v128_t vi2x89ABCDEF = wasm_u16x8_load8x8(i2 + 8);
      const v128_t vk2x89ABCDEF = wasm_u16x8_load8x8((const void*) ((uintptr_t) w + 24 * sizeof(int32_t) + 56 * sizeof(uint8_t)));
      const v128_t vi2xGHIJKLMN = wasm_u16x8_load8x8(i2 + 16);
      const v128_t vk2xGHIJKLMN = wasm_u16x8_load8x8((const void*) ((uintptr_t) w + 24 * sizeof(int32_t) + 64 * sizeof(uint8_t)));
      vsumx01234567 = wasm_i16x8_add(vsumx01234567, vi2x01234567);
      vsumx89ABCDEF = wasm_i16x8_add(vsumx89ABCDEF, vi2x89ABCDEF);
      vsumxGHIJKLMN = wasm_i16x8_add(vsumxGHIJKLMN, vi2xGHIJKLMN);
      i2 += 24;

      vprod01234567 = wasm_i16x8_mul(vi2x01234567, vk2x01234567);
      vprod89ABCDEF = wasm_i16x8_mul(vi2x89ABCDEF, vk2x89ABCDEF);
      vprodGHIJKLMN = wasm_i16x8_mul(vi2xGHIJKLMN, vk2xGHIJKLMN);

      vacc0123 = wasm_i32x4_add(vacc0123, wasm_u32x4_extend_low_u16x8(vprod01234567));
      vacc4567 = wasm_i32x4_add(vacc4567, wasm_u32x4_extend_high_u16x8(vprod01234567));
      vacc89AB = wasm_i32x4_add(vacc89AB, wasm_u32x4_extend_low_u16x8(vprod89ABCDEF));
      vaccCDEF = wasm_i32x4_add(vaccCDEF, wasm_u32x4_extend_high_u16x8(vprod89ABCDEF));
      vaccGHIJ = wasm_i32x4_add(vaccGHIJ, wasm_u32x4_extend_low_u16x8(vprodGHIJKLMN));
      vaccKLMN = wasm_i32x4_add(vaccKLMN, wasm_u32x4_extend_high_u16x8(vprodGHIJKLMN));

      const v128_t vi3x01234567 = wasm_u16x8_load8x8(i3);
      const v128_t vk3x01234567 = wasm_u16x8_load8x8((const void*) ((uintptr_t) w + 24 * sizeof(int32_t) + 72 * sizeof(uint8_t)));
      const v128_t vi3x89ABCDEF = wasm_u16x8_load8x8(i3 + 8);
      const v128_t vk3x89ABCDEF = wasm_u16x8_load8x8((const void*) ((uintptr_t) w + 24 * sizeof(int32_t) + 80 * sizeof(uint8_t)));
      const v128_t vi3xGHIJKLMN = wasm_u16x8_load8x8(i3 + 16);
      const v128_t vk3xGHIJKLMN = wasm_u16x8_load8x8((const void*) ((uintptr_t) w + 24 * sizeof(int32_t) + 88 * sizeof(uint8_t)));
      vsumx01234567 = wasm_i16x8_add(vsumx01234567, vi3x01234567);
      vsumx89ABCDEF = wasm_i16x8_add(vsumx89ABCDEF, vi3x89ABCDEF);
      vsumxGHIJKLMN = wasm_i16x8_add(vsumxGHIJKLMN, vi3xGHIJKLMN);
      i3 += 24;

      vprod01234567 = wasm_i16x8_mul(vi3x01234567, vk3x01234567);
      vprod89ABCDEF = wasm_i16x8_mul(vi3x89ABCDEF, vk3x89ABCDEF);
      vprodGHIJKLMN = wasm_i16x8_mul(vi3xGHIJKLMN, vk3xGHIJKLMN);

      vacc0123 = wasm_i32x4_add(vacc0123, wasm_u32x4_extend_low_u16x8(vprod01234567));
      vacc4567 = wasm_i32x4_add(vacc4567, wasm_u32x4_extend_high_u16x8(vprod01234567));
      vacc89AB = wasm_i32x4_add(vacc89AB, wasm_u32x4_extend_low_u16x8(vprod89ABCDEF));
      vaccCDEF = wasm_i32x4_add(vaccCDEF, wasm_u32x4_extend_high_u16x8(vprod89ABCDEF));
      vaccGHIJ = wasm_i32x4_add(vaccGHIJ, wasm_u32x4_extend_low_u16x8(vprodGHIJKLMN));
      vaccKLMN = wasm_i32x4_add(vaccKLMN, wasm_u32x4_extend_high_u16x8(vprodGHIJKLMN));

      const v128_t vi4x01234567 = wasm_u16x8_load8x8(i4);
      const v128_t vk4x01234567 = wasm_u16x8_load8x8((const void*) ((uintptr_t) w + 24 * sizeof(int32_t) + 96 * sizeof(uint8_t)));
      const v128_t vi4x89ABCDEF = wasm_u16x8_load8x8(i4 + 8);
      const v128_t vk4x89ABCDEF = wasm_u16x8_load8x8((const void*) ((uintptr_t) w + 24 * sizeof(int32_t) + 104 * sizeof(uint8_t)));
      const v128_t vi4xGHIJKLMN = wasm_u16x8_load8x8(i4 + 16);
      const v128_t vk4xGHIJKLMN = wasm_u16x8_load8x8((const void*) ((uintptr_t) w + 24 * sizeof(int32_t) + 112 * sizeof(uint8_t)));
      vsumx01234567 = wasm_i16x8_add(vsumx01234567, vi4x01234567);
      vsumx89ABCDEF = wasm_i16x8_add(vsumx89ABCDEF, vi4x89ABCDEF);
      vsumxGHIJKLMN = wasm_i16x8_add(vsumxGHIJKLMN, vi4xGHIJKLMN);
      i4 += 24;

      vprod01234567 = wasm_i16x8_mul(vi4x01234567, vk4x01234567);
      vprod89ABCDEF = wasm_i16x8_mul(vi4x89ABCDEF, vk4x89ABCDEF);
      vprodGHIJKLMN = wasm_i16x8_mul(vi4xGHIJKLMN, vk4xGHIJKLMN);

      vacc0123 = wasm_i32x4_add(vacc0123, wasm_u32x4_extend_low_u16x8(vprod01234567));
      vacc4567 = wasm_i32x4_add(vacc4567, wasm_u32x4_extend_high_u16x8(vprod01234567));
      vacc89AB = wasm_i32x4_add(vacc89AB, wasm_u32x4_extend_low_u16x8(vprod89ABCDEF));
      vaccCDEF = wasm_i32x4_add(vaccCDEF, wasm_u32x4_extend_high_u16x8(vprod89ABCDEF));
      vaccGHIJ = wasm_i32x4_add(vaccGHIJ, wasm_u32x4_extend_low_u16x8(vprodGHIJKLMN));
      vaccKLMN = wasm_i32x4_add(vaccKLMN, wasm_u32x4_extend_high_u16x8(vprodGHIJKLMN));

      const v128_t vi5x01234567 = wasm_u16x8_load8x8(i5);
      const v128_t vk5x01234567 = wasm_u16x8_load8x8((const void*) ((uintptr_t) w + 24 * sizeof(int32_t) + 120 * sizeof(uint8_t)));
      const v128_t vi5x89ABCDEF = wasm_u16x8_load8x8(i5 + 8);
      const v128_t vk5x89ABCDEF = wasm_u16x8_load8x8((const void*) ((uintptr_t) w + 24 * sizeof(int32_t) + 128 * sizeof(uint8_t)));
      const v128_t vi5xGHIJKLMN = wasm_u16x8_load8x8(i5 + 16);
      const v128_t vk5xGHIJKLMN = wasm_u16x8_load8x8((const void*) ((uintptr_t) w + 24 * sizeof(int32_t) + 136 * sizeof(uint8_t)));
      vsumx01234567 = wasm_i16x8_add(vsumx01234567, vi5x01234567);
      vsumx89ABCDEF = wasm_i16x8_add(vsumx89ABCDEF, vi5x89ABCDEF);
      vsumxGHIJKLMN = wasm_i16x8_add(vsumxGHIJKLMN, vi5xGHIJKLMN);
      i5 += 24;

      vprod01234567 = wasm_i16x8_mul(vi5x01234567, vk5x01234567);
      vprod89ABCDEF = wasm_i16x8_mul(vi5x89ABCDEF, vk5x89ABCDEF);
      vprodGHIJKLMN = wasm_i16x8_mul(vi5xGHIJKLMN, vk5xGHIJKLMN);

      vacc0123 = wasm_i32x4_add(vacc0123, wasm_u32x4_extend_low_u16x8(vprod01234567));
      vacc4567 = wasm_i32x4_add(vacc4567, wasm_u32x4_extend_high_u16x8(vprod01234567));
      vacc89AB = wasm_i32x4_add(vacc89AB, wasm_u32x4_extend_low_u16x8(vprod89ABCDEF));
      vaccCDEF = wasm_i32x4_add(vaccCDEF, wasm_u32x4_extend_high_u16x8(vprod89ABCDEF));
      vaccGHIJ = wasm_i32x4_add(vaccGHIJ, wasm_u32x4_extend_low_u16x8(vprodGHIJKLMN));
      vaccKLMN = wasm_i32x4_add(vaccKLMN, wasm_u32x4_extend_high_u16x8(vprodGHIJKLMN));

      const v128_t vi6x01234567 = wasm_u16x8_load8x8(i6);
      const v128_t vk6x01234567 = wasm_u16x8_load8x8((const void*) ((uintptr_t) w + 24 * sizeof(int32_t) + 144 * sizeof(uint8_t)));
      const v128_t vi6x89ABCDEF = wasm_u16x8_load8x8(i6 + 8);
      const v128_t vk6x89ABCDEF = wasm_u16x8_load8x8((const void*) ((uintptr_t) w + 24 * sizeof(int32_t) + 152 * sizeof(uint8_t)));
      const v128_t vi6xGHIJKLMN = wasm_u16x8_load8x8(i6 + 16);
      const v128_t vk6xGHIJKLMN = wasm_u16x8_load8x8((const void*) ((uintptr_t) w + 24 * sizeof(int32_t) + 160 * sizeof(uint8_t)));
      vsumx01234567 = wasm_i16x8_add(vsumx01234567, vi6x01234567);
      vsumx89ABCDEF = wasm_i16x8_add(vsumx89ABCDEF, vi6x89ABCDEF);
      vsumxGHIJKLMN = wasm_i16x8_add(vsumxGHIJKLMN, vi6xGHIJKLMN);
      i6 += 24;

      vprod01234567 = wasm_i16x8_mul(vi6x01234567, vk6x01234567);
      vprod89ABCDEF = wasm_i16x8_mul(vi6x89ABCDEF, vk6x89ABCDEF);
      vprodGHIJKLMN = wasm_i16x8_mul(vi6xGHIJKLMN, vk6xGHIJKLMN);

      vacc0123 = wasm_i32x4_add(vacc0123, wasm_u32x4_extend_low_u16x8(vprod01234567));
      vacc4567 = wasm_i32x4_add(vacc4567, wasm_u32x4_extend_high_u16x8(vprod01234567));
      vacc89AB = wasm_i32x4_add(vacc89AB, wasm_u32x4_extend_low_u16x8(vprod89ABCDEF));
      vaccCDEF = wasm_i32x4_add(vaccCDEF, wasm_u32x4_extend_high_u16x8(vprod89ABCDEF));
      vaccGHIJ = wasm_i32x4_add(vaccGHIJ, wasm_u32x4_extend_low_u16x8(vprodGHIJKLMN));
      vaccKLMN = wasm_i32x4_add(vaccKLMN, wasm_u32x4_extend_high_u16x8(vprodGHIJKLMN));

      const v128_t vi7x01234567 = wasm_u16x8_load8x8(i7);
      const v128_t vk7x01234567 = wasm_u16x8_load8x8((const void*) ((uintptr_t) w + 24 * sizeof(int32_t) + 168 * sizeof(uint8_t)));
      const v128_t vi7x89ABCDEF = wasm_u16x8_load8x8(i7 + 8);
      const v128_t vk7x89ABCDEF = wasm_u16x8_load8x8((const void*) ((uintptr_t) w + 24 * sizeof(int32_t) + 176 * sizeof(uint8_t)));
      const v128_t vi7xGHIJKLMN = wasm_u16x8_load8x8(i7 + 16);
      const v128_t vk7xGHIJKLMN = wasm_u16x8_load8x8((const void*) ((uintptr_t) w + 24 * sizeof(int32_t) + 184 * sizeof(uint8_t)));
      vsumx01234567 = wasm_i16x8_add(vsumx01234567, vi7x01234567);
      vsumx89ABCDEF = wasm_i16x8_add(vsumx89ABCDEF, vi7x89ABCDEF);
      vsumxGHIJKLMN = wasm_i16x8_add(vsumxGHIJKLMN, vi7xGHIJKLMN);
      i7 += 24;

      vprod01234567 = wasm_i16x8_mul(vi7x01234567, vk7x01234567);
      vprod89ABCDEF = wasm_i16x8_mul(vi7x89ABCDEF, vk7x89ABCDEF);
      vprodGHIJKLMN = wasm_i16x8_mul(vi7xGHIJKLMN, vk7xGHIJKLMN);

      vacc0123 = wasm_i32x4_add(vacc0123, wasm_u32x4_extend_low_u16x8(vprod01234567));
      vacc4567 = wasm_i32x4_add(vacc4567, wasm_u32x4_extend_high_u16x8(vprod01234567));
      vacc89AB = wasm_i32x4_add(vacc89AB, wasm_u32x4_extend_low_u16x8(vprod89ABCDEF));
      vaccCDEF = wasm_i32x4_add(vaccCDEF, wasm_u32x4_extend_high_u16x8(vprod89ABCDEF));
      vaccGHIJ = wasm_i32x4_add(vaccGHIJ, wasm_u32x4_extend_low_u16x8(vprodGHIJKLMN));
      vaccKLMN = wasm_i32x4_add(vaccKLMN, wasm_u32x4_extend_high_u16x8(vprodGHIJKLMN));

      const v128_t vi8x01234567 = wasm_u16x8_load8x8(i8);
      const v128_t vk8x01234567 = wasm_u16x8_load8x8((const void*) ((uintptr_t) w + 24 * sizeof(int32_t) + 192 * sizeof(uint8_t)));
      const v128_t vi8x89ABCDEF = wasm_u16x8_load8x8(i8 + 8);
      const v128_t vk8x89ABCDEF = wasm_u16x8_load8x8((const void*) ((uintptr_t) w + 24 * sizeof(int32_t) + 200 * sizeof(uint8_t)));
      const v128_t vi8xGHIJKLMN = wasm_u16x8_load8x8(i8 + 16);
      const v128_t vk8xGHIJKLMN = wasm_u16x8_load8x8((const void*) ((uintptr_t) w + 24 * sizeof(int32_t) + 208 * sizeof(uint8_t)));
      vsumx01234567 = wasm_i16x8_add(vsumx01234567, vi8x01234567);
      vsumx89ABCDEF = wasm_i16x8_add(vsumx89ABCDEF, vi8x89ABCDEF);
      vsumxGHIJKLMN = wasm_i16x8_add(vsumxGHIJKLMN, vi8xGHIJKLMN);
      i8 += 24;

      vprod01234567 = wasm_i16x8_mul(vi8x01234567, vk8x01234567);
      vprod89ABCDEF = wasm_i16x8_mul(vi8x89ABCDEF, vk8x89ABCDEF);
      vprodGHIJKLMN = wasm_i16x8_mul(vi8xGHIJKLMN, vk8xGHIJKLMN);

      vacc0123 = wasm_i32x4_add(vacc0123, wasm_u32x4_extend_low_u16x8(vprod01234567));
      vacc4567 = wasm_i32x4_add(vacc4567, wasm_u32x4_extend_high_u16x8(vprod01234567));
      vacc89AB = wasm_i32x4_add(vacc89AB, wasm_u32x4_extend_low_u16x8(vprod89ABCDEF));
      vaccCDEF = wasm_i32x4_add(vaccCDEF, wasm_u32x4_extend_high_u16x8(vprod89ABCDEF));
      vaccGHIJ = wasm_i32x4_add(vaccGHIJ, wasm_u32x4_extend_low_u16x8(vprodGHIJKLMN));
      vaccKLMN = wasm_i32x4_add(vaccKLMN, wasm_u32x4_extend_high_u16x8(vprodGHIJKLMN));

      vacc0123 = wasm_i32x4_sub(vacc0123, wasm_i32x4_mul(wasm_u32x4_extend_low_u16x8(vsumx01234567), vkernel_zero_point));
      vacc4567 = wasm_i32x4_sub(vacc4567, wasm_i32x4_mul(wasm_u32x4_extend_high_u16x8(vsumx01234567), vkernel_zero_point));
      vacc89AB = wasm_i32x4_sub(vacc89AB, wasm_i32x4_mul(wasm_u32x4_extend_low_u16x8(vsumx89ABCDEF), vkernel_zero_point));
      vaccCDEF = wasm_i32x4_sub(vaccCDEF, wasm_i32x4_mul(wasm_u32x4_extend_high_u16x8(vsumx89ABCDEF), vkernel_zero_point));
      vaccGHIJ = wasm_i32x4_sub(vaccGHIJ, wasm_i32x4_mul(wasm_u32x4_extend_low_u16x8(vsumxGHIJKLMN), vkernel_zero_point));
      vaccKLMN = wasm_i32x4_sub(vaccKLMN, wasm_i32x4_mul(wasm_u32x4_extend_high_u16x8(vsumxGHIJKLMN), vkernel_zero_point));

      w = (const void*) ((uintptr_t) w + 24 * sizeof(int32_t) + 216 * sizeof(uint8_t));

      vacc0123 = wasm_f32x4_convert_i32x4(vacc0123);
      vacc4567 = wasm_f32x4_convert_i32x4(vacc4567);
      vacc89AB = wasm_f32x4_convert_i32x4(vacc89AB);
      vaccCDEF = wasm_f32x4_convert_i32x4(vaccCDEF);
      vaccGHIJ = wasm_f32x4_convert_i32x4(vaccGHIJ);
      vaccKLMN = wasm_f32x4_convert_i32x4(vaccKLMN);

      const v128_t vscale = wasm_v128_load64_splat(params->fp32_wasmsimd.scale);
      vacc0123 = wasm_f32x4_mul(vacc0123, vscale);
      vacc4567 = wasm_f32x4_mul(vacc4567, vscale);
      vacc89AB = wasm_f32x4_mul(vacc89AB, vscale);
      vaccCDEF = wasm_f32x4_mul(vaccCDEF, vscale);
      vaccGHIJ = wasm_f32x4_mul(vaccGHIJ, vscale);
      vaccKLMN = wasm_f32x4_mul(vaccKLMN, vscale);

      const v128_t vmagic_bias = wasm_v128_load64_splat(params->fp32_wasmsimd.magic_bias);
      vacc0123 = wasm_f32x4_add(vacc0123, vmagic_bias);
      vacc4567 = wasm_f32x4_add(vacc4567, vmagic_bias);
      vacc89AB = wasm_f32x4_add(vacc89AB, vmagic_bias);
      vaccCDEF = wasm_f32x4_add(vaccCDEF, vmagic_bias);
      vaccGHIJ = wasm_f32x4_add(vaccGHIJ, vmagic_bias);
      vaccKLMN = wasm_f32x4_add(vaccKLMN, vmagic_bias);

      const v128_t vmagic_min = wasm_v128_load64_splat(params->fp32_wasmsimd.magic_min);
      vacc0123 = wasm_i32x4_max(vacc0123, vmagic_min);
      vacc4567 = wasm_i32x4_max(vacc4567, vmagic_min);
      vacc89AB = wasm_i32x4_max(vacc89AB, vmagic_min);
      vaccCDEF = wasm_i32x4_max(vaccCDEF, vmagic_min);
      vaccGHIJ = wasm_i32x4_max(vaccGHIJ, vmagic_min);
      vaccKLMN = wasm_i32x4_max(vaccKLMN, vmagic_min);

      const v128_t vmagic_bias_less_output_zero_point = wasm_v128_load64_splat(params->fp32_wasmsimd.magic_bias_less_output_zero_point);
      vacc0123 = wasm_i32x4_sub(vacc0123, vmagic_bias_less_output_zero_point);
      vacc4567 = wasm_i32x4_sub(vacc4567, vmagic_bias_less_output_zero_point);
      vacc89AB = wasm_i32x4_sub(vacc89AB, vmagic_bias_less_output_zero_point);
      vaccCDEF = wasm_i32x4_sub(vaccCDEF, vmagic_bias_less_output_zero_point);
      vaccGHIJ = wasm_i32x4_sub(vaccGHIJ, vmagic_bias_less_output_zero_point);
      vaccKLMN = wasm_i32x4_sub(vaccKLMN, vmagic_bias_less_output_zero_point);

      v128_t vout01234567 = wasm_i16x8_narrow_i32x4(vacc0123, vacc4567);
      v128_t vout89ABCDEF = wasm_i16x8_narrow_i32x4(vacc89AB, vaccCDEF);
      v128_t voutGHIJKLMN = wasm_i16x8_narrow_i32x4(vaccGHIJ, vaccKLMN);

      v128_t vout0123456789ABCDEF = wasm_u8x16_narrow_i16x8(vout01234567, vout89ABCDEF);
      v128_t voutGHIJKLMNGHIJKLMN = wasm_u8x16_narrow_i16x8(voutGHIJKLMN, voutGHIJKLMN);

      const v128_t voutput_max = wasm_v128_load64_splat(params->fp32_wasmsimd.output_max);
      vout0123456789ABCDEF = wasm_u8x16_min(vout0123456789ABCDEF, voutput_max);
      voutGHIJKLMNGHIJKLMN = wasm_u8x16_min(voutGHIJKLMNGHIJKLMN, voutput_max);

      wasm_v128_store(output, vout0123456789ABCDEF);
      *((double*) (output + 16)) = wasm_f64x2_extract_lane(voutGHIJKLMNGHIJKLMN, 0);
      output += 24;
    }
    if XNN_UNLIKELY(c != 0) {
      const uint8_t* k = (const uint8_t*) ((uintptr_t) w + 24 * sizeof(int32_t));
      do {
        v128_t vacc0123 = wasm_v128_load(w);
        v128_t vacc4567 = wasm_v128_load((const void*) ((uintptr_t) w + 4 * sizeof(int32_t)));


        const v128_t vi0x01234567 = wasm_u16x8_load8x8(i0);
        const v128_t vk0x01234567 = wasm_u16x8_load8x8(k);
        i0 += 8;

        v128_t vprod01234567 = wasm_i16x8_mul(vi0x01234567, vk0x01234567);

        vacc0123 = wasm_i32x4_add(vacc0123, wasm_u32x4_extend_low_u16x8(vprod01234567));
        vacc4567 = wasm_i32x4_add(vacc4567, wasm_u32x4_extend_high_u16x8(vprod01234567));

        const v128_t vi1x01234567 = wasm_u16x8_load8x8(i1);
        const v128_t vk1x01234567 = wasm_u16x8_load8x8((const void*) (k + 24));
        v128_t vsumx01234567 = wasm_i16x8_add(vi0x01234567, vi1x01234567);
        i1 += 8;

        vprod01234567 = wasm_i16x8_mul(vi1x01234567, vk1x01234567);

        vacc0123 = wasm_i32x4_add(vacc0123, wasm_u32x4_extend_low_u16x8(vprod01234567));
        vacc4567 = wasm_i32x4_add(vacc4567, wasm_u32x4_extend_high_u16x8(vprod01234567));

        const v128_t vi2x01234567 = wasm_u16x8_load8x8(i2);
        const v128_t vk2x01234567 = wasm_u16x8_load8x8((const void*) (k + 48));
        vsumx01234567 = wasm_i16x8_add(vsumx01234567, vi2x01234567);
        i2 += 8;

        vprod01234567 = wasm_i16x8_mul(vi2x01234567, vk2x01234567);

        vacc0123 = wasm_i32x4_add(vacc0123, wasm_u32x4_extend_low_u16x8(vprod01234567));
        vacc4567 = wasm_i32x4_add(vacc4567, wasm_u32x4_extend_high_u16x8(vprod01234567));

        const v128_t vi3x01234567 = wasm_u16x8_load8x8(i3);
        const v128_t vk3x01234567 = wasm_u16x8_load8x8((const void*) (k + 72));
        vsumx01234567 = wasm_i16x8_add(vsumx01234567, vi3x01234567);
        i3 += 8;

        vprod01234567 = wasm_i16x8_mul(vi3x01234567, vk3x01234567);

        vacc0123 = wasm_i32x4_add(vacc0123, wasm_u32x4_extend_low_u16x8(vprod01234567));
        vacc4567 = wasm_i32x4_add(vacc4567, wasm_u32x4_extend_high_u16x8(vprod01234567));

        const v128_t vi4x01234567 = wasm_u16x8_load8x8(i4);
        const v128_t vk4x01234567 = wasm_u16x8_load8x8((const void*) (k + 96));
        vsumx01234567 = wasm_i16x8_add(vsumx01234567, vi4x01234567);
        i4 += 8;

        vprod01234567 = wasm_i16x8_mul(vi4x01234567, vk4x01234567);

        vacc0123 = wasm_i32x4_add(vacc0123, wasm_u32x4_extend_low_u16x8(vprod01234567));
        vacc4567 = wasm_i32x4_add(vacc4567, wasm_u32x4_extend_high_u16x8(vprod01234567));

        const v128_t vi5x01234567 = wasm_u16x8_load8x8(i5);
        const v128_t vk5x01234567 = wasm_u16x8_load8x8((const void*) (k + 120));
        vsumx01234567 = wasm_i16x8_add(vsumx01234567, vi5x01234567);
        i5 += 8;

        vprod01234567 = wasm_i16x8_mul(vi5x01234567, vk5x01234567);

        vacc0123 = wasm_i32x4_add(vacc0123, wasm_u32x4_extend_low_u16x8(vprod01234567));
        vacc4567 = wasm_i32x4_add(vacc4567, wasm_u32x4_extend_high_u16x8(vprod01234567));

        const v128_t vi6x01234567 = wasm_u16x8_load8x8(i6);
        const v128_t vk6x01234567 = wasm_u16x8_load8x8((const void*) (k + 144));
        vsumx01234567 = wasm_i16x8_add(vsumx01234567, vi6x01234567);
        i6 += 8;

        vprod01234567 = wasm_i16x8_mul(vi6x01234567, vk6x01234567);

        vacc0123 = wasm_i32x4_add(vacc0123, wasm_u32x4_extend_low_u16x8(vprod01234567));
        vacc4567 = wasm_i32x4_add(vacc4567, wasm_u32x4_extend_high_u16x8(vprod01234567));

        const v128_t vi7x01234567 = wasm_u16x8_load8x8(i7);
        const v128_t vk7x01234567 = wasm_u16x8_load8x8((const void*) (k + 168));
        vsumx01234567 = wasm_i16x8_add(vsumx01234567, vi7x01234567);
        i7 += 8;

        vprod01234567 = wasm_i16x8_mul(vi7x01234567, vk7x01234567);

        vacc0123 = wasm_i32x4_add(vacc0123, wasm_u32x4_extend_low_u16x8(vprod01234567));
        vacc4567 = wasm_i32x4_add(vacc4567, wasm_u32x4_extend_high_u16x8(vprod01234567));

        const v128_t vi8x01234567 = wasm_u16x8_load8x8(i8);
        const v128_t vk8x01234567 = wasm_u16x8_load8x8((const void*) (k + 192));
        vsumx01234567 = wasm_i16x8_add(vsumx01234567, vi8x01234567);
        i8 += 8;

        vprod01234567 = wasm_i16x8_mul(vi8x01234567, vk8x01234567);

        vacc0123 = wasm_i32x4_add(vacc0123, wasm_u32x4_extend_low_u16x8(vprod01234567));
        vacc4567 = wasm_i32x4_add(vacc4567, wasm_u32x4_extend_high_u16x8(vprod01234567));

        k += 8;

      vacc0123 = wasm_i32x4_sub(vacc0123, wasm_i32x4_mul(wasm_u32x4_extend_low_u16x8(vsumx01234567), vkernel_zero_point));
      vacc4567 = wasm_i32x4_sub(vacc4567, wasm_i32x4_mul(wasm_u32x4_extend_high_u16x8(vsumx01234567), vkernel_zero_point));

      vacc0123 = wasm_f32x4_convert_i32x4(vacc0123);
      vacc4567 = wasm_f32x4_convert_i32x4(vacc4567);

      const v128_t vscale = wasm_v128_load64_splat(params->fp32_wasmsimd.scale);
      vacc0123 = wasm_f32x4_mul(vacc0123, vscale);
      vacc4567 = wasm_f32x4_mul(vacc4567, vscale);

      const v128_t vmagic_bias = wasm_v128_load64_splat(params->fp32_wasmsimd.magic_bias);
      vacc0123 = wasm_f32x4_add(vacc0123, vmagic_bias);
      vacc4567 = wasm_f32x4_add(vacc4567, vmagic_bias);

      const v128_t vmagic_min = wasm_v128_load64_splat(params->fp32_wasmsimd.magic_min);
      vacc0123 = wasm_i32x4_max(vacc0123, vmagic_min);
      vacc4567 = wasm_i32x4_max(vacc4567, vmagic_min);

      const v128_t vmagic_bias_less_output_zero_point = wasm_v128_load64_splat(params->fp32_wasmsimd.magic_bias_less_output_zero_point);
      vacc0123 = wasm_i32x4_sub(vacc0123, vmagic_bias_less_output_zero_point);
      vacc4567 = wasm_i32x4_sub(vacc4567, vmagic_bias_less_output_zero_point);

      v128_t vout01234567 = wasm_i16x8_narrow_i32x4(vacc0123, vacc4567);
      v128_t vout0123456701234567 = wasm_u8x16_narrow_i16x8(vout01234567, vout01234567);

      const v128_t voutput_max = wasm_v128_load64_splat(params->fp32_wasmsimd.output_max);
      vout0123456701234567 = wasm_u8x16_min(vout0123456701234567, voutput_max);

      w = (const void*) ((uintptr_t) w + 8 * sizeof(int32_t));

      if XNN_LIKELY(c >= 8) {
        *((double*) output) = wasm_f64x2_extract_lane(vout0123456701234567, 0);
        output += 8;
        c -= 8;
      } else {
        if (c & 4) {
          *((float*) output) = wasm_f32x4_extract_lane(vout0123456701234567, 0);
          vout0123456701234567 = wasm_u64x2_shr(vout0123456701234567, 32);
          output += 4;
        }
        uint32_t vout0123 = wasm_i32x4_extract_lane(vout0123456701234567, 0);
        if (c & 2) {
          *((uint16_t*) output) = (uint16_t) vout0123;
          vout0123 >>= 16;
          output += 2;
        }
        if (c & 1) {
          *output = (uint8_t) vout0123;
          output += 1;
        }
        c = 0;
      }
      } while (c != 0);
    }

    output = (uint8_t*) ((uintptr_t) output + output_increment);
  } while (--output_width != 0);
}
