// ============ PBMATH.H ================

#ifndef PBMATH_H
#define PBMATH_H

// ================= Include =================

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

// ================= Define ==================

#define PBMATH_EPSILON 0.0000001

// ================= Data structure ===================

// Vector of float values
typedef struct Vec {
  // Dimension
  int _dim;
  // Values
  float *_val;
} Vec;

// ================ Functions declaration ====================

// Create a new Vec of dimension 'dim'
// Values are initalized to 0.0
// Return NULL if we couldn't create the Vec
Vec* VecCreate(int dim);

// Clone the Vec
// Return NULL if we couldn't clone the Vec
Vec* VecClone(Vec *that);

// Load the Vec from the stream
// If the Vec is already allocated, it is freed before loading
// Return 0 in case of success, or:
// 1: invalid arguments
// 2: can't allocate memory
// 3: invalid data
// 4: fscanf error
int VecLoad(Vec **that, FILE *stream);

// Save the Vec to the stream
// Return 0 upon success, or
// 1: invalid arguments
// 2: fprintf error
int VecSave(Vec *that, FILE *stream);

// Free the memory used by a Vec
// Do nothing if arguments are invalid
void VecFree(Vec **that);

// Print the Vec on 'stream'
// Do nothing if arguments are invalid
void VecPrint(Vec *that, FILE *stream);

// Return the i-th value of the Vec
// Index starts at 0
// Return 0.0 if arguments are invalid
float VecGet(Vec *that, int i);

// Set the i-th value of the Vec to v
// Index starts at 0
// Do nohting if arguments are invalid
void VecSet(Vec *that, int i, float v);

// Return the dimension of the Vec
// Return 0 if arguments are invalid
int VecDim(Vec *that);

#endif
