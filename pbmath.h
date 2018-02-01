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

// ================= Define ==================

#define PBMATH_EPSILON 0.00001
#define PBMATH_TWOPI 6.283185307
#define PBMATH_TWOPI_DIV_360 0.01745329252
#define PBMATH_PI 3.141592654
#define PBMATH_HALFPI 1.570796327
#define PBMATH_QUARTERPI 0.7853981634
#define PBMATH_SQRTTWO 1.414213562
#define PBMATH_SQRTONEHALF 0.707106781
#if BUILDWITHGRAPHICLIB != 1
#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#endif
#define ISEQUALF(a,b) (fabs((a)-(b))<PBMATH_EPSILON)
#define SHORT(a) ((short)(round(a)))
#define INT(a) ((int)(round(a)))
#define rnd() (float)(rand())/(float)(RAND_MAX)

// ================= Polymorphism ==================

#define VecClone(V) _Generic((V), \
  VecFloat*: VecFloatClone, \
  VecShort*: VecShortClone, \
  default: PBErrInvalidPolymorphism)(V)

#define VecLoad(V, S) _Generic((V), \
  VecFloat**: VecFloatLoad, \
  VecShort**: VecShortLoad, \
  default: PBErrInvalidPolymorphism)(V, S)

#define VecSave(V, S) _Generic((V), \
  VecFloat*: VecFloatSave, \
  VecFloat2D*: VecFloatSave, \
  VecFloat3D*: VecFloatSave, \
  VecShort*: VecShortSave, \
  VecShort2D*: VecShortSave, \
  VecShort3D*: VecShortSave, \
  VecShort4D*: VecShortSave, \
  default: PBErrInvalidPolymorphism)( \
    _Generic((V),  \
      VecFloat2D*: (VecFloat*)(V), \
      VecFloat3D*: (VecFloat*)(V), \
      VecShort2D*: (VecShort*)(V), \
      VecShort3D*: (VecShort*)(V), \
      VecShort4D*: (VecShort*)(V), \
      default: (V)),  \
    S)

#define VecFree(V) _Generic((V), \
  VecFloat**: VecFloatFree, \
  VecShort**: VecShortFree, \
  default: PBErrInvalidPolymorphism)(V)

#define VecPrint(V, S) _Generic((V), \
  VecFloat*: VecFloatPrintDef, \
  VecFloat2D*: VecFloatPrintDef, \
  VecFloat3D*: VecFloatPrintDef, \
  VecShort*: VecShortPrint, \
  VecShort2D*: VecShortPrint, \
  VecShort3D*: VecShortPrint, \
  VecShort4D*: VecShortPrint, \
  default: PBErrInvalidPolymorphism)( \
    _Generic((V),  \
      VecFloat2D*: (VecFloat*)(V), \
      VecFloat3D*: (VecFloat*)(V), \
      VecShort2D*: (VecShort*)(V), \
      VecShort3D*: (VecShort*)(V), \
      VecShort4D*: (VecShort*)(V), \
      default: (V)),  \
    S)

#define VecGet(V, I) _Generic((V), \
  VecFloat*: VecFloatGet, \
  VecFloat2D*: VecFloatGet2D, \
  VecFloat3D*: VecFloatGet3D, \
  VecShort*: VecShortGet, \
  VecShort2D*: VecShortGet2D, \
  VecShort3D*: VecShortGet3D, \
  VecShort4D*: VecShortGet4D, \
  default: PBErrInvalidPolymorphism)(V, I)

#define VecSet(V, I, VAL) _Generic((V), \
  VecFloat*: VecFloatSet, \
  VecFloat2D*: VecFloatSet2D, \
  VecFloat3D*: VecFloatSet3D, \
  VecShort*: VecShortSet, \
  VecShort2D*: VecShortSet2D, \
  VecShort3D*: VecShortSet3D, \
  VecShort4D*: VecShortSet4D, \
  default: PBErrInvalidPolymorphism)(V, I, VAL)

#define VecSetNull(V) _Generic((V), \
  VecFloat*: VecFloatSetNull, \
  VecFloat2D*: VecFloatSetNull2D, \
  VecFloat3D*: VecFloatSetNull3D, \
  VecShort*: VecShortSetNull, \
  VecShort2D*: VecShortSetNull2D, \
  VecShort3D*: VecShortSetNull3D, \
  VecShort4D*: VecShortSetNull4D, \
  default: PBErrInvalidPolymorphism)(V)

