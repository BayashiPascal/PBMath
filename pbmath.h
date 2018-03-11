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

// ================= Polymorphism ==================

#define VecClone(Vec) _Generic(Vec, \
  VecFloat*: _VecFloatClone, \
  VecShort*: _VecShortClone, \
  default: PBErrInvalidPolymorphism)(Vec)

#define VecLoad(VecRef, Stream) _Generic(VecRef, \
  VecFloat**: _VecFloatLoad, \
  VecShort**: _VecShortLoad, \
  default: PBErrInvalidPolymorphism)(VecRef, Stream)

#define VecSave(Vec, Stream) _Generic(Vec, \
  VecFloat*: _VecFloatSave, \
  VecFloat2D*: _VecFloatSave, \
  VecFloat3D*: _VecFloatSave, \
  VecShort*: _VecShortSave, \
  VecShort2D*: _VecShortSave, \
  VecShort3D*: _VecShortSave, \
  VecShort4D*: _VecShortSave, \
  default: PBErrInvalidPolymorphism)( \
    _Generic(Vec,  \
      VecFloat2D*: (VecFloat*)(Vec), \
      VecFloat3D*: (VecFloat*)(Vec), \
      VecShort2D*: (VecShort*)(Vec), \
      VecShort3D*: (VecShort*)(Vec), \
      VecShort4D*: (VecShort*)(Vec), \
      default: Vec),  \
    Stream)

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
  default: PBErrInvalidPolymorphism)( \
    _Generic(Vec,  \
      VecFloat2D*: (VecFloat*)(Vec), \
      VecFloat3D*: (VecFloat*)(Vec), \
      VecShort2D*: (VecShort*)(Vec), \
      VecShort3D*: (VecShort*)(Vec), \
      VecShort4D*: (VecShort*)(Vec), \
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
    default: PBErrInvalidPolymorphism), \
  VecFloat2D*: _Generic(VecSrc, \
    VecFloat*: _VecFloatCopy, \
    VecFloat2D*: _VecFloatCopy, \
    default: PBErrInvalidPolymorphism), \
  VecFloat3D*: _Generic(VecSrc, \
    VecFloat*: _VecFloatCopy, \
    VecFloat3D*: _VecFloatCopy, \
    default: PBErrInvalidPolymorphism), \
  VecShort*: _Generic(VecSrc, \
    VecShort*: _VecShortCopy, \
    VecShort2D*: _VecShortCopy, \
    VecShort3D*: _VecShortCopy, \
    VecShort4D*: _VecShortCopy, \
    default: PBErrInvalidPolymorphism), \
  VecShort2D*: _Generic(VecSrc, \
    VecShort*: _VecShortCopy, \
    VecShort2D*: _VecShortCopy, \
    default: PBErrInvalidPolymorphism), \
  VecShort3D*: _Generic(VecSrc, \
    VecShort*: _VecShortCopy, \
    VecShort3D*: _VecShortCopy, \
    default: PBErrInvalidPolymorphism), \
  VecShort4D*: _Generic(VecSrc, \
    VecShort*: _VecShortCopy, \
    VecShort4D*: _VecShortCopy, \
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
      VecFloat2D*: (VecFloat*)(VecSrc), \
      VecFloat3D*: (VecFloat*)(VecSrc), \
      VecShort2D*: (VecShort*)(VecSrc), \
      VecShort3D*: (VecShort*)(VecSrc), \
      VecShort4D*: (VecShort*)(VecSrc), \
      default: VecSrc))

#define VecGetDim(Vec) _Generic(Vec, \
  VecFloat*: _VecFloatGetDim, \
  VecFloat2D*: _VecFloatGetDim, \
  VecFloat3D*: _VecFloatGetDim, \
  VecShort*: _VecShortGetDim, \
  VecShort2D*: _VecShortGetDim, \
  VecShort3D*: _VecShortGetDim, \
  VecShort4D*: _VecShortGetDim, \
  default: PBErrInvalidPolymorphism)( \
    _Generic(Vec, \
      VecFloat*: Vec, \
      VecFloat2D*: (VecFloat*)(Vec), \
      VecFloat3D*: (VecFloat*)(Vec), \
      VecShort*: Vec, \
      VecShort2D*: (VecShort*)(Vec), \
      VecShort3D*: (VecShort*)(Vec), \
      VecShort4D*: (VecShort*)(Vec), \
      default: Vec))

#define VecGetNewDim(Vec, Dim) _Generic(Vec, \
  VecFloat*: _VecFloatGetNewDim, \
  default: PBErrInvalidPolymorphism)( \
    _Generic(Vec, \
      VecFloat*: Vec, \
      default: Vec), Dim)

#define VecNorm(Vec) _Generic(Vec, \
  VecFloat*: _VecFloatNorm, \
  VecFloat2D*: _VecFloatNorm2D, \
  VecFloat3D*: _VecFloatNorm3D, \
  default: PBErrInvalidPolymorphism)(Vec)

#define VecNormalise(Vec) _Generic(Vec, \
  VecFloat*: _VecFloatNormalise, \
  VecFloat2D*: _VecFloatNormalise2D, \
  VecFloat3D*: _VecFloatNormalise3D, \
  default: PBErrInvalidPolymorphism)(Vec)

