// ============ PBMATH.H ================

#ifndef PBMATH_H
#define PBMATH_H

// ================= Include =================

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "pberr.h"
#include "pbjson.h"

// ================= Define ==================

#define PBMATH_EPSILON 0.00001
#define PBMATH_TWOPI 6.283185307
#define PBMATH_TWOPI_DIV_360 0.01745329252
#define PBMATH_PI 3.141592654
#define PBMATH_HALFPI 1.570796327
#define PBMATH_QUARTERPI 0.7853981634
#define PBMATH_SQRTTWO 1.414213562
#define PBMATH_SQRTONEHALF 0.707106781
#ifndef MAX
  #define MAX(a,b) ((a)>(b)?(a):(b))
#endif
#ifndef MIN
  #define MIN(a,b) ((a)<(b)?(a):(b))
#endif
#define ISEQUALF(a,b) (fabs((a)-(b))<PBMATH_EPSILON)
#define SHORT(a) ((short)(round(a)))
#define INT(a) ((int)(round(a)))
#define rnd() (float)(rand())/(float)(RAND_MAX)

// -------------- VecShort

// ================= Data structure ===================

// Vector of short values
typedef struct VecShort {
  // Dimension
  int _dim;
  // Values
  short _val[0];
} VecShort;

typedef struct VecShort2D {
  // Dimension
  int _dim;
  // Values
  short _val[2];
} VecShort2D;

typedef struct VecShort3D {
  // Dimension
  int _dim;
  // Values
  short _val[3];
} VecShort3D;

typedef struct VecShort4D {
  // Dimension
  int _dim;
  // Values
  short _val[4];
} VecShort4D;

// ================ Functions declaration ====================

// Create a new VecShort of dimension 'dim'
// Values are initalized to 0.0
VecShort* VecShortCreate(const int dim);

// Static constructors for VecShort
#if BUILDMODE != 0
inline
#endif 
VecShort2D VecShortCreateStatic2D();
#if BUILDMODE != 0
inline
#endif 
VecShort3D VecShortCreateStatic3D();
#if BUILDMODE != 0
inline
#endif 
VecShort4D VecShortCreateStatic4D();

// Clone the VecShort
// Return NULL if we couldn't clone the VecShort
VecShort* _VecShortClone(const VecShort* const that);

// Function which return the JSON encoding of 'that' 
JSONNode* _VecShortEncodeAsJSON(const VecShort* const that);

// Function which decode from JSON encoding 'json' to 'that'
bool _VecShortDecodeAsJSON(VecShort** that, const JSONNode* const json);

// Load the VecShort from the stream
// If the VecShort is already allocated, it is freed before loading
// Return true in case of success, else false
bool _VecShortLoad(VecShort** that, FILE* const stream);

// Save the VecShort to the stream
// If 'compact' equals true it saves in compact form, else it saves in 
// readable form
// Return true in case of success, else false
bool _VecShortSave(const VecShort* const that, 
  FILE* const stream, const bool compact);

// Free the memory used by a VecShort
// Do nothing if arguments are invalid
void _VecShortFree(VecShort** that);

// Print the VecShort on 'stream'
void _VecShortPrint(const VecShort* const that, 
  FILE* const stream);

// Return the i-th value of the VecShort
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortGet(const VecShort* const that, const int i);
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortGet2D(const VecShort2D* const that, const int i);
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortGet3D(const VecShort3D* const that, const int i);
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortGet4D(const VecShort4D* const that, const int i);

// Set the i-th value of the VecShort to v
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortSet(VecShort* const that, const int i, const short v);
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortSet2D(VecShort2D* const that, const int i, const short v);
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortSet3D(VecShort3D* const that, const int i, const short v);
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortSet4D(VecShort4D* const that, const int i, const short v);

// Set the i-th value of the VecShort to v plus its current value
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortSetAdd(VecShort* const that, const int i, const short v);
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortSetAdd2D(VecShort2D* const that, const int i, const short v);
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortSetAdd3D(VecShort3D* const that, const int i, const short v);
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortSetAdd4D(VecShort4D* const that, const int i, const short v);

// Return the dimension of the VecShort
// Return 0 if arguments are invalid
#if BUILDMODE != 0 
inline 
#endif 
int _VecShortGetDim(const VecShort* const that);

// Return the Hamiltonian distance between the VecShort 'that' and 'tho'
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortHamiltonDist(const VecShort* const that, const VecShort* const tho);
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortHamiltonDist2D(const VecShort2D* const that, const VecShort2D* const tho);
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortHamiltonDist3D(const VecShort3D* const that, const VecShort3D* const tho);
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortHamiltonDist4D(const VecShort4D* const that, const VecShort4D* const tho);

// Return true if the VecShort 'that' is equal to 'tho', else false
#if BUILDMODE != 0 
inline 
#endif 
bool _VecShortIsEqual(const VecShort* const that, 
  const VecShort* const tho);

// Copy the values of 'w' in 'that' (must have same dimensions)
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortCopy(VecShort* const that, const VecShort* const w);

// Return the dot product of 'that' and 'tho'
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortDotProd(const VecShort* const that, 
  const VecShort* const tho);
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortDotProd2D(const VecShort2D* const that, 
  const VecShort2D* const tho);
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortDotProd3D(const VecShort3D* const that, 
  const VecShort3D* const tho);
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortDotProd4D(const VecShort4D* const that, 
  const VecShort4D* const tho);

// Set all values of the vector 'that' to 0
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortSetNull(VecShort* const that);

// Step the values of the vector incrementally by 1 from 0
// in the following order (for example) : 
// (0,0,0)->(0,0,1)->(0,0,2)->(0,1,0)->(0,1,1)->...
// The upper limit for each value is given by 'bound' (val[i] < dim[i])
// Return false if all values of 'that' have reached their upper limit 
// (in which case 'that''s values are all set back to 0)
// Return true else
bool _VecShortStep(VecShort* const that, const VecShort* const bound);

// Step the values of the vector incrementally by 1 from 0
// in the following order (for example) : 
// (0,0,0)->(1,0,0)->(2,0,0)->(0,1,0)->(1,1,0)->...
// The upper limit for each value is given by 'bound' (val[i] < dim[i])
// Return false if all values of 'that' have reached their upper limit 
// (in which case 'that''s values are all set back to 0)
// Return true else
bool _VecShortPStep(VecShort* const that, const VecShort* const bound);

// Step the values of the vector incrementally by 1
// in the following order (for example) : 
// (0,0,0)->(0,0,1)->(0,0,2)->(0,1,0)->(0,1,1)->...
// The lower limit for each value is given by 'from' (val[i] >= from[i])
// The upper limit for each value is given by 'to' (val[i] < to[i])
// 'that' must be initialised to 'from' before the first call of this
// function
// Return false if all values of 'that' have reached their upper limit 
// (in which case 'that''s values are all set back to from)
// Return true else
bool _VecShortShiftStep(VecShort* const that, 
  const VecShort* const from, const VecShort* const to);

// Step the values of the vector incrementally by delta from 0
// in the following order (for example) : 
// (0,0,0)->(0,0,1)->(0,0,2)->(0,1,0)->(0,1,1)->...
// The upper limit for each value is given by 'bound' (val[i] <= dim[i])
// Return false after all values of 'that' have reached their upper 
// limit (in which case 'that''s values are all set back to 0)
// Return true else
bool _VecShortStepDelta(VecShort* const that, 
  const VecShort* const bound, const VecShort* const delta);

// Step the values of the vector incrementally by delta from 0
// in the following order (for example) : 
// (0,0,0)->(1,0,0)->(2,0,0)->(0,1,0)->(1,1,0)->...
// The upper limit for each value is given by 'bound' (val[i] <= dim[i])
// Return false after all values of 'that' have reached their upper 
// limit (in which case 'that''s values are all set back to 0)
// Return true else
bool _VecShortPStepDelta(VecShort* const that, 
  const VecShort* const bound, const VecShort* const delta);

// Calculate (that * a + tho * b) and store the result in 'that'
// 'tho' can be null, in which case it is consider to be the null vector
// If 'tho' is not null it must be of same dimension as 'that'
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortOp(VecShort* const that, const short a, 
  const VecShort* const tho, const short b);
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortOp2D(VecShort2D* const that, const short a, 
  const VecShort2D* const tho, const short b);
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortOp3D(VecShort3D* const that, const short a, 
  const VecShort3D* const tho, const short b);
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortOp4D(VecShort4D* const that, const short a, 
  const VecShort4D* const tho, const short b);

// Return a VecShort equal to (that * a + tho * b)
// Return NULL if arguments are invalid
// 'tho' can be null, in which case it is consider to be the null vector
// If 'tho' is not null it must be of same dimension as 'that'
#if BUILDMODE != 0 
inline 
#endif 
VecShort* _VecShortGetOp(const VecShort* const that, const short a, 
  const VecShort* const tho, const short b);
#if BUILDMODE != 0 
inline 
#endif 
VecShort2D _VecShortGetOp2D(const VecShort2D* const that, const short a, 
  const VecShort2D* const tho, const short b);
#if BUILDMODE != 0 
inline 
#endif 
VecShort3D _VecShortGetOp3D(const VecShort3D* const that, const short a, 
  const VecShort3D* const tho, const short b);
#if BUILDMODE != 0 
inline 
#endif 
VecShort4D _VecShortGetOp4D(const VecShort4D* const that, const short a, 
  const VecShort4D* const tho, const short b);

// Calculate the Hadamard product of that by tho and store the 
// result in 'that'
// 'tho' and 'that' must be of same dimension
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortHadamardProd(VecShort* const that, 
  const VecShort* const tho);
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortHadamardProd2D(VecShort2D* const that, 
  const VecShort2D* const tho);
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortHadamardProd3D(VecShort3D* const that, 
  const VecShort3D* const tho);
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortHadamardProd4D(VecShort4D* const that, 
  const VecShort4D* const tho);

// Return a VecShort equal to the hadamard product of 'that' and 'tho'
// Return NULL if arguments are invalid
// 'tho' and 'that' must be of same dimension
#if BUILDMODE != 0 
inline 
#endif 
VecShort* _VecShortGetHadamardProd(const VecShort* const that, 
  const VecShort* const tho);
#if BUILDMODE != 0 
inline 
#endif 
VecShort2D _VecShortGetHadamardProd2D(const VecShort2D* const that, 
  const VecShort2D* const tho);
#if BUILDMODE != 0 
inline 
#endif 
VecShort3D _VecShortGetHadamardProd3D(const VecShort3D* const that, 
  const VecShort3D* const tho);
#if BUILDMODE != 0 
inline 
#endif 
VecShort4D _VecShortGetHadamardProd4D(const VecShort4D* const that, 
  const VecShort4D* const tho);

// Get the max value in components of the vector 'that'
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortGetMaxVal(const VecShort* const that);

// Get the min value in components of the vector 'that'
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortGetMinVal(const VecShort* const that);

// Get the max value (in absolute value) in components of the 
// vector 'that'
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortGetMaxValAbs(const VecShort* const that);

// Get the min value (in absolute value) in components of the 
// vector 'that'
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortGetMinValAbs(const VecShort* const that);

// Get the index of the max value in components of the vector 'that'
#if BUILDMODE != 0 
inline 
#endif 
int _VecShortGetIMaxVal(const VecShort* const that);

// -------------- VecFloat

// ================= Data structure ===================

// Vector of float values
typedef struct VecFloat {
  // Dimension
  int _dim;
  // Values
  float _val[0];
} VecFloat;

typedef struct VecFloat2D {
  // Dimension
  int _dim;
  // Values
  float _val[2];
} VecFloat2D;

typedef struct VecFloat3D {
  // Dimension
  int _dim;
  // Values
  float _val[3];
} VecFloat3D;

// ================ Functions declaration ====================

// Create a new VecFloat of dimension 'dim'
// Values are initalized to 0.0
VecFloat* VecFloatCreate(const int dim);

// Static constructors for VecFloat
#if BUILDMODE != 0 
inline 
#endif 
VecFloat2D VecFloatCreateStatic2D();
#if BUILDMODE != 0 
inline 
#endif 
VecFloat3D VecFloatCreateStatic3D();