#define VecCopy(V, W) _Generic((V), \
  VecFloat*: _Generic((W), \
    VecFloat*: VecFloatCopy, \
    VecFloat2D*: VecFloatCopy, \
    VecFloat3D*: VecFloatCopy, \
    default: PBErrInvalidPolymorphism), \
  VecFloat2D*: _Generic((W), \
    VecFloat*: VecFloatCopy, \
    VecFloat2D*: VecFloatCopy, \
    default: PBErrInvalidPolymorphism), \
  VecFloat3D*: _Generic((W), \
    VecFloat*: VecFloatCopy, \
    VecFloat3D*: VecFloatCopy, \
    default: PBErrInvalidPolymorphism), \
  VecShort*: _Generic((W), \
    VecShort*: VecShortCopy, \
    VecShort2D*: VecShortCopy, \
    VecShort3D*: VecShortCopy, \
    VecShort4D*: VecShortCopy, \
    default: PBErrInvalidPolymorphism), \
  VecShort2D*: _Generic((W), \
    VecShort*: VecShortCopy, \
    VecShort2D*: VecShortCopy, \
    default: PBErrInvalidPolymorphism), \
  VecShort3D*: _Generic((W), \
    VecShort*: VecShortCopy, \
    VecShort3D*: VecShortCopy, \
    default: PBErrInvalidPolymorphism), \
  VecShort4D*: _Generic((W), \
    VecShort*: VecShortCopy, \
    VecShort4D*: VecShortCopy, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)( \
    _Generic((V),  \
      VecFloat2D*: (VecFloat*)(V), \
      VecFloat3D*: (VecFloat*)(V), \
      VecShort2D*: (VecShort*)(V), \
      VecShort3D*: (VecShort*)(V), \
      VecShort4D*: (VecShort*)(V), \
      default: (V)),  \
    _Generic((W),  \
      VecFloat2D*: (VecFloat*)(W), \
      VecFloat3D*: (VecFloat*)(W), \
      VecShort2D*: (VecShort*)(W), \
      VecShort3D*: (VecShort*)(W), \
      VecShort4D*: (VecShort*)(W), \
      default: (W)))

#define VecDim(V) _Generic((V), \
  VecFloat*: VecFloatDim, \
  VecShort*: VecShortDim, \
  default: PBErrInvalidPolymorphism)(V)

#define VecNorm(V) _Generic((V), \
  VecFloat*: VecFloatNorm, \
  VecFloat2D*: VecFloatNorm2D, \
  VecFloat3D*: VecFloatNorm3D, \
  default: PBErrInvalidPolymorphism)(V)

#define VecNormalise(V) _Generic((V), \
  VecFloat*: VecFloatNormalise, \
  VecFloat2D*: VecFloatNormalise2D, \
  VecFloat3D*: VecFloatNormalise3D, \
  default: PBErrInvalidPolymorphism)(V)

