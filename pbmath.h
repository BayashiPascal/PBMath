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
#define PBMATH_PI 3.14159

// -------------- VecFloat

// ================= Generic functions ==================

void VecTypeUnsupported(void*t, ...); 
#define VecClone(V) _Generic((V), \
  VecFloat*: VecFloatClone, \
  default: VecTypeUnsupported)(V)
#define VecLoad(V, S) _Generic((V), \
  VecFloat**: VecFloatLoad, \
  default: VecTypeUnsupported)(V, S)
#define VecSave(V, S) _Generic((V), \
  VecFloat*: VecFloatSave, \
  default: VecTypeUnsupported)(V, S)
#define VecFree(V) _Generic((V), \
  VecFloat**: VecFloatFree, \
  default: VecTypeUnsupported)(V)
#define VecPrint(V, S) _Generic((V), \
  VecFloat*: VecFloatPrintDef, \
  default: VecTypeUnsupported)(V, S)
#define VecGet(V, I) _Generic((V), \
  VecFloat*: VecFloatGet, \
  default: VecTypeUnsupported)(V, I)
#define VecSet(V, I, VAL) _Generic((V), \
  VecFloat*: VecFloatSet, \
  default: VecTypeUnsupported)(V, I, VAL)
#define VecCopy(V, W) _Generic((V), \
  VecFloat*: VecFloatCopy, \
  default: VecTypeUnsupported)(V, W)
#define VecDim(V) _Generic((V), \
  VecFloat*: VecFloatDim, \
  default: VecTypeUnsupported)(V)
#define VecNorm(V) _Generic((V), \
  VecFloat*: VecFloatNorm, \
  default: VecTypeUnsupported)(V)
#define VecNormalise(V) _Generic((V), \
  VecFloat*: VecFloatNormalise, \
  default: VecTypeUnsupported)(V)
#define VecDist(V, W) _Generic((V), \
  VecFloat*: VecFloatDist, \
  default: VecTypeUnsupported)(V, W)
#define VecIsEqual(V, W) _Generic((V), \
  VecFloat*: VecFloatIsEqual, \
  default: VecTypeUnsupported)(V, W)
#define VecOp(V, A, W, B) _Generic((V), \
  VecFloat*: VecFloatOp, \
  default: VecTypeUnsupported)(V, A, W, B)
#define VecGetOp(V, A, W, B) _Generic((V), \
  VecFloat*: VecFloatGetOp, \
  default: VecTypeUnsupported)(V, A, W, B)
#define VecRot2D(V, A) _Generic((V), \
  VecFloat*: VecFloatRot2D, \
  default: VecTypeUnsupported)(V, A)
#define VecGetRot2D(V, A) _Generic((V), \
  VecFloat*: VecFloatGetRot2D, \
  default: VecTypeUnsupported)(V, A)
#define VecDotProd(V, W) _Generic((V), \
  VecFloat*: VecFloatDotProd, \
  default: VecTypeUnsupported)(V, W)

// ================= Data structure ===================

// Vector of float values
typedef struct VecFloat {
  // Dimension
  int _dim;
  // Values
  float *_val;
} VecFloat;

// ================ Functions declaration ====================

// Create a new VecFloat of dimension 'dim'
// Values are initalized to 0.0
// Return NULL if we couldn't create the VecFloat
VecFloat* VecFloatCreate(int dim);

// Clone the VecFloat
// Return NULL if we couldn't clone the VecFloat
VecFloat* VecFloatClone(VecFloat *that);

// Load the VecFloat from the stream
// If the VecFloat is already allocated, it is freed before loading
// Return 0 in case of success, or:
// 1: invalid arguments
// 2: can't allocate memory
// 3: invalid data
// 4: fscanf error
int VecFloatLoad(VecFloat **that, FILE *stream);

// Save the VecFloat to the stream
// Return 0 upon success, or
// 1: invalid arguments
// 2: fprintf error
int VecFloatSave(VecFloat *that, FILE *stream);

// Free the memory used by a VecFloat
// Do nothing if arguments are invalid
void VecFloatFree(VecFloat **that);