#define VecDist(VecA, VecB) _Generic(VecA, \
  VecFloat*: _Generic(VecB, \
    VecFloat*: _VecFloatDist, \
    default: PBErrInvalidPolymorphism), \
  VecFloat2D*: _Generic(VecB, \
    VecFloat2D*: _VecFloatDist2D, \
    default: PBErrInvalidPolymorphism), \
  VecFloat3D*: _Generic(VecB, \
    VecFloat3D*: _VecFloatDist3D, \
    default: PBErrInvalidPolymorphism), \
  VecShort*: _Generic(VecB, \
    VecShort*: _VecShortHamiltonDist,\
    default: PBErrInvalidPolymorphism), \
  VecShort2D*: _Generic(VecB, \
    VecShort2D*: _VecShortHamiltonDist2D,\
    default: PBErrInvalidPolymorphism), \
  VecShort3D*: _Generic(VecB, \
    VecShort3D*: _VecShortHamiltonDist3D,\
    default: PBErrInvalidPolymorphism), \
  VecShort4D*: _Generic(VecB, \
    VecShort4D*: _VecShortHamiltonDist4D,\
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(VecA, VecB)

#define VecHamiltonDist(VecA, VecB) _Generic(VecA, \
  VecFloat*: _Generic(VecB, \
    VecFloat*: _VecFloatHamiltonDist, \
    default: PBErrInvalidPolymorphism), \
  VecFloat2D*: _Generic(VecB, \
    VecFloat2D*: _VecFloatHamiltonDist2D, \
    default: PBErrInvalidPolymorphism), \
  VecFloat3D*: _Generic(VecB, \
    VecFloat3D*: _VecFloatHamiltonDist3D, \
    default: PBErrInvalidPolymorphism), \
  VecShort*: _Generic(VecB, \
    VecShort*: _VecShortHamiltonDist,\
    default: PBErrInvalidPolymorphism), \
  VecShort2D*: _Generic(VecB, \
    VecShort2D*: _VecShortHamiltonDist2D,\
    default: PBErrInvalidPolymorphism), \
  VecShort3D*: _Generic(VecB, \
    VecShort3D*: _VecShortHamiltonDist3D,\
    default: PBErrInvalidPolymorphism), \
  VecShort4D*: _Generic(VecB, \
    VecShort4D*: _VecShortHamiltonDist4D,\
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(VecA, VecB)

#define VecPixelDist(VecA, VecB) _Generic(VecA, \
  VecFloat*: _Generic(VecB, \
    VecFloat*: _VecFloatPixelDist, \
    default: PBErrInvalidPolymorphism), \
  VecFloat2D*: _Generic(VecB, \
    VecFloat2D*: _VecFloatPixelDist2D, \
    default: PBErrInvalidPolymorphism), \
  VecFloat3D*: _Generic(VecB, \
    VecFloat3D*: _VecFloatPixelDist3D, \
    default: PBErrInvalidPolymorphism), \
  VecShort*: _Generic(VecB, \
    VecShort*: _VecShortHamiltonDist,\
    default: PBErrInvalidPolymorphism), \
  VecShort2D*: _Generic(VecB, \
    VecShort2D*: _VecShortHamiltonDist2D,\
    default: PBErrInvalidPolymorphism), \
  VecShort3D*: _Generic(VecB, \
    VecShort3D*: _VecShortHamiltonDist3D,\
    default: PBErrInvalidPolymorphism), \
  VecShort4D*: _Generic(VecB, \
    VecShort4D*: _VecShortHamiltonDist4D,\
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(VecA, VecB)

#define VecIsEqual(VecA, VecB) _Generic(VecA, \
  VecFloat*: _Generic(VecB, \
    VecFloat*: _VecFloatIsEqual, \
    VecFloat2D*: _VecFloatIsEqual, \
    VecFloat3D*: _VecFloatIsEqual, \
    default: PBErrInvalidPolymorphism), \
  VecFloat2D*: _Generic(VecB, \
    VecFloat*: _VecFloatIsEqual, \
    VecFloat2D*: _VecFloatIsEqual, \
    default: PBErrInvalidPolymorphism), \
  VecFloat3D*: _Generic(VecB, \
    VecFloat*: _VecFloatIsEqual, \
    VecFloat3D*: _VecFloatIsEqual, \
    default: PBErrInvalidPolymorphism), \
  VecShort*: _Generic(VecB, \
    VecShort*: _VecShortIsEqual,\
    VecShort2D*: _VecShortIsEqual,\
    VecShort3D*: _VecShortIsEqual,\
    VecShort4D*: _VecShortIsEqual,\
    default: PBErrInvalidPolymorphism), \
  VecShort2D*: _Generic(VecB, \
    VecShort*: _VecShortIsEqual,\
    VecShort2D*: _VecShortIsEqual,\
    default: PBErrInvalidPolymorphism), \
  VecShort3D*: _Generic(VecB, \
    VecShort*: _VecShortIsEqual,\
    VecShort3D*: _VecShortIsEqual,\
    default: PBErrInvalidPolymorphism), \
  VecShort4D*: _Generic(VecB, \
    VecShort*: _VecShortIsEqual,\
    VecShort4D*: _VecShortIsEqual,\
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)( \
    _Generic(VecA,  \
      VecFloat2D*: (VecFloat*)(VecA), \
      VecFloat3D*: (VecFloat*)(VecA), \
      VecShort2D*: (VecShort*)(VecA), \
      VecShort3D*: (VecShort*)(VecA), \
      VecShort4D*: (VecShort*)(VecA), \
      default: VecA),  \
    _Generic(VecB,  \
      VecFloat2D*: (VecFloat*)(VecB), \
      VecFloat3D*: (VecFloat*)(VecB), \
      VecShort2D*: (VecShort*)(VecB), \
      VecShort3D*: (VecShort*)(VecB), \
      VecShort4D*: (VecShort*)(VecB), \
      default: VecB))

#define VecOp(VecA, CoeffA, VecB, CoeffB) _Generic(VecA, \
  VecFloat*: _Generic(VecB, \
    VecFloat*: _VecFloatOp, \
    default: PBErrInvalidPolymorphism), \
  VecFloat2D*: _Generic(VecB, \
    VecFloat2D*: _VecFloatOp2D, \
    default: PBErrInvalidPolymorphism), \
  VecFloat3D*: _Generic(VecB, \
    VecFloat3D*: _VecFloatOp3D, \
    default: PBErrInvalidPolymorphism), \
  VecShort*: _Generic(VecB, \
    VecShort*: _VecShortOp, \
    default: PBErrInvalidPolymorphism), \
  VecShort2D*: _Generic(VecB, \
    VecShort2D*: _VecShortOp2D, \
    default: PBErrInvalidPolymorphism), \
  VecShort3D*: _Generic(VecB, \
    VecShort3D*: _VecShortOp3D, \
    default: PBErrInvalidPolymorphism), \
  VecShort4D*: _Generic(VecB, \
    VecShort4D*: _VecShortOp4D, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(VecA, CoeffA, VecB, CoeffB)

#define VecGetOp(VecA, CoeffA, VecB, CoeffB) _Generic(VecA, \
  VecFloat*: _Generic(VecB, \
    VecFloat*: _VecFloatGetOp, \
    default: PBErrInvalidPolymorphism), \
  VecFloat2D*: _Generic(VecB, \
    VecFloat2D*: _VecFloatGetOp2D, \
    default: PBErrInvalidPolymorphism), \
  VecFloat3D*: _Generic(VecB, \
    VecFloat3D*: _VecFloatGetOp3D, \
    default: PBErrInvalidPolymorphism), \
  VecShort*: _Generic(VecB, \
    VecShort*: _VecShortGetOp, \
    default: PBErrInvalidPolymorphism), \
  VecShort2D*: _Generic(VecB, \
    VecShort2D*: _VecShortGetOp2D, \
    default: PBErrInvalidPolymorphism), \
  VecShort3D*: _Generic(VecB, \
    VecShort3D*: _VecShortGetOp3D, \
    default: PBErrInvalidPolymorphism), \
  VecShort4D*: _Generic(VecB, \
    VecShort4D*: _VecShortGetOp4D, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(VecA, CoeffA, VecB, CoeffB)

#define VecHadamardProd(VecA, VecB) _Generic(VecA, \
  VecFloat*: _Generic(VecB, \
    VecFloat*: _VecFloatHadamardProd, \
    default: PBErrInvalidPolymorphism), \
  VecFloat2D*: _Generic(VecB, \
    VecFloat2D*: _VecFloatHadamardProd2D, \
    default: PBErrInvalidPolymorphism), \
  VecFloat3D*: _Generic(VecB, \
    VecFloat3D*: _VecFloatHadamardProd3D, \
    default: PBErrInvalidPolymorphism), \
  VecShort*: _Generic(VecB, \
    VecShort*: _VecShortHadamardProd, \
    default: PBErrInvalidPolymorphism), \
  VecShort2D*: _Generic(VecB, \
    VecShort2D*: _VecShortHadamardProd2D, \
    default: PBErrInvalidPolymorphism), \
  VecShort3D*: _Generic(VecB, \
    VecShort3D*: _VecShortHadamardProd3D, \
    default: PBErrInvalidPolymorphism), \
  VecShort4D*: _Generic(VecB, \
    VecShort4D*: _VecShortHadamardProd4D, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(VecA, VecB)

#define VecGetHadamardProd(VecA, VecB) _Generic(VecA, \
  VecFloat*: _Generic(VecB, \
    VecFloat*: _VecFloatGetHadamardProd, \
    default: PBErrInvalidPolymorphism), \
  VecFloat2D*: _Generic(VecB, \
    VecFloat2D*: _VecFloatGetHadamardProd2D, \
    default: PBErrInvalidPolymorphism), \
  VecFloat3D*: _Generic(VecB, \
    VecFloat3D*: _VecFloatGetHadamardProd3D, \
    default: PBErrInvalidPolymorphism), \
  VecShort*: _Generic(VecB, \
    VecShort*: _VecShortGetHadamardProd, \
    default: PBErrInvalidPolymorphism), \
  VecShort2D*: _Generic(VecB, \
    VecShort2D*: _VecShortGetHadamardProd2D, \
    default: PBErrInvalidPolymorphism), \
  VecShort3D*: _Generic(VecB, \
    VecShort3D*: _VecShortGetHadamardProd3D, \
    default: PBErrInvalidPolymorphism), \
  VecShort4D*: _Generic(VecB, \
    VecShort4D*: _VecShortGetHadamardProd4D, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(VecA, VecB)

#define VecScale(Vec, Scale) _Generic(Vec, \
  VecFloat*: _VecFloatScale, \
  VecFloat2D*: _VecFloatScale2D, \
  VecFloat3D*: _VecFloatScale3D, \
  default: PBErrInvalidPolymorphism)(Vec, Scale)

#define VecGetScale(Vec, Scale) _Generic(Vec, \
  VecFloat*: _VecFloatGetScale, \
  VecFloat2D*: _VecFloatGetScale2D, \
  VecFloat3D*: _VecFloatGetScale3D, \
  default: PBErrInvalidPolymorphism)(Vec, Scale)

#define VecRot(Vec, Theta) _Generic(Vec, \
  VecFloat*: _VecFloatRot2D, \
  VecFloat2D*: _VecFloatRot2D, \
  default: PBErrInvalidPolymorphism)((VecFloat2D*)(Vec), Theta)

#define VecGetRot(Vec, Theta) _Generic(Vec, \
  VecFloat*: _VecFloatGetRot2D, \
  VecFloat2D*: _VecFloatGetRot2D, \
  default: PBErrInvalidPolymorphism)((VecFloat2D*)(Vec), Theta)

#define VecRotAxis(Vec, Axis, Theta) _Generic(Vec, \
  VecFloat*: _VecFloatRotAxis, \
  VecFloat3D*: _VecFloatRotAxis, \
  default: PBErrInvalidPolymorphism)((VecFloat3D*)(Vec), \
    (VecFloat3D*)(Axis), Theta)

#define VecGetRotAxis(Vec, Axis, Theta) _Generic(Vec, \
  VecFloat*: _VecFloatGetRotAxis, \
  VecFloat3D*: _VecFloatGetRotAxis, \
  default: PBErrInvalidPolymorphism)((VecFloat3D*)(Vec), \
    (VecFloat3D*)(Axis), Theta)

#define VecRotX(Vec, Theta) _Generic(Vec, \
  VecFloat*: _VecFloatRotX, \
  VecFloat3D*: _VecFloatRotX, \
  default: PBErrInvalidPolymorphism)((VecFloat3D*)(Vec), Theta)