// Clone the VecFloat
VecFloat* _VecFloatClone(const VecFloat* const that);

// Function which return the JSON encoding of 'that' 
JSONNode* _VecFloatEncodeAsJSON(const VecFloat* const that);

// Function which decode from JSON encoding 'json' to 'that'
bool _VecFloatDecodeAsJSON(VecFloat** that, const JSONNode* const json);

// Load the VecFloat from the stream
// If the VecFloat is already allocated, it is freed before loading
// Return true in case of success, else false
bool _VecFloatLoad(VecFloat** that, FILE* const stream);

// Save the VecFloat to the stream
// If 'compact' equals true it saves in compact form, else it saves in 
// readable form
// Return true in case of success, else false
bool _VecFloatSave(const VecFloat* const that, 
  FILE* const stream, const bool compact);

// Free the memory used by a VecFloat
// Do nothing if arguments are invalid
void _VecFloatFree(VecFloat** that);

// Print the VecFloat on 'stream' with 'prec' digit precision
// Do nothing if arguments are invalid
void VecFloatPrint(const VecFloat* const that, FILE* const stream, 
  const unsigned int prec);
inline void _VecFloatPrintDef(const VecFloat* const that, 
  FILE* const stream) {
  VecFloatPrint(that, stream, 3);
}

// Return the 'i'-th value of the VecFloat
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatGet(const VecFloat* const that, const int i);
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatGet2D(const VecFloat2D* const that, const int i);
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatGet3D(const VecFloat3D* const that, const int i);

// Set the 'i'-th value of the VecFloat to 'v'
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatSet(VecFloat* const that, const int i, const float v);
#if BUILDMODE != 0
inline
#endif 
void _VecFloatSet2D(VecFloat2D* const that, const int i, const float v);
#if BUILDMODE != 0
inline
#endif 
void _VecFloatSet3D(VecFloat3D* const that, const int i, const float v);

// Set the 'i'-th value of the VecFloat to 'v' plus its current value
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatSetAdd(VecFloat* const that, const int i, const float v);
#if BUILDMODE != 0
inline
#endif 
void _VecFloatSetAdd2D(VecFloat2D* const that, const int i, 
  const float v);
#if BUILDMODE != 0
inline
#endif 
void _VecFloatSetAdd3D(VecFloat3D* const that, const int i, 
  const float v);

// Set all values of the vector 'that' to 0
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatSetNull(VecFloat* const that);
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatSetNull2D(VecFloat2D* const that);
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatSetNull3D(VecFloat3D* const that);

// Return the dimension of the VecFloat
// Return 0 if arguments are invalid
#if BUILDMODE != 0 
inline 
#endif 
int _VecFloatGetDim(const VecFloat* const that);

// Return a new VecFloat as a copy of the VecFloat 'that' with 
// dimension changed to 'dim'
// if it is extended, the values of new components are 0.0
// If it is shrinked, values are discarded from the end of the vector
VecFloat* _VecFloatGetNewDim(const VecFloat* const that, const int dim); 

// Copy the values of 'w' in 'that' (must have same dimensions)
// Do nothing if arguments are invalid
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatCopy(VecFloat* const that, const VecFloat* const w);

// Return the norm of the VecFloat
// Return 0.0 if arguments are invalid
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatNorm(const VecFloat* const that);
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatNorm2D(const VecFloat2D* const that);
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatNorm3D(const VecFloat3D* const that);

// Normalise the VecFloat
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatNormalise(VecFloat* const that);
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatNormalise2D(VecFloat2D* const that);
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatNormalise3D(VecFloat3D* const that);

// Return the distance between the VecFloat 'that' and 'tho'
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatDist(const VecFloat* const that, 
  const VecFloat* const tho);
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatDist2D(const VecFloat2D* const that, 
  const VecFloat2D* const tho);
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatDist3D(const VecFloat3D* const that, 
  const VecFloat3D* const tho);

// Return the Hamiltonian distance between the VecFloat 'that' and 'tho'
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatHamiltonDist(const VecFloat* const that, 
  const VecFloat* const tho);
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatHamiltonDist2D(const VecFloat2D* const that, 
  const VecFloat2D* const tho);
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatHamiltonDist3D(const VecFloat3D* const that, 
  const VecFloat3D* const tho);

// Return the Pixel distance between the VecFloat 'that' and 'tho'
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatPixelDist(const VecFloat* const that, 
  const VecFloat* const tho);
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatPixelDist2D(const VecFloat2D* const that, 
  const VecFloat2D* const tho);
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatPixelDist3D(const VecFloat3D* const that, 
  const VecFloat3D* const tho);

// Return true if the VecFloat 'that' is equal to 'tho', else false
#if BUILDMODE != 0 
inline 
#endif 
bool _VecFloatIsEqual(const VecFloat* const that, 
  const VecFloat* const tho);

// Calculate (that * a) and store the result in 'that'
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatScale(VecFloat* const that, const float a);
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatScale2D(VecFloat2D* const that, const float a);
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatScale3D(VecFloat3D* const that, const float a);

// Return a VecFloat equal to (that * a)
#if BUILDMODE != 0 
inline 
#endif 
VecFloat* _VecFloatGetScale(const VecFloat* const that, const float a);
#if BUILDMODE != 0 
inline 
#endif 
VecFloat2D _VecFloatGetScale2D(const VecFloat2D* const that, 
  const float a);
#if BUILDMODE != 0 
inline 
#endif 
VecFloat3D _VecFloatGetScale3D(const VecFloat3D* const that, 
  const float a);

// Calculate (that * a + tho * b) and store the result in 'that'
// 'tho' can be null, in which case it is consider to be the null vector
// If 'tho' is not null it must be of same dimension as 'that'
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatOp(VecFloat* const that, const float a, 
  const VecFloat* const tho, const float b);
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatOp2D(VecFloat2D* const that, const float a, 
  const VecFloat2D* const tho, const float b);
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatOp3D(VecFloat3D* const that, const float a, 
  const VecFloat3D* const tho, const float b);

// Return a VecFloat equal to (that * a + tho * b)
// Return NULL if arguments are invalid
// 'tho' can be null, in which case it is consider to be the null vector
// If 'tho' is not null it must be of same dimension as 'that'
#if BUILDMODE != 0 
inline 
#endif 
VecFloat* _VecFloatGetOp(const VecFloat* const that, const float a, 
  const VecFloat* const tho, const float b);
#if BUILDMODE != 0 
inline 
#endif 
VecFloat2D _VecFloatGetOp2D(const VecFloat2D* const that, const float a, 
  const VecFloat2D* const tho, const float b);
#if BUILDMODE != 0 
inline 
#endif 
VecFloat3D _VecFloatGetOp3D(const VecFloat3D* const that, const float a, 
  const VecFloat3D* const tho, const float b);

// Calculate the Hadamard product of that by tho and store the 
// result in 'that'
// 'tho' and 'that' must be of same dimension
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatHadamardProd(VecFloat* const that, 
  const VecFloat* const tho);
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatHadamardProd2D(VecFloat2D* const that, 
  const VecFloat2D* const tho);
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatHadamardProd3D(VecFloat3D* const that, 
  const VecFloat3D* const tho);

// Return a VecFloat equal to the hadamard product of 'that' and 'tho'
// Return NULL if arguments are invalid
// 'tho' and 'that' must be of same dimension
#if BUILDMODE != 0 
inline 
#endif 
VecFloat* _VecFloatGetHadamardProd(const VecFloat* const that, 
  const VecFloat* const tho);
#if BUILDMODE != 0 
inline 
#endif 
VecFloat2D _VecFloatGetHadamardProd2D(const VecFloat2D* const that, 
  const VecFloat2D* const tho);
#if BUILDMODE != 0 
inline 
#endif 
VecFloat3D _VecFloatGetHadamardProd3D(const VecFloat3D* const that, 
  const VecFloat3D* const tho);

// Rotate CCW 'that' by 'theta' radians and store the result in 'that'
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatRot2D(VecFloat2D* const that, const float theta);

// Return a VecFloat2D equal to 'that' rotated CCW by 'theta' radians
#if BUILDMODE != 0 
inline 
#endif 
VecFloat2D _VecFloatGetRot2D(const VecFloat2D* const that, 
  const float theta);

// Rotate right-hand 'that' by 'theta' radians around 'axis' and 
// store the result in 'that'
// 'axis' must be normalized
// https://en.wikipedia.org/wiki/Rotation_matrix
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatRotAxis(VecFloat3D* const that, 
  const VecFloat3D* const axis, const float theta);

// Return a VecFloat3D equal to 'that' rotated right-hand by 'theta' 
// radians around 'axis'
// 'axis' must be normalized
// https://en.wikipedia.org/wiki/Rotation_matrix
VecFloat3D _VecFloatGetRotAxis(const VecFloat3D* const that, 
  const VecFloat3D* const axis, const float theta);

// Rotate right-hand 'that' by 'theta' radians around X and 
// store the result in 'that'
#if BUILDMODE != 0
inline
#endif 
void _VecFloatRotX(VecFloat3D* const that, const float theta);

// Rotate right-hand 'that' by 'theta' radians around Y and 
// store the result in 'that'
#if BUILDMODE != 0
inline
#endif 
void _VecFloatRotY(VecFloat3D* const that, const float theta);

// Rotate right-hand 'that' by 'theta' radians around Z and 
// store the result in 'that'
#if BUILDMODE != 0
inline
#endif 
void _VecFloatRotZ(VecFloat3D* const that, const float theta);

// Return a VecFloat3D equal to 'that' rotated right-hand by 'theta' 
// radians around X
VecFloat3D _VecFloatGetRotX(const VecFloat3D* const that, 
  const float theta);

// Return a VecFloat3D equal to 'that' rotated right-hand by 'theta' 
// radians around Y
VecFloat3D _VecFloatGetRotY(const VecFloat3D* const that, 
  const float theta);

// Return a VecFloat3D equal to 'that' rotated right-hand by 'theta' 
// radians around Z
VecFloat3D _VecFloatGetRotZ(const VecFloat3D* const that, 
  const float theta);

// Return the dot product of 'that' and 'tho'
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatDotProd(const VecFloat* const that, 
  const VecFloat* const tho);
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatDotProd2D(const VecFloat2D* const that, 
  const VecFloat2D* const tho);
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatDotProd3D(const VecFloat3D* const that, 
  const VecFloat3D* const tho);

// Return the angle of the rotation making 'that' colinear to 'tho'
// 'that' and 'tho' must be normalised
// Return a value in [-PI,PI]
float _VecFloatAngleTo2D(const VecFloat2D* const that, 
  const VecFloat2D* const tho);

// Return the conversion of VecFloat 'that' to a VecShort using round()
#if BUILDMODE != 0 
inline 
#endif 
VecShort* VecFloatToShort(const VecFloat* const that);
#if BUILDMODE != 0 
inline 
#endif 
VecShort2D VecFloatToShort2D(const VecFloat2D* const that);
#if BUILDMODE != 0 
inline 
#endif 
VecShort3D VecFloatToShort3D(const VecFloat3D* const that);

// Return the conversion of VecShort 'that' to a VecFloat
#if BUILDMODE != 0 
inline 
#endif 
VecFloat* VecShortToFloat(const VecShort* const that);
#if BUILDMODE != 0 
inline 
#endif 
VecFloat2D VecShortToFloat2D(const VecShort2D* const that);
#if BUILDMODE != 0 
inline 
#endif 
VecFloat3D VecShortToFloat3D(const VecShort3D* const that);

// Get the max value in components of the vector 'that'
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatGetMaxVal(const VecFloat* const that);

// Get the min value in components of the vector 'that'
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatGetMinVal(const VecFloat* const that);

// Get the max value (in absolute value) in components of the 
// vector 'that'
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatGetMaxValAbs(const VecFloat* const that);

// Get the min value (in absolute value) in components of the 
// vector 'that'
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatGetMinValAbs(const VecFloat* const that);

// Step the values of the vector incrementally by delta from 0
// in the following order (for example) : 
// (0.,0.,0.)->(0.,0.,1.)->(0.,0.,2.)->(0.,1.,0.)->(0.,1.,1.)->...
// The upper limit for each value is given by 'bound' (val[i] <= dim[i])
// Return false after all values of 'that' have reached their upper 
// limit (in which case 'that''s values are all set back to 0.)
// Return true else
bool _VecFloatStepDelta(VecFloat* const that, 
  const VecFloat* const bound, const VecFloat* const delta);

