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
#define PBMATH_TWOPI 6.28319
#define PBMATH_PI 3.14159
#define PBMATH_HALFPI 1.57080
#define PBMATH_QUARTERPI 0.78540
#define PBMATH_SQRTTWO 1.41421
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define EQUALF(a,b) (fabs(a-b)<PBMATH_EPSILON)
#define SHORT(a) ((short)(round(a)))

// ================= Generic functions ==================

void VecTypeUnsupported(void*t, ...); 
#define VecClone(V) _Generic((V), \
  VecFloat*: VecFloatClone, \
  VecShort*: VecShortClone, \
  default: VecTypeUnsupported)(V)
#define VecLoad(V, S) _Generic((V), \
  VecFloat**: VecFloatLoad, \
  VecShort**: VecShortLoad, \
  default: VecTypeUnsupported)(V, S)
#define VecSave(V, S) _Generic((V), \
  VecFloat*: VecFloatSave, \
  VecShort*: VecShortSave, \
  default: VecTypeUnsupported)(V, S)
#define VecFree(V) _Generic((V), \
  VecFloat**: VecFloatFree, \
  VecShort**: VecShortFree, \
  default: VecTypeUnsupported)(V)
#define VecPrint(V, S) _Generic((V), \
  VecFloat*: VecFloatPrintDef, \
  VecShort*: VecShortPrint, \
  default: VecTypeUnsupported)(V, S)
#define VecGet(V, I) _Generic((V), \
  VecFloat*: VecFloatGet, \
  VecShort*: VecShortGet, \
  default: VecTypeUnsupported)(V, I)
#define VecSet(V, I, VAL) _Generic((V), \
  VecFloat*: VecFloatSet, \
  VecShort*: VecShortSet, \
  default: VecTypeUnsupported)(V, I, VAL)
#define VecCopy(V, W) _Generic((V), \
  VecFloat*: VecFloatCopy, \
  VecShort*: VecShortCopy, \
  default: VecTypeUnsupported)(V, W)
#define VecDim(V) _Generic((V), \
  VecFloat*: VecFloatDim, \
  VecShort*: VecShortDim, \
  default: VecTypeUnsupported)(V)
#define VecNorm(V) _Generic((V), \
  VecFloat*: VecFloatNorm, \
  default: VecTypeUnsupported)(V)
#define VecNormalise(V) _Generic((V), \
  VecFloat*: VecFloatNormalise, \
  default: VecTypeUnsupported)(V)
#define VecDist(V, W) _Generic((V), \
  VecFloat*: VecFloatDist, \
  VecShort*: VecShortHamiltonDist, \
  default: VecTypeUnsupported)(V, W)
#define VecHamiltonDist(V, W) _Generic((V), \
  VecFloat*: VecFloatHamiltonDist, \
  VecShort*: VecShortHamiltonDist, \
  default: VecTypeUnsupported)(V, W)
#define VecPixelDist(V, W) _Generic((V), \
  VecFloat*: VecFloatPixelDist, \
  VecShort*: VecShortHamiltonDist, \
  default: VecTypeUnsupported)(V, W)
#define VecIsEqual(V, W) _Generic((V), \
  VecFloat*: _Generic((W), \
    VecFloat*: VecFloatIsEqual, \
    default: VecTypeUnsupported), \
  VecShort*: _Generic((W), \
    VecShort*: VecShortIsEqual,\
    default: VecTypeUnsupported), \
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
  VecShort*: VecShortDotProd,\
  VecFloat*: VecFloatDotProd, \
  default: VecTypeUnsupported)(V, W)
#define VecAngleTo2D(V, W) _Generic((V), \
  VecFloat*: VecFloatAngleTo2D, \
  default: VecTypeUnsupported)(V, W)

void MatTypeUnsupported(void*t, ...); 
#define MatClone(M) _Generic((M), \
  MatFloat*: MatFloatClone, \
  default: MatTypeUnsupported)(M)