#define VecDist(V, W) _Generic((V), \
  VecFloat*: _Generic((W), \
    VecFloat*: VecFloatDist, \
    default: PBErrInvalidPolymorphism), \
  VecFloat2D*: _Generic((W), \
    VecFloat2D*: VecFloatDist2D, \
    default: PBErrInvalidPolymorphism), \
  VecFloat3D*: _Generic((W), \
    VecFloat3D*: VecFloatDist3D, \
    default: PBErrInvalidPolymorphism), \
  VecShort*: _Generic((W), \
    VecShort*: VecShortHamiltonDist,\
    default: PBErrInvalidPolymorphism), \
  VecShort2D*: _Generic((W), \
    VecShort2D*: VecShortHamiltonDist2D,\
    default: PBErrInvalidPolymorphism), \
  VecShort3D*: _Generic((W), \
    VecShort3D*: VecShortHamiltonDist3D,\
    default: PBErrInvalidPolymorphism), \
  VecShort4D*: _Generic((W), \
    VecShort4D*: VecShortHamiltonDist4D,\
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(V, W)

#define VecHamiltonDist(V, W) _Generic((V), \
  VecFloat*: _Generic((W), \
    VecFloat*: VecFloatHamiltonDist, \
    default: PBErrInvalidPolymorphism), \
  VecFloat2D*: _Generic((W), \
    VecFloat2D*: VecFloatHamiltonDist2D, \
    default: PBErrInvalidPolymorphism), \
  VecFloat3D*: _Generic((W), \
    VecFloat3D*: VecFloatHamiltonDist3D, \
    default: PBErrInvalidPolymorphism), \
  VecShort*: _Generic((W), \
    VecShort*: VecShortHamiltonDist,\
    default: PBErrInvalidPolymorphism), \
  VecShort2D*: _Generic((W), \
    VecShort2D*: VecShortHamiltonDist2D,\
    default: PBErrInvalidPolymorphism), \
  VecShort3D*: _Generic((W), \
    VecShort3D*: VecShortHamiltonDist3D,\
    default: PBErrInvalidPolymorphism), \
  VecShort4D*: _Generic((W), \
    VecShort4D*: VecShortHamiltonDist4D,\
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(V, W)

#define VecPixelDist(V, W) _Generic((V), \
  VecFloat*: _Generic((W), \
    VecFloat*: VecFloatPixelDist, \
    default: PBErrInvalidPolymorphism), \
  VecFloat2D*: _Generic((W), \
    VecFloat2D*: VecFloatPixelDist2D, \
    default: PBErrInvalidPolymorphism), \
  VecFloat3D*: _Generic((W), \
    VecFloat3D*: VecFloatPixelDist3D, \
    default: PBErrInvalidPolymorphism), \
  VecShort*: _Generic((W), \
    VecShort*: VecShortHamiltonDist,\
    default: PBErrInvalidPolymorphism), \
  VecShort2D*: _Generic((W), \
    VecShort2D*: VecShortHamiltonDist2D,\
    default: PBErrInvalidPolymorphism), \
  VecShort3D*: _Generic((W), \
    VecShort3D*: VecShortHamiltonDist3D,\
    default: PBErrInvalidPolymorphism), \
  VecShort4D*: _Generic((W), \
    VecShort4D*: VecShortHamiltonDist4D,\
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(V, W)

#define VecIsEqual(V, W) _Generic((V), \
  VecFloat*: _Generic((W), \
    VecFloat*: VecFloatIsEqual, \
    default: PBErrInvalidPolymorphism), \
  VecFloat2D*: _Generic((W), \
    VecFloat2D*: VecFloatIsEqual2D, \
    default: PBErrInvalidPolymorphism), \
  VecFloat3D*: _Generic((W), \
    VecFloat3D*: VecFloatIsEqual3D, \
    default: PBErrInvalidPolymorphism), \
  VecShort*: _Generic((W), \
    VecShort*: VecShortIsEqual,\
    default: PBErrInvalidPolymorphism), \
  VecShort2D*: _Generic((W), \
    VecShort2D*: VecShortIsEqual2D,\
    default: PBErrInvalidPolymorphism), \
  VecShort3D*: _Generic((W), \
    VecShort3D*: VecShortIsEqual3D,\
    default: PBErrInvalidPolymorphism), \
  VecShort4D*: _Generic((W), \
    VecShort4D*: VecShortIsEqual4D,\
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(V, W)

#define VecOp(V, A, W, B) _Generic((V), \
  VecFloat*: _Generic((W), \
    VecFloat*: VecFloatOp, \
    default: PBErrInvalidPolymorphism), \
  VecFloat2D*: _Generic((W), \
    VecFloat2D*: VecFloatOp2D, \
    default: PBErrInvalidPolymorphism), \
  VecFloat3D*: _Generic((W), \
    VecFloat3D*: VecFloatOp3D, \
    default: PBErrInvalidPolymorphism), \
  VecShort*: _Generic((W), \
    VecShort*: VecShortOp, \
    default: PBErrInvalidPolymorphism), \
  VecShort2D*: _Generic((W), \
    VecShort2D*: VecShortOp2D, \
    default: PBErrInvalidPolymorphism), \
  VecShort3D*: _Generic((W), \
    VecShort3D*: VecShortOp3D, \
    default: PBErrInvalidPolymorphism), \
  VecShort4D*: _Generic((W), \
    VecShort4D*: VecShortOp4D, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(V, A, W, B)

#define VecGetOp(V, A, W, B) _Generic((V), \
  VecFloat*: _Generic((W), \
    VecFloat*: VecFloatGetOp, \
    default: PBErrInvalidPolymorphism), \
  VecFloat2D*: _Generic((W), \
    VecFloat2D*: VecFloatGetOp2D, \
    default: PBErrInvalidPolymorphism), \
  VecFloat3D*: _Generic((W), \
    VecFloat3D*: VecFloatGetOp3D, \
    default: PBErrInvalidPolymorphism), \
  VecShort*: _Generic((W), \
    VecShort*: VecShortGetOp, \
    default: PBErrInvalidPolymorphism), \
  VecShort2D*: _Generic((W), \
    VecShort2D*: VecShortGetOp2D, \
    default: PBErrInvalidPolymorphism), \
  VecShort3D*: _Generic((W), \
    VecShort3D*: VecShortGetOp3D, \
    default: PBErrInvalidPolymorphism), \
  VecShort4D*: _Generic((W), \
    VecShort4D*: VecShortGetOp4D, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(V, A, W, B)

#define VecScale(V, A) _Generic((V), \
  VecFloat*: VecFloatScale, \
  VecFloat2D*: VecFloatScale2D, \
  VecFloat3D*: VecFloatScale3D, \
  default: PBErrInvalidPolymorphism)(V, A)

#define VecGetScale(V, A) _Generic((V), \
  VecFloat*: VecFloatGetScale, \
  VecFloat2D*: VecFloatGetScale2D, \
  VecFloat3D*: VecFloatGetScale3D, \
  default: PBErrInvalidPolymorphism)(V, A)

#define VecRot(V, A) _Generic((V), \
  VecFloat*: VecFloatRot2D, \
  VecFloat2D*: VecFloatRot2D, \
  default: PBErrInvalidPolymorphism)((VecFloat2D*)V, A)

#define VecGetRot(V, A) _Generic((V), \
  VecFloat2D*: VecFloatGetRot2D, \
  default: PBErrInvalidPolymorphism)(V, A)

#define VecDotProd(V, W) _Generic((V), \
  VecShort*: VecShortDotProd,\
  VecShort2D*: VecShortDotProd2D,\
  VecShort3D*: VecShortDotProd3D,\
  VecShort4D*: VecShortDotProd4D,\
  VecFloat*: VecFloatDotProd, \
  VecFloat2D*: VecFloatDotProd2D, \
  VecFloat3D*: VecFloatDotProd3D, \
  default: PBErrInvalidPolymorphism) (V, W) \

#define VecAngleTo(V, W) _Generic((V), \
  VecFloat*: VecFloatAngleTo2D, \
  VecFloat2D*: VecFloatAngleTo2D, \
  default: PBErrInvalidPolymorphism)((VecFloat2D*)V, (VecFloat2D*)W)

#define VecStep(V, W) _Generic((V), \
  VecShort*: VecShortStep, \
  VecShort2D*: VecShortStep, \
  VecShort3D*: VecShortStep, \
  VecShort4D*: VecShortStep, \
  default: PBErrInvalidPolymorphism)((VecShort*)V, (VecShort*)W)