// Step the values of the vector incrementally by delta
// in the following order (for example) : 
// (0.,0.,0.)->(0.,0.,1.)->(0.,0.,2.)->(0.,1.,0.)->(0.,1.,1.)->...
// The lower limit for each value is given by 'from' (val[i] >= from[i])
// The upper limit for each value is given by 'to' (val[i] <= to[i])
// 'that' must be initialised to 'from' before the first call of this
// function
// Return false after all values of 'that' have reached their upper 
// limit (in which case 'that''s values are all set back to from)
// Return true else
bool _VecFloatShiftStepDelta(VecFloat* const that, 
  const VecFloat* const from, const VecFloat* const to, 
  const VecFloat* const delta);

// Get the index of the max value in components of the vector 'that'
#if BUILDMODE != 0 
inline 
#endif 
int _VecFloatGetIMaxVal(const VecFloat* const that);

// -------------- MatFloat

// ================= Data structure ===================

// Vector of float values
typedef struct MatFloat {
  // Dimension
  const VecShort2D _dim;
  // Values (memorized by lines)
  float _val[0];
} MatFloat;

// ================ Functions declaration ====================

// Create a new MatFloat of dimension 'dim' (nbCol, nbLine)
// Values are initalized to 0.0
MatFloat* MatFloatCreate(const VecShort2D* const dim);

// Set the MatFloat to the identity matrix
// The matrix must be a square matrix
#if BUILDMODE != 0 
inline 
#endif 
void _MatFloatSetIdentity(MatFloat* const that);

// Clone the MatFloat
MatFloat* _MatFloatClone(const MatFloat* const that);

// Copy the values of 'w' in 'that' (must have same dimensions)
#if BUILDMODE != 0 
inline 
#endif 
void _MatFloatCopy(MatFloat* const that, const MatFloat* const tho);

// Function which return the JSON encoding of 'that' 
JSONNode* _MatFloatEncodeAsJSON(MatFloat* const that);

// Function which decode from JSON encoding 'json' to 'that'
bool _MatFloatDecodeAsJSON(MatFloat** that, JSONNode* json);

// Load the MatFloat from the stream
// If the MatFloat is already allocated, it is freed before loading
// Return true upon success, else false
bool _MatFloatLoad(MatFloat** that, FILE* stream);

// Save the MatFloat to the stream
// If 'compact' equals true it saves in compact form, else it saves in 
// readable form
// Return true upon success, else false
bool _MatFloatSave(MatFloat* const that, FILE* stream, bool compact);

// Free the memory used by a MatFloat
// Do nothing if arguments are invalid
void _MatFloatFree(MatFloat** that);

// Print the MatFloat on 'stream' with 'prec' digit precision
// Do nothing if arguments are invalid
void MatFloatPrintln(MatFloat* const that, FILE* stream, unsigned int prec);
inline void _MatFloatPrintlnDef(MatFloat* const that, FILE* stream) {
  MatFloatPrintln(that, stream, 3);
}

// Return the value at index (col, line) of the MatFloat
// Index starts at 0, index in matrix = line * nbCol + col
#if BUILDMODE != 0 
inline 
#endif 
float _MatFloatGet(const MatFloat* const that, 
  VecShort2D* index);

// Set the value at index (col, line) of the MatFloat to 'v'
// Index starts at 0, index in matrix = line * nbCol + col
#if BUILDMODE != 0 
inline 
#endif 
void _MatFloatSet(MatFloat* const that, VecShort2D* index, float v);

// Return the dimension of the MatFloat
#if BUILDMODE != 0 
inline 
#endif 
const VecShort2D* _MatFloatDim(MatFloat* const that);

// Return a VecShort2D containing the dimension of the MatFloat
#if BUILDMODE != 0 
inline 
#endif 
VecShort2D _MatFloatGetDim(MatFloat* const that);

// Return the inverse matrix of 'that'
// The matrix must be a square matrix
MatFloat* _MatFloatInv(MatFloat* const that);

// Return the product of matrix 'that' and vector 'v'
// Number of columns of 'that' must equal dimension of 'v'
VecFloat* _MatFloatGetProdVecFloat(MatFloat* const that, VecFloat* v);

// Return the product of matrix 'that' by matrix 'tho'
// Number of columns of 'that' must equal number of line of 'tho'
MatFloat* _MatFloatGetProdMatFloat(MatFloat* const that, MatFloat* tho);

// Return the addition of matrix 'that' with matrix 'tho'
// 'that' and 'tho' must have same dimensions
#if BUILDMODE != 0 
inline 
#endif 
MatFloat* _MatFloatGetAdd(MatFloat* const that, MatFloat* tho);

// Add matrix 'that' with matrix 'tho' and store the result in 'that'
// 'that' and 'tho' must have same dimensions
#if BUILDMODE != 0 
inline 
#endif 
void _MatFloatAdd(MatFloat* const that, MatFloat* tho);

// Return true if 'that' is equal to 'tho', false else
bool _MatFloatIsEqual(MatFloat* const that, MatFloat* tho);

// -------------- Gauss

// ================= Define ==================

// ================= Data structure ===================

// Should be vector of float values
typedef struct Gauss {
  // Mean
  float _mean;
  // Sigma
  float _sigma;
} Gauss;

// ================ Functions declaration ====================

// Create a new Gauss of mean 'mean' and sigma 'sigma'
// Return NULL if we couldn't create the Gauss
Gauss* GaussCreate(const float mean, const float sigma);
Gauss GaussCreateStatic(const float mean, const float sigma);

// Free the memory used by a Gauss
// Do nothing if arguments are invalid
void GaussFree(Gauss** that);

// Return the value of the Gauss 'that' at 'x'
#if BUILDMODE != 0 
inline 
#endif 
float GaussGet(const Gauss* const that, const float x);

// Return a random value according to the Gauss 'that'
// random() must have been called before calling this function
#if BUILDMODE != 0 
inline 
#endif 
float GaussRnd(Gauss* const that);

// -------------- Smoother

// ================= Define ==================

// ================= Data structure ===================

// ================ Functions declaration ====================

// Return the order 1 smooth value of 'x'
// if x < 0.0 return 0.0
// if x > 1.0 return 1.0
#if BUILDMODE != 0 
inline 
#endif 
float SmoothStep(const float x);

// Return the order 2 smooth value of 'x'
// if x < 0.0 return 0.0
// if x > 1.0 return 1.0
#if BUILDMODE != 0 
inline 
#endif 
float SmootherStep(const float x);

// -------------- Conversion functions

// ================ Functions declaration ====================

// Convert radians to degrees
inline float ConvRad2Deg(const float rad) {
  return rad / PBMATH_TWOPI_DIV_360;
}

// Convert degrees to radians
inline float ConvDeg2Rad(const float deg) {
  return PBMATH_TWOPI_DIV_360 * deg;
}

// -------------- SysLinEq

// ================= Data structure ===================

// Linear system of equalities
typedef struct SysLinEq {
  // Matrix
  MatFloat* _M;
  // Inverse of the matrix
  MatFloat* _Minv;
  // Vector
  VecFloat* _V;
} SysLinEq;

// ================ Functions declaration ====================

// Create a new SysLinEq with matrix 'm' and vector 'v'
// The dimension of 'v' must be equal to the number of column of 'm'
// If 'v' is null the vector null is used instead
// The matrix 'm' must be a square matrix
// Return NULL if we couldn't create the SysLinEq
SysLinEq* _SLECreate(const MatFloat* const m, const VecFloat* const v);

// Free the memory used by the SysLinEq
// Do nothing if arguments are invalid
void SysLinEqFree(SysLinEq** that);

// Clone the SysLinEq 'that'
// Return NULL if we couldn't clone the SysLinEq
SysLinEq* SysLinEqClone(const SysLinEq* const that);

// Solve the SysLinEq _M.x = _V
// Return the solution vector, or null if there is no solution or the 
// arguments are invalid
#if BUILDMODE != 0 
inline 
#endif 
VecFloat* SysLinEqSolve(const SysLinEq* const that);

// Set the matrix of the SysLinEq to a clone of 'm'
// Do nothing if arguments are invalid
#if BUILDMODE != 0 
inline 
#endif 
void SysLinEqSetM(SysLinEq* const that, const MatFloat* const m);

// Set the vector of the SysLinEq to a clone of 'v'
// Do nothing if arguments are invalid
#if BUILDMODE != 0 
inline 
#endif 
void _SLESetV(SysLinEq* const that, const VecFloat* const v);

// -------------- Usefull basic functions

// ================ Functions declaration ====================

// Return x^y when x and y are int
// to avoid numerical imprecision from (pow(double,double)
// From https://stackoverflow.com/questions/29787310/
// does-pow-work-for-int-data-type-in-c
#if BUILDMODE != 0 
inline 
#endif 
int powi(const int base, const int exp);

// Compute a^n, faster than std::pow for n<~100
inline float fastpow(const float a, const int n) {
  double ret = 1.0;
  double b = a;
  for (int i = n; i--;) ret *= b;
  return (float)ret;
}

// Compute a^2
inline float fsquare(const float a) {
  return a * a;
}

// ================= Polymorphism ==================

#define VecClone(Vec) _Generic(Vec, \
  VecFloat*: _VecFloatClone, \
  VecShort*: _VecShortClone, \
  const VecFloat*: _VecFloatClone, \
  const VecShort*: _VecShortClone, \
  default: PBErrInvalidPolymorphism)(Vec)

#define VecEncodeAsJSON(Vec) _Generic(Vec, \
  VecFloat*: _VecFloatEncodeAsJSON, \
  VecShort*: _VecShortEncodeAsJSON, \
  const VecFloat*: _VecFloatEncodeAsJSON, \
  const VecShort*: _VecShortEncodeAsJSON, \
  default: PBErrInvalidPolymorphism)(Vec)

#define VecDecodeAsJSON(VecRef, Json) _Generic(VecRef, \
  VecFloat**: _VecFloatDecodeAsJSON, \
  VecShort**: _VecShortDecodeAsJSON, \
  default: PBErrInvalidPolymorphism)(VecRef, Json)

#define VecLoad(VecRef, Stream) _Generic(VecRef, \
  VecFloat**: _VecFloatLoad, \
  VecShort**: _VecShortLoad, \
  default: PBErrInvalidPolymorphism)(VecRef, Stream)

#define VecSave(Vec, Stream, Compact) _Generic(Vec, \
  VecFloat*: _VecFloatSave, \
  VecFloat2D*: _VecFloatSave, \
  VecFloat3D*: _VecFloatSave, \
  VecShort*: _VecShortSave, \
  VecShort2D*: _VecShortSave, \
  VecShort3D*: _VecShortSave, \
  VecShort4D*: _VecShortSave, \
  const VecFloat*: _VecFloatSave, \
  const VecFloat2D*: _VecFloatSave, \
  const VecFloat3D*: _VecFloatSave, \
  const VecShort*: _VecShortSave, \
  const VecShort2D*: _VecShortSave, \
  const VecShort3D*: _VecShortSave, \
  const VecShort4D*: _VecShortSave, \
  default: PBErrInvalidPolymorphism)( \
    _Generic(Vec,  \
      VecFloat2D*: (const VecFloat*)(Vec), \
      VecFloat3D*: (const VecFloat*)(Vec), \
      VecShort2D*: (const VecShort*)(Vec), \
      VecShort3D*: (const VecShort*)(Vec), \
      VecShort4D*: (const VecShort*)(Vec), \
      const VecFloat2D*: (const VecFloat*)(Vec), \
      const VecFloat3D*: (const VecFloat*)(Vec), \
      const VecShort2D*: (const VecShort*)(Vec), \
      const VecShort3D*: (const VecShort*)(Vec), \
      const VecShort4D*: (const VecShort*)(Vec), \
      default: Vec),  \
    Stream, Compact)

#define VecFree(VecRef) _Generic(VecRef, \
  VecFloat**: _VecFloatFree, \
  VecShort**: _VecShortFree, \
  default: PBErrInvalidPolymorphism)(VecRef)