// Print the VecFloat on 'stream' with 'prec' digit precision
// Do nothing if arguments are invalid
void VecFloatPrint(VecFloat *that, FILE *stream, int prec);
void VecFloatPrintDef(VecFloat *that, FILE *stream);

// Return the i-th value of the VecFloat
// Index starts at 0
// Return 0.0 if arguments are invalid
float VecFloatGet(VecFloat *that, int i);

// Set the i-th value of the VecFloat to v
// Index starts at 0
// Do nothing if arguments are invalid
void VecFloatSet(VecFloat *that, int i, float v);

// Return the dimension of the VecFloat
// Return 0 if arguments are invalid
int VecFloatDim(VecFloat *that);

// Copy the values of 'w' in 'that' (must have same dimensions)
// Do nothing if arguments are invalid
void VecFloatCopy(VecFloat *that, VecFloat *w);

// Return the norm of the VecFloat
// Return 0.0 if arguments are invalid
float VecFloatNorm(VecFloat *that);

// Normalise the VecFloat
// Do nothing if arguments are invalid
void VecFloatNormalise(VecFloat *that);

// Return the distance between the VecFloat 'that' and 'tho'
// Return NaN if arguments are invalid
// If dimensions are different, missing ones are considered to 
// be equal to 0.0
float VecFloatDist(VecFloat *that, VecFloat *tho);

// Return true if the VecFloat 'that' is equal to 'tho'
// Return false if arguments are invalid
// If dimensions are different, missing ones are considered to 
// be equal to 0.0
bool VecFloatIsEqual(VecFloat *that, VecFloat *tho);

// Calculate (that * a + tho * b) and store the result in 'that'
// Do nothing if arguments are invalid
// 'tho' can be null, in which case it is consider to be the null vector
// If 'tho' is not null it must be of same dimension as 'that'
void VecFloatOp(VecFloat *that, float a, VecFloat *tho, float b);

// Return a VecFloat equal to (that * a + tho * b)
// Return NULL if arguments are invalid
// 'tho' can be null, in which case it is consider to be the null vector
// If 'tho' is not null it must be of same dimension as 'that'
VecFloat* VecFloatGetOp(VecFloat *that, float a, 
  VecFloat *tho, float b);

// Rotate CCW 'that' by 'theta' radians and store the result in 'that'
// Do nothing if arguments are invalid
void VecFloatRot2D(VecFloat *that, float theta);

// Return a VecFloat equal to 'that' rotated CCW by 'theta' radians
// Return NULL if arguments are invalid
VecFloat* VecFloatGetRot2D(VecFloat *that, float theta);

// Return the dot product of 'that' and 'tho'
// Return 0.0 if arguments are invalid
float VecFloatDotProd(VecFloat *that, VecFloat *tho);

// -------------- Gauss

// ================= Define ==================

// ================= Data structure ===================

// Vector of float values
typedef struct Gauss {
  // Mean
  float _mean;
  // Sigma
  float _sigma;
} Gauss;

// ================ Functions declaration ====================

// Create a new Gauss of mean 'mean' and sigma 'sigma'
// Return NULL if we couldn't create the Gauss
Gauss* GaussCreate(float mean, float sigma);

// Free the memory used by a Gauss
// Do nothing if arguments are invalid
void GaussFree(Gauss **that);

// Return the value of the Gauss 'that' at 'x'
// Return 0.0 if the arguments are invalid
float GaussGet(Gauss *that, float x);

// Return a random value according to the Gauss 'that'
// random() must have been called before calling this function
// Return 0.0 if the arguments are invalid
float GaussRnd(Gauss *that);

// -------------- Smoother

// ================= Define ==================

// ================= Data structure ===================

// ================ Functions declaration ====================

// Return the order 1 smooth value of 'x'
// if x < 0.0 return 0.0
// if x > 1.0 return 1.0
float SmoothStep(float x);

// Return the order 2 smooth value of 'x'
// if x < 0.0 return 0.0
// if x > 1.0 return 1.0
float SmootherStep(float x);

#endif