#define VecPStep(V, W) _Generic((V), \
  VecShort*: VecShortPStep, \
  VecShort2D*: VecShortPStep, \
  VecShort3D*: VecShortPStep, \
  VecShort4D*: VecShortPStep, \
  default: PBErrInvalidPolymorphism)((VecShort*)V, (VecShort*)W)

#define MatClone(M) _Generic((M), \
  MatFloat*: MatFloatClone, \
  default: PBErrInvalidPolymorphism)(M)

#define MatLoad(M, S) _Generic((M), \
  MatFloat**: MatFloatLoad, \
  default: PBErrInvalidPolymorphism)(M, S)

#define MatSave(M, S) _Generic((M), \
  MatFloat*: MatFloatSave, \
  default: PBErrInvalidPolymorphism)(M, S)

#define MatFree(M) _Generic((M), \
  MatFloat**: MatFloatFree, \
  default: PBErrInvalidPolymorphism)(M)

#define MatPrintln(M, S) _Generic((M), \
  MatFloat*: MatFloatPrintlnDef, \
  default: PBErrInvalidPolymorphism)(M, S)

#define MatGet(M, I) _Generic((M), \
  MatFloat*: MatFloatGet, \
  default: PBErrInvalidPolymorphism)(M, I)

#define MatSet(M, I, VAL) _Generic((M), \
  MatFloat*: MatFloatSet, \
  default: PBErrInvalidPolymorphism)(M, I, VAL)

#define MatCopy(M, W) _Generic((M), \
  MatFloat*: _Generic ((W), \
    MatFloat*: MatFloatCopy, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(M, W)

#define MatDim(M) _Generic((M), \
  MatFloat*: MatFloatDim, \
  default: PBErrInvalidPolymorphism)(M)

#define MatInv(M) _Generic((M), \
  MatFloat*: MatFloatInv, \
  default: PBErrInvalidPolymorphism)(M)

#define MatProdMat(A, B) _Generic(A, \
  MatFloat*: _Generic(B, \
    MatFloat*: MatFloatProdMatFloat, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)((A), (B))

#define MatProdVec(A, B) _Generic(A, \
  MatFloat*: _Generic(B, \
    VecFloat*: MatFloatProdVecFloat, \
    VecFloat2D*: MatFloatProdVecFloat, \
    VecFloat3D*: MatFloatProdVecFloat, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)((A), (VecFloat*)(B))

#define MatSetIdentity(M) _Generic((M), \
  MatFloat*: MatFloatSetIdentity, \
  default: PBErrInvalidPolymorphism)(M)

#define MatIsEqual(A, B) _Generic(A, \
  MatFloat*: _Generic(B, \
    MatFloat*: MatFloatIsEqual, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)((A), (B))

#define SysLinEqCreate(M, V) _Generic((V), \
  VecFloat*: SLECreate, \
  VecFloat2D*: SLECreate, \
  VecFloat3D*: SLECreate, \
  default: PBErrInvalidPolymorphism)(M, (VecFloat*)V)

#define SysLinEqSetV(S, V) _Generic((V), \
  VecFloat*: SLESetV, \
  VecFloat2D*: SLESetV, \
  VecFloat3D*: SLESetV, \
  default: PBErrInvalidPolymorphism)(S, (VecFloat*)V)

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
VecShort* VecShortCreate(int dim);

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
VecShort* VecShortClone(VecShort *that);

// Load the VecShort from the stream
// If the VecShort is already allocated, it is freed before loading
// Return true in case of success, else false
bool VecShortLoad(VecShort **that, FILE *stream);

// Save the VecShort to the stream
// Return true in case of success, else false
bool VecShortSave(VecShort *that, FILE *stream);

// Free the memory used by a VecShort
// Do nothing if arguments are invalid
void VecShortFree(VecShort **that);

// Print the VecShort on 'stream'
void VecShortPrint(VecShort *that, FILE *stream);

// Return the i-th value of the VecShort
#if BUILDMODE != 0 
inline 
#endif 
short VecShortGet(VecShort *that, int i);
#if BUILDMODE != 0 
inline 
#endif 
short VecShortGet2D(VecShort2D *that, int i);
#if BUILDMODE != 0 
inline 
#endif 
short VecShortGet3D(VecShort3D *that, int i);
#if BUILDMODE != 0 
inline 
#endif 
short VecShortGet4D(VecShort4D *that, int i);

// Set the i-th value of the VecShort to v
#if BUILDMODE != 0 
inline 
#endif 
void VecShortSet(VecShort *that, int i, short v);
#if BUILDMODE != 0 
inline 
#endif 
void VecShortSet2D(VecShort2D *that, int i, short v);
#if BUILDMODE != 0 
inline 
#endif 
void VecShortSet3D(VecShort3D *that, int i, short v);
#if BUILDMODE != 0 
inline 
#endif 
void VecShortSet4D(VecShort4D *that, int i, short v);

// Return the dimension of the VecShort
// Return 0 if arguments are invalid
#if BUILDMODE != 0 
inline 
#endif 
int VecShortDim(VecShort *that);