#define VecGetRotX(Vec, Theta) _Generic(Vec, \
  VecFloat*: _VecFloatGetRotX, \
  VecFloat3D*: _VecFloatGetRotX, \
  default: PBErrInvalidPolymorphism)((VecFloat3D*)(Vec), Theta)

#define VecRotY(Vec, Theta) _Generic(Vec, \
  VecFloat*: _VecFloatRotY, \
  VecFloat3D*: _VecFloatRotY, \
  default: PBErrInvalidPolymorphism)((VecFloat3D*)(Vec), Theta)

#define VecGetRotY(Vec, Theta) _Generic(Vec, \
  VecFloat*: _VecFloatGetRotY, \
  VecFloat3D*: _VecFloatGetRotY, \
  default: PBErrInvalidPolymorphism)((VecFloat3D*)(Vec), Theta)

#define VecRotZ(Vec, Theta) _Generic(Vec, \
  VecFloat*: _VecFloatRotZ, \
  VecFloat3D*: _VecFloatRotZ, \
  default: PBErrInvalidPolymorphism)((VecFloat3D*)(Vec), Theta)

#define VecGetRotZ(Vec, Theta) _Generic(Vec, \
  VecFloat*: _VecFloatGetRotZ, \
  VecFloat3D*: _VecFloatGetRotZ, \
  default: PBErrInvalidPolymorphism)((VecFloat3D*)(Vec), Theta)

#define VecDotProd(VecA, VecB) _Generic(VecA, \
  VecShort*: _VecShortDotProd,\
  VecShort2D*: _VecShortDotProd2D,\
  VecShort3D*: _VecShortDotProd3D,\
  VecShort4D*: _VecShortDotProd4D,\
  VecFloat*: _VecFloatDotProd, \
  VecFloat2D*: _VecFloatDotProd2D, \
  VecFloat3D*: _VecFloatDotProd3D, \
  default: PBErrInvalidPolymorphism) (VecA, VecB) \