#define VecPrint(Vec, Stream) _Generic(Vec, \
  VecFloat*: _VecFloatPrintDef, \
  VecFloat2D*: _VecFloatPrintDef, \
  VecFloat3D*: _VecFloatPrintDef, \
  VecShort*: _VecShortPrint, \
  VecShort2D*: _VecShortPrint, \
  VecShort3D*: _VecShortPrint, \
  VecShort4D*: _VecShortPrint, \
  const VecFloat*: _VecFloatPrintDef, \
  const VecFloat2D*: _VecFloatPrintDef, \
  const VecFloat3D*: _VecFloatPrintDef, \
  const VecShort*: _VecShortPrint, \
  const VecShort2D*: _VecShortPrint, \
  const VecShort3D*: _VecShortPrint, \
  const VecShort4D*: _VecShortPrint, \
  default: PBErrInvalidPolymorphism)( \
    _Generic(Vec,  \
      VecFloat2D*: (const VecFloat*)(Vec), \
      VecFloat3D*: (const VecFloat*)(Vec), \
      VecShort2D*: (const VecShort*)(Vec), \
      VecShort3D*: (const VecShort*)(Vec), \
      VecShort4D*: (const VecShort*)(Vec), \
      const VecFloat2D*: (const VecFloat*)(Vec), \
      const VecFloat3D*: (const VecFloat*)(Vec), \
      const VecShort2D*: (const VecShort*)(Vec), \
      const VecShort3D*: (const VecShort*)(Vec), \
      const VecShort4D*: (const VecShort*)(Vec), \
      default: Vec),  \
    Stream)

#define VecGet(Vec, Index) _Generic(Vec, \
  VecFloat*: _VecFloatGet, \
  VecFloat2D*: _VecFloatGet2D, \
  VecFloat3D*: _VecFloatGet3D, \
  VecShort*: _VecShortGet, \
  VecShort2D*: _VecShortGet2D, \
  VecShort3D*: _VecShortGet3D, \
  VecShort4D*: _VecShortGet4D, \
  const VecFloat*: _VecFloatGet, \
  const VecFloat2D*: _VecFloatGet2D, \
  const VecFloat3D*: _VecFloatGet3D, \
  const VecShort*: _VecShortGet, \
  const VecShort2D*: _VecShortGet2D, \
  const VecShort3D*: _VecShortGet3D, \
  const VecShort4D*: _VecShortGet4D, \
  default: PBErrInvalidPolymorphism)(Vec, Index)

#define VecSet(Vec, Index, Val) _Generic(Vec, \
  VecFloat*: _VecFloatSet, \
  VecFloat2D*: _VecFloatSet2D, \
  VecFloat3D*: _VecFloatSet3D, \
  VecShort*: _VecShortSet, \
  VecShort2D*: _VecShortSet2D, \
  VecShort3D*: _VecShortSet3D, \
  VecShort4D*: _VecShortSet4D, \
  default: PBErrInvalidPolymorphism)(Vec, Index, Val)

#define VecSetAdd(Vec, Index, Val) _Generic(Vec, \
  VecFloat*: _VecFloatSetAdd, \
  VecFloat2D*: _VecFloatSetAdd2D, \
  VecFloat3D*: _VecFloatSetAdd3D, \
  VecShort*: _VecShortSetAdd, \
  VecShort2D*: _VecShortSetAdd2D, \
  VecShort3D*: _VecShortSetAdd3D, \
  VecShort4D*: _VecShortSetAdd4D, \
  default: PBErrInvalidPolymorphism)(Vec, Index, Val)

#define VecSetNull(Vec) _Generic(Vec, \
  VecFloat*: _VecFloatSetNull, \
  VecFloat2D*: _VecFloatSetNull, \
  VecFloat3D*: _VecFloatSetNull, \
  VecShort*: _VecShortSetNull, \
  VecShort2D*: _VecShortSetNull, \
  VecShort3D*: _VecShortSetNull, \
  VecShort4D*: _VecShortSetNull, \
  default: PBErrInvalidPolymorphism)( \
    _Generic(Vec,  \
      VecFloat2D*: (VecFloat*)(Vec), \
      VecFloat3D*: (VecFloat*)(Vec), \
      VecShort2D*: (VecShort*)(Vec), \
      VecShort3D*: (VecShort*)(Vec), \
      VecShort4D*: (VecShort*)(Vec), \
      default: Vec))

#define VecCopy(VecDest, VecSrc) _Generic(VecDest, \
  VecFloat*: _Generic(VecSrc, \
    VecFloat*: _VecFloatCopy, \
    VecFloat2D*: _VecFloatCopy, \
    VecFloat3D*: _VecFloatCopy, \
    const VecFloat*: _VecFloatCopy, \
    const VecFloat2D*: _VecFloatCopy, \
    const VecFloat3D*: _VecFloatCopy, \
    default: PBErrInvalidPolymorphism), \
  VecFloat2D*: _Generic(VecSrc, \
    VecFloat*: _VecFloatCopy, \
    VecFloat2D*: _VecFloatCopy, \
    const VecFloat*: _VecFloatCopy, \
    const VecFloat2D*: _VecFloatCopy, \
    default: PBErrInvalidPolymorphism), \
  VecFloat3D*: _Generic(VecSrc, \
    VecFloat*: _VecFloatCopy, \
    VecFloat3D*: _VecFloatCopy, \
    const VecFloat*: _VecFloatCopy, \
    const VecFloat3D*: _VecFloatCopy, \
    default: PBErrInvalidPolymorphism), \
  VecShort*: _Generic(VecSrc, \
    VecShort*: _VecShortCopy, \
    VecShort2D*: _VecShortCopy, \
    VecShort3D*: _VecShortCopy, \
    VecShort4D*: _VecShortCopy, \
    const VecShort*: _VecShortCopy, \
    const VecShort2D*: _VecShortCopy, \
    const VecShort3D*: _VecShortCopy, \
    const VecShort4D*: _VecShortCopy, \
    default: PBErrInvalidPolymorphism), \
  VecShort2D*: _Generic(VecSrc, \
    VecShort*: _VecShortCopy, \
    VecShort2D*: _VecShortCopy, \
    const VecShort*: _VecShortCopy, \
    const VecShort2D*: _VecShortCopy, \
    default: PBErrInvalidPolymorphism), \
  VecShort3D*: _Generic(VecSrc, \
    VecShort*: _VecShortCopy, \
    VecShort3D*: _VecShortCopy, \
    const VecShort*: _VecShortCopy, \
    const VecShort3D*: _VecShortCopy, \
    default: PBErrInvalidPolymorphism), \
  VecShort4D*: _Generic(VecSrc, \
    VecShort*: _VecShortCopy, \
    VecShort4D*: _VecShortCopy, \
    const VecShort*: _VecShortCopy, \
    const VecShort4D*: _VecShortCopy, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)( \
    _Generic(VecDest,  \
      VecFloat2D*: (VecFloat*)(VecDest), \
      VecFloat3D*: (VecFloat*)(VecDest), \
      VecShort2D*: (VecShort*)(VecDest), \
      VecShort3D*: (VecShort*)(VecDest), \
      VecShort4D*: (VecShort*)(VecDest), \
      default: VecDest),  \
    _Generic(VecSrc,  \
      VecFloat2D*: (const VecFloat*)(VecSrc), \
      VecFloat3D*: (const VecFloat*)(VecSrc), \
      VecShort2D*: (const VecShort*)(VecSrc), \
      VecShort3D*: (const VecShort*)(VecSrc), \
      VecShort4D*: (const VecShort*)(VecSrc), \
      const VecFloat2D*: (const VecFloat*)(VecSrc), \
      const VecFloat3D*: (const VecFloat*)(VecSrc), \
      const VecShort2D*: (const VecShort*)(VecSrc), \
      const VecShort3D*: (const VecShort*)(VecSrc), \
      const VecShort4D*: (const VecShort*)(VecSrc), \
      default: VecSrc))

#define VecGetDim(Vec) _Generic(Vec, \
  VecFloat*: _VecFloatGetDim, \
  VecFloat2D*: _VecFloatGetDim, \
  VecFloat3D*: _VecFloatGetDim, \
  VecShort*: _VecShortGetDim, \
  VecShort2D*: _VecShortGetDim, \
  VecShort3D*: _VecShortGetDim, \
  VecShort4D*: _VecShortGetDim, \
  const VecFloat*: _VecFloatGetDim, \
  const VecFloat2D*: _VecFloatGetDim, \
  const VecFloat3D*: _VecFloatGetDim, \
  const VecShort*: _VecShortGetDim, \
  const VecShort2D*: _VecShortGetDim, \
  const VecShort3D*: _VecShortGetDim, \
  const VecShort4D*: _VecShortGetDim, \
  default: PBErrInvalidPolymorphism)( \
    _Generic(Vec, \
      VecFloat*: (const VecFloat*)(Vec), \
      VecFloat2D*: (const VecFloat*)(Vec), \
      VecFloat3D*: (const VecFloat*)(Vec), \
      VecShort*: (const VecShort*)(Vec), \
      VecShort2D*: (const VecShort*)(Vec), \
      VecShort3D*: (const VecShort*)(Vec), \
      VecShort4D*: (const VecShort*)(Vec), \
      const VecFloat*: Vec, \
      const VecFloat2D*: (const VecFloat*)(Vec), \
      const VecFloat3D*: (const VecFloat*)(Vec), \
      const VecShort*: Vec, \
      const VecShort2D*: (const VecShort*)(Vec), \
      const VecShort3D*: (const VecShort*)(Vec), \
      const VecShort4D*: (const VecShort*)(Vec), \
      default: Vec))

#define VecGetNewDim(Vec, Dim) _Generic(Vec, \
  VecFloat*: _VecFloatGetNewDim, \
  const VecFloat*: _VecFloatGetNewDim, \
  default: PBErrInvalidPolymorphism)( \
    _Generic(Vec, \
      VecFloat*: Vec, \
      const VecFloat*: Vec, \
      default: Vec), Dim)

#define VecNorm(Vec) _Generic(Vec, \
  VecFloat*: _VecFloatNorm, \
  VecFloat2D*: _VecFloatNorm2D, \
  VecFloat3D*: _VecFloatNorm3D, \
  const VecFloat*: _VecFloatNorm, \
  const VecFloat2D*: _VecFloatNorm2D, \
  const VecFloat3D*: _VecFloatNorm3D, \
  default: PBErrInvalidPolymorphism)(Vec)

#define VecNormalise(Vec) _Generic(Vec, \
  VecFloat*: _VecFloatNormalise, \
  VecFloat2D*: _VecFloatNormalise2D, \
  VecFloat3D*: _VecFloatNormalise3D, \
  default: PBErrInvalidPolymorphism)(Vec)