// Return the Hamiltonian distance between the VecShort 'that' and 'tho'
#if BUILDMODE != 0 
inline 
#endif 
short VecShortHamiltonDist(VecShort *that, VecShort *tho);
#if BUILDMODE != 0 
inline 
#endif 
short VecShortHamiltonDist2D(VecShort2D *that, VecShort2D *tho);
#if BUILDMODE != 0 
inline 
#endif 
short VecShortHamiltonDist3D(VecShort3D *that, VecShort3D *tho);
#if BUILDMODE != 0 
inline 
#endif 
short VecShortHamiltonDist4D(VecShort4D *that, VecShort4D *tho);

// Return true if the VecShort 'that' is equal to 'tho', else false
#if BUILDMODE != 0 
inline 
#endif 
bool VecShortIsEqual(VecShort *that, VecShort *tho);
#if BUILDMODE != 0 
inline 
#endif 
bool VecShortIsEqual2D(VecShort2D *that, VecShort2D *tho);
#if BUILDMODE != 0 
inline 
#endif 
bool VecShortIsEqual3D(VecShort3D *that, VecShort3D *tho);
#if BUILDMODE != 0 
inline 
#endif 
bool VecShortIsEqual4D(VecShort4D *that, VecShort4D *tho);

// Copy the values of 'w' in 'that' (must have same dimensions)
#if BUILDMODE != 0 
inline 
#endif 
void VecShortCopy(VecShort *that, VecShort *w);

// Return the dot product of 'that' and 'tho'
#if BUILDMODE != 0 
inline 
#endif 
short VecShortDotProd(VecShort *that, VecShort *tho);
#if BUILDMODE != 0 
inline 
#endif 
short VecShortDotProd2D(VecShort2D *that, VecShort2D *tho);
#if BUILDMODE != 0 
inline 
#endif 
short VecShortDotProd3D(VecShort3D *that, VecShort3D *tho);
#if BUILDMODE != 0 
inline 
#endif 
short VecShortDotProd4D(VecShort4D *that, VecShort4D *tho);

// Set all values of the vector 'that' to 0
#if BUILDMODE != 0 
inline 
#endif 
void VecShortSetNull(VecShort *that);
#if BUILDMODE != 0 
inline 
#endif 
void VecShortSetNull2D(VecShort2D *that);
#if BUILDMODE != 0 
inline 
#endif 
void VecShortSetNull3D(VecShort3D *that);
#if BUILDMODE != 0 
inline 
#endif 
void VecShortSetNull4D(VecShort4D *that);

// Step the values of the vector incrementally by 1 from 0
// in the following order (for example) : 
// (0,0,0)->(0,0,1)->(0,0,2)->(0,1,0)->(0,1,1)->...
// The upper limit for each value is given by 'bound' (val[i] < dim[i])
// Return false if all values of 'that' have reached their upper limit 
// (in which case 'that''s values are all set back to 0)
// Return true else
bool VecShortStep(VecShort *that, VecShort *bound);

// Step the values of the vector incrementally by 1 from 0
// in the following order (for example) : 
// (0,0,0)->(1,0,0)->(2,0,0)->(0,1,0)->(1,1,0)->...
// The upper limit for each value is given by 'bound' (val[i] < dim[i])
// Return false if all values of 'that' have reached their upper limit 
// (in which case 'that''s values are all set back to 0)
// Return true else
bool VecShortPStep(VecShort *that, VecShort *bound);

// Calculate (that * a + tho * b) and store the result in 'that'
// 'tho' can be null, in which case it is consider to be the null vector
// If 'tho' is not null it must be of same dimension as 'that'
#if BUILDMODE != 0 
inline 
#endif 
void VecShortOp(VecShort *that, short a, VecShort *tho, short b);
#if BUILDMODE != 0 
inline 
#endif 
void VecShortOp2D(VecShort2D *that, short a, VecShort2D *tho, short b);
#if BUILDMODE != 0 
inline 
#endif 
void VecShortOp3D(VecShort3D *that, short a, VecShort3D *tho, short b);
#if BUILDMODE != 0 
inline 
#endif 
void VecShortOp4D(VecShort4D *that, short a, VecShort4D *tho, short b);

// Return a VecShort equal to (that * a + tho * b)
// Return NULL if arguments are invalid
// 'tho' can be null, in which case it is consider to be the null vector
// If 'tho' is not null it must be of same dimension as 'that'
#if BUILDMODE != 0 
inline 
#endif 
VecShort* VecShortGetOp(VecShort *that, short a, 
  VecShort *tho, short b);
#if BUILDMODE != 0 
inline 
#endif 
VecShort2D VecShortGetOp2D(VecShort2D *that, short a, 
  VecShort2D *tho, short b);
#if BUILDMODE != 0 
inline 
#endif 
VecShort3D VecShortGetOp3D(VecShort3D *that, short a, 
  VecShort3D *tho, short b);
#if BUILDMODE != 0 
inline 
#endif 
VecShort4D VecShortGetOp4D(VecShort4D *that, short a, 
  VecShort4D *tho, short b);

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
VecFloat* VecFloatCreate(int dim);

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
VecFloat* VecFloatClone(VecFloat *that);

// Load the VecFloat from the stream
// If the VecFloat is already allocated, it is freed before loading
// Return true in case of success, else false
bool VecFloatLoad(VecFloat **that, FILE *stream);