#define VecAngleTo(VecFrom, VecTo) _Generic(VecFrom, \
  VecFloat*: _VecFloatAngleTo2D, \
  VecFloat2D*: _VecFloatAngleTo2D, \
  default: PBErrInvalidPolymorphism)((VecFloat2D*)(VecFrom), \
    (VecFloat2D*)(VecTo))

#define VecStep(Vec, VecBound) _Generic(Vec, \
  VecShort*: _VecShortStep, \
  VecShort2D*: _VecShortStep, \
  VecShort3D*: _VecShortStep, \
  VecShort4D*: _VecShortStep, \
  default: PBErrInvalidPolymorphism)((VecShort*)(Vec), \
    (VecShort*)(VecBound))

#define VecPStep(Vec, VecBound) _Generic(Vec, \
  VecShort*: _VecShortPStep, \
  VecShort2D*: _VecShortPStep, \
  VecShort3D*: _VecShortPStep, \
  VecShort4D*: _VecShortPStep, \
  default: PBErrInvalidPolymorphism)((VecShort*)(Vec), \
    (VecShort*)(VecBound))

#define VecShiftStep(Vec, VecFrom, VecTo) _Generic(Vec, \
  VecShort*: _VecShortShiftStep, \
  VecShort2D*: _VecShortShiftStep, \
  VecShort3D*: _VecShortShiftStep, \
  VecShort4D*: _VecShortShiftStep, \
  default: PBErrInvalidPolymorphism)((VecShort*)(Vec), \
    (VecShort*)(VecFrom), (VecShort*)(VecTo))

#define VecGetMaxVal(Vec) _Generic(Vec, \
  VecFloat*: _VecFloatGetMaxVal, \
  VecFloat2D*: _VecFloatGetMaxVal, \
  VecFloat3D*: _VecFloatGetMaxVal, \
  VecShort*: _VecShortGetMaxVal, \
  VecShort2D*: _VecShortGetMaxVal, \
  VecShort3D*: _VecShortGetMaxVal, \
  VecShort4D*: _VecShortGetMaxVal, \
  default: PBErrInvalidPolymorphism) (_Generic(Vec, \
    VecFloat2D*: (VecFloat*)(Vec), \
    VecFloat3D*: (VecFloat*)(Vec), \
    VecShort2D*: (VecShort*)(Vec), \
    VecShort3D*: (VecShort*)(Vec), \
    VecShort4D*: (VecShort*)(Vec), \
    default: Vec))

#define VecGetMinVal(Vec) _Generic(Vec, \
  VecFloat*: _VecFloatGetMinVal, \
  VecFloat2D*: _VecFloatGetMinVal, \
  VecFloat3D*: _VecFloatGetMinVal, \
  VecShort*: _VecShortGetMinVal, \
  VecShort2D*: _VecShortGetMinVal, \
  VecShort3D*: _VecShortGetMinVal, \
  VecShort4D*: _VecShortGetMinVal, \
  default: PBErrInvalidPolymorphism) (_Generic(Vec, \
    VecFloat2D*: (VecFloat*)(Vec), \
    VecFloat3D*: (VecFloat*)(Vec), \
    VecShort2D*: (VecShort*)(Vec), \
    VecShort3D*: (VecShort*)(Vec), \
    VecShort4D*: (VecShort*)(Vec), \
    default: Vec))

#define VecGetMaxValAbs(Vec) _Generic(Vec, \
  VecFloat*: _VecFloatGetMaxValAbs, \
  VecFloat2D*: _VecFloatGetMaxValAbs, \
  VecFloat3D*: _VecFloatGetMaxValAbs, \
  VecShort*: _VecShortGetMaxValAbs, \
  VecShort2D*: _VecShortGetMaxValAbs, \
  VecShort3D*: _VecShortGetMaxValAbs, \
  VecShort4D*: _VecShortGetMaxValAbs, \
  default: PBErrInvalidPolymorphism) (_Generic(Vec, \
    VecFloat2D*: (VecFloat*)(Vec), \
    VecFloat3D*: (VecFloat*)(Vec), \
    VecShort2D*: (VecShort*)(Vec), \
    VecShort3D*: (VecShort*)(Vec), \
    VecShort4D*: (VecShort*)(Vec), \
    default: Vec))

#define VecGetMinValAbs(Vec) _Generic(Vec, \
  VecFloat*: _VecFloatGetMinValAbs, \
  VecFloat2D*: _VecFloatGetMinValAbs, \
  VecFloat3D*: _VecFloatGetMinValAbs, \
  VecShort*: _VecShortGetMinValAbs, \
  VecShort2D*: _VecShortGetMinValAbs, \
  VecShort3D*: _VecShortGetMinValAbs, \
  VecShort4D*: _VecShortGetMinValAbs, \
  default: PBErrInvalidPolymorphism) (_Generic(Vec, \
    VecFloat2D*: (VecFloat*)(Vec), \
    VecFloat3D*: (VecFloat*)(Vec), \
    VecShort2D*: (VecShort*)(Vec), \
    VecShort3D*: (VecShort*)(Vec), \
    VecShort4D*: (VecShort*)(Vec), \
    default: Vec))

#define VecStepDelta(Vec, VecBound, Delta) _Generic(Vec, \
  VecFloat*: _VecFloatStepDelta, \
  VecFloat2D*: _VecFloatStepDelta, \
  VecFloat3D*: _VecFloatStepDelta, \
  default: PBErrInvalidPolymorphism)((VecFloat*)(Vec), \
    (VecFloat*)(VecBound), (VecFloat*)(Delta))

#define VecShiftStepDelta(Vec, VecFrom, VecTo, Delta) _Generic(Vec, \
  VecFloat*: _VecFloatShiftStepDelta, \
  VecFloat2D*: _VecFloatShiftStepDelta, \
  VecFloat3D*: _VecFloatShiftStepDelta, \
  default: PBErrInvalidPolymorphism)((VecFloat*)(Vec), \
    (VecFloat*)(VecFrom), (VecFloat*)(VecTo), (VecFloat*)(Delta))

#define MatClone(Mat) _Generic(Mat, \
  MatFloat*: _MatFloatClone, \
  default: PBErrInvalidPolymorphism)(Mat)

#define MatLoad(MatRef, Stream) _Generic(MatRef, \
  MatFloat**: _MatFloatLoad, \
  default: PBErrInvalidPolymorphism)(MatRef, Stream)

