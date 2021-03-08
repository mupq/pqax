/*=============================================================================
 * Copyright (c) 2020 by Cryptographic Engineering Research Group (CERG)
 * ECE Department, George Mason University
 * Fairfax, VA, U.S.A.
 * Author: Duc Tri Nguyen

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

=============================================================================*/
#ifndef NEON_BATCH_MULTIPLICATION_H
#define NEON_BATCH_MULTIPLICATION_H

#include <stdint.h>

#define SB_ITER 8 // Round up of 7*3*3/8
#define SB_ITER_INNER_PROD 6


void schoolbook16x16(uint16_t *restrict c_in_mem,
                     uint16_t *restrict a_in_mem,
                     uint16_t *restrict b_in_mem,
                     const unsigned int iter);

void c_schoolbook16x16(uint16_t c[32],
                 const uint16_t b[16],
                 const uint16_t a[16]);
#endif