// Save the VecFloat to the stream
// Return true in case of success, else false
bool VecFloatSave(VecFloat *that, FILE *stream);

// Free the memory used by a VecFloat
// Do nothing if arguments are invalid
void VecFloatFree(VecFloat **that);

// Print the VecFloat on 'stream' with 'prec' digit precision
// Do nothing if arguments are invalid
void VecFloatPrint(VecFloat *that, FILE *stream, unsigned int prec);
inline void VecFloatPrintDef(VecFloat *that, FILE *stream) {
  VecFloatPrint(that, stream, 3);
}

// Return the 'i'-th value of the VecFloat
#if BUILDMODE != 0 
inline 
#endif 
float VecFloatGet(VecFloat *that, int i);
#if BUILDMODE != 0 
inline 
#endif 
float VecFloatGet2D(VecFloat2D *that, int i);
#if BUILDMODE != 0 
inline 
#endif 
float VecFloatGet3D(VecFloat3D *that, int i);

// Set the 'i'-th value of the VecFloat to 'v'
#if BUILDMODE != 0 
inline 
#endif 
void VecFloatSet(VecFloat *that, int i, float v);
#if BUILDMODE != 0
inline
#endif 
void VecFloatSet2D(VecFloat2D *that, int i, float v);
#if BUILDMODE != 0
inline
#endif 
void VecFloatSet3D(VecFloat3D *that, int i, float v);

// Set all values of the vector 'that' to 0
#if BUILDMODE != 0 
inline 
#endif 
void VecFloatSetNull(VecFloat *that);
#if BUILDMODE != 0 
inline 
#endif 
void VecFloatSetNull2D(VecFloat2D *that);
#if BUILDMODE != 0 
inline 
#endif 
void VecFloatSetNull3D(VecFloat3D *that);

// Return the dimension of the VecFloat
// Return 0 if arguments are invalid
#if BUILDMODE != 0 
inline 
#endif 
int VecFloatDim(VecFloat *that);

// Copy the values of 'w' in 'that' (must have same dimensions)
// Do nothing if arguments are invalid
#if BUILDMODE != 0 
inline 
#endif 
void VecFloatCopy(VecFloat *that, VecFloat *w);

// Return the norm of the VecFloat
// Return 0.0 if arguments are invalid
#if BUILDMODE != 0 
inline 
#endif 
float VecFloatNorm(VecFloat *that);
#if BUILDMODE != 0 
inline 
#endif 
float VecFloatNorm2D(VecFloat2D *that);
#if BUILDMODE != 0 
inline 
#endif 
float VecFloatNorm3D(VecFloat3D *that);

// Normalise the VecFloat
#if BUILDMODE != 0 
inline 
#endif 
void VecFloatNormalise(VecFloat *that);
#if BUILDMODE != 0 
inline 
#endif 
void VecFloatNormalise2D(VecFloat2D *that);
#if BUILDMODE != 0 
inline 
#endif 
void VecFloatNormalise3D(VecFloat3D *that);

// Return the distance between the VecFloat 'that' and 'tho'
#if BUILDMODE != 0 
inline 
#endif 
float VecFloatDist(VecFloat *that, VecFloat *tho);
#if BUILDMODE != 0 
inline 
#endif 
float VecFloatDist2D(VecFloat2D *that, VecFloat2D *tho);
#if BUILDMODE != 0 
inline 
#endif 
float VecFloatDist3D(VecFloat3D *that, VecFloat3D *tho);

// Return the Hamiltonian distance between the VecFloat 'that' and 'tho'
#if BUILDMODE != 0 
inline 
#endif 
float VecFloatHamiltonDist(VecFloat *that, VecFloat *tho);
#if BUILDMODE != 0 
inline 
#endif 
float VecFloatHamiltonDist2D(VecFloat2D *that, VecFloat2D *tho);
#if BUILDMODE != 0 
inline 
#endif 
float VecFloatHamiltonDist3D(VecFloat3D *that, VecFloat3D *tho);

// Return the Pixel distance between the VecFloat 'that' and 'tho'
#if BUILDMODE != 0 
inline 
#endif 
float VecFloatPixelDist(VecFloat *that, VecFloat *tho);
#if BUILDMODE != 0 
inline 
#endif 
float VecFloatPixelDist2D(VecFloat2D *that, VecFloat2D *tho);
#if BUILDMODE != 0 
inline 
#endif 
float VecFloatPixelDist3D(VecFloat3D *that, VecFloat3D *tho);

// Return true if the VecFloat 'that' is equal to 'tho', else false
#if BUILDMODE != 0 
inline 
#endif 
bool VecFloatIsEqual(VecFloat *that, VecFloat *tho);
#if BUILDMODE != 0 
inline 
#endif 
bool VecFloatIsEqual2D(VecFloat2D *that, VecFloat2D *tho);
#if BUILDMODE != 0 
inline 
#endif 
bool VecFloatIsEqual3D(VecFloat3D *that, VecFloat3D *tho);

// Calculate (that * a) and store the result in 'that'
#if BUILDMODE != 0 
inline 
#endif 
void VecFloatScale(VecFloat *that, float a);
#if BUILDMODE != 0 
inline 
#endif 
void VecFloatScale2D(VecFloat2D *that, float a);
#if BUILDMODE != 0 
inline 
#endif 
void VecFloatScale3D(VecFloat3D *that, float a);