#define MatSave(Mat, Stream) _Generic(Mat, \
  MatFloat*: _MatFloatSave, \
  default: PBErrInvalidPolymorphism)(Mat, Stream)

#define MatFree(MatRef) _Generic(MatRef, \
  MatFloat**: _MatFloatFree, \
  default: PBErrInvalidPolymorphism)(MatRef)

#define MatPrintln(Mat, Stream) _Generic(Mat, \
  MatFloat*: _MatFloatPrintlnDef, \
  default: PBErrInvalidPolymorphism)(Mat, Stream)

#define MatGet(Mat, VecIndex) _Generic(Mat, \
  MatFloat*: _MatFloatGet, \
  default: PBErrInvalidPolymorphism)(Mat, VecIndex)

#define MatSet(Mat, VecIndex, Val) _Generic(Mat, \
  MatFloat*: _MatFloatSet, \
  default: PBErrInvalidPolymorphism)(Mat, VecIndex, Val)

#define MatCopy(MatDest, MatSrc) _Generic(MatDest, \
  MatFloat*: _Generic (MatSrc, \
    MatFloat*: _MatFloatCopy, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(MatDest, MatSrc)

#define MatDim(Mat) _Generic(Mat, \
  MatFloat*: _MatFloatDim, \
  default: PBErrInvalidPolymorphism)(Mat)

#define MatGetDim(Mat) _Generic(Mat, \
  MatFloat*: _MatFloatGetDim, \
  default: PBErrInvalidPolymorphism)(Mat)

#define MatInv(Mat) _Generic(Mat, \
  MatFloat*: _MatFloatInv, \
  default: PBErrInvalidPolymorphism)(Mat)

#define MatGetProdMat(MatA, MatB) _Generic(MatA, \
  MatFloat*: _Generic(MatB, \
    MatFloat*: _MatFloatGetProdMatFloat, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(MatA, MatB)

#define MatGetProdVec(Mat, Vec) _Generic(Mat, \
  MatFloat*: _Generic(Vec, \
    VecFloat*: _MatFloatGetProdVecFloat, \
    VecFloat2D*: _MatFloatGetProdVecFloat, \
    VecFloat3D*: _MatFloatGetProdVecFloat, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(Mat, (VecFloat*)(Vec))

#define MatAdd(MatA, MatB) _Generic(MatA, \
  MatFloat*: _Generic(MatB, \
    MatFloat*: _MatFloatAdd, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(MatA, MatB)

#define MatGetAdd(MatA, MatB) _Generic(MatA, \
  MatFloat*: _Generic(MatB, \
    MatFloat*: _MatFloatGetAdd, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(MatA, MatB)

#define MatSetIdentity(Mat) _Generic(Mat, \
  MatFloat*: _MatFloatSetIdentity, \
  default: PBErrInvalidPolymorphism)(Mat)

#define MatIsEqual(MatA, MatB) _Generic(MatA, \
  MatFloat*: _Generic(MatB, \
    MatFloat*: _MatFloatIsEqual, \
    default: PBErrInvalidPolymorphism), \
  default: PBErrInvalidPolymorphism)(MatA, MatB)

#define SysLinEqCreate(Mat, Vec) _Generic(Vec, \
  VecFloat*: _SLECreate, \
  VecFloat2D*: _SLECreate, \
  VecFloat3D*: _SLECreate, \
  default: PBErrInvalidPolymorphism)(Mat, (VecFloat*)(Vec))

#define SysLinEqSetV(Sys, Vec) _Generic(Vec, \
  VecFloat*: _SLESetV, \
  VecFloat2D*: _SLESetV, \
  VecFloat3D*: _SLESetV, \
  default: PBErrInvalidPolymorphism)(Sys, (VecFloat*)(Vec))

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
VecShort* _VecShortClone(VecShort* that);

// Load the VecShort from the stream
// If the VecShort is already allocated, it is freed before loading
// Return true in case of success, else false
bool _VecShortLoad(VecShort** that, FILE* stream);

// Save the VecShort to the stream
// Return true in case of success, else false
bool _VecShortSave(VecShort* that, FILE* stream);

// Free the memory used by a VecShort
// Do nothing if arguments are invalid
void _VecShortFree(VecShort** that);

// Print the VecShort on 'stream'
void _VecShortPrint(VecShort* that, FILE* stream);

// Return the i-th value of the VecShort
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortGet(VecShort* that, int i);
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortGet2D(VecShort2D* that, int i);
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortGet3D(VecShort3D* that, int i);
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortGet4D(VecShort4D* that, int i);

// Set the i-th value of the VecShort to v
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortSet(VecShort* that, int i, short v);
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortSet2D(VecShort2D* that, int i, short v);
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortSet3D(VecShort3D* that, int i, short v);
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortSet4D(VecShort4D* that, int i, short v);

// Return the dimension of the VecShort
// Return 0 if arguments are invalid
#if BUILDMODE != 0 
inline 
#endif 
int _VecShortGetDim(VecShort* that);

// Return the Hamiltonian distance between the VecShort 'that' and 'tho'
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortHamiltonDist(VecShort* that, VecShort* tho);
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortHamiltonDist2D(VecShort2D* that, VecShort2D* tho);
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortHamiltonDist3D(VecShort3D* that, VecShort3D* tho);
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortHamiltonDist4D(VecShort4D* that, VecShort4D* tho);

// Return true if the VecShort 'that' is equal to 'tho', else false
#if BUILDMODE != 0 
inline 
#endif 
bool _VecShortIsEqual(VecShort* that, VecShort* tho);

// Copy the values of 'w' in 'that' (must have same dimensions)
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortCopy(VecShort* that, VecShort* w);

// Return the dot product of 'that' and 'tho'
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortDotProd(VecShort* that, VecShort* tho);
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortDotProd2D(VecShort2D* that, VecShort2D* tho);
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortDotProd3D(VecShort3D* that, VecShort3D* tho);
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortDotProd4D(VecShort4D* that, VecShort4D* tho);

// Set all values of the vector 'that' to 0
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortSetNull(VecShort* that);

// Step the values of the vector incrementally by 1 from 0
// in the following order (for example) : 
// (0,0,0)->(0,0,1)->(0,0,2)->(0,1,0)->(0,1,1)->...
// The upper limit for each value is given by 'bound' (val[i] < dim[i])
// Return false if all values of 'that' have reached their upper limit 
// (in which case 'that''s values are all set back to 0)
// Return true else
bool _VecShortStep(VecShort* that, VecShort* bound);