#define MatLoad(M, S) _Generic((M), \
  MatFloat**: MatFloatLoad, \
  default: MatTypeUnsupported)(M, S)
#define MatSave(M, S) _Generic((M), \
  MatFloat*: MatFloatSave, \
  default: MatTypeUnsupported)(M, S)
#define MatFree(M) _Generic((M), \
  MatFloat**: MatFloatFree, \
  default: MatTypeUnsupported)(M)
#define MatPrint(M, S) _Generic((M), \
  MatFloat*: MatFloatPrintDef, \
  default: MatTypeUnsupported)(M, S)
#define MatGet(M, I) _Generic((M), \
  MatFloat*: MatFloatGet, \
  default: MatTypeUnsupported)(M, I)
#define MatSet(M, I, VAL) _Generic((M), \
  MatFloat*: MatFloatSet, \
  default: MatTypeUnsupported)(M, I, VAL)
#define MatCopy(M, W) _Generic((M), \
  MatFloat*: _Generic ((W), \
    MatFloat*: MatFloatCopy, \
    default: MatTypeUnsupported), \
  default: MatTypeUnsupported)(M, W)
#define MatDim(M) _Generic((M), \
  MatFloat*: MatFloatDim, \
  default: MatTypeUnsupported)(M)
#define MatInv(M) _Generic((M), \
  MatFloat*: MatFloatInv, \
  default: MatTypeUnsupported)(M)
#define MatProd(A, B) _Generic(A, \
  MatFloat*: _Generic(B, \
    VecFloat*: MatFloatProdVecFloat, \
    MatFloat*: MatFloatProdMatFloat, \
    default: MatTypeUnsupported), \
  default: MatTypeUnsupported)(A, B)
#define MatSetIdentity(M) _Generic((M), \
  MatFloat*: MatFloatSetIdentity, \
  default: MatTypeUnsupported)(M)

void LinSysTypeUnsupported(void*t, ...); 
#define LinSysFree(S) _Generic((S), \
  EqLinSys*: EqLinSysFree, \
  default: LinSysTypeUnsupported)(S)
#define LinSysSolve(S) _Generic((S), \
  EqLinSys*: EqLinSysSolve, \
  default: LinSysTypeUnsupported)(S)

// -------------- VecShort

// ================= Data structure ===================

// Vector of short values
typedef struct VecShort {
  // Dimension
  int _dim;
  // Values
  short *_val;
} VecShort;

// ================ Functions declaration ====================

// Create a new VecShort of dimension 'dim'
// Values are initalized to 0.0
// Return NULL if we couldn't create the VecShort
VecShort* VecShortCreate(int dim);

// Clone the VecShort
// Return NULL if we couldn't clone the VecShort
VecShort* VecShortClone(VecShort *that);

// Load the VecShort from the stream
// If the VecShort is already allocated, it is freed before loading
// Return 0 in case of success, or:
// 1: invalid arguments
// 2: can't allocate memory
// 3: invalid data
// 4: fscanf error
int VecShortLoad(VecShort **that, FILE *stream);

// Save the VecShort to the stream
// Return 0 upon success, or
// 1: invalid arguments
// 2: fprintf error
int VecShortSave(VecShort *that, FILE *stream);

// Free the memory used by a VecShort
// Do nothing if arguments are invalid
void VecShortFree(VecShort **that);

// Print the VecShort on 'stream'
// Do nothing if arguments are invalid
void VecShortPrint(VecShort *that, FILE *stream);

// Return the i-th value of the VecShort
// Index starts at 0
// Return 0.0 if arguments are invalid
short VecShortGet(VecShort *that, int i);

// Set the i-th value of the VecShort to v
// Index starts at 0
// Do nothing if arguments are invalid
void VecShortSet(VecShort *that, int i, short v);

// Return the dimension of the VecShort
// Return 0 if arguments are invalid
int VecShortDim(VecShort *that);