// Return a VecFloat equal to (that * a)
#if BUILDMODE != 0 
inline 
#endif 
VecFloat* VecFloatGetScale(VecFloat *that, float a);
#if BUILDMODE != 0 
inline 
#endif 
VecFloat2D VecFloatGetScale2D(VecFloat2D *that, float a);
#if BUILDMODE != 0 
inline 
#endif 
VecFloat3D VecFloatGetScale3D(VecFloat3D *that, float a);

// Calculate (that * a + tho * b) and store the result in 'that'
// 'tho' can be null, in which case it is consider to be the null vector
// If 'tho' is not null it must be of same dimension as 'that'
#if BUILDMODE != 0 
inline 
#endif 
void VecFloatOp(VecFloat *that, float a, VecFloat *tho, float b);
#if BUILDMODE != 0 
inline 
#endif 
void VecFloatOp2D(VecFloat2D *that, float a, VecFloat2D *tho, float b);
#if BUILDMODE != 0 
inline 
#endif 
void VecFloatOp3D(VecFloat3D *that, float a, VecFloat3D *tho, float b);

// Return a VecFloat equal to (that * a + tho * b)
// Return NULL if arguments are invalid
// 'tho' can be null, in which case it is consider to be the null vector
// If 'tho' is not null it must be of same dimension as 'that'
#if BUILDMODE != 0 
inline 
#endif 
VecFloat* VecFloatGetOp(VecFloat *that, float a, 
  VecFloat *tho, float b);
#if BUILDMODE != 0 
inline 
#endif 
VecFloat2D VecFloatGetOp2D(VecFloat2D *that, float a, 
  VecFloat2D *tho, float b);
#if BUILDMODE != 0 
inline 
#endif 
VecFloat3D VecFloatGetOp3D(VecFloat3D *that, float a, 
  VecFloat3D *tho, float b);

// Rotate CCW 'that' by 'theta' radians and store the result in 'that'
#if BUILDMODE != 0 
inline 
#endif 
void VecFloatRot2D(VecFloat2D *that, float theta);

// Return a VecFloat equal to 'that' rotated CCW by 'theta' radians
#if BUILDMODE != 0 
inline 
#endif 
VecFloat2D VecFloatGetRot2D(VecFloat2D *that, float theta);

// Return the dot product of 'that' and 'tho'
#if BUILDMODE != 0 
inline 
#endif 
float VecFloatDotProd(VecFloat *that, VecFloat *tho);
#if BUILDMODE != 0 
inline 
#endif 
float VecFloatDotProd2D(VecFloat2D *that, VecFloat2D *tho);
#if BUILDMODE != 0 
inline 
#endif 
float VecFloatDotProd3D(VecFloat3D *that, VecFloat3D *tho);

// Return the angle of the rotation making 'that' colinear to 'tho'
// 'that' and 'tho' must be normalised
// Return a value in [-PI,PI]
float VecFloatAngleTo2D(VecFloat2D *that, VecFloat2D *tho);

// Return the conversion of VecFloat 'that' to a VecShort using round()
#if BUILDMODE != 0 
inline 
#endif 
VecShort* VecFloatToShort(VecFloat *that);
#if BUILDMODE != 0 
inline 
#endif 
VecShort2D VecFloatToShort2D(VecFloat2D *that);
#if BUILDMODE != 0 
inline 
#endif 
VecShort3D VecFloatToShort3D(VecFloat3D *that);

// Return the conversion of VecShort 'that' to a VecFloat
#if BUILDMODE != 0 
inline 
#endif 
VecFloat* VecShortToFloat(VecShort *that);
#if BUILDMODE != 0 
inline 
#endif 
VecFloat2D VecShortToFloat2D(VecShort2D *that);
#if BUILDMODE != 0 
inline 
#endif 
VecFloat3D VecShortToFloat3D(VecShort3D *that);

// -------------- MatFloat

// ================= Data structure ===================

// Vector of float values
typedef struct MatFloat {
  // Dimension
  VecShort2D _dim;
  // Values (memorized by columns)
  float _val[0];
} MatFloat;

// ================ Functions declaration ====================

// Create a new MatFloat of dimension 'dim' (nbCol, nbLine)
// Values are initalized to 0.0
MatFloat* MatFloatCreate(VecShort2D *dim);

// Set the MatFloat to the identity matrix
// The matrix must be a square matrix
#if BUILDMODE != 0 
inline 
#endif 
void MatFloatSetIdentity(MatFloat *that);

// Clone the MatFloat
MatFloat* MatFloatClone(MatFloat *that);

// Copy the values of 'w' in 'that' (must have same dimensions)
#if BUILDMODE != 0 
inline 
#endif 
void MatFloatCopy(MatFloat *that, MatFloat *w);

// Load the MatFloat from the stream
// If the MatFloat is already allocated, it is freed before loading
// Return true upon success, else false
bool MatFloatLoad(MatFloat **that, FILE *stream);

// Save the MatFloat to the stream
// Return true upon success, else false
bool MatFloatSave(MatFloat *that, FILE *stream);