// Step the values of the vector incrementally by 1 from 0
// in the following order (for example) : 
// (0,0,0)->(1,0,0)->(2,0,0)->(0,1,0)->(1,1,0)->...
// The upper limit for each value is given by 'bound' (val[i] < dim[i])
// Return false if all values of 'that' have reached their upper limit 
// (in which case 'that''s values are all set back to 0)
// Return true else
bool _VecShortPStep(VecShort* that, VecShort* bound);

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
bool _VecShortShiftStep(VecShort* that, VecShort* from, VecShort* to);

// Calculate (that * a + tho * b) and store the result in 'that'
// 'tho' can be null, in which case it is consider to be the null vector
// If 'tho' is not null it must be of same dimension as 'that'
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortOp(VecShort* that, short a, VecShort* tho, short b);
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortOp2D(VecShort2D* that, short a, VecShort2D* tho, short b);
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortOp3D(VecShort3D* that, short a, VecShort3D* tho, short b);
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortOp4D(VecShort4D* that, short a, VecShort4D* tho, short b);

// Return a VecShort equal to (that * a + tho * b)
// Return NULL if arguments are invalid
// 'tho' can be null, in which case it is consider to be the null vector
// If 'tho' is not null it must be of same dimension as 'that'
#if BUILDMODE != 0 
inline 
#endif 
VecShort* _VecShortGetOp(VecShort* that, short a, 
  VecShort* tho, short b);
#if BUILDMODE != 0 
inline 
#endif 
VecShort2D _VecShortGetOp2D(VecShort2D* that, short a, 
  VecShort2D* tho, short b);
#if BUILDMODE != 0 
inline 
#endif 
VecShort3D _VecShortGetOp3D(VecShort3D* that, short a, 
  VecShort3D* tho, short b);
#if BUILDMODE != 0 
inline 
#endif 
VecShort4D _VecShortGetOp4D(VecShort4D* that, short a, 
  VecShort4D* tho, short b);

// Calculate the Hadamard product of that by tho and store the 
// result in 'that'
// 'tho' and 'that' must be of same dimension
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortHadamardProd(VecShort* that, VecShort* tho);
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortHadamardProd2D(VecShort2D* that, VecShort2D* tho);
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortHadamardProd3D(VecShort3D* that, VecShort3D* tho);
#if BUILDMODE != 0 
inline 
#endif 
void _VecShortHadamardProd4D(VecShort4D* that, VecShort4D* tho);

// Return a VecShort equal to the hadamard product of 'that' and 'tho'
// Return NULL if arguments are invalid
// 'tho' and 'that' must be of same dimension
#if BUILDMODE != 0 
inline 
#endif 
VecShort* _VecShortGetHadamardProd(VecShort* that, VecShort* tho);
#if BUILDMODE != 0 
inline 
#endif 
VecShort2D _VecShortGetHadamardProd2D(VecShort2D* that, 
  VecShort2D* tho);
#if BUILDMODE != 0 
inline 
#endif 
VecShort3D _VecShortGetHadamardProd3D(VecShort3D* that, 
  VecShort3D* tho);
#if BUILDMODE != 0 
inline 
#endif 
VecShort4D _VecShortGetHadamardProd4D(VecShort4D* that, 
  VecShort4D* tho);

// Get the max value in components of the vector 'that'
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortGetMaxVal(VecShort* that);

// Get the min value in components of the vector 'that'
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortGetMinVal(VecShort* that);

// Get the max value (in absolute value) in components of the 
// vector 'that'
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortGetMaxValAbs(VecShort* that);

// Get the min value (in absolute value) in components of the 
// vector 'that'
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortGetMinValAbs(VecShort* that);

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
VecFloat* _VecFloatClone(VecFloat* that);

// Load the VecFloat from the stream
// If the VecFloat is already allocated, it is freed before loading
// Return true in case of success, else false
bool _VecFloatLoad(VecFloat** that, FILE* stream);

// Save the VecFloat to the stream
// Return true in case of success, else false
bool _VecFloatSave(VecFloat* that, FILE* stream);

// Free the memory used by a VecFloat
// Do nothing if arguments are invalid
void _VecFloatFree(VecFloat** that);

// Print the VecFloat on 'stream' with 'prec' digit precision
// Do nothing if arguments are invalid
void VecFloatPrint(VecFloat* that, FILE* stream, unsigned int prec);
inline void _VecFloatPrintDef(VecFloat* that, FILE* stream) {
  VecFloatPrint(that, stream, 3);
}

// Return the 'i'-th value of the VecFloat
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatGet(VecFloat* that, int i);
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatGet2D(VecFloat2D* that, int i);
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatGet3D(VecFloat3D* that, int i);

// Set the 'i'-th value of the VecFloat to 'v'
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatSet(VecFloat* that, int i, float v);
#if BUILDMODE != 0
inline
#endif 
void _VecFloatSet2D(VecFloat2D* that, int i, float v);
#if BUILDMODE != 0
inline
#endif 
void _VecFloatSet3D(VecFloat3D* that, int i, float v);

// Set all values of the vector 'that' to 0
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatSetNull(VecFloat* that);
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatSetNull2D(VecFloat2D* that);
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatSetNull3D(VecFloat3D* that);

// Return the dimension of the VecFloat
// Return 0 if arguments are invalid
#if BUILDMODE != 0 
inline 
#endif 
int _VecFloatGetDim(VecFloat* that);

// Return a new VecFloat as a copy of the VecFloat 'that' with 
// dimension changed to 'dim'
// if it is extended, the values of new components are 0.0
// If it is shrinked, values are discarded from the end of the vector
VecFloat* _VecFloatGetNewDim(VecFloat* that, int dim); 

// Copy the values of 'w' in 'that' (must have same dimensions)
// Do nothing if arguments are invalid
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatCopy(VecFloat* that, VecFloat* w);

// Return the norm of the VecFloat
// Return 0.0 if arguments are invalid
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatNorm(VecFloat* that);
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatNorm2D(VecFloat2D* that);
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatNorm3D(VecFloat3D* that);

// Normalise the VecFloat
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatNormalise(VecFloat* that);
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatNormalise2D(VecFloat2D* that);
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatNormalise3D(VecFloat3D* that);

// Return the distance between the VecFloat 'that' and 'tho'
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatDist(VecFloat* that, VecFloat* tho);
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatDist2D(VecFloat2D* that, VecFloat2D* tho);
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatDist3D(VecFloat3D* that, VecFloat3D* tho);