#define VecDist(VecA, VecB) _Generic(VecA, \
  VecFloat*: _Generic(VecB, \
    VecFloat*: _VecFloatDist, \
    const VecFloat*: _VecFloatDist, \
    default: PBErrInvalidPolymorphism), \
  VecFloat2D*: _Generic(VecB, \
    VecFloat2D*: _VecFloatDist2D, \
    const VecFloat2D*: _VecFloatDist2D, \
    default: PBErrInvalidPolymorphism), \
  VecFloat3D*: _Generic(VecB, \
    VecFloat3D*: _VecFloatDist3D, \
    const VecFloat3D*: _VecFloatDist3D, \
    default: PBErrInvalidPolymorphism), \
  VecShort*: _Generic(VecB, \
    VecShort*: _VecShortHamiltonDist,\
    const VecShort*: _VecShortHamiltonDist,\
    default: PBErrInvalidPolymorphism), \
  VecShort2D*: _Generic(VecB, \
    VecShort2D*: _VecShortHamiltonDist2D,\
    const VecShort2D*: _VecShortHamiltonDist2D,\
    default: PBErrInvalidPolymorphism), \
  VecShort3D*: _Generic(VecB, \
    VecShort3D*: _VecShortHamiltonDist3D,\
    const VecShort3D*: _VecShortHamiltonDist3D,\
    default: PBErrInvalidPolymorphism), \
  VecShort4D*: _Generic(VecB, \
    VecShort4D*: _VecShortHamiltonDist4D,\
    const VecShort4D*: _VecShortHamiltonDist4D,\
    default: PBErrInvalidPolymorphism), \
  const VecFloat*: _Generic(VecB, \
    VecFloat*: _VecFloatDist, \
    const VecFloat*: _VecFloatDist, \
    default: PBErrInvalidPolymorphism), \
  const VecFloat2D*: _Generic(VecB, \
    VecFloat2D*: _VecFloatDist2D, \
    const VecFloat2D*: _VecFloatDist2D, \
    default: PBErrInvalidPolymorphism), \
  const VecFloat3D*: _Generic(VecB, \
    VecFloat3D*: _VecFloatDist3D, \
    const VecFloat3D*: _VecFloatDist3D, \
    default: PBErrInvalidPolymorphism), \
  const VecShort*: _Generic(VecB, \
    VecShort*: _VecShortHamiltonDist,\
    const VecShort*: _VecShortHamiltonDist,\
    default: PBErrInvalidPolymorphism), \
  const VecShort2D*: _Generic(VecB, \
    VecShort2D*: _VecShortHamiltonDist2D,\
    const VecShort2D*: _VecShortHamiltonDist2D,\
    default: PBErrInvalidPolymorphism), \
  const VecShort3D*: _Generic(VecB, \
    VecShort3D*: _VecShortHamiltonDist3D,\
    const VecShort3D*: _VecShortHamiltonDist3D,\
    default: PBErrInvalidPolymorphism), \
  const VecShort4D*: _Generic(VecB, \
    VecShort4D*: _VecShortHamiltonDist4D,\
    const VecShort4D*: _VecShortHamiltonDist4D,\
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(VecA, VecB)

#define VecHamiltonDist(VecA, VecB) _Generic(VecA, \
  VecFloat*: _Generic(VecB, \
    VecFloat*: _VecFloatHamiltonDist, \
    const VecFloat*: _VecFloatHamiltonDist, \
    default: PBErrInvalidPolymorphism), \
  VecFloat2D*: _Generic(VecB, \
    VecFloat2D*: _VecFloatHamiltonDist2D, \
    const VecFloat2D*: _VecFloatHamiltonDist2D, \
    default: PBErrInvalidPolymorphism), \
  VecFloat3D*: _Generic(VecB, \
    VecFloat3D*: _VecFloatHamiltonDist3D, \
    const VecFloat3D*: _VecFloatHamiltonDist3D, \
    default: PBErrInvalidPolymorphism), \
  VecShort*: _Generic(VecB, \
    VecShort*: _VecShortHamiltonDist,\
    const VecShort*: _VecShortHamiltonDist,\
    default: PBErrInvalidPolymorphism), \
  VecShort2D*: _Generic(VecB, \
    VecShort2D*: _VecShortHamiltonDist2D,\
    const VecShort2D*: _VecShortHamiltonDist2D,\
    default: PBErrInvalidPolymorphism), \
  VecShort3D*: _Generic(VecB, \
    VecShort3D*: _VecShortHamiltonDist3D,\
    const VecShort3D*: _VecShortHamiltonDist3D,\
    default: PBErrInvalidPolymorphism), \
  VecShort4D*: _Generic(VecB, \
    VecShort4D*: _VecShortHamiltonDist4D,\
    const VecShort4D*: _VecShortHamiltonDist4D,\
    default: PBErrInvalidPolymorphism), \
  const VecFloat*: _Generic(VecB, \
    VecFloat*: _VecFloatHamiltonDist, \
    const VecFloat*: _VecFloatHamiltonDist, \
    default: PBErrInvalidPolymorphism), \
  const VecFloat2D*: _Generic(VecB, \
    VecFloat2D*: _VecFloatHamiltonDist2D, \
    const VecFloat2D*: _VecFloatHamiltonDist2D, \
    default: PBErrInvalidPolymorphism), \
  const VecFloat3D*: _Generic(VecB, \
    VecFloat3D*: _VecFloatHamiltonDist3D, \
    const VecFloat3D*: _VecFloatHamiltonDist3D, \
    default: PBErrInvalidPolymorphism), \
  const VecShort*: _Generic(VecB, \
    VecShort*: _VecShortHamiltonDist,\
    const VecShort*: _VecShortHamiltonDist,\
    default: PBErrInvalidPolymorphism), \
  const VecShort2D*: _Generic(VecB, \
    VecShort2D*: _VecShortHamiltonDist2D,\
    const VecShort2D*: _VecShortHamiltonDist2D,\
    default: PBErrInvalidPolymorphism), \
  const VecShort3D*: _Generic(VecB, \
    VecShort3D*: _VecShortHamiltonDist3D,\
    const VecShort3D*: _VecShortHamiltonDist3D,\
    default: PBErrInvalidPolymorphism), \
  const VecShort4D*: _Generic(VecB, \
    VecShort4D*: _VecShortHamiltonDist4D,\
    const VecShort4D*: _VecShortHamiltonDist4D,\
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(VecA, VecB)

#define VecPixelDist(VecA, VecB) _Generic(VecA, \
  VecFloat*: _Generic(VecB, \
    VecFloat*: _VecFloatPixelDist, \
    const VecFloat*: _VecFloatPixelDist, \
    default: PBErrInvalidPolymorphism), \
  VecFloat2D*: _Generic(VecB, \
    VecFloat2D*: _VecFloatPixelDist2D, \
    const VecFloat2D*: _VecFloatPixelDist2D, \
    default: PBErrInvalidPolymorphism), \
  VecFloat3D*: _Generic(VecB, \
    VecFloat3D*: _VecFloatPixelDist3D, \
    const VecFloat3D*: _VecFloatPixelDist3D, \
    default: PBErrInvalidPolymorphism), \
  VecShort*: _Generic(VecB, \
    VecShort*: _VecShortHamiltonDist,\
    const VecShort*: _VecShortHamiltonDist,\
    default: PBErrInvalidPolymorphism), \
  VecShort2D*: _Generic(VecB, \
    VecShort2D*: _VecShortHamiltonDist2D,\
    const VecShort2D*: _VecShortHamiltonDist2D,\
    default: PBErrInvalidPolymorphism), \
  VecShort3D*: _Generic(VecB, \
    VecShort3D*: _VecShortHamiltonDist3D,\
    const VecShort3D*: _VecShortHamiltonDist3D,\
    default: PBErrInvalidPolymorphism), \
  VecShort4D*: _Generic(VecB, \
    VecShort4D*: _VecShortHamiltonDist4D,\
    const VecShort4D*: _VecShortHamiltonDist4D,\
    default: PBErrInvalidPolymorphism), \
  const VecFloat*: _Generic(VecB, \
    VecFloat*: _VecFloatPixelDist, \
    const VecFloat*: _VecFloatPixelDist, \
    default: PBErrInvalidPolymorphism), \
  const VecFloat2D*: _Generic(VecB, \
    VecFloat2D*: _VecFloatPixelDist2D, \
    const VecFloat2D*: _VecFloatPixelDist2D, \
    default: PBErrInvalidPolymorphism), \
  const VecFloat3D*: _Generic(VecB, \
    VecFloat3D*: _VecFloatPixelDist3D, \
    const VecFloat3D*: _VecFloatPixelDist3D, \
    default: PBErrInvalidPolymorphism), \
  const VecShort*: _Generic(VecB, \
    VecShort*: _VecShortHamiltonDist,\
    const VecShort*: _VecShortHamiltonDist,\
    default: PBErrInvalidPolymorphism), \
  const VecShort2D*: _Generic(VecB, \
    VecShort2D*: _VecShortHamiltonDist2D,\
    const VecShort2D*: _VecShortHamiltonDist2D,\
    default: PBErrInvalidPolymorphism), \
  const VecShort3D*: _Generic(VecB, \
    VecShort3D*: _VecShortHamiltonDist3D,\
    const VecShort3D*: _VecShortHamiltonDist3D,\
    default: PBErrInvalidPolymorphism), \
  const VecShort4D*: _Generic(VecB, \
    VecShort4D*: _VecShortHamiltonDist4D,\
    const VecShort4D*: _VecShortHamiltonDist4D,\
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(VecA, VecB)

#define VecIsEqual(VecA, VecB) _Generic(VecA, \
  VecFloat*: _Generic(VecB, \
    VecFloat*: _VecFloatIsEqual, \
    VecFloat2D*: _VecFloatIsEqual, \
    VecFloat3D*: _VecFloatIsEqual, \
    const VecFloat*: _VecFloatIsEqual, \
    const VecFloat2D*: _VecFloatIsEqual, \
    const VecFloat3D*: _VecFloatIsEqual, \
    default: PBErrInvalidPolymorphism), \
  VecFloat2D*: _Generic(VecB, \
    VecFloat*: _VecFloatIsEqual, \
    VecFloat2D*: _VecFloatIsEqual, \
    const VecFloat*: _VecFloatIsEqual, \
    const VecFloat2D*: _VecFloatIsEqual, \
    default: PBErrInvalidPolymorphism), \
  VecFloat3D*: _Generic(VecB, \
    VecFloat*: _VecFloatIsEqual, \
    VecFloat3D*: _VecFloatIsEqual, \
    const VecFloat*: _VecFloatIsEqual, \
    const VecFloat3D*: _VecFloatIsEqual, \
    default: PBErrInvalidPolymorphism), \
  VecShort*: _Generic(VecB, \
    VecShort*: _VecShortIsEqual,\
    VecShort2D*: _VecShortIsEqual,\
    VecShort3D*: _VecShortIsEqual,\
    VecShort4D*: _VecShortIsEqual,\
    const VecShort*: _VecShortIsEqual,\
    const VecShort2D*: _VecShortIsEqual,\
    const VecShort3D*: _VecShortIsEqual,\
    const VecShort4D*: _VecShortIsEqual,\
    default: PBErrInvalidPolymorphism), \
  VecShort2D*: _Generic(VecB, \
    VecShort*: _VecShortIsEqual,\
    VecShort2D*: _VecShortIsEqual,\
    const VecShort*: _VecShortIsEqual,\
    const VecShort2D*: _VecShortIsEqual,\
    default: PBErrInvalidPolymorphism), \
  VecShort3D*: _Generic(VecB, \
    VecShort*: _VecShortIsEqual,\
    VecShort3D*: _VecShortIsEqual,\
    const VecShort*: _VecShortIsEqual,\
    const VecShort3D*: _VecShortIsEqual,\
    default: PBErrInvalidPolymorphism), \
  VecShort4D*: _Generic(VecB, \
    VecShort*: _VecShortIsEqual,\
    VecShort4D*: _VecShortIsEqual,\
    const VecShort*: _VecShortIsEqual,\
    const VecShort4D*: _VecShortIsEqual,\
    default: PBErrInvalidPolymorphism), \
  const VecFloat*: _Generic(VecB, \
    VecFloat*: _VecFloatIsEqual, \
    VecFloat2D*: _VecFloatIsEqual, \
    VecFloat3D*: _VecFloatIsEqual, \
    const VecFloat*: _VecFloatIsEqual, \
    const VecFloat2D*: _VecFloatIsEqual, \
    const VecFloat3D*: _VecFloatIsEqual, \
    default: PBErrInvalidPolymorphism), \
  const VecFloat2D*: _Generic(VecB, \
    VecFloat*: _VecFloatIsEqual, \
    VecFloat2D*: _VecFloatIsEqual, \
    const VecFloat*: _VecFloatIsEqual, \
    const VecFloat2D*: _VecFloatIsEqual, \
    default: PBErrInvalidPolymorphism), \
  const VecFloat3D*: _Generic(VecB, \
    VecFloat*: _VecFloatIsEqual, \
    VecFloat3D*: _VecFloatIsEqual, \
    const VecFloat*: _VecFloatIsEqual, \
    const VecFloat3D*: _VecFloatIsEqual, \
    default: PBErrInvalidPolymorphism), \
  const VecShort*: _Generic(VecB, \
    VecShort*: _VecShortIsEqual,\
    VecShort2D*: _VecShortIsEqual,\
    VecShort3D*: _VecShortIsEqual,\
    VecShort4D*: _VecShortIsEqual,\
    const VecShort*: _VecShortIsEqual,\
    const VecShort2D*: _VecShortIsEqual,\
    const VecShort3D*: _VecShortIsEqual,\
    const VecShort4D*: _VecShortIsEqual,\
    default: PBErrInvalidPolymorphism), \
  const VecShort2D*: _Generic(VecB, \
    VecShort*: _VecShortIsEqual,\
    VecShort2D*: _VecShortIsEqual,\
    const VecShort*: _VecShortIsEqual,\
    const VecShort2D*: _VecShortIsEqual,\
    default: PBErrInvalidPolymorphism), \
  const VecShort3D*: _Generic(VecB, \
    VecShort*: _VecShortIsEqual,\
    VecShort3D*: _VecShortIsEqual,\
    const VecShort*: _VecShortIsEqual,\
    const VecShort3D*: _VecShortIsEqual,\
    default: PBErrInvalidPolymorphism), \
  const VecShort4D*: _Generic(VecB, \
    VecShort*: _VecShortIsEqual,\
    VecShort4D*: _VecShortIsEqual,\
    const VecShort*: _VecShortIsEqual,\
    const VecShort4D*: _VecShortIsEqual,\
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)( \
    _Generic(VecA,  \
      VecFloat2D*: (const VecFloat*)(VecA), \
      VecFloat3D*: (const VecFloat*)(VecA), \
      VecShort2D*: (const VecShort*)(VecA), \
      VecShort3D*: (const VecShort*)(VecA), \
      VecShort4D*: (const VecShort*)(VecA), \
      const VecFloat2D*: (const VecFloat*)(VecA), \
      const VecFloat3D*: (const VecFloat*)(VecA), \
      const VecShort2D*: (const VecShort*)(VecA), \
      const VecShort3D*: (const VecShort*)(VecA), \
      const VecShort4D*: (const VecShort*)(VecA), \
      default: VecA),  \
    _Generic(VecB,  \
      VecFloat2D*: (const VecFloat*)(VecB), \
      VecFloat3D*: (const VecFloat*)(VecB), \
      VecShort2D*: (const VecShort*)(VecB), \
      VecShort3D*: (const VecShort*)(VecB), \
      VecShort4D*: (const VecShort*)(VecB), \
      const VecFloat2D*: (const VecFloat*)(VecB), \
      const VecFloat3D*: (const VecFloat*)(VecB), \
      const VecShort2D*: (const VecShort*)(VecB), \
      const VecShort3D*: (const VecShort*)(VecB), \
      const VecShort4D*: (const VecShort*)(VecB), \
      default: VecB))

#define VecOp(VecA, CoeffA, VecB, CoeffB) _Generic(VecA, \
  VecFloat*: _Generic(VecB, \
    VecFloat*: _VecFloatOp, \
    const VecFloat*: _VecFloatOp, \
    default: PBErrInvalidPolymorphism), \
  VecFloat2D*: _Generic(VecB, \
    VecFloat2D*: _VecFloatOp2D, \
    const VecFloat2D*: _VecFloatOp2D, \
    default: PBErrInvalidPolymorphism), \
  VecFloat3D*: _Generic(VecB, \
    VecFloat3D*: _VecFloatOp3D, \
    const VecFloat3D*: _VecFloatOp3D, \
    default: PBErrInvalidPolymorphism), \
  VecShort*: _Generic(VecB, \
    VecShort*: _VecShortOp, \
    const VecShort*: _VecShortOp, \
    default: PBErrInvalidPolymorphism), \
  VecShort2D*: _Generic(VecB, \
    VecShort2D*: _VecShortOp2D, \
    const VecShort2D*: _VecShortOp2D, \
    default: PBErrInvalidPolymorphism), \
  VecShort3D*: _Generic(VecB, \
    VecShort3D*: _VecShortOp3D, \
    const VecShort3D*: _VecShortOp3D, \
    default: PBErrInvalidPolymorphism), \
  VecShort4D*: _Generic(VecB, \
    VecShort4D*: _VecShortOp4D, \
    const VecShort4D*: _VecShortOp4D, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(VecA, CoeffA, VecB, CoeffB)

#define VecGetOp(VecA, CoeffA, VecB, CoeffB) _Generic(VecA, \
  VecFloat*: _Generic(VecB, \
    VecFloat*: _VecFloatGetOp, \
    const VecFloat*: _VecFloatGetOp, \
    default: PBErrInvalidPolymorphism), \
  VecFloat2D*: _Generic(VecB, \
    VecFloat2D*: _VecFloatGetOp2D, \
    const VecFloat2D*: _VecFloatGetOp2D, \
    default: PBErrInvalidPolymorphism), \
  VecFloat3D*: _Generic(VecB, \
    VecFloat3D*: _VecFloatGetOp3D, \
    const VecFloat3D*: _VecFloatGetOp3D, \
    default: PBErrInvalidPolymorphism), \
  VecShort*: _Generic(VecB, \
    VecShort*: _VecShortGetOp, \
    const VecShort*: _VecShortGetOp, \
    default: PBErrInvalidPolymorphism), \
  VecShort2D*: _Generic(VecB, \
    VecShort2D*: _VecShortGetOp2D, \
    const VecShort2D*: _VecShortGetOp2D, \
    default: PBErrInvalidPolymorphism), \
  VecShort3D*: _Generic(VecB, \
    VecShort3D*: _VecShortGetOp3D, \
    const VecShort3D*: _VecShortGetOp3D, \
    default: PBErrInvalidPolymorphism), \
  VecShort4D*: _Generic(VecB, \
    VecShort4D*: _VecShortGetOp4D, \
    const VecShort4D*: _VecShortGetOp4D, \
    default: PBErrInvalidPolymorphism), \
  const VecFloat*: _Generic(VecB, \
    VecFloat*: _VecFloatGetOp, \
    const VecFloat*: _VecFloatGetOp, \
    default: PBErrInvalidPolymorphism), \
  const VecFloat2D*: _Generic(VecB, \
    VecFloat2D*: _VecFloatGetOp2D, \
    const VecFloat2D*: _VecFloatGetOp2D, \
    default: PBErrInvalidPolymorphism), \
  const VecFloat3D*: _Generic(VecB, \
    VecFloat3D*: _VecFloatGetOp3D, \
    const VecFloat3D*: _VecFloatGetOp3D, \
    default: PBErrInvalidPolymorphism), \
  const VecShort*: _Generic(VecB, \
    VecShort*: _VecShortGetOp, \
    const VecShort*: _VecShortGetOp, \
    default: PBErrInvalidPolymorphism), \
  const VecShort2D*: _Generic(VecB, \
    VecShort2D*: _VecShortGetOp2D, \
    const VecShort2D*: _VecShortGetOp2D, \
    default: PBErrInvalidPolymorphism), \
  const VecShort3D*: _Generic(VecB, \
    VecShort3D*: _VecShortGetOp3D, \
    const VecShort3D*: _VecShortGetOp3D, \
    default: PBErrInvalidPolymorphism), \
  const VecShort4D*: _Generic(VecB, \
    VecShort4D*: _VecShortGetOp4D, \
    const VecShort4D*: _VecShortGetOp4D, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(VecA, CoeffA, VecB, CoeffB)

#define VecHadamardProd(VecA, VecB) _Generic(VecA, \
  VecFloat*: _Generic(VecB, \
    VecFloat*: _VecFloatHadamardProd, \
    const VecFloat*: _VecFloatHadamardProd, \
    default: PBErrInvalidPolymorphism), \
  VecFloat2D*: _Generic(VecB, \
    VecFloat2D*: _VecFloatHadamardProd2D, \
    const VecFloat2D*: _VecFloatHadamardProd2D, \
    default: PBErrInvalidPolymorphism), \
  VecFloat3D*: _Generic(VecB, \
    VecFloat3D*: _VecFloatHadamardProd3D, \
    const VecFloat3D*: _VecFloatHadamardProd3D, \
    default: PBErrInvalidPolymorphism), \
  VecShort*: _Generic(VecB, \
    VecShort*: _VecShortHadamardProd, \
    const VecShort*: _VecShortHadamardProd, \
    default: PBErrInvalidPolymorphism), \
  VecShort2D*: _Generic(VecB, \
    VecShort2D*: _VecShortHadamardProd2D, \
    const VecShort2D*: _VecShortHadamardProd2D, \
    default: PBErrInvalidPolymorphism), \
  VecShort3D*: _Generic(VecB, \
    VecShort3D*: _VecShortHadamardProd3D, \
    const VecShort3D*: _VecShortHadamardProd3D, \
    default: PBErrInvalidPolymorphism), \
  VecShort4D*: _Generic(VecB, \
    VecShort4D*: _VecShortHadamardProd4D, \
    const VecShort4D*: _VecShortHadamardProd4D, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(VecA, VecB)

#define VecGetHadamardProd(VecA, VecB) _Generic(VecA, \
  VecFloat*: _Generic(VecB, \
    VecFloat*: _VecFloatGetHadamardProd, \
    const VecFloat*: _VecFloatGetHadamardProd, \
    default: PBErrInvalidPolymorphism), \
  VecFloat2D*: _Generic(VecB, \
    VecFloat2D*: _VecFloatGetHadamardProd2D, \
    const VecFloat2D*: _VecFloatGetHadamardProd2D, \
    default: PBErrInvalidPolymorphism), \
  VecFloat3D*: _Generic(VecB, \
    VecFloat3D*: _VecFloatGetHadamardProd3D, \
    const VecFloat3D*: _VecFloatGetHadamardProd3D, \
    default: PBErrInvalidPolymorphism), \
  VecShort*: _Generic(VecB, \
    VecShort*: _VecShortGetHadamardProd, \
    const VecShort*: _VecShortGetHadamardProd, \
    default: PBErrInvalidPolymorphism), \
  VecShort2D*: _Generic(VecB, \
    VecShort2D*: _VecShortGetHadamardProd2D, \
    const VecShort2D*: _VecShortGetHadamardProd2D, \
    default: PBErrInvalidPolymorphism), \
  VecShort3D*: _Generic(VecB, \
    VecShort3D*: _VecShortGetHadamardProd3D, \
    const VecShort3D*: _VecShortGetHadamardProd3D, \
    default: PBErrInvalidPolymorphism), \
  VecShort4D*: _Generic(VecB, \
    VecShort4D*: _VecShortGetHadamardProd4D, \
    const VecShort4D*: _VecShortGetHadamardProd4D, \
    default: PBErrInvalidPolymorphism), \
  const VecFloat*: _Generic(VecB, \
    VecFloat*: _VecFloatGetHadamardProd, \
    const VecFloat*: _VecFloatGetHadamardProd, \
    default: PBErrInvalidPolymorphism), \
  const VecFloat2D*: _Generic(VecB, \
    VecFloat2D*: _VecFloatGetHadamardProd2D, \
    const VecFloat2D*: _VecFloatGetHadamardProd2D, \
    default: PBErrInvalidPolymorphism), \
  const VecFloat3D*: _Generic(VecB, \
    VecFloat3D*: _VecFloatGetHadamardProd3D, \
    const VecFloat3D*: _VecFloatGetHadamardProd3D, \
    default: PBErrInvalidPolymorphism), \
  const VecShort*: _Generic(VecB, \
    VecShort*: _VecShortGetHadamardProd, \
    const VecShort*: _VecShortGetHadamardProd, \
    default: PBErrInvalidPolymorphism), \
  const VecShort2D*: _Generic(VecB, \
    VecShort2D*: _VecShortGetHadamardProd2D, \
    const VecShort2D*: _VecShortGetHadamardProd2D, \
    default: PBErrInvalidPolymorphism), \
  const VecShort3D*: _Generic(VecB, \
    VecShort3D*: _VecShortGetHadamardProd3D, \
    const VecShort3D*: _VecShortGetHadamardProd3D, \
    default: PBErrInvalidPolymorphism), \
  const VecShort4D*: _Generic(VecB, \
    VecShort4D*: _VecShortGetHadamardProd4D, \
    const VecShort4D*: _VecShortGetHadamardProd4D, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(VecA, VecB)

#define VecScale(Vec, Scale) _Generic(Vec, \
  VecFloat*: _VecFloatScale, \
  VecFloat2D*: _VecFloatScale2D, \
  VecFloat3D*: _VecFloatScale3D, \
  default: PBErrInvalidPolymorphism)(Vec, Scale)

#define VecGetScale(Vec, Scale) _Generic(Vec, \
  VecFloat*: _VecFloatGetScale, \
  const VecFloat*: _VecFloatGetScale, \
  VecFloat2D*: _VecFloatGetScale2D, \
  const VecFloat2D*: _VecFloatGetScale2D, \
  VecFloat3D*: _VecFloatGetScale3D, \
  const VecFloat3D*: _VecFloatGetScale3D, \
  default: PBErrInvalidPolymorphism)(Vec, Scale)

#define VecRot(Vec, Theta) _Generic(Vec, \
  VecFloat*: _VecFloatRot2D, \
  VecFloat2D*: _VecFloatRot2D, \
  default: PBErrInvalidPolymorphism)((VecFloat2D*)(Vec), Theta)

#define VecGetRot(Vec, Theta) _Generic(Vec, \
  VecFloat*: _VecFloatGetRot2D, \
  const VecFloat*: _VecFloatGetRot2D, \
  VecFloat2D*: _VecFloatGetRot2D, \
  const VecFloat2D*: _VecFloatGetRot2D, \
  default: PBErrInvalidPolymorphism)((const VecFloat2D*)(Vec), Theta)

#define VecRotAxis(Vec, Axis, Theta) _Generic(Vec, \
  VecFloat*: _VecFloatRotAxis, \
  VecFloat3D*: _VecFloatRotAxis, \
  default: PBErrInvalidPolymorphism)((VecFloat3D*)(Vec), \
    (VecFloat3D*)(Axis), Theta)

#define VecGetRotAxis(Vec, Axis, Theta) _Generic(Vec, \
  VecFloat*: _VecFloatGetRotAxis, \
  const VecFloat*: _VecFloatGetRotAxis, \
  VecFloat3D*: _VecFloatGetRotAxis, \
  const VecFloat3D*: _VecFloatGetRotAxis, \
  default: PBErrInvalidPolymorphism)((const VecFloat3D*)(Vec), \
    (const VecFloat3D*)(Axis), Theta)

#define VecRotX(Vec, Theta) _Generic(Vec, \
  VecFloat*: _VecFloatRotX, \
  VecFloat3D*: _VecFloatRotX, \
  default: PBErrInvalidPolymorphism)((VecFloat3D*)(Vec), Theta)