// Free the memory used by a MatFloat
// Do nothing if arguments are invalid
void MatFloatFree(MatFloat **that);

// Print the MatFloat on 'stream' with 'prec' digit precision
// Do nothing if arguments are invalid
void MatFloatPrintln(MatFloat *that, FILE *stream, unsigned int prec);
inline void MatFloatPrintlnDef(MatFloat *that, FILE *stream) {
  MatFloatPrintln(that, stream, 3);
}

// Return the value at index (col, line) of the MatFloat
// Index starts at 0, index in matrix = line * nbCol + col
#if BUILDMODE != 0 
inline 
#endif 
float MatFloatGet(MatFloat *that, VecShort2D *index);

// Set the value at index (col, line) of the MatFloat to 'v'
// Index starts at 0, index in matrix = line * nbCol + col
#if BUILDMODE != 0 
inline 
#endif 
void MatFloatSet(MatFloat *that, VecShort2D *index, float v);

// Return a VecShort2D containing the dimension of the MatFloat
#if BUILDMODE != 0 
inline 
#endif 
VecShort2D MatFloatDim(MatFloat *that);

// Return the inverse matrix of 'that'
// The matrix must be a square matrix
MatFloat* MatFloatInv(MatFloat *that);

// Return the product of matrix 'that' and vector 'v'
// Number of columns of 'that' must equal dimension of 'v'
VecFloat* MatFloatProdVecFloat(MatFloat *that, VecFloat *v);

// Return the product of matrix 'that' by matrix 'tho'
// Number of columns of 'that' must equal number of line of 'tho'
MatFloat* MatFloatProdMatFloat(MatFloat *that, MatFloat *tho);

// Return true if 'that' is equal to 'tho', false else
bool MatFloatIsEqual(MatFloat *that, MatFloat *tho);

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
Gauss GaussCreateStatic(float mean, float sigma);

// Free the memory used by a Gauss
// Do nothing if arguments are invalid
void GaussFree(Gauss **that);

// Return the value of the Gauss 'that' at 'x'
#if BUILDMODE != 0 
inline 
#endif 
float GaussGet(Gauss *that, float x);

// Return a random value according to the Gauss 'that'
// random() must have been called before calling this function
#if BUILDMODE != 0 
inline 
#endif 
float GaussRnd(Gauss *that);

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
float SmoothStep(float x);

// Return the order 2 smooth value of 'x'
// if x < 0.0 return 0.0
// if x > 1.0 return 1.0
#if BUILDMODE != 0 
inline 
#endif 
float SmootherStep(float x);

// -------------- Conversion functions

// ================ Functions declaration ====================

// Convert radians to degrees
inline float ConvRad2Deg(float rad) {
  return rad / PBMATH_TWOPI_DIV_360;
}

// Convert degrees to radians
inline float ConvDeg2Rad(float deg) {
  return PBMATH_TWOPI_DIV_360 * deg;
}

// -------------- SysLinEq

// ================= Data structure ===================

// Linear system of equalities
typedef struct SysLinEq {
  // Matrix
  MatFloat *_M;
  // Inverse of the matrix
  MatFloat *_Minv;
  // Vector
  VecFloat *_V;
} SysLinEq;

// ================ Functions declaration ====================

// Create a new SysLinEq with matrix 'm' and vector 'v'
// The dimension of 'v' must be equal to the number of column of 'm'
// If 'v' is null the vector null is used instead
// The matrix 'm' must be a square matrix
// Return NULL if we couldn't create the SysLinEq
SysLinEq* SLECreate(MatFloat *m, VecFloat *v);

// Free the memory used by the SysLinEq
// Do nothing if arguments are invalid
void SysLinEqFree(SysLinEq **that);

// Clone the SysLinEq 'that'
// Return NULL if we couldn't clone the SysLinEq
SysLinEq* SysLinEqClone(SysLinEq * that);

// Solve the SysLinEq _M.x = _V
// Return the solution vector, or null if there is no solution or the 
// arguments are invalid
#if BUILDMODE != 0 
inline 
#endif 
VecFloat* SysLinEqSolve(SysLinEq *that);

// Set the matrix of the SysLinEq to a clone of 'm'
// Do nothing if arguments are invalid
#if BUILDMODE != 0 
inline 
#endif 
void SysLinEqSetM(SysLinEq *that, MatFloat *m);

// Set the vector of the SysLinEq to a clone of 'v'
// Do nothing if arguments are invalid
#if BUILDMODE != 0 
inline 
#endif 
void SLESetV(SysLinEq *that, VecFloat *v);

// -------------- Usefull basic functions

// ================ Functions declaration ====================

// Return x^y when x and y are int
// to avoid numerical imprecision from (pow(double,double)
// From https://stackoverflow.com/questions/29787310/
// does-pow-work-for-int-data-type-in-c
#if BUILDMODE != 0 
inline 
#endif 
int powi(int base, int exp);

// Compute a^n, faster than std::pow for n<~100
inline float fastpow(float a, int n) {
  double ret = 1.0;
  for (; n--;) ret *= (double)a;
  return (float)ret;
}

// Compute a^2
inline float fsquare(float a) {
  return a * a;
}

// ================ Inliner ====================

#if BUILDMODE != 0
#include "pbmath-inline.c"
#endif


#endif