// Return the Hamiltonian distance between the VecFloat 'that' and 'tho'
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatHamiltonDist(VecFloat* that, VecFloat* tho);
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatHamiltonDist2D(VecFloat2D* that, VecFloat2D* tho);
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatHamiltonDist3D(VecFloat3D* that, VecFloat3D* tho);

// Return the Pixel distance between the VecFloat 'that' and 'tho'
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatPixelDist(VecFloat* that, VecFloat* tho);
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatPixelDist2D(VecFloat2D* that, VecFloat2D* tho);
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatPixelDist3D(VecFloat3D* that, VecFloat3D* tho);

// Return true if the VecFloat 'that' is equal to 'tho', else false
#if BUILDMODE != 0 
inline 
#endif 
bool _VecFloatIsEqual(VecFloat* that, VecFloat* tho);

// Calculate (that * a) and store the result in 'that'
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatScale(VecFloat* that, float a);
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatScale2D(VecFloat2D* that, float a);
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatScale3D(VecFloat3D* that, float a);

// Return a VecFloat equal to (that * a)
#if BUILDMODE != 0 
inline 
#endif 
VecFloat* _VecFloatGetScale(VecFloat* that, float a);
#if BUILDMODE != 0 
inline 
#endif 
VecFloat2D _VecFloatGetScale2D(VecFloat2D* that, float a);
#if BUILDMODE != 0 
inline 
#endif 
VecFloat3D _VecFloatGetScale3D(VecFloat3D* that, float a);

// Calculate (that * a + tho * b) and store the result in 'that'
// 'tho' can be null, in which case it is consider to be the null vector
// If 'tho' is not null it must be of same dimension as 'that'
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatOp(VecFloat* that, float a, VecFloat* tho, float b);
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatOp2D(VecFloat2D* that, float a, VecFloat2D* tho, float b);
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatOp3D(VecFloat3D* that, float a, VecFloat3D* tho, float b);

// Return a VecFloat equal to (that * a + tho * b)
// Return NULL if arguments are invalid
// 'tho' can be null, in which case it is consider to be the null vector
// If 'tho' is not null it must be of same dimension as 'that'
#if BUILDMODE != 0 
inline 
#endif 
VecFloat* _VecFloatGetOp(VecFloat* that, float a, 
  VecFloat* tho, float b);
#if BUILDMODE != 0 
inline 
#endif 
VecFloat2D _VecFloatGetOp2D(VecFloat2D* that, float a, 
  VecFloat2D* tho, float b);
#if BUILDMODE != 0 
inline 
#endif 
VecFloat3D _VecFloatGetOp3D(VecFloat3D* that, float a, 
  VecFloat3D* tho, float b);

// Calculate the Hadamard product of that by tho and store the 
// result in 'that'
// 'tho' and 'that' must be of same dimension
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatHadamardProd(VecFloat* that, VecFloat* tho);
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatHadamardProd2D(VecFloat2D* that, VecFloat2D* tho);
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatHadamardProd3D(VecFloat3D* that, VecFloat3D* tho);

// Return a VecFloat equal to the hadamard product of 'that' and 'tho'
// Return NULL if arguments are invalid
// 'tho' and 'that' must be of same dimension
#if BUILDMODE != 0 
inline 
#endif 
VecFloat* _VecFloatGetHadamardProd(VecFloat* that, VecFloat* tho);
#if BUILDMODE != 0 
inline 
#endif 
VecFloat2D _VecFloatGetHadamardProd2D(VecFloat2D* that, 
  VecFloat2D* tho);
#if BUILDMODE != 0 
inline 
#endif 
VecFloat3D _VecFloatGetHadamardProd3D(VecFloat3D* that, 
  VecFloat3D* tho);

// Rotate CCW 'that' by 'theta' radians and store the result in 'that'
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatRot2D(VecFloat2D* that, float theta);

// Return a VecFloat2D equal to 'that' rotated CCW by 'theta' radians
#if BUILDMODE != 0 
inline 
#endif 
VecFloat2D _VecFloatGetRot2D(VecFloat2D* that, float theta);

// Rotate right-hand 'that' by 'theta' radians around 'axis' and 
// store the result in 'that'
// 'axis' must be normalized
// https://en.wikipedia.org/wiki/Rotation_matrix
#if BUILDMODE != 0 
inline 
#endif 
void _VecFloatRotAxis(VecFloat3D* that, VecFloat3D* axis, float theta);

// Return a VecFloat3D equal to 'that' rotated right-hand by 'theta' 
// radians around 'axis'
// 'axis' must be normalized
// https://en.wikipedia.org/wiki/Rotation_matrix
VecFloat3D _VecFloatGetRotAxis(VecFloat3D* that, VecFloat3D* axis, 
  float theta);

// Rotate right-hand 'that' by 'theta' radians around X and 
// store the result in 'that'
#if BUILDMODE != 0
inline
#endif 
void _VecFloatRotX(VecFloat3D* that, float theta);

// Rotate right-hand 'that' by 'theta' radians around Y and 
// store the result in 'that'
#if BUILDMODE != 0
inline
#endif 
void _VecFloatRotY(VecFloat3D* that, float theta);

// Rotate right-hand 'that' by 'theta' radians around Z and 
// store the result in 'that'
#if BUILDMODE != 0
inline
#endif 
void _VecFloatRotZ(VecFloat3D* that, float theta);

// Return a VecFloat3D equal to 'that' rotated right-hand by 'theta' 
// radians around X
VecFloat3D _VecFloatGetRotX(VecFloat3D* that, float theta);

// Return a VecFloat3D equal to 'that' rotated right-hand by 'theta' 
// radians around Y
VecFloat3D _VecFloatGetRotY(VecFloat3D* that, float theta);

// Return a VecFloat3D equal to 'that' rotated right-hand by 'theta' 
// radians around Z
VecFloat3D _VecFloatGetRotZ(VecFloat3D* that, float theta);

// Return the dot product of 'that' and 'tho'
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatDotProd(VecFloat* that, VecFloat* tho);
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatDotProd2D(VecFloat2D* that, VecFloat2D* tho);
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatDotProd3D(VecFloat3D* that, VecFloat3D* tho);

// Return the angle of the rotation making 'that' colinear to 'tho'
// 'that' and 'tho' must be normalised
// Return a value in [-PI,PI]
float _VecFloatAngleTo2D(VecFloat2D* that, VecFloat2D* tho);