#define VecGetRotX(Vec, Theta) _Generic(Vec, \
  VecFloat*: _VecFloatGetRotX, \
  const VecFloat*: _VecFloatGetRotX, \
  VecFloat3D*: _VecFloatGetRotX, \
  const VecFloat3D*: _VecFloatGetRotX, \
  default: PBErrInvalidPolymorphism)((const VecFloat3D*)(Vec), Theta)

#define VecRotY(Vec, Theta) _Generic(Vec, \
  VecFloat*: _VecFloatRotY, \
  VecFloat3D*: _VecFloatRotY, \
  default: PBErrInvalidPolymorphism)((VecFloat3D*)(Vec), Theta)

#define VecGetRotY(Vec, Theta) _Generic(Vec, \
  VecFloat*: _VecFloatGetRotY, \
  const VecFloat*: _VecFloatGetRotY, \
  VecFloat3D*: _VecFloatGetRotY, \
  const VecFloat3D*: _VecFloatGetRotY, \
  default: PBErrInvalidPolymorphism)((const VecFloat3D*)(Vec), Theta)

#define VecRotZ(Vec, Theta) _Generic(Vec, \
  VecFloat*: _VecFloatRotZ, \
  VecFloat3D*: _VecFloatRotZ, \
  default: PBErrInvalidPolymorphism)((VecFloat3D*)(Vec), Theta)