// Return the Hamiltonian distance between the VecShort 'that' and 'tho'
// Return -1 if arguments are invalid
// If dimensions are different, missing ones are considered to 
// be equal to 0
short VecShortHamiltonDist(VecShort *that, VecShort *tho);

// Return true if the VecShort 'that' is equal to 'tho'
// Return false if arguments are invalid
// If dimensions are different, missing ones are considered to 
// be equal to 0.0
bool VecShortIsEqual(VecShort *that, VecShort *tho);

// Copy the values of 'w' in 'that' (must have same dimensions)
// Do nothing if arguments are invalid
void VecShortCopy(VecShort *that, VecShort *w);

// Return the dot product of 'that' and 'tho'
// Return NAN if arguments are invalid
short VecShortDotProd(VecShort *that, VecShort *tho);

// Set all values of the vector 'that' to 0
// Do nothing if arguments are invalid
void VecSetNull(VecShort *that);

// Step the values of the vector incrementally by 1
// in the following order (for example) : 
// (0,0,0)->(0,0,1)->(0,0,2)->(0,1,0)->(0,1,1)->...
// The upper limit for each value is given by 'bound'
// Return false if arguments are invalid or 
// all values of 'that' have reach there upper limit (in which case
// 'that''s values are all set back to 0
// Return true else
bool VecStep(VecShort *that, VecShort *bound);

// -------------- VecFloat

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

// Return the 'i'-th value of the VecFloat
// Index starts at 0
// Return 0.0 if arguments are invalid
float VecFloatGet(VecFloat *that, int i);

// Set the 'i'-th value of the VecFloat to 'v'
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

// Return the Hamiltonian distance between the VecFloat 'that' and 'tho'
// Return NaN if arguments are invalid
// If dimensions are different, missing ones are considered to 
// be equal to 0.0
float VecFloatHamiltonDist(VecFloat *that, VecFloat *tho);

// Return the Pixel distance between the VecFloat 'that' and 'tho'
// Return NaN if arguments are invalid
// If dimensions are different, missing ones are considered to 
// be equal to 0.0
float VecFloatPixelDist(VecFloat *that, VecFloat *tho);

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

// Return the angle of the rotation making 'that' colinear to 'tho'
// Return 0.0 if arguments are invalid
float VecFloatAngleTo2D(VecFloat *that, VecFloat *tho);

// Return the conversion of VecFloat 'that' to a VecShort using round()
// Return null if arguments are invalid or couldn't create the result
VecShort* VecFloatToShort(VecFloat *that);

// Return the conversion of VecShort 'that' to a VecFloat
// Return null if arguments are invalid or couldn't create the result
VecFloat* VecShortToFloat(VecShort *that);

// -------------- MatFloat

// ================= Data structure ===================

// Vector of float values
typedef struct MatFloat {
  // Dimension
  VecShort *_dim;
  // Values (memorized by lines)
  float *_val;
} MatFloat;

// ================ Functions declaration ====================

// Create a new MatFloat of dimension 'dim' (nbcol, nbline)
// Values are initalized to 0.0, 'dim' must be a VecShort of dimension 2
// Return NULL if we couldn't create the MatFloat
MatFloat* MatFloatCreate(VecShort *dim);

// Set the MatFloat to the identity matrix
// The matrix must be a square matrix
// Do nothing if arguments are invalid
void MatFloatSetIdentity(MatFloat *that);

// Clone the MatFloat
// Return NULL if we couldn't clone the MatFloat
MatFloat* MatFloatClone(MatFloat *that);

// Copy the values of 'w' in 'that' (must have same dimensions)
// Do nothing if arguments are invalid
void MatFloatCopy(MatFloat *that, MatFloat *w);

// Load the MatFloat from the stream
// If the MatFloat is already allocated, it is freed before loading
// Return 0 in case of success, or:
// 1: invalid arguments
// 2: can't allocate memory
// 3: invalid data
// 4: fscanf error
int MatFloatLoad(MatFloat **that, FILE *stream);