// Return the conversion of VecFloat 'that' to a VecShort using round()
#if BUILDMODE != 0 
inline 
#endif 
VecShort* VecFloatToShort(VecFloat* that);
#if BUILDMODE != 0 
inline 
#endif 
VecShort2D VecFloatToShort2D(VecFloat2D* that);
#if BUILDMODE != 0 
inline 
#endif 
VecShort3D VecFloatToShort3D(VecFloat3D* that);

// Return the conversion of VecShort 'that' to a VecFloat
#if BUILDMODE != 0 
inline 
#endif 
VecFloat* VecShortToFloat(VecShort* that);
#if BUILDMODE != 0 
inline 
#endif 
VecFloat2D VecShortToFloat2D(VecShort2D* that);
#if BUILDMODE != 0 
inline 
#endif 
VecFloat3D VecShortToFloat3D(VecShort3D* that);

// Get the max value in components of the vector 'that'
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatGetMaxVal(VecFloat* that);

// Get the min value in components of the vector 'that'
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatGetMinVal(VecFloat* that);

// Get the max value (in absolute value) in components of the 
// vector 'that'
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatGetMaxValAbs(VecFloat* that);

// Get the min value (in absolute value) in components of the 
// vector 'that'
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatGetMinValAbs(VecFloat* that);

// Step the values of the vector incrementally by delta from 0
// in the following order (for example) : 
// (0.,0.,0.)->(0.,0.,1.)->(0.,0.,2.)->(0.,1.,0.)->(0.,1.,1.)->...
// The upper limit for each value is given by 'bound' (val[i] <= dim[i])
// Return false after all values of 'that' have reached their upper 
// limit (in which case 'that''s values are all set back to 0.)
// Return true else
bool _VecFloatStepDelta(VecFloat* that, VecFloat* bound, 
  VecFloat* delta);

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
bool _VecFloatShiftStepDelta(VecFloat* that, VecFloat* from, 
  VecFloat* to, VecFloat* delta);

// -------------- MatFloat

// ================= Data structure ===================

// Vector of float values
typedef struct MatFloat {
  // Dimension
  VecShort2D _dim;
  // Values (memorized by lines)
  float _val[0];
} MatFloat;

// ================ Functions declaration ====================

// Create a new MatFloat of dimension 'dim' (nbCol, nbLine)
// Values are initalized to 0.0
MatFloat* MatFloatCreate(VecShort2D* dim);

// Set the MatFloat to the identity matrix
// The matrix must be a square matrix
#if BUILDMODE != 0 
inline 
#endif 
void _MatFloatSetIdentity(MatFloat* that);

// Clone the MatFloat
MatFloat* _MatFloatClone(MatFloat* that);

// Copy the values of 'w' in 'that' (must have same dimensions)
#if BUILDMODE != 0 
inline 
#endif 
void _MatFloatCopy(MatFloat* that, MatFloat* w);

// Load the MatFloat from the stream
// If the MatFloat is already allocated, it is freed before loading
// Return true upon success, else false
bool _MatFloatLoad(MatFloat** that, FILE* stream);

// Save the MatFloat to the stream
// Return true upon success, else false
bool _MatFloatSave(MatFloat* that, FILE* stream);

// Free the memory used by a MatFloat
// Do nothing if arguments are invalid
void _MatFloatFree(MatFloat** that);

// Print the MatFloat on 'stream' with 'prec' digit precision
// Do nothing if arguments are invalid
void MatFloatPrintln(MatFloat* that, FILE* stream, unsigned int prec);
inline void _MatFloatPrintlnDef(MatFloat* that, FILE* stream) {
  MatFloatPrintln(that, stream, 3);
}

// Return the value at index (col, line) of the MatFloat
// Index starts at 0, index in matrix = line * nbCol + col
#if BUILDMODE != 0 
inline 
#endif 
float _MatFloatGet(MatFloat* that, VecShort2D* index);

// Set the value at index (col, line) of the MatFloat to 'v'
// Index starts at 0, index in matrix = line * nbCol + col
#if BUILDMODE != 0 
inline 
#endif 
void _MatFloatSet(MatFloat* that, VecShort2D* index, float v);

// Return the dimension of the MatFloat
#if BUILDMODE != 0 
inline 
#endif 
VecShort2D* _MatFloatDim(MatFloat* that);

// Return a VecShort2D containing the dimension of the MatFloat
#if BUILDMODE != 0 
inline 
#endif 
VecShort2D _MatFloatGetDim(MatFloat* that);

// Return the inverse matrix of 'that'
// The matrix must be a square matrix
MatFloat* _MatFloatInv(MatFloat* that);

// Return the product of matrix 'that' and vector 'v'
// Number of columns of 'that' must equal dimension of 'v'
VecFloat* _MatFloatGetProdVecFloat(MatFloat* that, VecFloat* v);

// Return the product of matrix 'that' by matrix 'tho'
// Number of columns of 'that' must equal number of line of 'tho'
MatFloat* _MatFloatGetProdMatFloat(MatFloat* that, MatFloat* tho);

// Return the addition of matrix 'that' with matrix 'tho'
// 'that' and 'tho' must have same dimensions
#if BUILDMODE != 0 
inline 
#endif 
MatFloat* _MatFloatGetAdd(MatFloat* that, MatFloat* tho);

// Add matrix 'that' with matrix 'tho' and store the result in 'that'
// 'that' and 'tho' must have same dimensions
#if BUILDMODE != 0 
inline 
#endif 
void _MatFloatAdd(MatFloat* that, MatFloat* tho);

// Return true if 'that' is equal to 'tho', false else
bool _MatFloatIsEqual(MatFloat* that, MatFloat* tho);

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
SysLinEq* _SLECreate(MatFloat* m, VecFloat* v);

// Free the memory used by the SysLinEq
// Do nothing if arguments are invalid
void SysLinEqFree(SysLinEq** that);

// Clone the SysLinEq 'that'
// Return NULL if we couldn't clone the SysLinEq
SysLinEq* SysLinEqClone(SysLinEq*  that);

// Solve the SysLinEq _M.x = _V
// Return the solution vector, or null if there is no solution or the 
// arguments are invalid
#if BUILDMODE != 0 
inline 
#endif 
VecFloat* SysLinEqSolve(SysLinEq* that);

// Set the matrix of the SysLinEq to a clone of 'm'
// Do nothing if arguments are invalid
#if BUILDMODE != 0 
inline 
#endif 
void SysLinEqSetM(SysLinEq* that, MatFloat* m);

// Set the vector of the SysLinEq to a clone of 'v'
// Do nothing if arguments are invalid
#if BUILDMODE != 0 
inline 
#endif 
void _SLESetV(SysLinEq* that, VecFloat* v);

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