#define VecGetRotZ(Vec, Theta) _Generic(Vec, \
  VecFloat*: _VecFloatGetRotZ, \
  const VecFloat*: _VecFloatGetRotZ, \
  VecFloat3D*: _VecFloatGetRotZ, \
  const VecFloat3D*: _VecFloatGetRotZ, \
  default: PBErrInvalidPolymorphism)((const VecFloat3D*)(Vec), Theta)

#define VecDotProd(VecA, VecB) _Generic(VecA, \
  VecShort*: _VecShortDotProd,\
  const VecShort*: _VecShortDotProd,\
  VecShort2D*: _VecShortDotProd2D,\
  const VecShort2D*: _VecShortDotProd2D,\
  VecShort3D*: _VecShortDotProd3D,\
  const VecShort3D*: _VecShortDotProd3D,\
  VecShort4D*: _VecShortDotProd4D,\
  const VecShort4D*: _VecShortDotProd4D,\
  VecFloat*: _VecFloatDotProd, \
  const VecFloat*: _VecFloatDotProd, \
  VecFloat2D*: _VecFloatDotProd2D, \
  const VecFloat2D*: _VecFloatDotProd2D, \
  VecFloat3D*: _VecFloatDotProd3D, \
  const VecFloat3D*: _VecFloatDotProd3D, \
  default: PBErrInvalidPolymorphism) (VecA, VecB) \

#define VecAngleTo(VecFrom, VecTo) _Generic(VecFrom, \
  VecFloat*: _VecFloatAngleTo2D, \
  const VecFloat*: _VecFloatAngleTo2D, \
  VecFloat2D*: _VecFloatAngleTo2D, \
  const VecFloat2D*: _VecFloatAngleTo2D, \
  default: PBErrInvalidPolymorphism)((const VecFloat2D*)(VecFrom), \
    (const VecFloat2D*)(VecTo))

#define VecStep(Vec, VecBound) _Generic(Vec, \
  VecShort*: _VecShortStep, \
  VecShort2D*: _VecShortStep, \
  VecShort3D*: _VecShortStep, \
  VecShort4D*: _VecShortStep, \
  default: PBErrInvalidPolymorphism)((VecShort*)(Vec), \
    (const VecShort*)(VecBound))

#define VecPStep(Vec, VecBound) _Generic(Vec, \
  VecShort*: _VecShortPStep, \
  VecShort2D*: _VecShortPStep, \
  VecShort3D*: _VecShortPStep, \
  VecShort4D*: _VecShortPStep, \
  default: PBErrInvalidPolymorphism)((VecShort*)(Vec), \
    (const VecShort*)(VecBound))

#define VecShiftStep(Vec, VecFrom, VecTo) _Generic(Vec, \
  VecShort*: _VecShortShiftStep, \
  VecShort2D*: _VecShortShiftStep, \
  VecShort3D*: _VecShortShiftStep, \
  VecShort4D*: _VecShortShiftStep, \
  default: PBErrInvalidPolymorphism)((VecShort*)(Vec), \
    (const VecShort*)(VecFrom), (const VecShort*)(VecTo))

#define VecPStepDelta(Vec, VecBound, VecDelta) _Generic(Vec, \
  VecShort*: _VecShortPStepDelta, \
  VecShort2D*: _VecShortPStepDelta, \
  VecShort3D*: _VecShortPStepDelta, \
  VecShort4D*: _VecShortPStepDelta, \
  default: PBErrInvalidPolymorphism)((VecShort*)(Vec), \
    (const VecShort*)(VecBound), (const VecShort*)(VecDelta))

#define VecGetMaxVal(Vec) _Generic(Vec, \
  VecFloat*: _VecFloatGetMaxVal, \
  const VecFloat*: _VecFloatGetMaxVal, \
  VecFloat2D*: _VecFloatGetMaxVal, \
  const VecFloat2D*: _VecFloatGetMaxVal, \
  VecFloat3D*: _VecFloatGetMaxVal, \
  const VecFloat3D*: _VecFloatGetMaxVal, \
  VecShort*: _VecShortGetMaxVal, \
  const VecShort*: _VecShortGetMaxVal, \
  VecShort2D*: _VecShortGetMaxVal, \
  const VecShort2D*: _VecShortGetMaxVal, \
  VecShort3D*: _VecShortGetMaxVal, \
  const VecShort3D*: _VecShortGetMaxVal, \
  VecShort4D*: _VecShortGetMaxVal, \
  const VecShort4D*: _VecShortGetMaxVal, \
  default: PBErrInvalidPolymorphism) (_Generic(Vec, \
    VecFloat2D*: (const VecFloat*)(Vec), \
    const VecFloat2D*: (const VecFloat*)(Vec), \
    VecFloat3D*: (const VecFloat*)(Vec), \
    const VecFloat3D*: (const VecFloat*)(Vec), \
    VecShort2D*: (const VecShort*)(Vec), \
    const VecShort2D*: (const VecShort*)(Vec), \
    VecShort3D*: (const VecShort*)(Vec), \
    const VecShort3D*: (const VecShort*)(Vec), \
    VecShort4D*: (const VecShort*)(Vec), \
    const VecShort4D*: (const VecShort*)(Vec), \
    default: Vec))

#define VecGetMinVal(Vec) _Generic(Vec, \
  VecFloat*: _VecFloatGetMinVal, \
  const VecFloat*: _VecFloatGetMinVal, \
  VecFloat2D*: _VecFloatGetMinVal, \
  const VecFloat2D*: _VecFloatGetMinVal, \
  VecFloat3D*: _VecFloatGetMinVal, \
  const VecFloat3D*: _VecFloatGetMinVal, \
  VecShort*: _VecShortGetMinVal, \
  const VecShort*: _VecShortGetMinVal, \
  VecShort2D*: _VecShortGetMinVal, \
  const VecShort2D*: _VecShortGetMinVal, \
  VecShort3D*: _VecShortGetMinVal, \
  const VecShort3D*: _VecShortGetMinVal, \
  VecShort4D*: _VecShortGetMinVal, \
  const VecShort4D*: _VecShortGetMinVal, \
  default: PBErrInvalidPolymorphism) (_Generic(Vec, \
    VecFloat2D*: (const VecFloat*)(Vec), \
    const VecFloat2D*: (const VecFloat*)(Vec), \
    VecFloat3D*: (const VecFloat*)(Vec), \
    const VecFloat3D*: (const VecFloat*)(Vec), \
    VecShort2D*: (const VecShort*)(Vec), \
    const VecShort2D*: (const VecShort*)(Vec), \
    VecShort3D*: (const VecShort*)(Vec), \
    const VecShort3D*: (const VecShort*)(Vec), \
    VecShort4D*: (const VecShort*)(Vec), \
    const VecShort4D*: (const VecShort*)(Vec), \
    default: Vec))

#define VecGetMaxValAbs(Vec) _Generic(Vec, \
  VecFloat*: _VecFloatGetMaxValAbs, \
  const VecFloat*: _VecFloatGetMaxValAbs, \
  VecFloat2D*: _VecFloatGetMaxValAbs, \
  const VecFloat2D*: _VecFloatGetMaxValAbs, \
  VecFloat3D*: _VecFloatGetMaxValAbs, \
  const VecFloat3D*: _VecFloatGetMaxValAbs, \
  VecShort*: _VecShortGetMaxValAbs, \
  const VecShort*: _VecShortGetMaxValAbs, \
  VecShort2D*: _VecShortGetMaxValAbs, \
  const VecShort2D*: _VecShortGetMaxValAbs, \
  VecShort3D*: _VecShortGetMaxValAbs, \
  const VecShort3D*: _VecShortGetMaxValAbs, \
  VecShort4D*: _VecShortGetMaxValAbs, \
  const VecShort4D*: _VecShortGetMaxValAbs, \
  default: PBErrInvalidPolymorphism) (_Generic(Vec, \
    VecFloat2D*: (const VecFloat*)(Vec), \
    const VecFloat2D*: (const VecFloat*)(Vec), \
    VecFloat3D*: (const VecFloat*)(Vec), \
    const VecFloat3D*: (const VecFloat*)(Vec), \
    VecShort2D*: (const VecShort*)(Vec), \
    const VecShort2D*: (const VecShort*)(Vec), \
    VecShort3D*: (const VecShort*)(Vec), \
    const VecShort3D*: (const VecShort*)(Vec), \
    VecShort4D*: (const VecShort*)(Vec), \
    const VecShort4D*: (const VecShort*)(Vec), \
    default: Vec))