// Save the MatFloat to the stream
// Return 0 upon success, or
// 1: invalid arguments
// 2: fprintf error
int MatFloatSave(MatFloat *that, FILE *stream);

// Free the memory used by a MatFloat
// Do nothing if arguments are invalid
void MatFloatFree(MatFloat **that);

// Print the MatFloat on 'stream' with 'prec' digit precision
// Do nothing if arguments are invalid
void MatFloatPrint(MatFloat *that, FILE *stream, int prec);
void MatFloatPrintDef(MatFloat *that, FILE *stream);

// Return the value at index 'i' of the MatFloat
// Index starts at 0, i must be a VecShort of dimension 2
// Return 0.0 if arguments are invalid
float MatFloatGet(MatFloat *that, VecShort *i);

// Set the value at index 'i' of the MatFloat to 'v'
// Index starts at 0, 'i' must be a VecShort of dimension 2
// Do nothing if arguments are invalid
void MatFloatSet(MatFloat *that, VecShort *i, float v);

// Return a VecShort of dimension 2 containing the dimension of 
// the MatFloat
// Return NULL if arguments are invalid
VecShort* MatFloatDim(MatFloat *that);

// Return the inverse matrix of 'that'
// The matrix must be a square matrix
// Return null if arguments are invalids
MatFloat* MatFloatInv(MatFloat *that);

// Return the product of matrix 'that' and vector 'v'
// Number of columns of 'that' must equal dimension of 'v'
// Return null if arguments are invalids
VecFloat* MatFloatProdVecFloat(MatFloat *that, VecFloat *v);

// Return the product of matrix 'that' by matrix 'tho'
// Number of columns of 'that' must equal number of line of 'tho'
// Return null if arguments are invalids
MatFloat* MatFloatProdMatFloat(MatFloat *that, MatFloat *tho);

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

// -------------- Conversion functions

// ================ Functions declaration ====================

// Convert radians to degrees
float ConvRad2Deg(float rad);

// Convert degrees to radians
float ConvDeg2Rad(float deg);

// -------------- EqLinSys

// ================= Data structure ===================

// Linear system of equalities
typedef struct EqLinSys {
  // Matrix
  MatFloat *_M;
  // Inverse of the matrix
  MatFloat *_Minv;
  // Vector
  VecFloat *_V;
} EqLinSys;

// ================ Functions declaration ====================

// Create a new EqLinSys with matrix 'm' and vector 'v'
// The dimension of 'v' must be equal to the number of column of 'm'
// If 'v' is null the vector null is used instead
// The matrix 'm' must be a square matrix
// Return NULL if we couldn't create the EqLinSys
EqLinSys* EqLinSysCreate(MatFloat *m, VecFloat *v);

// Free the memory used by the EqLinSys
// Do nothing if arguments are invalid
void EqLinSysFree(EqLinSys **that);

// Clone the EqLinSys 'that'
// Return NULL if we couldn't clone the EqLinSys
EqLinSys* EqLinSysClone(EqLinSys * that);

// Solve the EqLinSys _M.x = _V
// Return the solution vector, or null if there is no solution or the 
// arguments are invalid
VecFloat* EqLinSysSolve(EqLinSys *that);

// Set the matrix of the EqLinSys to a clone of 'm'
// Do nothing if arguments are invalid
void EqLinSysSetM(EqLinSys *that, MatFloat *m);

// Set the vector of the EqLinSys to a clone of 'v'
// Do nothing if arguments are invalid
void EqLinSysSetV(EqLinSys *that, VecFloat *v);

// -------------- Usefull basic functions

// ================ Functions declaration ====================

// Return x^y when x and y are int
// to avoid numerical imprecision from (pow(double,double)
// From https://stackoverflow.com/questions/29787310/
// does-pow-work-for-int-data-type-in-c
int powi(int base, int exp);

#endif