#define VecGetMinValAbs(Vec) _Generic(Vec, \
  VecFloat*: _VecFloatGetMinValAbs, \
  const VecFloat*: _VecFloatGetMinValAbs, \
  VecFloat2D*: _VecFloatGetMinValAbs, \
  const VecFloat2D*: _VecFloatGetMinValAbs, \
  VecFloat3D*: _VecFloatGetMinValAbs, \
  const VecFloat3D*: _VecFloatGetMinValAbs, \
  VecShort*: _VecShortGetMinValAbs, \
  const VecShort*: _VecShortGetMinValAbs, \
  VecShort2D*: _VecShortGetMinValAbs, \
  const VecShort2D*: _VecShortGetMinValAbs, \
  VecShort3D*: _VecShortGetMinValAbs, \
  const VecShort3D*: _VecShortGetMinValAbs, \
  VecShort4D*: _VecShortGetMinValAbs, \
  const VecShort4D*: _VecShortGetMinValAbs, \
  default: PBErrInvalidPolymorphism) (_Generic(Vec, \
    VecFloat2D*: (const VecFloat*)(Vec), \
    const VecFloat2D*: (const VecFloat*)(Vec), \
    VecFloat3D*: (const VecFloat*)(Vec), \
    const VecFloat3D*: (const VecFloat*)(Vec), \
    VecShort2D*: (const VecShort*)(Vec), \
    const VecShort2D*: (const VecShort*)(Vec), \
    VecShort3D*: (const VecShort*)(Vec), \
    const VecShort3D*: (const VecShort*)(Vec), \
    VecShort4D*: (const VecShort*)(Vec), \
    const VecShort4D*: (const VecShort*)(Vec), \
    default: Vec))

#define VecStepDelta(Vec, VecBound, Delta) _Generic(Vec, \
  VecFloat*: _VecFloatStepDelta, \
  VecFloat2D*: _VecFloatStepDelta, \
  VecFloat3D*: _VecFloatStepDelta, \
  VecShort*: _VecShortStepDelta, \
  VecShort2D*: _VecShortStepDelta, \
  VecShort3D*: _VecShortStepDelta, \
  VecShort4D*: _VecShortStepDelta, \
  default: PBErrInvalidPolymorphism)(_Generic(Vec, \
    VecFloat*: Vec, \
    VecFloat2D*: (VecFloat*)(Vec), \
    VecFloat3D*: (VecFloat*)(Vec), \
    VecShort*: Vec, \
    VecShort2D*: (VecShort*)(Vec), \
    VecShort3D*: (VecShort*)(Vec), \
    VecShort4D*: (VecShort*)(Vec)), _Generic(Vec, \
    VecFloat*: VecBound, \
    VecFloat2D*: (VecFloat*)(VecBound), \
    VecFloat3D*: (VecFloat*)(VecBound), \
    VecShort*: VecBound, \
    VecShort2D*: (VecShort*)(VecBound), \
    VecShort3D*: (VecShort*)(VecBound), \
    VecShort4D*: (VecShort*)(VecBound)), _Generic(Vec, \
    VecFloat*: Delta, \
    VecFloat2D*: (VecFloat*)(Delta), \
    VecFloat3D*: (VecFloat*)(Delta), \
    VecShort*: Delta, \
    VecShort2D*: (VecShort*)(Delta), \
    VecShort3D*: (VecShort*)(Delta), \
    VecShort4D*: (VecShort*)(Delta)))  

#define VecShiftStepDelta(Vec, VecFrom, VecTo, Delta) _Generic(Vec, \
  VecFloat*: _VecFloatShiftStepDelta, \
  VecFloat2D*: _VecFloatShiftStepDelta, \
  VecFloat3D*: _VecFloatShiftStepDelta, \
  default: PBErrInvalidPolymorphism)((VecFloat*)(Vec), \
    (VecFloat*)(VecFrom), (VecFloat*)(VecTo), (VecFloat*)(Delta))

#define VecGetIMaxVal(Vec) _Generic(Vec, \
  VecFloat*: _VecFloatGetIMaxVal, \
  const VecFloat*: _VecFloatGetIMaxVal, \
  VecFloat2D*: _VecFloatGetIMaxVal, \
  const VecFloat2D*: _VecFloatGetIMaxVal, \
  VecFloat3D*: _VecFloatGetIMaxVal, \
  const VecFloat3D*: _VecFloatGetIMaxVal, \
  VecShort*: _VecShortGetIMaxVal, \
  const VecShort*: _VecShortGetIMaxVal, \
  VecShort2D*: _VecShortGetIMaxVal, \
  const VecShort2D*: _VecShortGetIMaxVal, \
  VecShort3D*: _VecShortGetIMaxVal, \
  const VecShort3D*: _VecShortGetIMaxVal, \
  VecShort4D*: _VecShortGetIMaxVal, \
  const VecShort4D*: _VecShortGetIMaxVal, \
  default: PBErrInvalidPolymorphism) (_Generic(Vec, \
    VecFloat2D*: (const VecFloat*)(Vec), \
    const VecFloat2D*: (const VecFloat*)(Vec), \
    VecFloat3D*: (const VecFloat*)(Vec), \
    const VecFloat3D*: (const VecFloat*)(Vec), \
    VecShort2D*: (const VecShort*)(Vec), \
    const VecShort2D*: (const VecShort*)(Vec), \
    VecShort3D*: (const VecShort*)(Vec), \
    const VecShort3D*: (const VecShort*)(Vec), \
    VecShort4D*: (const VecShort*)(Vec), \
    const VecShort4D*: (const VecShort*)(Vec), \
    default: Vec))

#define MatClone(Mat) _Generic(Mat, \
  MatFloat*: _MatFloatClone, \
  const MatFloat*: _MatFloatClone, \
  default: PBErrInvalidPolymorphism)(Mat)

#define MatEncodeAsJSON(Mat) _Generic(Mat, \
  MatFloat*: _MatFloatEncodeAsJSON, \
  const MatFloat*: _MatFloatEncodeAsJSON, \
  default: PBErrInvalidPolymorphism)(Mat)

#define MatDecodeAsJSON(MatRef, Json) _Generic(MatRef, \
  MatFloat**: _MatFloatDecodeAsJSON, \
  default: PBErrInvalidPolymorphism)(MatRef, Json)

#define MatLoad(MatRef, Stream) _Generic(MatRef, \
  MatFloat**: _MatFloatLoad, \
  default: PBErrInvalidPolymorphism)(MatRef, Stream)

#define MatSave(Mat, Stream, Compact) _Generic(Mat, \
  MatFloat*: _MatFloatSave, \
  const MatFloat*: _MatFloatSave, \
  default: PBErrInvalidPolymorphism)(Mat, Stream, Compact)

#define MatFree(MatRef) _Generic(MatRef, \
  MatFloat**: _MatFloatFree, \
  default: PBErrInvalidPolymorphism)(MatRef)

#define MatPrintln(Mat, Stream) _Generic(Mat, \
  MatFloat*: _MatFloatPrintlnDef, \
  const MatFloat*: _MatFloatPrintlnDef, \
  default: PBErrInvalidPolymorphism)(Mat, Stream)

#define MatGet(Mat, VecIndex) _Generic(Mat, \
  MatFloat*: _MatFloatGet, \
  const MatFloat*: _MatFloatGet, \
  default: PBErrInvalidPolymorphism)(Mat, VecIndex)

#define MatSet(Mat, VecIndex, Val) _Generic(Mat, \
  MatFloat*: _MatFloatSet, \
  default: PBErrInvalidPolymorphism)(Mat, VecIndex, Val)

#define MatCopy(MatDest, MatSrc) _Generic(MatDest, \
  MatFloat*: _Generic (MatSrc, \
    MatFloat*: _MatFloatCopy, \
    const MatFloat*: _MatFloatCopy, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(MatDest, MatSrc)

#define MatDim(Mat) _Generic(Mat, \
  MatFloat*: _MatFloatDim, \
  const MatFloat*: _MatFloatDim, \
  default: PBErrInvalidPolymorphism)(Mat)

#define MatGetDim(Mat) _Generic(Mat, \
  MatFloat*: _MatFloatGetDim, \
  const MatFloat*: _MatFloatGetDim, \
  default: PBErrInvalidPolymorphism)(Mat)

#define MatInv(Mat) _Generic(Mat, \
  MatFloat*: _MatFloatInv, \
  const MatFloat*: _MatFloatInv, \
  default: PBErrInvalidPolymorphism)(Mat)

#define MatGetProdMat(MatA, MatB) _Generic(MatA, \
  MatFloat*: _Generic(MatB, \
    MatFloat*: _MatFloatGetProdMatFloat, \
    const MatFloat*: _MatFloatGetProdMatFloat, \
    default: PBErrInvalidPolymorphism), \
  const MatFloat*: _Generic(MatB, \
    MatFloat*: _MatFloatGetProdMatFloat, \
    const MatFloat*: _MatFloatGetProdMatFloat, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(MatA, MatB)

#define MatGetProdVec(Mat, Vec) _Generic(Mat, \
  MatFloat*: _Generic(Vec, \
    VecFloat*: _MatFloatGetProdVecFloat, \
    const VecFloat*: _MatFloatGetProdVecFloat, \
    VecFloat2D*: _MatFloatGetProdVecFloat, \
    const VecFloat2D*: _MatFloatGetProdVecFloat, \
    VecFloat3D*: _MatFloatGetProdVecFloat, \
    const VecFloat3D*: _MatFloatGetProdVecFloat, \
    default: PBErrInvalidPolymorphism), \
  const MatFloat*: _Generic(Vec, \
    VecFloat*: _MatFloatGetProdVecFloat, \
    const VecFloat*: _MatFloatGetProdVecFloat, \
    VecFloat2D*: _MatFloatGetProdVecFloat, \
    const VecFloat2D*: _MatFloatGetProdVecFloat, \
    VecFloat3D*: _MatFloatGetProdVecFloat, \
    const VecFloat3D*: _MatFloatGetProdVecFloat, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(Mat, (VecFloat*)(Vec))

#define MatAdd(MatA, MatB) _Generic(MatA, \
  MatFloat*: _Generic(MatB, \
    MatFloat*: _MatFloatAdd, \
    const MatFloat*: _MatFloatAdd, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(MatA, MatB)

#define MatGetAdd(MatA, MatB) _Generic(MatA, \
  MatFloat*: _Generic(MatB, \
    MatFloat*: _MatFloatGetAdd, \
    const MatFloat*: _MatFloatGetAdd, \
    default: PBErrInvalidPolymorphism), \
  const MatFloat*: _Generic(MatB, \
    MatFloat*: _MatFloatGetAdd, \
    const MatFloat*: _MatFloatGetAdd, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(MatA, MatB)

#define MatSetIdentity(Mat) _Generic(Mat, \
  MatFloat*: _MatFloatSetIdentity, \
  default: PBErrInvalidPolymorphism)(Mat)

#define MatIsEqual(MatA, MatB) _Generic(MatA, \
  MatFloat*: _Generic(MatB, \
    MatFloat*: _MatFloatIsEqual, \
    const MatFloat*: _MatFloatIsEqual, \
    default: PBErrInvalidPolymorphism), \
  const MatFloat*: _Generic(MatB, \
    MatFloat*: _MatFloatIsEqual, \
    const MatFloat*: _MatFloatIsEqual, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(MatA, MatB)

#define SysLinEqCreate(Mat, Vec) _Generic(Vec, \
  VecFloat*: _SLECreate, \
  const VecFloat*: _SLECreate, \
  VecFloat2D*: _SLECreate, \
  const VecFloat2D*: _SLECreate, \
  VecFloat3D*: _SLECreate, \
  const VecFloat3D*: _SLECreate, \
  default: PBErrInvalidPolymorphism)(Mat, (VecFloat*)(Vec))

#define SysLinEqSetV(Sys, Vec) _Generic(Vec, \
  VecFloat*: _SLESetV, \
  const VecFloat*: _SLESetV, \
  VecFloat2D*: _SLESetV, \
  const VecFloat2D*: _SLESetV, \
  VecFloat3D*: _SLESetV, \
  const VecFloat3D*: _SLESetV, \
  default: PBErrInvalidPolymorphism)(Sys, (VecFloat*)(Vec))

// ================ Inliner ====================

#if BUILDMODE != 0
#include "pbmath-inline.c"
#endif


#endif
