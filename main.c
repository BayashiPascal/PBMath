#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include "pberr.h"
#include "pbmath.h"

#define RANDOMSEED 0

void UnitTestPowi() {
  int a;
  int n;
  for (n = 1; n <= 5; ++n) {
    for (a = 0; a <= 10; ++a) {
      int b = powi(a, n);
      int c = 1;
      int m = n;
      for (; m--;) c *= a;
      if (b != c) {
        PBMathErr->_type = PBErrTypeUnitTestFailed;
        sprintf(PBMathErr->_msg, 
          "powi(%d, %d) = %d , %d^%d = %d",
          a, n, b, a, n, c);
        PBErrCatch(PBMathErr);
      }
    }
  }
  printf("powi OK\n");
}

void UnitTestFastPow() {
  srandom(RANDOMSEED);
  int nbTest = 1000;
  float sumErr = 0.0;
  float maxErr = 0.0;
  int i = nbTest;
  for (; i--;) {
    float a = (rnd() - 0.5) * 1000.0;
    int n = INT(rnd() * 5.0);
    float b = fastpow(a, n);
    float c = pow(a, n);
    float err = fabs(b - c);
    sumErr += err;
    if (maxErr < err)
      maxErr = err;
  }
  float avgErr = sumErr / (float)nbTest;
  printf("average error: %f < %f, max error: %f < %f\n",
    avgErr, PBMATH_EPSILON, maxErr, PBMATH_EPSILON * 10.0);
  if (avgErr >= PBMATH_EPSILON ||
    maxErr >= PBMATH_EPSILON * 10.0) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "fastpow NOK");
    PBErrCatch(PBMathErr);
  }
  printf("fastpow OK\n");
}

void UnitTestSpeedFastPow() {
  srandom(RANDOMSEED);
  int nbTest = 1000;
  int i = nbTest;
  clock_t clockBefore = clock();
  for (; i--;) {
    float a = (rnd() - 0.5) * 1000.0;
    int n = INT(rnd() * 5.0);
    float b = fastpow(a, n);
    b = b;
  }
  clock_t clockAfter = clock();
  double timeFastpow = ((double)(clockAfter - clockBefore)) / 
    CLOCKS_PER_SEC * 1000.0;
  srandom(RANDOMSEED);
  i = nbTest;
  clockBefore = clock();
  for (; i--;) {
    float a = (rnd() - 0.5) * 1000.0;
    int n = INT(rnd() * 5.0);
    float c = pow(a, n);
    c = c;
  }
  clockAfter = clock();
  double timePow = ((double)(clockAfter - clockBefore)) / 
    CLOCKS_PER_SEC * 1000.0;
  printf("fastpow: %fms, pow: %fms\n", 
    timeFastpow / (float)nbTest, timePow / (float)nbTest);
  if (timeFastpow >= timePow) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    PBMathErr->_fatal = false;
    sprintf(PBMathErr->_msg, "speed fastpow NOK");
    PBErrCatch(PBMathErr);
  }
  printf("speed fastpow OK\n");
}

void UnitTestFSquare() {
  srandom(RANDOMSEED);
  int nbTest = 1000;
  for (; nbTest--;) {
    float a = (rnd() - 0.5) * 2000.0;
    float b = fsquare(a);
    float c = a * a;
    if (!ISEQUALF(b, c)) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      PBMathErr->_fatal = false;
      sprintf(PBMathErr->_msg, 
        "fsquare(%f) = %f , %f*%f = %f",
        a, b, a, a, c);
      PBErrCatch(PBMathErr);
    }
  }
  printf("fsquare OK\n");
}

void UnitTestVecShortCreateFree() {
  VecShort* v = VecShortCreate(5);
  VecShort2D v2 = VecShortCreateStatic2D();
  VecShort3D v3 = VecShortCreateStatic3D();
  VecShort4D v4 = VecShortCreateStatic4D();
  VecPrint(v, stdout);printf("\n");
  VecPrint(&v2, stdout);printf("\n");
  VecPrint(&v3, stdout);printf("\n");
  VecPrint(&v4, stdout);printf("\n");
  VecFree(&v);
  if (v != NULL) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShort is not null after VecFree");
    PBErrCatch(PBMathErr);
  }
  printf("VecShortCreateFree OK\n");
}

void UnitTestVecShortClone() {
  VecShort* v = VecShortCreate(5);
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  VecShort* w = VecClone(v);
  if (memcmp(v, w, sizeof(VecShort) + sizeof(short) * 5) != 0) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortClone NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  VecFree(&w);
  printf("_VecShortClone OK\n");
}

void UnitTestVecShortLoadSave() {
  VecShort* v = VecShortCreate(5);
  VecShort2D v2 = VecShortCreateStatic2D();
  VecShort3D v3 = VecShortCreateStatic3D();
  VecShort4D v4 = VecShortCreateStatic4D();
  for (long i = 5; i--;) VecSet(v, i, i + 1);
  for (long i = 2; i--;) VecSet(&v2, i, i + 1);
  for (long i = 3; i--;) VecSet(&v3, i, i + 1);
  for (long i = 4; i--;) VecSet(&v4, i, i + 1);
  FILE* f = fopen("./UnitTestVecShortLoadSave.txt", "w");
  if (f == NULL) {
    PBMathErr->_type = PBErrTypeOther;
    sprintf(PBMathErr->_msg, 
      "Can't open ./UnitTestVecShortLoadSave.txt for writing");
    PBErrCatch(PBMathErr);
  }
  bool compact = false;
  if (!VecSave(v, f, compact)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortSave NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecSave(&v2, f, compact)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortSave NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecSave(&v3, f, compact)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortSave NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecSave(&v4, f, compact)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortSave NOK");
    PBErrCatch(PBMathErr);
  }
  fclose(f);
  VecShort* w = VecShortCreate(2);
  f = fopen("./UnitTestVecShortLoadSave.txt", "r");
  if (f == NULL) {
    PBMathErr->_type = PBErrTypeOther;
    sprintf(PBMathErr->_msg, 
      "Can't open ./UnitTestVecShortLoadSave.txt for reading");
    PBErrCatch(PBMathErr);
  }
  if (!VecLoad(&w, f)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortLoad NOK");
    PBErrCatch(PBMathErr);
  }
  if (memcmp(v, w, sizeof(VecShort) + sizeof(short) * 5) != 0) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortLoadSave NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecLoad(&w, f)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortLoad NOK");
    PBErrCatch(PBMathErr);
  }
  if (memcmp(&v2, w, sizeof(VecShort) + sizeof(short) * 2) != 0) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortLoadSave NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecLoad(&w, f)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortLoad NOK");
    PBErrCatch(PBMathErr);
  }
  if (memcmp(&v3, w, sizeof(VecShort) + sizeof(short) * 3) != 0) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortLoadSave NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecLoad(&w, f)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortLoad NOK");
    PBErrCatch(PBMathErr);
  }
  if (memcmp(&v4, w, sizeof(VecShort) + sizeof(short) * 4) != 0) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortLoadSave NOK");
    PBErrCatch(PBMathErr);
  }
  fclose(f);
  VecFree(&v);
  VecFree(&w);
  int ret = system("cat ./UnitTestVecShortLoadSave.txt");
  printf("_VecShortLoadSave OK\n");
  ret = ret;
}

void UnitTestVecShortGetSetDim() {
  VecShort* v = VecShortCreate(5);
  VecShort2D v2 = VecShortCreateStatic2D();
  VecShort3D v3 = VecShortCreateStatic3D();
  VecShort4D v4 = VecShortCreateStatic4D();
  if (VecGetDim(v) != 5) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortGetDim NOK");
    PBErrCatch(PBMathErr);
  }
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  for (int i = 2; i--;) VecSet(&v2, i, i + 1);
  for (int i = 3; i--;) VecSet(&v3, i, i + 1);
  for (int i = 4; i--;) VecSet(&v4, i, i + 1);
  for (int i = 5; i--;)
    if (v->_val[i] != i + 1) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecShortSet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 2; i--;)
    if (v2._val[i] != i + 1) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecShortSet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 3; i--;)
    if (v3._val[i] != i + 1) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecShortSet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 4; i--;)
    if (v4._val[i] != i + 1) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecShortSet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 5; i--;)
    if (VecGet(v, i) != i + 1) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecShortGet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 2; i--;)
    if (VecGet(&v2, i) != i + 1) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecShortGet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 3; i--;)
    if (VecGet(&v3, i) != i + 1) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecShortGet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 4; i--;)
    if (VecGet(&v4, i) != i + 1) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecShortGet NOK");
      PBErrCatch(PBMathErr);
    }
VecPrint(v,stdout);printf("\n");
  for (int i = 5; i--;) VecSetAdd(v, i, i + 1);
  for (int i = 2; i--;) VecSetAdd(&v2, i, i + 1);
  for (int i = 3; i--;) VecSetAdd(&v3, i, i + 1);
  for (int i = 4; i--;) VecSetAdd(&v4, i, i + 1);
  for (int i = 5; i--;)
    if (VecGet(v, i) != 2 * (i + 1)) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecShortSetAdd NOK1");
      PBErrCatch(PBMathErr);
    }
  for (int i = 2; i--;)
    if (VecGet(&v2, i) != 2 * (i + 1)) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecShortSetAdd NOK2");
      PBErrCatch(PBMathErr);
    }
  for (int i = 3; i--;)
    if (VecGet(&v3, i) != 2 * (i + 1)) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecShortSetAdd NOK3");
      PBErrCatch(PBMathErr);
    }
  for (int i = 4; i--;)
    if (VecGet(&v4, i) != 2 * (i + 1)) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecShortSetAdd NOK4");
      PBErrCatch(PBMathErr);
    }
  VecSetNull(v);
  VecSetNull(&v2);
  VecSetNull(&v3);
  VecSetNull(&v4);
  for (int i = 5; i--;)
    if (VecGet(v, i) != 0) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecShortGet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 2; i--;)
    if (VecGet(&v2, i) != 0) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecShortGet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 3; i--;)
    if (VecGet(&v3, i) != 0) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecShortGet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 4; i--;)
    if (VecGet(&v4, i) != 0) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecShortGet NOK");
      PBErrCatch(PBMathErr);
    }
  VecFree(&v);
  printf("_VecShortGetSetDim OK\n");
}

void UnitTestVecShortStep() {
  VecShort* v = VecShortCreate(5);
  VecShort2D v2 = VecShortCreateStatic2D();
  VecShort3D v3 = VecShortCreateStatic3D();
  VecShort4D v4 = VecShortCreateStatic4D();
  VecShort* bv = VecShortCreate(5);
  VecShort2D bv2 = VecShortCreateStatic2D();
  VecShort3D bv3 = VecShortCreateStatic3D();
  VecShort4D bv4 = VecShortCreateStatic4D();
  short b[5] = {2, 3, 4, 5, 6};
  for (int i = 5; i--;) VecSet(bv, i, b[i]);
  for (int i = 2; i--;) VecSet(&bv2, i, b[i]);
  for (int i = 3; i--;) VecSet(&bv3, i, b[i]);
  for (int i = 4; i--;) VecSet(&bv4, i, b[i]);
  int acheck[2 * 3 * 4 * 5 * 6];
  for (int i = 0; i < 2 * 3 * 4 * 5 * 6; ++i)
    acheck[i] = i;
  int iCheck = 0;
  do {
    int a = VecGet(v, 0);
    for (int i = 1; i < VecGetDim(v); ++i)
      a = a * b[i] + VecGet(v, i);
    if (a != acheck[iCheck]) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecShortStep NOK");
      PBErrCatch(PBMathErr);
    }
    ++iCheck;
  } while (VecStep(v, bv));
  iCheck = 0;
  do {
    int a = VecGet(&v2, 0);
    for (int i = 1; i < 2; ++i)
      a = a * b[i] + VecGet(&v2, i);
    if (a != acheck[iCheck]) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecShortStep NOK");
      PBErrCatch(PBMathErr);
    }
    ++iCheck;
  } while (VecStep(&v2, &bv2));
  iCheck = 0;
  do {
    int a = VecGet(&v3, 0);
    for (int i = 1; i < 3; ++i)
      a = a * b[i] + VecGet(&v3, i);
    if (a != acheck[iCheck]) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecShortStep NOK");
      PBErrCatch(PBMathErr);
    }
    ++iCheck;
  } while (VecStep(&v3, &bv3));
  iCheck = 0;
  do {
    int a = VecGet(&v4, 0);
    for (int i = 1; i < 4; ++i)
      a = a * b[i] + VecGet(&v4, i);
    if (a != acheck[iCheck]) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecShortStep NOK");
      PBErrCatch(PBMathErr);
    }
    ++iCheck;
  } while (VecStep(&v4, &bv4));
  iCheck = 0;
  do {
    int a = VecGet(v, VecGetDim(v) - 1);
    for (int i = VecGetDim(v) - 2; i >= 0; --i)
      a = a * b[i] + VecGet(v, i);
    if (a != acheck[iCheck]) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecShortPStep NOK");
      PBErrCatch(PBMathErr);
    }
    ++iCheck;
  } while (VecPStep(v, bv));
  iCheck = 0;
  do {
    int a = VecGet(&v2, 1);
    a = a * b[0] + VecGet(&v2, 0);
    if (a != acheck[iCheck]) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecShortPStep NOK");
      PBErrCatch(PBMathErr);
    }
    ++iCheck;
  } while (VecPStep(&v2, &bv2));
  iCheck = 0;
  do {
    int a = VecGet(&v3, 2);
    for (int i = 1; i >= 0; --i)
      a = a * b[i] + VecGet(&v3, i);
    if (a != acheck[iCheck]) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecShortPStep NOK");
      PBErrCatch(PBMathErr);
    }
    ++iCheck;
  } while (VecPStep(&v3, &bv3));
  iCheck = 0;
  do {
    int a = VecGet(&v4, 3);
    for (int i = 2; i >= 0; --i)
      a = a * b[i] + VecGet(&v4, i);
    if (a != acheck[iCheck]) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecShortPStep NOK");
      PBErrCatch(PBMathErr);
    }
    ++iCheck;
  } while (VecPStep(&v4, &bv4));
  VecFree(&v);
  VecFree(&bv);
  VecShort2D w = VecShortCreateStatic2D();
  VecShort2D wDelta = VecShortCreateStatic2D();
  VecShort2D wBound = VecShortCreateStatic2D();
  VecSet(&wDelta, 0, 2);
  VecSet(&wDelta, 1, 3);
  VecSet(&wBound, 0, 4);
  VecSet(&wBound, 1, 6);
  int checkDelta[8] = {0, 0, 0, 3, 2, 0, 2, 3};
  iCheck = 0;
  do {
    if (VecGet(&w, 0) != checkDelta[iCheck * 2] ||
      VecGet(&w, 1) != checkDelta[iCheck * 2 + 1]) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecShortStepDelta NOK");
      PBErrCatch(PBMathErr);
    }
    ++iCheck;
  } while (VecStepDelta(&w, &wBound, &wDelta));
  int checkDeltaB[8] = {0, 0, 2, 0, 0, 3, 2, 3};
  VecSetNull(&w);
  iCheck = 0;
  do {
    if (VecGet(&w, 0) != checkDeltaB[iCheck * 2] ||
      VecGet(&w, 1) != checkDeltaB[iCheck * 2 + 1]) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecShortStepDelta NOK");
      PBErrCatch(PBMathErr);
    }
    ++iCheck;
  } while (VecPStepDelta(&w, &wBound, &wDelta));

  printf("UnitTestVecShortStep OK\n");
}

void UnitTestVecShortHamiltonDist() {
  VecShort* v = VecShortCreate(5);
  VecShort2D v2 = VecShortCreateStatic2D();
  VecShort3D v3 = VecShortCreateStatic3D();
  VecShort4D v4 = VecShortCreateStatic4D();
  VecShort* w = VecShortCreate(5);
  VecShort2D w2 = VecShortCreateStatic2D();
  VecShort3D w3 = VecShortCreateStatic3D();
  VecShort4D w4 = VecShortCreateStatic4D();
  short b[5] = {-2, -1, 0, 1, 2};
  for (int i = 5; i--;) VecSet(v, i, b[i]);
  for (int i = 2; i--;) VecSet(&v2, i, b[i]);
  for (int i = 3; i--;) VecSet(&v3, i, b[i]);
  for (int i = 4; i--;) VecSet(&v4, i, b[i]);
  for (int i = 5; i--;) VecSet(w, i, b[4 - i] + 1);
  for (int i = 2; i--;) VecSet(&w2, i, b[1 - i] + 1);
  for (int i = 3; i--;) VecSet(&w3, i, b[2 - i] + 1);
  for (int i = 4; i--;) VecSet(&w4, i, b[3 - i] + 1);
  short dist = VecHamiltonDist(v, w);
  if (dist != 13) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortHamiltonDist NOK");
    PBErrCatch(PBMathErr);
  }
  dist = VecHamiltonDist(&v2, &w2);
  if (dist != 2) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortHamiltonDist NOK");
    PBErrCatch(PBMathErr);
  }
  dist = VecHamiltonDist(&v3, &w3);
  if (dist != 5) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortHamiltonDist NOK");
    PBErrCatch(PBMathErr);
  }
  dist = VecHamiltonDist(&v4, &w4);
  if (dist != 8) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortHamiltonDist NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  VecFree(&w);
  printf("UnitTestVecShortHamiltonDist OK\n");
}

void UnitTestVecShortIsEqual() {
  VecShort* v = VecShortCreate(5);
  VecShort2D v2 = VecShortCreateStatic2D();
  VecShort3D v3 = VecShortCreateStatic3D();
  VecShort4D v4 = VecShortCreateStatic4D();
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  for (int i = 2; i--;) VecSet(&v2, i, i + 1);
  for (int i = 3; i--;) VecSet(&v3, i, i + 1);
  for (int i = 4; i--;) VecSet(&v4, i, i + 1);
  VecShort* w = VecShortCreate(5);
  VecShort2D w2 = VecShortCreateStatic2D();
  VecShort3D w3 = VecShortCreateStatic3D();
  VecShort4D w4 = VecShortCreateStatic4D();
  if (VecIsEqual(v, w)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  if (VecIsEqual(&v2, &w2)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  if (VecIsEqual(&v3, &w3)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  if (VecIsEqual(&v4, &w4)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  for (int i = 5; i--;) VecSet(w, i, i + 1);
  for (int i = 2; i--;) VecSet(&w2, i, i + 1);
  for (int i = 3; i--;) VecSet(&w3, i, i + 1);
  for (int i = 4; i--;) VecSet(&w4, i, i + 1);
  if (!VecIsEqual(v, w)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v2, &w2)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v3, &w3)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v4, &w4)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  VecFree(&w);
  printf("UnitTestVecShortIsEqual OK\n");
}

void UnitTestVecShortCopy() {
  VecShort* v = VecShortCreate(5);
  VecShort2D v2 = VecShortCreateStatic2D();
  VecShort3D v3 = VecShortCreateStatic3D();
  VecShort4D v4 = VecShortCreateStatic4D();
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  for (int i = 2; i--;) VecSet(&v2, i, i + 1);
  for (int i = 3; i--;) VecSet(&v3, i, i + 1);
  for (int i = 4; i--;) VecSet(&v4, i, i + 1);
  VecShort* w = VecShortCreate(5);
  VecShort2D w2 = VecShortCreateStatic2D();
  VecShort3D w3 = VecShortCreateStatic3D();
  VecShort4D w4 = VecShortCreateStatic4D();
  VecCopy(w, v);
  VecCopy(&w2, &v2);
  VecCopy(&w3, &v3);
  VecCopy(&w4, &v4);
  if (!VecIsEqual(v, w)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortCopy NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v2, &w2)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortCopy NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v3, &w3)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortCopy NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v4, &w4)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortCopy NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  VecFree(&w);
  printf("UnitTestVecShortCopy OK\n");
}

void UnitTestVecShortDotProd() {
  VecShort* v = VecShortCreate(5);
  VecShort2D v2 = VecShortCreateStatic2D();
  VecShort3D v3 = VecShortCreateStatic3D();
  VecShort4D v4 = VecShortCreateStatic4D();
  VecShort* w = VecShortCreate(5);
  VecShort2D w2 = VecShortCreateStatic2D();
  VecShort3D w3 = VecShortCreateStatic3D();
  VecShort4D w4 = VecShortCreateStatic4D();
  short b[5] = {-2, -1, 0, 1, 2};
  for (int i = 5; i--;) VecSet(v, i, b[i]);
  for (int i = 2; i--;) VecSet(&v2, i, b[i]);
  for (int i = 3; i--;) VecSet(&v3, i, b[i]);
  for (int i = 4; i--;) VecSet(&v4, i, b[i]);
  for (int i = 5; i--;) VecSet(w, i, b[4 - i] + 1);
  for (int i = 2; i--;) VecSet(&w2, i, b[1 - i] + 1);
  for (int i = 3; i--;) VecSet(&w3, i, b[2 - i] + 1);
  for (int i = 4; i--;) VecSet(&w4, i, b[3 - i] + 1);
  short prod = VecDotProd(v, w);
  if (prod != -10) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortDotProd NOK");
    PBErrCatch(PBMathErr);
  }
  prod = VecDotProd(&v2, &w2);
  if (prod != 1) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortDotProd NOK");
    PBErrCatch(PBMathErr);
  }
  prod = VecDotProd(&v3, &w3);
  if (prod != -2) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortDotProd NOK");
    PBErrCatch(PBMathErr);
  }
  prod = VecDotProd(&v4, &w4);
  if (prod != -6) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortDotProd NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  VecFree(&w);
  printf("UnitTestVecShortDotProd OK\n");
}

void UnitTestSpeedVecShort() {
  VecShort* v = VecShortCreate(5);
  VecShort2D v2 = VecShortCreateStatic2D();
  VecShort3D v3 = VecShortCreateStatic3D();
  VecShort4D v4 = VecShortCreateStatic4D();
  int nbTest = 100000;

  srandom(RANDOMSEED);
  int i = nbTest;
  clock_t clockBefore = clock();
  for (; i--;) {
    int j = INT(rnd() * ((float)(VecGetDim(v) - 1) - PBMATH_EPSILON));
    short val = 1;
    VecSet(v, j, val);
    short valb = VecGet(v, j);
    valb = valb;
  }
  clock_t clockAfter = clock();
  double timeV = ((double)(clockAfter - clockBefore)) / 
    CLOCKS_PER_SEC * 1000.0;
  srandom(RANDOMSEED);
  i = nbTest;
  clockBefore = clock();
  short* array = malloc(sizeof(short) * 5);
  for (; i--;) {
    int j = INT(rnd() * ((float)(VecGetDim(v) - 1) - PBMATH_EPSILON));
    short val = 1;
    array[j] = val;
    short valb = array[j];
    valb = valb;
  }
  clockAfter = clock();
  double timeRef = ((double)(clockAfter - clockBefore)) / 
    CLOCKS_PER_SEC * 1000.0;
  printf("VecShort: %fms, array: %fms\n", 
    timeV / (float)nbTest, timeRef / (float)nbTest);
  if (timeV / (float)nbTest > 5.0 * timeRef / (float)nbTest) {
#if BUILDMODE == 0 
    PBMathErr->_fatal = false;
#endif
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "UnitTestSpeedVecShort NOK");
    PBErrCatch(PBMathErr);
  }

  srandom(RANDOMSEED);
  i = nbTest;
  clockBefore = clock();
  for (; i--;) {
    int j = INT(rnd() * (1.0 - PBMATH_EPSILON));
    short val = 1;
    VecSet(&v2, j, val);
    short valb = VecGet(&v2, j);
    valb = valb;
  }
  clockAfter = clock();
  timeV = ((double)(clockAfter - clockBefore)) / 
    CLOCKS_PER_SEC * 1000.0;
  srandom(RANDOMSEED);
  i = nbTest;
  clockBefore = clock();
  short array2[2];
  for (; i--;) {
    int j = INT(rnd() * (1.0 - PBMATH_EPSILON));
    short val = 1;
    array2[j] = val;
    short valb = array2[j];
    valb = valb;
  }
  clockAfter = clock();
  timeRef = ((double)(clockAfter - clockBefore)) / 
    CLOCKS_PER_SEC * 1000.0;
  printf("VecShort2D: %fms, array: %fms\n", 
    timeV / (float)nbTest, timeRef / (float)nbTest);
  if (timeV / (float)nbTest > 2.0 * timeRef / (float)nbTest) {
#if BUILDMODE == 0 
    PBMathErr->_fatal = false;
#endif
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "UnitTestSpeedVecShort NOK");
    PBErrCatch(PBMathErr);
  }

  srandom(RANDOMSEED);
  i = nbTest;
  clockBefore = clock();
  for (; i--;) {
    int j = INT(rnd() * (2.0 - PBMATH_EPSILON));
    short val = 1;
    VecSet(&v3, j, val);
    short valb = VecGet(&v3, j);
    valb = valb;
  }
  clockAfter = clock();
  timeV = ((double)(clockAfter - clockBefore)) / 
    CLOCKS_PER_SEC * 1000.0;
  srandom(RANDOMSEED);
  i = nbTest;
  clockBefore = clock();
  short array3[3];
  for (; i--;) {
    int j = INT(rnd() * (2.0 - PBMATH_EPSILON));
    short val = 1;
    array3[j] = val;
    short valb = array3[j];
    valb = valb;
  }
  clockAfter = clock();
  timeRef = ((double)(clockAfter - clockBefore)) / 
    CLOCKS_PER_SEC * 1000.0;
  printf("VecShort3D: %fms, array: %fms\n", 
    timeV / (float)nbTest, timeRef / (float)nbTest);
  if (timeV / (float)nbTest > 2.0 * timeRef / (float)nbTest) {
#if BUILDMODE == 0 
    PBMathErr->_fatal = false;
#endif
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "UnitTestSpeedVecShort NOK");
    PBErrCatch(PBMathErr);
  }

  srandom(RANDOMSEED);
  i = nbTest;
  clockBefore = clock();
  for (; i--;) {
    int j = INT(rnd() * (3.0 - PBMATH_EPSILON));
    short val = 1;
    VecSet(&v4, j, val);
    short valb = VecGet(&v4, j);
    valb = valb;
  }
  clockAfter = clock();
  timeV = ((double)(clockAfter - clockBefore)) / 
    CLOCKS_PER_SEC * 1000.0;
  srandom(RANDOMSEED);
  i = nbTest;
  clockBefore = clock();
  short array4[4];
  for (; i--;) {
    int j = INT(rnd() * (3.0 - PBMATH_EPSILON));
    short val = 1;
    array4[j] = val;
    short valb = array4[j];
    valb = valb;
  }
  clockAfter = clock();
  timeRef = ((double)(clockAfter - clockBefore)) / 
    CLOCKS_PER_SEC * 1000.0;
  printf("VecShort4D: %fms, array: %fms\n", 
    timeV / (float)nbTest, timeRef / (float)nbTest);
  if (timeV / (float)nbTest > 2.0 * timeRef / (float)nbTest) {
#if BUILDMODE == 0 
    PBMathErr->_fatal = false;
#endif
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "UnitTestSpeedVecShort NOK");
    PBErrCatch(PBMathErr);
  }

  VecFree(&v);
  free(array);
  printf("UnitTestSpeedVecShort OK\n");
}

void UnitTestVecShortToFloat() {
  VecShort* v = VecShortCreate(5);
  VecShort2D v2 = VecShortCreateStatic2D();
  VecShort3D v3 = VecShortCreateStatic3D();
  VecShort4D v4 = VecShortCreateStatic4D();
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  for (int i = 2; i--;) VecSet(&v2, i, i + 1);
  for (int i = 3; i--;) VecSet(&v3, i, i + 1);
  for (int i = 4; i--;) VecSet(&v4, i, i + 1);
  VecFloat* w = VecShortToFloat(v);
  VecFloat2D w2 = VecShortToFloat2D(&v2);
  VecFloat3D w3 = VecShortToFloat3D(&v3);
  VecPrint(w, stdout); printf("\n");
  VecPrint(&w2, stdout); printf("\n");
  VecPrint(&w3, stdout); printf("\n");
  VecFree(&v);
  VecFree(&w);
  printf("UnitTestVecShortToFloat OK\n");
}

void UnitTestVecLongToFloat() {
  VecLong* v = VecLongCreate(5);
  VecLong2D v2 = VecLongCreateStatic2D();
  VecLong3D v3 = VecLongCreateStatic3D();
  VecLong4D v4 = VecLongCreateStatic4D();
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  for (int i = 2; i--;) VecSet(&v2, i, i + 1);
  for (int i = 3; i--;) VecSet(&v3, i, i + 1);
  for (int i = 4; i--;) VecSet(&v4, i, i + 1);
  VecFloat* w = VecLongToFloat(v);
  VecFloat2D w2 = VecLongToFloat2D(&v2);
  VecFloat3D w3 = VecLongToFloat3D(&v3);
  VecPrint(w, stdout); printf("\n");
  VecPrint(&w2, stdout); printf("\n");
  VecPrint(&w3, stdout); printf("\n");
  VecFree(&v);
  VecFree(&w);
  printf("UnitTestVecLongToFloat OK\n");
}

void UnitTestVecShortOp() {
  VecShort* v = VecShortCreate(5);
  VecShort2D v2 = VecShortCreateStatic2D();
  VecShort3D v3 = VecShortCreateStatic3D();
  VecShort4D v4 = VecShortCreateStatic4D();
  VecShort* w = VecShortCreate(5);
  VecShort2D w2 = VecShortCreateStatic2D();
  VecShort3D w3 = VecShortCreateStatic3D();
  VecShort4D w4 = VecShortCreateStatic4D();
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  for (int i = 2; i--;) VecSet(&v2, i, i + 1);
  for (int i = 3; i--;) VecSet(&v3, i, i + 1);
  short a[2] = {-1, 2};
  short b[5] = {-2, -1, 0, 1, 2};
  for (int i = 5; i--;) VecSet(v, i, b[i]);
  for (int i = 2; i--;) VecSet(&v2, i, b[i]);
  for (int i = 3; i--;) VecSet(&v3, i, b[i]);
  for (int i = 4; i--;) VecSet(&v4, i, b[i]);
  for (int i = 5; i--;) VecSet(w, i, b[4 - i] + 1);
  for (int i = 2; i--;) VecSet(&w2, i, b[1 - i] + 1);
  for (int i = 3; i--;) VecSet(&w3, i, b[2 - i] + 1);
  for (int i = 4; i--;) VecSet(&w4, i, b[3 - i] + 1);
  VecShort* u = VecGetOp(v, a[0], w, a[1]);
  VecShort2D u2 = VecGetOp(&v2, a[0], &w2, a[1]);
  VecShort3D u3 = VecGetOp(&v3, a[0], &w3, a[1]);
  VecShort4D u4 = VecGetOp(&v4, a[0], &w4, a[1]);
  short checku[5] = {8,5,2,-1,-4};
  short checku2[2] = {2,-1};
  short checku3[3] = {4,1,-2};
  short checku4[4] = {6,3,0,-3};
  for (int i = 5; i--;)
    if (!ISEQUALF(VecGet(u, i), checku[i])) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecShortGetOp NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 2; i--;)
    if (!ISEQUALF(VecGet(&u2, i), checku2[i])) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecShortGetOp NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 3; i--;)
    if (!ISEQUALF(VecGet(&u3, i), checku3[i])) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecShortGetOp NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 4; i--;)
    if (!ISEQUALF(VecGet(&u4, i), checku4[i])) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecShortGetOp NOK");
      PBErrCatch(PBMathErr);
    }
  VecOp(v, a[0], w, a[1]);
  VecOp(&v2, a[0], &w2, a[1]);
  VecOp(&v3, a[0], &w3, a[1]);
  VecOp(&v4, a[0], &w4, a[1]);
  if (!VecIsEqual(v, u)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortOp NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v2, &u2)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortOp NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v3, &u3)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortOp NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v4, &u4)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecShortOp NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  VecFree(&w);
  VecFree(&u);
  printf("UnitTestVecShortOp OK\n");
}

void UnitTestVecShortShiftStep() {
  VecShort3D v = VecShortCreateStatic3D();
  VecShort3D from = VecShortCreateStatic3D();
  VecShort3D to = VecShortCreateStatic3D();
  VecSet(&from, 0, 0);
  VecSet(&from, 1, 1);
  VecSet(&from, 2, 2);
  VecSet(&to, 0, 3);
  VecSet(&to, 1, 4);
  VecSet(&to, 2, 5);
  VecCopy(&v, &from);
  short check[81] = {
    0, 1, 2, 0, 1, 3, 0, 1, 4,
    0, 2, 2, 0, 2, 3, 0, 2, 4,
    0, 3, 2, 0, 3, 3, 0, 3, 4,
    1, 1, 2, 1, 1, 3, 1, 1, 4,
    1, 2, 2, 1, 2, 3, 1, 2, 4,
    1, 3, 2, 1, 3, 3, 1, 3, 4,
    2, 1, 2, 2, 1, 3, 2, 1, 4,
    2, 2, 2, 2, 2, 3, 2, 2, 4,
    2, 3, 2, 2, 3, 3, 2, 3, 4
    };
  int iCheck = 0;
  do {
    for (int i = 0; i < 3; ++i) {
      if (ISEQUALF(check[iCheck], VecGet(&v, i)) == false) {
        PBMathErr->_type = PBErrTypeUnitTestFailed;
        sprintf(PBMathErr->_msg, "VecShiftStep NOK");
        PBErrCatch(PBMathErr);
      }
      ++iCheck;
    }
  } while(VecShiftStep(&v, &from, &to));
  printf("UnitTestVecShortShiftStep OK\n");
}

void UnitTestVecShortGetMinMax() {
  VecShort3D v = VecShortCreateStatic3D();
  VecSet(&v, 0, 2); VecSet(&v, 1, 4); VecSet(&v, 2, 3);
  short val = VecGetMaxVal(&v);
  if (val != 4) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecGetMaxVal NOK");
    PBErrCatch(PBMathErr);
  }
  if (VecGetIMaxVal(&v) != 1) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecGetIMaxVal NOK");
    PBErrCatch(PBMathErr);
  }
  VecSet(&v, 0, 2); VecSet(&v, 1, 1); VecSet(&v, 2, 3);
  val = VecGetMinVal(&v);
  if (val != 1) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecGetMinVal NOK");
    PBErrCatch(PBMathErr);
  }
  VecSet(&v, 0, 2); VecSet(&v, 1, -4); VecSet(&v, 2, 3);
  val = VecGetMaxValAbs(&v);
  if (val != -4) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecGetMaxValAbs NOK");
    PBErrCatch(PBMathErr);
  }
  VecSet(&v, 0, -2); VecSet(&v, 1, 1); VecSet(&v, 2, 3);
  val = VecGetMinValAbs(&v);
  if (val != 1) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecGetMinValAbs NOK");
    PBErrCatch(PBMathErr);
  }
  printf("UnitTestVecShortGetMinMax OK\n");
}

void UnitTestVecShortHadamardProd() {
  VecShort* u = VecShortCreate(3);
  for (int i = 3; i--;)
    VecSet(u, i, i + 2);
  VecShort* uprod = VecGetHadamardProd(u, u);
  VecHadamardProd(u, u);
  short checku[3] = {4, 9, 16};
  for (int i = 3; i--;)
    if (ISEQUALF(VecGet(uprod, i), checku[i]) == false) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecGetHadamardProd NOK");
      PBErrCatch(PBMathErr);
    }
  if (VecIsEqual(uprod, u) == false) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecHadamardProd NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&uprod);
  VecFree(&u);
  VecShort2D v = VecShortCreateStatic2D();
  for (int i = 2; i--;)
    VecSet(&v, i, i + 2);
  VecShort2D vprod = VecGetHadamardProd(&v, &v);
  VecHadamardProd(&v, &v);
  short checkv[2] = {4, 9};
  for (int i = 2; i--;)
    if (ISEQUALF(VecGet(&vprod, i), checkv[i]) == false) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecGetHadamardProd NOK");
      PBErrCatch(PBMathErr);
    }
  if (VecIsEqual(&vprod, &v) == false) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecHadamardProd NOK");
    PBErrCatch(PBMathErr);
  }
  VecShort3D w = VecShortCreateStatic3D();
  for (int i = 3; i--;)
    VecSet(&w, i, i + 2);
  VecShort3D wprod = VecGetHadamardProd(&w, &w);
  VecHadamardProd(&w, &w);
  short checkw[3] = {4, 9, 16};
  for (int i = 3; i--;)
    if (ISEQUALF(VecGet(&wprod, i), checkw[i]) == false) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecGetHadamardProd NOK");
      PBErrCatch(PBMathErr);
    }
  if (VecIsEqual(&wprod, &w) == false) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecHadamardProd NOK");
    PBErrCatch(PBMathErr);
  }
  VecShort4D x = VecShortCreateStatic4D();
  for (int i = 4; i--;)
    VecSet(&x, i, i + 2);
  VecShort4D xprod = VecGetHadamardProd(&x, &x);
  VecHadamardProd(&x, &x);
  short checkx[4] = {4, 9, 16, 25};
  for (int i = 4; i--;)
    if (ISEQUALF(VecGet(&xprod, i), checkx[i]) == false) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecGetHadamardProd NOK");
      PBErrCatch(PBMathErr);
    }
  if (VecIsEqual(&xprod, &x) == false) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecHadamardProd NOK");
    PBErrCatch(PBMathErr);
  }
  printf("UnitTestVecShortHadamardProd OK\n");
}

void UnitTestVecShort() {
  UnitTestVecShortCreateFree();
  UnitTestVecShortClone();
  UnitTestVecShortLoadSave();
  UnitTestVecShortGetSetDim();
  UnitTestVecShortStep();
  UnitTestVecShortHamiltonDist();
  UnitTestVecShortIsEqual();
  UnitTestVecShortDotProd();
  UnitTestVecShortCopy();
  UnitTestSpeedVecShort();
  UnitTestVecShortToFloat();
  UnitTestVecLongToFloat();
  UnitTestVecShortOp();
  UnitTestVecShortShiftStep();
  UnitTestVecShortGetMinMax();
  UnitTestVecShortHadamardProd();
  printf("UnitTestVecShort OK\n");
}

void UnitTestVecLongCreateFree() {
  VecLong* v = VecLongCreate(5);
  VecLong2D v2 = VecLongCreateStatic2D();
  VecLong3D v3 = VecLongCreateStatic3D();
  VecLong4D v4 = VecLongCreateStatic4D();
  VecPrint(v, stdout);printf("\n");
  VecPrint(&v2, stdout);printf("\n");
  VecPrint(&v3, stdout);printf("\n");
  VecPrint(&v4, stdout);printf("\n");
  VecFree(&v);
  if (v != NULL) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecLong is not null after VecFree");
    PBErrCatch(PBMathErr);
  }
  printf("VecLongCreateFree OK\n");
}

void UnitTestVecLongClone() {
  VecLong* v = VecLongCreate(5);
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  VecLong* w = VecClone(v);
  if (memcmp(v, w, sizeof(VecLong) + sizeof(long) * 5) != 0) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongClone NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  VecFree(&w);
  printf("_VecLongClone OK\n");
}

void UnitTestVecLongLoadSave() {
  VecLong* v = VecLongCreate(5);
  VecLong2D v2 = VecLongCreateStatic2D();
  VecLong3D v3 = VecLongCreateStatic3D();
  VecLong4D v4 = VecLongCreateStatic4D();
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  for (int i = 2; i--;) VecSet(&v2, i, i + 1);
  for (int i = 3; i--;) VecSet(&v3, i, i + 1);
  for (int i = 4; i--;) VecSet(&v4, i, i + 1);
  FILE* f = fopen("./UnitTestVecLongLoadSave.txt", "w");
  if (f == NULL) {
    PBMathErr->_type = PBErrTypeOther;
    sprintf(PBMathErr->_msg, 
      "Can't open ./UnitTestVecLongLoadSave.txt for writing");
    PBErrCatch(PBMathErr);
  }
  bool compact = false;
  if (!VecSave(v, f, compact)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongSave NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecSave(&v2, f, compact)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongSave NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecSave(&v3, f, compact)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongSave NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecSave(&v4, f, compact)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongSave NOK");
    PBErrCatch(PBMathErr);
  }
  fclose(f);
  VecLong* w = VecLongCreate(2);
  f = fopen("./UnitTestVecLongLoadSave.txt", "r");
  if (f == NULL) {
    PBMathErr->_type = PBErrTypeOther;
    sprintf(PBMathErr->_msg, 
      "Can't open ./UnitTestVecLongLoadSave.txt for reading");
    PBErrCatch(PBMathErr);
  }
  if (!VecLoad(&w, f)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongLoad NOK");
    PBErrCatch(PBMathErr);
  }
  if (memcmp(v, w, sizeof(VecLong) + sizeof(long) * 5) != 0) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongLoadSave NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecLoad(&w, f)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongLoad NOK");
    PBErrCatch(PBMathErr);
  }
  if (memcmp(&v2, w, sizeof(VecLong) + sizeof(long) * 2) != 0) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongLoadSave NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecLoad(&w, f)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongLoad NOK");
    PBErrCatch(PBMathErr);
  }
  if (memcmp(&v3, w, sizeof(VecLong) + sizeof(long) * 3) != 0) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongLoadSave NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecLoad(&w, f)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongLoad NOK");
    PBErrCatch(PBMathErr);
  }
  if (memcmp(&v4, w, sizeof(VecLong) + sizeof(long) * 4) != 0) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongLoadSave NOK");
    PBErrCatch(PBMathErr);
  }
  fclose(f);
  VecFree(&v);
  VecFree(&w);
  int ret = system("cat ./UnitTestVecLongLoadSave.txt");
  printf("_VecLongLoadSave OK\n");
  ret = ret;
}

void UnitTestVecLongGetSetDim() {
  VecLong* v = VecLongCreate(5);
  VecLong2D v2 = VecLongCreateStatic2D();
  VecLong3D v3 = VecLongCreateStatic3D();
  VecLong4D v4 = VecLongCreateStatic4D();
  if (VecGetDim(v) != 5) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongGetDim NOK");
    PBErrCatch(PBMathErr);
  }
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  for (int i = 2; i--;) VecSet(&v2, i, i + 1);
  for (int i = 3; i--;) VecSet(&v3, i, i + 1);
  for (int i = 4; i--;) VecSet(&v4, i, i + 1);
  for (int i = 5; i--;)
    if (v->_val[i] != i + 1) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecLongSet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 2; i--;)
    if (v2._val[i] != i + 1) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecLongSet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 3; i--;)
    if (v3._val[i] != i + 1) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecLongSet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 4; i--;)
    if (v4._val[i] != i + 1) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecLongSet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 5; i--;)
    if (VecGet(v, i) != i + 1) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecLongGet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 2; i--;)
    if (VecGet(&v2, i) != i + 1) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecLongGet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 3; i--;)
    if (VecGet(&v3, i) != i + 1) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecLongGet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 4; i--;)
    if (VecGet(&v4, i) != i + 1) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecLongGet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 5; i--;) VecSetAdd(v, i, i + 1);
  for (int i = 2; i--;) VecSetAdd(&v2, i, i + 1);
  for (int i = 3; i--;) VecSetAdd(&v3, i, i + 1);
  for (int i = 4; i--;) VecSetAdd(&v4, i, i + 1);
  for (int i = 5; i--;)
    if (VecGet(v, i) != 2 * (i + 1)) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecLongSetAdd NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 2; i--;)
    if (VecGet(&v2, i) != 2 * (i + 1)) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecLongSetAdd NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 3; i--;)
    if (VecGet(&v3, i) != 2 * (i + 1)) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecLongSetAdd NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 4; i--;)
    if (VecGet(&v4, i) != 2 * (i + 1)) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecLongSetAdd NOK");
      PBErrCatch(PBMathErr);
    }
  VecSetNull(v);
  VecSetNull(&v2);
  VecSetNull(&v3);
  VecSetNull(&v4);
  for (int i = 5; i--;)
    if (VecGet(v, i) != 0) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecLongGet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 2; i--;)
    if (VecGet(&v2, i) != 0) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecLongGet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 3; i--;)
    if (VecGet(&v3, i) != 0) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecLongGet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 4; i--;)
    if (VecGet(&v4, i) != 0) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecLongGet NOK");
      PBErrCatch(PBMathErr);
    }
  VecFree(&v);
  printf("_VecLongGetSetDim OK\n");
}

void UnitTestVecLongStep() {
  VecLong* v = VecLongCreate(5);
  VecLong2D v2 = VecLongCreateStatic2D();
  VecLong3D v3 = VecLongCreateStatic3D();
  VecLong4D v4 = VecLongCreateStatic4D();
  VecLong* bv = VecLongCreate(5);
  VecLong2D bv2 = VecLongCreateStatic2D();
  VecLong3D bv3 = VecLongCreateStatic3D();
  VecLong4D bv4 = VecLongCreateStatic4D();
  long b[5] = {2, 3, 4, 5, 6};
  for (int i = 5; i--;) VecSet(bv, i, b[i]);
  for (int i = 2; i--;) VecSet(&bv2, i, b[i]);
  for (int i = 3; i--;) VecSet(&bv3, i, b[i]);
  for (int i = 4; i--;) VecSet(&bv4, i, b[i]);
  int acheck[2 * 3 * 4 * 5 * 6];
  for (int i = 0; i < 2 * 3 * 4 * 5 * 6; ++i)
    acheck[i] = i;
  int iCheck = 0;
  do {
    int a = VecGet(v, 0);
    for (int i = 1; i < VecGetDim(v); ++i)
      a = a * b[i] + VecGet(v, i);
    if (a != acheck[iCheck]) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecLongStep NOK");
      PBErrCatch(PBMathErr);
    }
    ++iCheck;
  } while (VecStep(v, bv));
  iCheck = 0;
  do {
    int a = VecGet(&v2, 0);
    for (int i = 1; i < 2; ++i)
      a = a * b[i] + VecGet(&v2, i);
    if (a != acheck[iCheck]) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecLongStep NOK");
      PBErrCatch(PBMathErr);
    }
    ++iCheck;
  } while (VecStep(&v2, &bv2));
  iCheck = 0;
  do {
    int a = VecGet(&v3, 0);
    for (int i = 1; i < 3; ++i)
      a = a * b[i] + VecGet(&v3, i);
    if (a != acheck[iCheck]) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecLongStep NOK");
      PBErrCatch(PBMathErr);
    }
    ++iCheck;
  } while (VecStep(&v3, &bv3));
  iCheck = 0;
  do {
    int a = VecGet(&v4, 0);
    for (int i = 1; i < 4; ++i)
      a = a * b[i] + VecGet(&v4, i);
    if (a != acheck[iCheck]) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecLongStep NOK");
      PBErrCatch(PBMathErr);
    }
    ++iCheck;
  } while (VecStep(&v4, &bv4));
  iCheck = 0;
  do {
    int a = VecGet(v, VecGetDim(v) - 1);
    for (int i = VecGetDim(v) - 2; i >= 0; --i)
      a = a * b[i] + VecGet(v, i);
    if (a != acheck[iCheck]) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecLongPStep NOK");
      PBErrCatch(PBMathErr);
    }
    ++iCheck;
  } while (VecPStep(v, bv));
  iCheck = 0;
  do {
    int a = VecGet(&v2, 1);
    a = a * b[0] + VecGet(&v2, 0);
    if (a != acheck[iCheck]) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecLongPStep NOK");
      PBErrCatch(PBMathErr);
    }
    ++iCheck;
  } while (VecPStep(&v2, &bv2));
  iCheck = 0;
  do {
    int a = VecGet(&v3, 2);
    for (int i = 1; i >= 0; --i)
      a = a * b[i] + VecGet(&v3, i);
    if (a != acheck[iCheck]) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecLongPStep NOK");
      PBErrCatch(PBMathErr);
    }
    ++iCheck;
  } while (VecPStep(&v3, &bv3));
  iCheck = 0;
  do {
    int a = VecGet(&v4, 3);
    for (int i = 2; i >= 0; --i)
      a = a * b[i] + VecGet(&v4, i);
    if (a != acheck[iCheck]) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecLongPStep NOK");
      PBErrCatch(PBMathErr);
    }
    ++iCheck;
  } while (VecPStep(&v4, &bv4));
  VecFree(&v);
  VecFree(&bv);
  VecLong2D w = VecLongCreateStatic2D();
  VecLong2D wDelta = VecLongCreateStatic2D();
  VecLong2D wBound = VecLongCreateStatic2D();
  VecSet(&wDelta, 0, 2);
  VecSet(&wDelta, 1, 3);
  VecSet(&wBound, 0, 4);
  VecSet(&wBound, 1, 6);
  int checkDelta[8] = {0, 0, 0, 3, 2, 0, 2, 3};
  iCheck = 0;
  do {
    if (VecGet(&w, 0) != checkDelta[iCheck * 2] ||
      VecGet(&w, 1) != checkDelta[iCheck * 2 + 1]) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecLongStepDelta NOK");
      PBErrCatch(PBMathErr);
    }
    ++iCheck;
  } while (VecStepDelta(&w, &wBound, &wDelta));
  int checkDeltaB[8] = {0, 0, 2, 0, 0, 3, 2, 3};
  VecSetNull(&w);
  iCheck = 0;
  do {
    if (VecGet(&w, 0) != checkDeltaB[iCheck * 2] ||
      VecGet(&w, 1) != checkDeltaB[iCheck * 2 + 1]) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecLongStepDelta NOK");
      PBErrCatch(PBMathErr);
    }
    ++iCheck;
  } while (VecPStepDelta(&w, &wBound, &wDelta));

  printf("UnitTestVecLongStep OK\n");
}

void UnitTestVecLongHamiltonDist() {
  VecLong* v = VecLongCreate(5);
  VecLong2D v2 = VecLongCreateStatic2D();
  VecLong3D v3 = VecLongCreateStatic3D();
  VecLong4D v4 = VecLongCreateStatic4D();
  VecLong* w = VecLongCreate(5);
  VecLong2D w2 = VecLongCreateStatic2D();
  VecLong3D w3 = VecLongCreateStatic3D();
  VecLong4D w4 = VecLongCreateStatic4D();
  long b[5] = {-2, -1, 0, 1, 2};
  for (int i = 5; i--;) VecSet(v, i, b[i]);
  for (int i = 2; i--;) VecSet(&v2, i, b[i]);
  for (int i = 3; i--;) VecSet(&v3, i, b[i]);
  for (int i = 4; i--;) VecSet(&v4, i, b[i]);
  for (int i = 5; i--;) VecSet(w, i, b[4 - i] + 1);
  for (int i = 2; i--;) VecSet(&w2, i, b[1 - i] + 1);
  for (int i = 3; i--;) VecSet(&w3, i, b[2 - i] + 1);
  for (int i = 4; i--;) VecSet(&w4, i, b[3 - i] + 1);
  long dist = VecHamiltonDist(v, w);
  if (dist != 13) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongHamiltonDist NOK");
    PBErrCatch(PBMathErr);
  }
  dist = VecHamiltonDist(&v2, &w2);
  if (dist != 2) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongHamiltonDist NOK");
    PBErrCatch(PBMathErr);
  }
  dist = VecHamiltonDist(&v3, &w3);
  if (dist != 5) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongHamiltonDist NOK");
    PBErrCatch(PBMathErr);
  }
  dist = VecHamiltonDist(&v4, &w4);
  if (dist != 8) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongHamiltonDist NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  VecFree(&w);
  printf("UnitTestVecLongHamiltonDist OK\n");
}

void UnitTestVecLongIsEqual() {
  VecLong* v = VecLongCreate(5);
  VecLong2D v2 = VecLongCreateStatic2D();
  VecLong3D v3 = VecLongCreateStatic3D();
  VecLong4D v4 = VecLongCreateStatic4D();
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  for (int i = 2; i--;) VecSet(&v2, i, i + 1);
  for (int i = 3; i--;) VecSet(&v3, i, i + 1);
  for (int i = 4; i--;) VecSet(&v4, i, i + 1);
  VecLong* w = VecLongCreate(5);
  VecLong2D w2 = VecLongCreateStatic2D();
  VecLong3D w3 = VecLongCreateStatic3D();
  VecLong4D w4 = VecLongCreateStatic4D();
  if (VecIsEqual(v, w)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  if (VecIsEqual(&v2, &w2)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  if (VecIsEqual(&v3, &w3)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  if (VecIsEqual(&v4, &w4)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  for (int i = 5; i--;) VecSet(w, i, i + 1);
  for (int i = 2; i--;) VecSet(&w2, i, i + 1);
  for (int i = 3; i--;) VecSet(&w3, i, i + 1);
  for (int i = 4; i--;) VecSet(&w4, i, i + 1);
  if (!VecIsEqual(v, w)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v2, &w2)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v3, &w3)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v4, &w4)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  VecFree(&w);
  printf("UnitTestVecLongIsEqual OK\n");
}

void UnitTestVecLongCopy() {
  VecLong* v = VecLongCreate(5);
  VecLong2D v2 = VecLongCreateStatic2D();
  VecLong3D v3 = VecLongCreateStatic3D();
  VecLong4D v4 = VecLongCreateStatic4D();
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  for (int i = 2; i--;) VecSet(&v2, i, i + 1);
  for (int i = 3; i--;) VecSet(&v3, i, i + 1);
  for (int i = 4; i--;) VecSet(&v4, i, i + 1);
  VecLong* w = VecLongCreate(5);
  VecLong2D w2 = VecLongCreateStatic2D();
  VecLong3D w3 = VecLongCreateStatic3D();
  VecLong4D w4 = VecLongCreateStatic4D();
  VecCopy(w, v);
  VecCopy(&w2, &v2);
  VecCopy(&w3, &v3);
  VecCopy(&w4, &v4);
  if (!VecIsEqual(v, w)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongCopy NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v2, &w2)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongCopy NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v3, &w3)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongCopy NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v4, &w4)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongCopy NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  VecFree(&w);
  printf("UnitTestVecLongCopy OK\n");
}

void UnitTestVecLongDotProd() {
  VecLong* v = VecLongCreate(5);
  VecLong2D v2 = VecLongCreateStatic2D();
  VecLong3D v3 = VecLongCreateStatic3D();
  VecLong4D v4 = VecLongCreateStatic4D();
  VecLong* w = VecLongCreate(5);
  VecLong2D w2 = VecLongCreateStatic2D();
  VecLong3D w3 = VecLongCreateStatic3D();
  VecLong4D w4 = VecLongCreateStatic4D();
  long b[5] = {-2, -1, 0, 1, 2};
  for (int i = 5; i--;) VecSet(v, i, b[i]);
  for (int i = 2; i--;) VecSet(&v2, i, b[i]);
  for (int i = 3; i--;) VecSet(&v3, i, b[i]);
  for (int i = 4; i--;) VecSet(&v4, i, b[i]);
  for (int i = 5; i--;) VecSet(w, i, b[4 - i] + 1);
  for (int i = 2; i--;) VecSet(&w2, i, b[1 - i] + 1);
  for (int i = 3; i--;) VecSet(&w3, i, b[2 - i] + 1);
  for (int i = 4; i--;) VecSet(&w4, i, b[3 - i] + 1);
  long prod = VecDotProd(v, w);
  if (prod != -10) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongDotProd NOK");
    PBErrCatch(PBMathErr);
  }
  prod = VecDotProd(&v2, &w2);
  if (prod != 1) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongDotProd NOK");
    PBErrCatch(PBMathErr);
  }
  prod = VecDotProd(&v3, &w3);
  if (prod != -2) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongDotProd NOK");
    PBErrCatch(PBMathErr);
  }
  prod = VecDotProd(&v4, &w4);
  if (prod != -6) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongDotProd NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  VecFree(&w);
  printf("UnitTestVecLongDotProd OK\n");
}

void UnitTestSpeedVecLong() {
  VecLong* v = VecLongCreate(5);
  VecLong2D v2 = VecLongCreateStatic2D();
  VecLong3D v3 = VecLongCreateStatic3D();
  VecLong4D v4 = VecLongCreateStatic4D();
  int nbTest = 100000;

  srandom(RANDOMSEED);
  int i = nbTest;
  clock_t clockBefore = clock();
  for (; i--;) {
    int j = INT(rnd() * ((float)(VecGetDim(v) - 1) - PBMATH_EPSILON));
    long val = 1;
    VecSet(v, j, val);
    long valb = VecGet(v, j);
    valb = valb;
  }
  clock_t clockAfter = clock();
  double timeV = ((double)(clockAfter - clockBefore)) / 
    CLOCKS_PER_SEC * 1000.0;
  srandom(RANDOMSEED);
  i = nbTest;
  clockBefore = clock();
  long* array = malloc(sizeof(long) * 5);
  for (; i--;) {
    int j = INT(rnd() * ((float)(VecGetDim(v) - 1) - PBMATH_EPSILON));
    long val = 1;
    array[j] = val;
    long valb = array[j];
    valb = valb;
  }
  clockAfter = clock();
  double timeRef = ((double)(clockAfter - clockBefore)) / 
    CLOCKS_PER_SEC * 1000.0;
  printf("VecLong: %fms, array: %fms\n", 
    timeV / (float)nbTest, timeRef / (float)nbTest);
  if (timeV / (float)nbTest > 2.0 * timeRef / (float)nbTest) {
#if BUILDMODE == 0 
    PBMathErr->_fatal = false;
#endif
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "UnitTestSpeedVecLong NOK");
    PBErrCatch(PBMathErr);
  }

  srandom(RANDOMSEED);
  i = nbTest;
  clockBefore = clock();
  for (; i--;) {
    int j = INT(rnd() * (1.0 - PBMATH_EPSILON));
    long val = 1;
    VecSet(&v2, j, val);
    long valb = VecGet(&v2, j);
    valb = valb;
  }
  clockAfter = clock();
  timeV = ((double)(clockAfter - clockBefore)) / 
    CLOCKS_PER_SEC * 1000.0;
  srandom(RANDOMSEED);
  i = nbTest;
  clockBefore = clock();
  long array2[2];
  for (; i--;) {
    int j = INT(rnd() * (1.0 - PBMATH_EPSILON));
    long val = 1;
    array2[j] = val;
    long valb = array2[j];
    valb = valb;
  }
  clockAfter = clock();
  timeRef = ((double)(clockAfter - clockBefore)) / 
    CLOCKS_PER_SEC * 1000.0;
  printf("VecLong2D: %fms, array: %fms\n", 
    timeV / (float)nbTest, timeRef / (float)nbTest);
  if (timeV / (float)nbTest > 2.0 * timeRef / (float)nbTest) {
#if BUILDMODE == 0 
    PBMathErr->_fatal = false;
#endif
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "UnitTestSpeedVecLong NOK");
    PBErrCatch(PBMathErr);
  }

  srandom(RANDOMSEED);
  i = nbTest;
  clockBefore = clock();
  for (; i--;) {
    int j = INT(rnd() * (2.0 - PBMATH_EPSILON));
    long val = 1;
    VecSet(&v3, j, val);
    long valb = VecGet(&v3, j);
    valb = valb;
  }
  clockAfter = clock();
  timeV = ((double)(clockAfter - clockBefore)) / 
    CLOCKS_PER_SEC * 1000.0;
  srandom(RANDOMSEED);
  i = nbTest;
  clockBefore = clock();
  long array3[3];
  for (; i--;) {
    int j = INT(rnd() * (2.0 - PBMATH_EPSILON));
    long val = 1;
    array3[j] = val;
    long valb = array3[j];
    valb = valb;
  }
  clockAfter = clock();
  timeRef = ((double)(clockAfter - clockBefore)) / 
    CLOCKS_PER_SEC * 1000.0;
  printf("VecLong3D: %fms, array: %fms\n", 
    timeV / (float)nbTest, timeRef / (float)nbTest);
  if (timeV / (float)nbTest > 2.0 * timeRef / (float)nbTest) {
#if BUILDMODE == 0 
    PBMathErr->_fatal = false;
#endif
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "UnitTestSpeedVecLong NOK");
    PBErrCatch(PBMathErr);
  }

  srandom(RANDOMSEED);
  i = nbTest;
  clockBefore = clock();
  for (; i--;) {
    int j = INT(rnd() * (3.0 - PBMATH_EPSILON));
    long val = 1;
    VecSet(&v4, j, val);
    long valb = VecGet(&v4, j);
    valb = valb;
  }
  clockAfter = clock();
  timeV = ((double)(clockAfter - clockBefore)) / 
    CLOCKS_PER_SEC * 1000.0;
  srandom(RANDOMSEED);
  i = nbTest;
  clockBefore = clock();
  long array4[4];
  for (; i--;) {
    int j = INT(rnd() * (3.0 - PBMATH_EPSILON));
    long val = 1;
    array4[j] = val;
    long valb = array4[j];
    valb = valb;
  }
  clockAfter = clock();
  timeRef = ((double)(clockAfter - clockBefore)) / 
    CLOCKS_PER_SEC * 1000.0;
  printf("VecLong4D: %fms, array: %fms\n", 
    timeV / (float)nbTest, timeRef / (float)nbTest);
  if (timeV / (float)nbTest > 2.0 * timeRef / (float)nbTest) {
#if BUILDMODE == 0 
    PBMathErr->_fatal = false;
#endif
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "UnitTestSpeedVecLong NOK");
    PBErrCatch(PBMathErr);
  }

  VecFree(&v);
  free(array);
  printf("UnitTestSpeedVecLong OK\n");
}

void UnitTestVecLongOp() {
  VecLong* v = VecLongCreate(5);
  VecLong2D v2 = VecLongCreateStatic2D();
  VecLong3D v3 = VecLongCreateStatic3D();
  VecLong4D v4 = VecLongCreateStatic4D();
  VecLong* w = VecLongCreate(5);
  VecLong2D w2 = VecLongCreateStatic2D();
  VecLong3D w3 = VecLongCreateStatic3D();
  VecLong4D w4 = VecLongCreateStatic4D();
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  for (int i = 2; i--;) VecSet(&v2, i, i + 1);
  for (int i = 3; i--;) VecSet(&v3, i, i + 1);
  long a[2] = {-1, 2};
  long b[5] = {-2, -1, 0, 1, 2};
  for (int i = 5; i--;) VecSet(v, i, b[i]);
  for (int i = 2; i--;) VecSet(&v2, i, b[i]);
  for (int i = 3; i--;) VecSet(&v3, i, b[i]);
  for (int i = 4; i--;) VecSet(&v4, i, b[i]);
  for (int i = 5; i--;) VecSet(w, i, b[4 - i] + 1);
  for (int i = 2; i--;) VecSet(&w2, i, b[1 - i] + 1);
  for (int i = 3; i--;) VecSet(&w3, i, b[2 - i] + 1);
  for (int i = 4; i--;) VecSet(&w4, i, b[3 - i] + 1);
  VecLong* u = VecGetOp(v, a[0], w, a[1]);
  VecLong2D u2 = VecGetOp(&v2, a[0], &w2, a[1]);
  VecLong3D u3 = VecGetOp(&v3, a[0], &w3, a[1]);
  VecLong4D u4 = VecGetOp(&v4, a[0], &w4, a[1]);
  long checku[5] = {8,5,2,-1,-4};
  long checku2[2] = {2,-1};
  long checku3[3] = {4,1,-2};
  long checku4[4] = {6,3,0,-3};
  for (int i = 5; i--;)
    if (!ISEQUALF(VecGet(u, i), checku[i])) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecLongGetOp NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 2; i--;)
    if (!ISEQUALF(VecGet(&u2, i), checku2[i])) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecLongGetOp NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 3; i--;)
    if (!ISEQUALF(VecGet(&u3, i), checku3[i])) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecLongGetOp NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 4; i--;)
    if (!ISEQUALF(VecGet(&u4, i), checku4[i])) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecLongGetOp NOK");
      PBErrCatch(PBMathErr);
    }
  VecOp(v, a[0], w, a[1]);
  VecOp(&v2, a[0], &w2, a[1]);
  VecOp(&v3, a[0], &w3, a[1]);
  VecOp(&v4, a[0], &w4, a[1]);
  if (!VecIsEqual(v, u)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongOp NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v2, &u2)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongOp NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v3, &u3)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongOp NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v4, &u4)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecLongOp NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  VecFree(&w);
  VecFree(&u);
  printf("UnitTestVecLongOp OK\n");
}

void UnitTestVecLongShiftStep() {
  VecLong3D v = VecLongCreateStatic3D();
  VecLong3D from = VecLongCreateStatic3D();
  VecLong3D to = VecLongCreateStatic3D();
  VecSet(&from, 0, 0);
  VecSet(&from, 1, 1);
  VecSet(&from, 2, 2);
  VecSet(&to, 0, 3);
  VecSet(&to, 1, 4);
  VecSet(&to, 2, 5);
  VecCopy(&v, &from);
  long check[81] = {
    0, 1, 2, 0, 1, 3, 0, 1, 4,
    0, 2, 2, 0, 2, 3, 0, 2, 4,
    0, 3, 2, 0, 3, 3, 0, 3, 4,
    1, 1, 2, 1, 1, 3, 1, 1, 4,
    1, 2, 2, 1, 2, 3, 1, 2, 4,
    1, 3, 2, 1, 3, 3, 1, 3, 4,
    2, 1, 2, 2, 1, 3, 2, 1, 4,
    2, 2, 2, 2, 2, 3, 2, 2, 4,
    2, 3, 2, 2, 3, 3, 2, 3, 4
    };
  int iCheck = 0;
  do {
    for (int i = 0; i < 3; ++i) {
      if (ISEQUALF(check[iCheck], VecGet(&v, i)) == false) {
        PBMathErr->_type = PBErrTypeUnitTestFailed;
        sprintf(PBMathErr->_msg, "VecShiftStep NOK");
        PBErrCatch(PBMathErr);
      }
      ++iCheck;
    }
  } while(VecShiftStep(&v, &from, &to));
  printf("UnitTestVecLongShiftStep OK\n");
}

void UnitTestVecLongGetMinMax() {
  VecLong3D v = VecLongCreateStatic3D();
  VecSet(&v, 0, 2); VecSet(&v, 1, 4); VecSet(&v, 2, 3);
  long val = VecGetMaxVal(&v);
  if (val != 4) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecGetMaxVal NOK");
    PBErrCatch(PBMathErr);
  }
  if (VecGetIMaxVal(&v) != 1) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecGetIMaxVal NOK");
    PBErrCatch(PBMathErr);
  }
  VecSet(&v, 0, 2); VecSet(&v, 1, 1); VecSet(&v, 2, 3);
  val = VecGetMinVal(&v);
  if (val != 1) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecGetMinVal NOK");
    PBErrCatch(PBMathErr);
  }
  VecSet(&v, 0, 2); VecSet(&v, 1, -4); VecSet(&v, 2, 3);
  val = VecGetMaxValAbs(&v);
  if (val != -4) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecGetMaxValAbs NOK");
    PBErrCatch(PBMathErr);
  }
  VecSet(&v, 0, -2); VecSet(&v, 1, 1); VecSet(&v, 2, 3);
  val = VecGetMinValAbs(&v);
  if (val != 1) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecGetMinValAbs NOK");
    PBErrCatch(PBMathErr);
  }
  printf("UnitTestVecLongGetMinMax OK\n");
}

void UnitTestVecLongHadamardProd() {
  VecLong* u = VecLongCreate(3);
  for (int i = 3; i--;)
    VecSet(u, i, i + 2);
  VecLong* uprod = VecGetHadamardProd(u, u);
  VecHadamardProd(u, u);
  long checku[3] = {4, 9, 16};
  for (int i = 3; i--;)
    if (ISEQUALF(VecGet(uprod, i), checku[i]) == false) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecGetHadamardProd NOK");
      PBErrCatch(PBMathErr);
    }
  if (VecIsEqual(uprod, u) == false) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecHadamardProd NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&uprod);
  VecFree(&u);
  VecLong2D v = VecLongCreateStatic2D();
  for (int i = 2; i--;)
    VecSet(&v, i, i + 2);
  VecLong2D vprod = VecGetHadamardProd(&v, &v);
  VecHadamardProd(&v, &v);
  long checkv[2] = {4, 9};
  for (int i = 2; i--;)
    if (ISEQUALF(VecGet(&vprod, i), checkv[i]) == false) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecGetHadamardProd NOK");
      PBErrCatch(PBMathErr);
    }
  if (VecIsEqual(&vprod, &v) == false) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecHadamardProd NOK");
    PBErrCatch(PBMathErr);
  }
  VecLong3D w = VecLongCreateStatic3D();
  for (int i = 3; i--;)
    VecSet(&w, i, i + 2);
  VecLong3D wprod = VecGetHadamardProd(&w, &w);
  VecHadamardProd(&w, &w);
  long checkw[3] = {4, 9, 16};
  for (int i = 3; i--;)
    if (ISEQUALF(VecGet(&wprod, i), checkw[i]) == false) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecGetHadamardProd NOK");
      PBErrCatch(PBMathErr);
    }
  if (VecIsEqual(&wprod, &w) == false) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecHadamardProd NOK");
    PBErrCatch(PBMathErr);
  }
  VecLong4D x = VecLongCreateStatic4D();
  for (int i = 4; i--;)
    VecSet(&x, i, i + 2);
  VecLong4D xprod = VecGetHadamardProd(&x, &x);
  VecHadamardProd(&x, &x);
  long checkx[4] = {4, 9, 16, 25};
  for (int i = 4; i--;)
    if (ISEQUALF(VecGet(&xprod, i), checkx[i]) == false) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecGetHadamardProd NOK");
      PBErrCatch(PBMathErr);
    }
  if (VecIsEqual(&xprod, &x) == false) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecHadamardProd NOK");
    PBErrCatch(PBMathErr);
  }
  printf("UnitTestVecLongHadamardProd OK\n");
}

void UnitTestVecLong() {
  UnitTestVecLongCreateFree();
  UnitTestVecLongClone();
  UnitTestVecLongLoadSave();
  UnitTestVecLongGetSetDim();
  UnitTestVecLongStep();
  UnitTestVecLongHamiltonDist();
  UnitTestVecLongIsEqual();
  UnitTestVecLongDotProd();
  UnitTestVecLongCopy();
  UnitTestSpeedVecLong();
  UnitTestVecLongOp();
  UnitTestVecLongShiftStep();
  UnitTestVecLongGetMinMax();
  UnitTestVecLongHadamardProd();
  printf("UnitTestVecLong OK\n");
}

void UnitTestVecFloatCreateFree() {
  VecFloat* v = VecFloatCreate(5);
  VecFloat2D v2 = VecFloatCreateStatic2D();
  VecFloat3D v3 = VecFloatCreateStatic3D();
  VecPrint(v, stdout);printf("\n");
  VecPrint(&v2, stdout);printf("\n");
  VecPrint(&v3, stdout);printf("\n");
  _VecFloatFree(&v);
  if (v != NULL) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloat is not null after _VecFloatFree");
    PBErrCatch(PBMathErr);
  }
  printf("VecFloatCreateFree OK\n");
}

void UnitTestVecFloatClone() {
  VecFloat* v = VecFloatCreate(5);
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  VecFloat* w = VecClone(v);
  if (memcmp(v, w, sizeof(VecFloat) + sizeof(float) * 5) != 0) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatClone NOK");
    PBErrCatch(PBMathErr);
  }
  _VecFloatFree(&v);
  _VecFloatFree(&w);
  printf("_VecFloatClone OK\n");
}

void UnitTestVecFloatLoadSave() {
  VecFloat* v = VecFloatCreate(5);
  VecFloat2D v2 = VecFloatCreateStatic2D();
  VecFloat3D v3 = VecFloatCreateStatic3D();
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  for (int i = 2; i--;) VecSet(&v2, i, i + 1);
  for (int i = 3; i--;) VecSet(&v3, i, i + 1);
  FILE* f = fopen("./UnitTestVecFloatLoadSave.txt", "w");
  if (f == NULL) {
    PBMathErr->_type = PBErrTypeOther;
    sprintf(PBMathErr->_msg, 
      "Can't open ./UnitTestVecFloatLoadSave.txt for writing");
    PBErrCatch(PBMathErr);
  }
  bool compact = false;
  if (!VecSave(v, f, compact)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatSave NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecSave(&v2, f, compact)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatSave NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecSave(&v3, f, compact)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatSave NOK");
    PBErrCatch(PBMathErr);
  }
  fclose(f);
  VecFloat* w = VecFloatCreate(2);
  f = fopen("./UnitTestVecFloatLoadSave.txt", "r");
  if (f == NULL) {
    PBMathErr->_type = PBErrTypeOther;
    sprintf(PBMathErr->_msg, 
      "Can't open ./UnitTestVecFloatLoadSave.txt for reading");
    PBErrCatch(PBMathErr);
  }
  if (!VecLoad(&w, f)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatLoad NOK");
    PBErrCatch(PBMathErr);
  }
  if (memcmp(v, w, sizeof(VecFloat) + sizeof(float) * 5) != 0) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatLoadSave NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecLoad(&w, f)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatLoad NOK");
    PBErrCatch(PBMathErr);
  }
  if (memcmp(&v2, w, sizeof(VecFloat) + sizeof(float) * 2) != 0) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatLoadSave NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecLoad(&w, f)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatLoad NOK");
    PBErrCatch(PBMathErr);
  }
  if (memcmp(&v3, w, sizeof(VecFloat) + sizeof(float) * 3) != 0) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatLoadSave NOK");
    PBErrCatch(PBMathErr);
  }
  fclose(f);
  VecFree(&v);
  VecFree(&w);
  int ret = system("cat ./UnitTestVecFloatLoadSave.txt");
  printf("_VecFloatLoadSave OK\n");
  ret = ret;
}

void UnitTestVecFloatGetSetDim() {
  VecFloat* v = VecFloatCreate(5);
  VecFloat2D v2 = VecFloatCreateStatic2D();
  VecFloat3D v3 = VecFloatCreateStatic3D();
  if (VecGetDim(v) != 5) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatGetDim NOK");
    PBErrCatch(PBMathErr);
  }
  for (int i = 5; i--;) VecSet(v, i, (float)(i + 1));
  for (int i = 2; i--;) VecSet(&v2, i, (float)(i + 1));
  for (int i = 3; i--;) VecSet(&v3, i, (float)(i + 1));
  for (int i = 5; i--;)
    if (!ISEQUALF(v->_val[i], (float)(i + 1))) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecFloatSet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 2; i--;)
    if (!ISEQUALF(v2._val[i], (float)(i + 1))) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecFloatSet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 3; i--;)
    if (!ISEQUALF(v3._val[i], (float)(i + 1))) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecFloatSet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 5; i--;)
    if (!ISEQUALF(VecGet(v, i), (float)(i + 1))) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecFloatGet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 2; i--;)
    if (!ISEQUALF(VecGet(&v2, i), (float)(i + 1))) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecFloatGet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 3; i--;)
    if (!ISEQUALF(VecGet(&v3, i), (float)(i + 1))) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecFloatGet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 5; i--;) VecSetAdd(v, i, (float)(i + 1));
  for (int i = 2; i--;) VecSetAdd(&v2, i, (float)(i + 1));
  for (int i = 3; i--;) VecSetAdd(&v3, i, (float)(i + 1));
  for (int i = 5; i--;)
    if (!ISEQUALF(VecGet(v, i), 2.0 * (float)(i + 1))) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecFloatSetAdd NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 2; i--;)
    if (!ISEQUALF(VecGet(&v2, i), 2.0 * (float)(i + 1))) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecFloatSetAdd NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 3; i--;)
    if (!ISEQUALF(VecGet(&v3, i), 2.0 * (float)(i + 1))) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecFloatSetAdd NOK");
      PBErrCatch(PBMathErr);
    }
  VecSetNull(v);
  VecSetNull(&v2);
  VecSetNull(&v3);
  for (int i = 5; i--;)
    if (!ISEQUALF(VecGet(v, i), 0.0)) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecFloatGet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 2; i--;)
    if (!ISEQUALF(VecGet(&v2, i), 0.0)) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecFloatGet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 3; i--;)
    if (!ISEQUALF(VecGet(&v3, i), 0.0)) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecFloatGet NOK");
      PBErrCatch(PBMathErr);
    }
  VecFree(&v);
  printf("_VecFloatGetSetDim OK\n");
}

void UnitTestVecFloatCopy() {
  VecFloat* v = VecFloatCreate(5);
  VecFloat2D v2 = VecFloatCreateStatic2D();
  VecFloat3D v3 = VecFloatCreateStatic3D();
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  for (int i = 2; i--;) VecSet(&v2, i, i + 1);
  for (int i = 3; i--;) VecSet(&v3, i, i + 1);
  VecFloat* w = VecFloatCreate(5);
  VecFloat2D w2 = VecFloatCreateStatic2D();
  VecFloat3D w3 = VecFloatCreateStatic3D();
  VecCopy(w, v);
  VecCopy(&w2, &v2);
  VecCopy(&w3, &v3);
  if (!VecIsEqual(v, w)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatCopy NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v2, &w2)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatCopy NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v3, &w3)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatCopy NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  VecFree(&w);
  printf("UnitTestVecFloatCopy OK\n");
}

void UnitTestVecFloatNorm() {
  VecFloat* v = VecFloatCreate(5);
  VecFloat2D v2 = VecFloatCreateStatic2D();
  VecFloat3D v3 = VecFloatCreateStatic3D();
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  for (int i = 2; i--;) VecSet(&v2, i, i + 1);
  for (int i = 3; i--;) VecSet(&v3, i, i + 1);
  if (!ISEQUALF(VecNorm(v), 7.416198)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatNorm NOK");
    PBErrCatch(PBMathErr);
  }
  if (!ISEQUALF(VecNorm(&v2), 2.236068)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatNorm NOK");
    PBErrCatch(PBMathErr);
  }
  if (!ISEQUALF(VecNorm(&v3), 3.741657)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatNorm NOK");
    PBErrCatch(PBMathErr);
  }
  VecNormalise(v);
  VecNormalise(&v2);
  VecNormalise(&v3);
  if (!ISEQUALF(VecNorm(v), 1.0)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatNormalise NOK");
    PBErrCatch(PBMathErr);
  }
  if (!ISEQUALF(VecNorm(&v2), 1.0)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatNormalise NOK");
    PBErrCatch(PBMathErr);
  }
  if (!ISEQUALF(VecNorm(&v3), 1.0)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatNormalise NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  printf("UnitTestVecFloatNorm OK\n");
}

void UnitTestVecFloatDist() {
  VecFloat* v = VecFloatCreate(5);
  VecFloat2D v2 = VecFloatCreateStatic2D();
  VecFloat3D v3 = VecFloatCreateStatic3D();
  VecFloat* w = VecFloatCreate(5);
  VecFloat2D w2 = VecFloatCreateStatic2D();
  VecFloat3D w3 = VecFloatCreateStatic3D();
  float b[5] = {-2.0, -1.0, 0.0, 1.0, 2.0};
  for (int i = 5; i--;) VecSet(v, i, b[i]);
  for (int i = 2; i--;) VecSet(&v2, i, b[i]);
  for (int i = 3; i--;) VecSet(&v3, i, b[i]);
  for (int i = 5; i--;) VecSet(w, i, b[4 - i] + 1.5);
  for (int i = 2; i--;) VecSet(&w2, i, b[1 - i] + 1.5);
  for (int i = 3; i--;) VecSet(&w3, i, b[2 - i] + 1.5);
  if (!ISEQUALF(VecDist(v, w), 7.158911)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatDist NOK");
    PBErrCatch(PBMathErr);
  }
  if (!ISEQUALF(VecDist(&v2, &w2), 2.549510)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatDist NOK");
    PBErrCatch(PBMathErr);
  }
  if (!ISEQUALF(VecDist(&v3, &w3), 3.840573)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatDist NOK");
    PBErrCatch(PBMathErr);
  }
  if (!ISEQUALF(VecHamiltonDist(v, w), 13.5)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatHamiltonDist NOK");
    PBErrCatch(PBMathErr);
  }
  if (!ISEQUALF(VecHamiltonDist(&v2, &w2), 3.0)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatHamiltonDist NOK");
    PBErrCatch(PBMathErr);
  }
  if (!ISEQUALF(VecHamiltonDist(&v3, &w3), 5.5)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatHamiltonDist NOK");
    PBErrCatch(PBMathErr);
  }
  if (!ISEQUALF(VecPixelDist(v, w), 13.0)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatPixelDist NOK");
    PBErrCatch(PBMathErr);
  }
  if (!ISEQUALF(VecPixelDist(&v2, &w2), 2.0)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatPixelDist NOK");
    PBErrCatch(PBMathErr);
  }
  if (!ISEQUALF(VecPixelDist(&v3, &w3), 5.0)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatPixelDist NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  VecFree(&w);
  printf("UnitTestVecFloatDist OK\n");
}

void UnitTestVecFloatIsEqual() {
  VecFloat* v = VecFloatCreate(5);
  VecFloat2D v2 = VecFloatCreateStatic2D();
  VecFloat3D v3 = VecFloatCreateStatic3D();
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  for (int i = 2; i--;) VecSet(&v2, i, i + 1);
  for (int i = 3; i--;) VecSet(&v3, i, i + 1);
  VecFloat* w = VecFloatCreate(5);
  VecFloat2D w2 = VecFloatCreateStatic2D();
  VecFloat3D w3 = VecFloatCreateStatic3D();
  if (VecIsEqual(v, w)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  if (VecIsEqual(&v2, &w2)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  if (VecIsEqual(&v3, &w3)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  for (int i = 5; i--;) VecSet(w, i, i + 1);
  for (int i = 2; i--;) VecSet(&w2, i, i + 1);
  for (int i = 3; i--;) VecSet(&w3, i, i + 1);
  if (!VecIsEqual(v, w)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v2, &w2)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v3, &w3)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  VecFree(&w);
  printf("UnitTestVecFloatIsEqual OK\n");
}

void UnitTestVecFloatScale() {
  VecFloat* v = VecFloatCreate(5);
  VecFloat2D v2 = VecFloatCreateStatic2D();
  VecFloat3D v3 = VecFloatCreateStatic3D();
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  for (int i = 2; i--;) VecSet(&v2, i, i + 1);
  for (int i = 3; i--;) VecSet(&v3, i, i + 1);
  float a = 0.1;
  VecFloat* w = VecGetScale(v, a);
  VecFloat2D w2 = VecGetScale(&v2, a);
  VecFloat3D w3 = VecGetScale(&v3, a);
  VecScale(v, a);
  VecScale(&v2, a);
  VecScale(&v3, a);
  for (int i = 5; i--;)
    if (!ISEQUALF(VecGet(w, i), (float)(i + 1) * a)) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecFloatGetScale NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 2; i--;)
    if (!ISEQUALF(VecGet(&w2, i), (float)(i + 1) * a)) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecFloatGetScale NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 3; i--;)
    if (!ISEQUALF(VecGet(&w3, i), (float)(i + 1) * a)) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecFloatGetScale NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 5; i--;)
    if (!ISEQUALF(VecGet(v, i), (float)(i + 1) * a)) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecFloatScale NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 2; i--;)
    if (!ISEQUALF(VecGet(&v2, i), (float)(i + 1) * a)) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecFloatScale NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 3; i--;)
    if (!ISEQUALF(VecGet(&v3, i), (float)(i + 1) * a)) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecFloatScale NOK");
      PBErrCatch(PBMathErr);
    }
  VecFree(&v);
  VecFree(&w);
  printf("UnitTestVecFloatScale OK\n");
}

void UnitTestVecFloatOp() {
  VecFloat* v = VecFloatCreate(5);
  VecFloat2D v2 = VecFloatCreateStatic2D();
  VecFloat3D v3 = VecFloatCreateStatic3D();
  VecFloat* w = VecFloatCreate(5);
  VecFloat2D w2 = VecFloatCreateStatic2D();
  VecFloat3D w3 = VecFloatCreateStatic3D();
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  for (int i = 2; i--;) VecSet(&v2, i, i + 1);
  for (int i = 3; i--;) VecSet(&v3, i, i + 1);
  float a[2] = {-0.1, 2.0};
  float b[5] = {-2.0, -1.0, 0.0, 1.0, 2.0};
  for (int i = 5; i--;) VecSet(v, i, b[i]);
  for (int i = 2; i--;) VecSet(&v2, i, b[i]);
  for (int i = 3; i--;) VecSet(&v3, i, b[i]);
  for (int i = 5; i--;) VecSet(w, i, b[4 - i] + 0.5);
  for (int i = 2; i--;) VecSet(&w2, i, b[1 - i] + 0.5);
  for (int i = 3; i--;) VecSet(&w3, i, b[2 - i] + 0.5);
  VecFloat* u = VecGetOp(v, a[0], w, a[1]);
  VecFloat2D u2 = VecGetOp(&v2, a[0], &w2, a[1]);
  VecFloat3D u3 = VecGetOp(&v3, a[0], &w3, a[1]);
  float checku[5] = {5.2,3.1,1.0,-1.1,-3.2};
  float checku2[2] = {-0.8,-2.9};
  float checku3[3] = {1.2,-0.9,-3.0};
  for (int i = 5; i--;)
    if (!ISEQUALF(VecGet(u, i), checku[i])) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecFloatGetOp NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 2; i--;)
    if (!ISEQUALF(VecGet(&u2, i), checku2[i])) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecFloatGetOp NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 3; i--;)
    if (!ISEQUALF(VecGet(&u3, i), checku3[i])) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecFloatGetOp NOK");
      PBErrCatch(PBMathErr);
    }
  VecOp(v, a[0], w, a[1]);
  VecOp(&v2, a[0], &w2, a[1]);
  VecOp(&v3, a[0], &w3, a[1]);
  if (!VecIsEqual(v, u)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatOp NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v2, &u2)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatOp NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v3, &u3)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatOp NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  VecFree(&w);
  VecFree(&u);
  printf("UnitTestVecFloatOp OK\n");
}

void UnitTestVecFloatDotProd() {
  VecFloat* v = VecFloatCreate(5);
  VecFloat2D v2 = VecFloatCreateStatic2D();
  VecFloat3D v3 = VecFloatCreateStatic3D();
  VecFloat* w = VecFloatCreate(5);
  VecFloat2D w2 = VecFloatCreateStatic2D();
  VecFloat3D w3 = VecFloatCreateStatic3D();
  float b[5] = {-2.0, -1.0, 0.0, 1.0, 2.0};
  for (int i = 5; i--;) VecSet(v, i, b[i]);
  for (int i = 2; i--;) VecSet(&v2, i, b[i]);
  for (int i = 3; i--;) VecSet(&v3, i, b[i]);
  for (int i = 5; i--;) VecSet(w, i, b[4 - i] + 1.5);
  for (int i = 2; i--;) VecSet(&w2, i, b[1 - i] + 1.5);
  for (int i = 3; i--;) VecSet(&w3, i, b[2 - i] + 1.5);
  float prod = VecDotProd(v, w);
  if (!ISEQUALF(prod, -10.0)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatDotProd NOK");
    PBErrCatch(PBMathErr);
  }
  prod = VecDotProd(&v2, &w2);
  if (!ISEQUALF(prod, -0.5)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatDotProd NOK");
    PBErrCatch(PBMathErr);
  }
  prod = VecDotProd(&v3, &w3);
  if (!ISEQUALF(prod, -3.5)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatDotProd NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  VecFree(&w);
  printf("UnitTestVecFloatDotProd OK\n");
}

void UnitTestVecFloatCrossProd() {
  VecFloat* v = VecFloatCreate(3);
  VecFloat3D v3 = VecFloatCreateStatic3D();
  VecFloat* w = VecFloatCreate(3);
  VecFloat3D w3 = VecFloatCreateStatic3D();
  float a[3] = {3.0, -3.0, 1.0};
  float b[3] = {4.0, 9.0, 2.0};
  float c[3] = {-15.0, -2.0, 39.0};
  for (int i = 3; i--;) VecSet(v, i, a[i]);
  for (int i = 3; i--;) VecSet(&v3, i, a[i]);
  for (int i = 3; i--;) VecSet(w, i, b[i]);
  for (int i = 3; i--;) VecSet(&w3, i, b[i]);
  VecFloat* prod = VecCrossProd(v, w);
  for (int i = 3; i--;)
    if (!ISEQUALF(VecGet(prod, i), c[i])) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecFloatCrossProd NOK");
      PBErrCatch(PBMathErr);
    }
  VecFloat3D prod3 = VecCrossProd(&v3, &w3);
  for (int i = 3; i--;)
    if (!ISEQUALF(VecGet(&prod3, i), c[i])) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "_VecFloatCrossProd3D NOK");
      PBErrCatch(PBMathErr);
    }
  VecFree(&v);
  VecFree(&w);
  VecFree(&prod);
  printf("UnitTestVecFloatCrossProd OK\n");
}

void UnitTestVecFloatRotAngleTo() {
  VecFloat* v = VecFloatCreate(2);
  VecFloat2D v2 = VecFloatCreateStatic2D();
  VecFloat* w = VecFloatCreate(2);
  VecFloat2D w2 = VecFloatCreateStatic2D();
  VecSet(v, 0, 1.0);
  VecSet(&v2, 0, 1.0);
  VecSet(w, 0, 1.0);
  VecSet(&w2, 0, 1.0);
  float a = 0.0;
  float da = PBMATH_TWOPI_DIV_360;
  for (int i = 360; i--;) {
    VecRot(v, da);
    VecNormalise(v);
    VecRot(&v2, da);
    VecNormalise(&v2);
    a += da;
    if (ISEQUALF(a, PBMATH_PI)) {
      a = -PBMATH_PI;
      if (!ISEQUALF(fabs(VecAngleTo(w, v)), fabs(a))) {
        PBMathErr->_type = PBErrTypeUnitTestFailed;
        sprintf(PBMathErr->_msg, "_VecFloatAngleTo NOK");
        PBErrCatch(PBMathErr);
      }
      if (!ISEQUALF(fabs(VecAngleTo(&w2, &v2)), fabs(a))) {
        PBMathErr->_type = PBErrTypeUnitTestFailed;
        sprintf(PBMathErr->_msg, "_VecFloatAngleTo NOK");
        PBErrCatch(PBMathErr);
      }
    } else {
      if (!ISEQUALF(VecAngleTo(w, v), a)) {
        PBMathErr->_type = PBErrTypeUnitTestFailed;
        sprintf(PBMathErr->_msg, "_VecFloatAngleTo NOK");
        PBErrCatch(PBMathErr);
      }
      if (!ISEQUALF(VecAngleTo(&w2, &v2), a)) {
        PBMathErr->_type = PBErrTypeUnitTestFailed;
        sprintf(PBMathErr->_msg, "_VecFloatAngleTo NOK");
        PBErrCatch(PBMathErr);
      }
    }
  }
  VecSet(v, 0, 1.0);
  VecSet(v, 1, 0.0);
  VecRot(v, PBMATH_QUARTERPI);
  VecFloatPrint(v,stdout,6);printf("\n");
  if (!ISEQUALF(VecGet(v, 0), 0.707107) ||
    !ISEQUALF(VecGet(v, 1), 0.707107)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_VecFloatRot NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  VecFree(&w);
  printf("UnitTestVecFloatAngleTo OK\n");
}

void UnitTestVecFloatToShort() {
  VecFloat* v = VecFloatCreate(5);
  VecFloat2D v2 = VecFloatCreateStatic2D();
  VecFloat3D v3 = VecFloatCreateStatic3D();
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  for (int i = 2; i--;) VecSet(&v2, i, i + 1);
  for (int i = 3; i--;) VecSet(&v3, i, i + 1);
  VecShort* w = VecFloatToShort(v);
  VecShort2D w2 = VecFloatToShort2D(&v2);
  VecShort3D w3 = VecFloatToShort3D(&v3);
  VecPrint(w, stdout); printf("\n");
  VecPrint(&w2, stdout); printf("\n");
  VecPrint(&w3, stdout); printf("\n");
  VecFree(&v);
  VecFree(&w);
  printf("UnitTestVecFloatToShort OK\n");
}

void UnitTestSpeedVecFloat() {
  VecFloat* v = VecFloatCreate(5);
  VecFloat2D v2 = VecFloatCreateStatic2D();
  VecFloat3D v3 = VecFloatCreateStatic3D();
  int nbTest = 100000;

  srandom(RANDOMSEED);
  int i = nbTest;
  clock_t clockBefore = clock();
  for (; i--;) {
    int j = INT(rnd() * ((float)(VecGetDim(v) - 1) - PBMATH_EPSILON));
    float val = 1.0;
    VecSet(v, j, val);
    float valb = VecGet(v, j);
    valb = valb;
  }
  clock_t clockAfter = clock();
  double timeV = ((double)(clockAfter - clockBefore)) / 
    CLOCKS_PER_SEC * 1000.0;
  srandom(RANDOMSEED);
  i = nbTest;
  clockBefore = clock();
  float* array = malloc(sizeof(float) * 5);
  for (; i--;) {
    int j = INT(rnd() * ((float)(VecGetDim(v) - 1) - PBMATH_EPSILON));
    float val = 1.0;
    array[j] = val;
    float valb = array[j];
    valb = valb;
  }
  clockAfter = clock();
  double timeRef = ((double)(clockAfter - clockBefore)) / 
    CLOCKS_PER_SEC * 1000.0;
  printf("VecFloat: %fms, array: %fms\n", 
    timeV / (float)nbTest, timeRef / (float)nbTest);
  if (timeV / (float)nbTest > 2.0 * timeRef / (float)nbTest) {
#if BUILDMODE == 0 
    PBMathErr->_fatal = false;
#endif
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "UnitTestSpeedVecFloat NOK");
    PBErrCatch(PBMathErr);
  }

  srandom(RANDOMSEED);
  i = nbTest;
  clockBefore = clock();
  for (; i--;) {
    int j = INT(rnd() * (1.0 - PBMATH_EPSILON));
    float val = 1.0;
    VecSet(&v2, j, val);
    float valb = VecGet(&v2, j);
    valb = valb;
  }
  clockAfter = clock();
  timeV = ((double)(clockAfter - clockBefore)) / 
    CLOCKS_PER_SEC * 1000.0;
  srandom(RANDOMSEED);
  i = nbTest;
  clockBefore = clock();
  float array2[2];
  for (; i--;) {
    int j = INT(rnd() * (1.0 - PBMATH_EPSILON));
    float val = 1.0;
    array2[j] = val;
    float valb = array2[j];
    valb = valb;
  }
  clockAfter = clock();
  timeRef = ((double)(clockAfter - clockBefore)) / 
    CLOCKS_PER_SEC * 1000.0;
  printf("VecFloat2D: %fms, array: %fms\n", 
    timeV / (float)nbTest, timeRef / (float)nbTest);
  if (timeV / (float)nbTest > 2.0 * timeRef / (float)nbTest) {
#if BUILDMODE == 0 
    PBMathErr->_fatal = false;
#endif
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "UnitTestSpeedVecFloat NOK");
    PBErrCatch(PBMathErr);
  }

  srandom(RANDOMSEED);
  i = nbTest;
  clockBefore = clock();
  for (; i--;) {
    int j = INT(rnd() * (2.0 - PBMATH_EPSILON));
    float val = 1.0;
    VecSet(&v3, j, val);
    float valb = VecGet(&v3, j);
    valb = valb;
  }
  clockAfter = clock();
  timeV = ((double)(clockAfter - clockBefore)) / 
    CLOCKS_PER_SEC * 1000.0;
  srandom(RANDOMSEED);
  i = nbTest;
  clockBefore = clock();
  float array3[3];
  for (; i--;) {
    int j = INT(rnd() * (2.0 - PBMATH_EPSILON));
    float val = 1.0;
    array3[j] = val;
    float valb = array3[j];
    valb = valb;
  }
  clockAfter = clock();
  timeRef = ((double)(clockAfter - clockBefore)) / 
    CLOCKS_PER_SEC * 1000.0;
  printf("VecFloat3D: %fms, array: %fms\n", 
    timeV / (float)nbTest, timeRef / (float)nbTest);
  if (timeV / (float)nbTest > 2.0 * timeRef / (float)nbTest) {
#if BUILDMODE == 0 
    PBMathErr->_fatal = false;
#endif
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "UnitTestSpeedVecFloat NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  free(array);
  printf("UnitTestSpeedVecFloat OK\n");
}

void UnitTestVecFloatRotAxis() {
  VecFloat3D v = VecFloatCreateStatic3D();
  VecSet(&v, 0, 1.0); VecSet(&v, 1, 0.0); VecSet(&v, 2, 1.0); 
  VecFloat3D axis = VecFloatCreateStatic3D();
  VecSet(&axis, 0, 1.0); VecSet(&axis, 1, 1.0); VecSet(&axis, 2, 1.0); 
  VecNormalise(&axis);
  float theta = PBMATH_PI;
  VecRotAxis(&v, &axis, theta);
  if (!ISEQUALF(VecGet(&v, 0), 0.333333) ||
    !ISEQUALF(VecGet(&v, 1), 1.333333) ||
    !ISEQUALF(VecGet(&v, 2), 0.333333)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecRotAxis NOK");
    PBErrCatch(PBMathErr);
  }
  theta = PBMATH_HALFPI;
  VecRotAxis(&v, &axis, theta);
  if (!ISEQUALF(VecGet(&v, 0), 0.089316) ||
    !ISEQUALF(VecGet(&v, 1), 0.666666) ||
    !ISEQUALF(VecGet(&v, 2), 1.244017)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecRotAxis NOK");
    PBErrCatch(PBMathErr);
  }
  VecSet(&v, 0, 1.0); VecSet(&v, 1, 1.0); VecSet(&v, 2, 1.0); 
  theta = PBMATH_PI;
  VecRotX(&v, theta);
  if (!ISEQUALF(VecGet(&v, 0), 1.0) ||
    !ISEQUALF(VecGet(&v, 1), -1.0) ||
    !ISEQUALF(VecGet(&v, 2), -1.0)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecRotX NOK");
    PBErrCatch(PBMathErr);
  }
  VecSet(&v, 0, 1.0); VecSet(&v, 1, 1.0); VecSet(&v, 2, 1.0); 
  theta = PBMATH_PI;
  VecRotY(&v, theta);
  if (!ISEQUALF(VecGet(&v, 0), -1.0) ||
    !ISEQUALF(VecGet(&v, 1), 1.0) ||
    !ISEQUALF(VecGet(&v, 2), -1.0)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecRotY NOK");
    PBErrCatch(PBMathErr);
  }
  VecSet(&v, 0, 1.0); VecSet(&v, 1, 1.0); VecSet(&v, 2, 1.0); 
  theta = PBMATH_PI;
  VecRotZ(&v, theta);
  if (!ISEQUALF(VecGet(&v, 0), -1.0) ||
    !ISEQUALF(VecGet(&v, 1), -1.0) ||
    !ISEQUALF(VecGet(&v, 2), 1.0)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecRotZ NOK");
    PBErrCatch(PBMathErr);
  }
  printf("UnitTestVecFloatRotAxis OK\n");
}

void UnitTestVecFloatGetMinMax() {
  VecFloat2D v = VecFloatCreateStatic2D();
  VecSet(&v, 0, 1.0); VecSet(&v, 1, 2.0);
  float val = VecGetMaxVal(&v);
  if (ISEQUALF(val, 2.0) == false) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecGetMaxVal NOK");
    PBErrCatch(PBMathErr);
  }
  if (VecGetIMaxVal(&v) != 1) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecGetIMaxVal NOK");
    PBErrCatch(PBMathErr);
  }
  val = VecGetMinVal(&v);
  if (ISEQUALF(val, 1.0) == false) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecGetMinVal NOK");
    PBErrCatch(PBMathErr);
  }
  VecSet(&v, 0, 1.0); VecSet(&v, 1, -2.0);
  val = VecGetMaxValAbs(&v);
  if (ISEQUALF(val, -2.0) == false) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecGetMaxValAbs NOK");
    PBErrCatch(PBMathErr);
  }
  val = VecGetMinValAbs(&v);
  if (ISEQUALF(val, 1.0) == false) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecGetMinValAbs NOK");
    PBErrCatch(PBMathErr);
  }
  printf("UnitTestVecFloatGetMinMax OK\n");
}

void UnitTestVecFloatGetNewDim() {
  VecFloat* v = VecFloatCreate(3);
  for (int i = 3; i--;)
    VecSet(v, i, (float)i);
  VecFloat* u = VecGetNewDim(v, 2);
  if (VecGetDim(u) != 2 ||
    ISEQUALF(VecGet(u, 0), 0.0) == false ||
    ISEQUALF(VecGet(u, 1), 1.0) == false) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecGetNewDim NOK");
    PBErrCatch(PBMathErr);
  }
  VecFloat* w = VecGetNewDim(v, 4);
  if (VecGetDim(w) != 4 ||
    ISEQUALF(VecGet(w, 0), 0.0) == false ||
    ISEQUALF(VecGet(w, 1), 1.0) == false ||
    ISEQUALF(VecGet(w, 2), 2.0) == false ||
    ISEQUALF(VecGet(w, 3), 0.0) == false) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecGetNewDim NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  VecFree(&u);
  VecFree(&w);
  printf("UnitTestVecFloatGetNewDim OK\n");
}

void UnitTestVecFloatHadamardProd() {
  VecFloat* u = VecFloatCreate(3);
  for (int i = 3; i--;)
    VecSet(u, i, (float)i + 2.0);
  VecFloat* uprod = VecGetHadamardProd(u, u);
  VecHadamardProd(u, u);
  float checku[3] = {4.0, 9.0, 16.0};
  for (int i = 3; i--;)
    if (ISEQUALF(VecGet(uprod, i), checku[i]) == false) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecGetHadamardProd NOK");
      PBErrCatch(PBMathErr);
    }
  if (VecIsEqual(uprod, u) == false) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecHadamardProd NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&uprod);
  VecFree(&u);
  VecFloat2D v = VecFloatCreateStatic2D();
  for (int i = 2; i--;)
    VecSet(&v, i, (float)i + 2.0);
  VecFloat2D vprod = VecGetHadamardProd(&v, &v);
  VecHadamardProd(&v, &v);
  float checkv[2] = {4.0, 9.0};
  for (int i = 2; i--;)
    if (ISEQUALF(VecGet(&vprod, i), checkv[i]) == false) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecGetHadamardProd NOK");
      PBErrCatch(PBMathErr);
    }
  if (VecIsEqual(&vprod, &v) == false) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecHadamardProd NOK");
    PBErrCatch(PBMathErr);
  }
  VecFloat3D w = VecFloatCreateStatic3D();
  for (int i = 3; i--;)
    VecSet(&w, i, (float)i + 2.0);
  VecFloat3D wprod = VecGetHadamardProd(&w, &w);
  VecHadamardProd(&w, &w);
  float checkw[3] = {4.0, 9.0, 16.0};
  for (int i = 3; i--;)
    if (ISEQUALF(VecGet(&wprod, i), checkw[i]) == false) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecGetHadamardProd NOK");
      PBErrCatch(PBMathErr);
    }
  if (VecIsEqual(&wprod, &w) == false) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecHadamardProd NOK");
    PBErrCatch(PBMathErr);
  }
  printf("UnitTestVecFloatHadamardProd OK\n");
}

void UnitTestVecFloat() {
  UnitTestVecFloatCreateFree();
  UnitTestVecFloatClone();
  UnitTestVecFloatLoadSave();
  UnitTestVecFloatGetSetDim();
  UnitTestVecFloatCopy();
  UnitTestVecFloatNorm();
  UnitTestVecFloatDist();
  UnitTestVecFloatIsEqual();
  UnitTestVecFloatScale();
  UnitTestVecFloatOp();
  UnitTestVecFloatDotProd();
  UnitTestVecFloatCrossProd();
  UnitTestVecFloatRotAngleTo();
  UnitTestVecFloatToShort();
  UnitTestVecFloatGetMinMax();
  UnitTestVecFloatRotAxis();
  UnitTestVecFloatGetNewDim();
  UnitTestVecFloatHadamardProd();
  UnitTestSpeedVecFloat();
  printf("UnitTestVecFloat OK\n");
}

void UnitTestMatFloatCreateFree() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 2);
  VecSet(&dim, 1, 3);
  MatFloat* mat = MatFloatCreate(&dim);
  for (int i = VecGet(&dim, 0) * VecGet(&dim, 1);i--;) {
    if (!ISEQUALF(mat->_val[i], 0.0)) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "UnitTestMatFloatCreateFree NOK");
      PBErrCatch(PBMathErr);
    }
  }
  MatFree(&mat);
  if (mat != NULL) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "mat is not null after MatFree");
    PBErrCatch(PBMathErr);
  }
  printf("UnitTestMatFloatCreateFree OK\n");
}

void UnitTestMatFloatGetSetDim() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 2);
  VecSet(&dim, 1, 3);
  MatFloat* mat = MatFloatCreate(&dim);
  if (!VecIsEqual(&(mat->_dim), &dim)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "UnitTestMatFloatGetSetDim NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(MatDim(mat), &dim)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "UnitTestMatFloatGetSetDim NOK");
    PBErrCatch(PBMathErr);
  }
  if (MatGetNbRow(mat) != 3) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "MatGetNbRow NOK");
    PBErrCatch(PBMathErr);
  }
  if (MatGetNbCol(mat) != 2) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "MatGetNbCol NOK");
    PBErrCatch(PBMathErr);
  }
  VecShort2D i = VecShortCreateStatic2D();
  float v = 1.0;
  do {
    MatSet(mat, &i, v);
    v += 1.0;
  } while(VecStep(&i, &dim));
  v = 1.0;
  for (int j = 0; j < VecGet(&dim, 0); ++j) {
    for (int k = 0; k < VecGet(&dim, 1); ++k) {
      if (!ISEQUALF(mat->_val[k * VecGet(&dim, 0) + j], v)) {
        PBMathErr->_type = PBErrTypeUnitTestFailed;
        sprintf(PBMathErr->_msg, "UnitTestMatFloatGetSetDim NOK");
        PBErrCatch(PBMathErr);
      }
      v += 1.0;
    }
  }
  VecSetNull(&i);
  v = 1.0;
  do {
    float w = MatGet(mat, &i);
    if (!ISEQUALF(v, w)) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "UnitTestMatFloatGetSetDim NOK");
      PBErrCatch(PBMathErr);
    }
    v += 1.0;
  } while(VecStep(&i, &dim));
  MatFree(&mat);
  printf("UnitTestMatFloatGetSetDim OK\n");
}

void UnitTestMatFloatCloneIsEqual() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 2);
  VecSet(&dim, 1, 3);
  MatFloat* mat = MatFloatCreate(&dim);
  VecShort2D i = VecShortCreateStatic2D();
  float v = 1.0;
  do {
    MatSet(mat, &i, v);
    v += 1.0;
  } while(VecStep(&i, &dim));
  MatFloat* clone = MatClone(mat);
  if (!VecIsEqual(&(mat->_dim), &(clone->_dim))) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "UnitTestMatFloatClone NOK");
    PBErrCatch(PBMathErr);
  }
  VecSetNull(&i);
  do {
    if (!ISEQUALF(MatGet(mat, &i), MatGet(clone, &i))) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "UnitTestMatFloatClone NOK");
      PBErrCatch(PBMathErr);
    }
  } while(VecStep(&i, &dim));
  if (MatIsEqual(mat, clone) == false) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "UnitTestMatFloatIsEqual NOK1");
    PBErrCatch(PBMathErr);
  }
  VecSet(&i, 0, 0); VecSet(&i, 1, 0);
  MatSet(clone, &i, -1.0);
  if (MatIsEqual(mat, clone) == true) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "UnitTestMatFloatIsEqual NOK2");
    PBErrCatch(PBMathErr);
  }
  MatFree(&mat);
  MatFree(&clone);
  printf("UnitTestMatFloatCloneIsEqual OK\n");
}

void UnitTestMatFloatLoadSave() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 2);
  VecSet(&dim, 1, 3);
  MatFloat* mat = MatFloatCreate(&dim);
  VecShort2D i = VecShortCreateStatic2D();
  float v = 1.0;
  do {
    MatSet(mat, &i, v);
    v += 1.0;
  } while(VecStep(&i, &dim));
  FILE* f = fopen("./UnitTestMatFloatLoadSave.txt", "w");
  if (f == NULL) {
    PBMathErr->_type = PBErrTypeOther;
    sprintf(PBMathErr->_msg, 
      "Can't open ./UnitTestMatFloatLoadSave.txt for writing");
    PBErrCatch(PBMathErr);
  }
  bool compact = false;
  if (!MatSave(mat, f, compact)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_MatFloatSave NOK");
    PBErrCatch(PBMathErr);
  }
  fclose(f);
  MatFloat* clone = MatFloatCreate(&dim);
  f = fopen("./UnitTestMatFloatLoadSave.txt", "r");
  if (f == NULL) {
    PBMathErr->_type = PBErrTypeOther;
    sprintf(PBMathErr->_msg, 
      "Can't open ./UnitTestMatFloatLoadSave.txt for reading");
    PBErrCatch(PBMathErr);
  }
  if (!MatLoad(&clone, f)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "_MatFloatLoad NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&(mat->_dim), &(clone->_dim))) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "UnitTestMatFloatLoadSave NOK");
    PBErrCatch(PBMathErr);
  }
  VecSetNull(&i);
  do {
    if (!ISEQUALF(MatGet(mat, &i), MatGet(clone, &i))) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "UnitTestMatFloatLoadSave NOK");
      PBErrCatch(PBMathErr);
    }
  } while(VecStep(&i, &dim));
  fclose(f);
  MatFree(&mat);
  MatFree(&clone);
  int ret = system("cat ./UnitTestMatFloatLoadSave.txt");
  ret = ret;
  printf("UnitTestMatFloatLoadSave OK\n");
}

void UnitTestMatFloatTransposeScale() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 2);
  VecSet(&dim, 1, 3);
  MatFloat* mat = MatFloatCreate(&dim);
  VecShort2D i = VecShortCreateStatic2D();
  float v[6] = {3.0, 2.0, 1.0, 2.0, -2.0, 1.0};
  int j = 0;
  do {
    MatSet(mat, &i, v[j]);
    ++j;
  } while(VecStep(&i, &dim));
  MatFloat* trans = MatGetTranspose(mat);
  float w[6] = {3.0, 2.0, 2.0, -2.0, 1.0, 1.0};
  VecSet(&dim, 0, 3);
  VecSet(&dim, 1, 2);
  VecSetNull(&i);
  j = 0;
  do {
    if (!ISEQUALF(MatGet(trans, &i), w[j])) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "UnitTestMatFloatTranspose NOK");
      PBErrCatch(PBMathErr);
    }
    ++j;
  } while(VecStep(&i, &dim));
  MatScale(mat, 2.0);
  j = 0;
  VecSet(&dim, 0, 2);
  VecSet(&dim, 1, 3);
  VecSetNull(&i);
  float u[6] = {6.0, 4.0, 2.0, 4.0, -4.0, 2.0};
  do {
    if (!ISEQUALF(MatGet(mat, &i), u[j])) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "MatScale NOK");
      PBErrCatch(PBMathErr);
    }
    ++j;
  } while(VecStep(&i, &dim));
  MatFree(&mat);
  MatFree(&trans);
  printf("UnitTestMatFloatTransposeScale OK\n");
}

void UnitTestMatFloatInv() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 3);
  VecSet(&dim, 1, 3);
  MatFloat* mat = MatFloatCreate(&dim);
  VecShort2D i = VecShortCreateStatic2D();
  float v[9] = {3.0, 2.0, 0.0, 0.0, 0.0, 1.0, 2.0, -2.0, 1.0};
  int j = 0;
  do {
    MatSet(mat, &i, v[j]);
    ++j;
  } while(VecStep(&i, &dim));
  MatFloat* inv = MatGetInv(mat);
  float w[9] = {0.2, -0.2, 0.2, 0.2, 0.3, -0.3, 0.0, 1.0, 0.0};
  VecSetNull(&i);
  j = 0;
  do {
    if (!ISEQUALF(MatGet(inv, &i), w[j])) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "UnitTestMatFloatInv NOK");
      PBErrCatch(PBMathErr);
    }
    ++j;
  } while(VecStep(&i, &dim));
  MatFree(&mat);
  MatFree(&inv);
  VecSet(&dim, 0, 2);
  VecSet(&dim, 1, 2);
  mat = MatFloatCreate(&dim);
  float vb[4] = {4.0, 2.0, 7.0, 6.0};
  VecSetNull(&i);
  j = 0;
  do {
    MatSet(mat, &i, vb[j]);
    ++j;
  } while(VecStep(&i, &dim));
  inv = MatGetInv(mat);
  float wb[4] = {0.6, -0.2, -0.7, 0.4};
  VecSetNull(&i);
  j = 0;
  do {
    if (!ISEQUALF(MatGet(inv, &i), wb[j])) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "UnitTestMatFloatInv NOK");
      PBErrCatch(PBMathErr);
    }
    ++j;
  } while(VecStep(&i, &dim));
  MatFree(&mat);
  MatFree(&inv);
  printf("UnitTestMatFloatInv OK\n");
}

void UnitTestMatFloatProdVecFloat() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 2);
  VecSet(&dim, 1, 3);
  MatFloat* mat = MatFloatCreate(&dim);
  VecShort2D i = VecShortCreateStatic2D();
  float v = 1.0;
  do {
    MatSet(mat, &i, v);
    v += 1.0;
  } while(VecStep(&i, &dim));
  VecFloat2D u = VecFloatCreateStatic2D();
  for (int j = 2; j--;)
    VecSet(&u, j, (float)j + 1.0);
  VecFloat* w = MatGetProdVec(mat, &u);
  float b[3] = {9.0, 12.0, 15.0};
  for (int j = 3; j--;) {
    if (!ISEQUALF(VecGet(w, j), b[j])) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "UnitTestMatFloatProdVecFloat NOK");
      PBErrCatch(PBMathErr);
    }
  }
  MatFree(&mat);
  VecFree(&w);
  printf("UnitTestMatFloatProdVecFloat OK\n");
}

void UnitTestMatFloatProdMatFloat() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 3);
  VecSet(&dim, 1, 2);
  MatFloat* mat = MatFloatCreate(&dim);
  VecShort2D i = VecShortCreateStatic2D();
  float v = 1.0;
  do {
    MatSet(mat, &i, v);
    v += 1.0;
  } while(VecStep(&i, &dim));
  VecSet(&dim, 0, 2);
  VecSet(&dim, 1, 3);
  MatFloat* matb = MatFloatCreate(&dim);
  VecSetNull(&i);
  v = 1.0;
  do {
    MatSet(matb, &i, v);
    v += 1.0;
  } while(VecStep(&i, &dim));
  MatFloat* matc = MatGetProdMat(mat, matb);
  float w[4] = {22.0, 28.0, 49.0, 64.0};
  VecSetNull(&i);
  int j = 0;
  VecSet(&dim, 0, 2);
  VecSet(&dim, 1, 2);
  if (!VecIsEqual(&dim, &(matc->_dim))) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "UnitTestMatFloatProdMatFloat NOK");
    PBErrCatch(PBMathErr);
  }
  do {
    if (!ISEQUALF(MatGet(matc, &i), w[j])) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "UnitTestMatFloatProdMatFloat NOK");
      PBErrCatch(PBMathErr);
    }
    ++j;
  } while(VecStep(&i, &dim));
  MatFree(&mat);
  MatFree(&matb);
  MatFree(&matc);
  printf("UnitTestMatFloatProdMatFloat OK\n");
}

void UnitTestMatFloatProdVecVecTranspose() {
  VecFloat2D v = VecFloatCreateStatic2D();
  VecFloat3D w = VecFloatCreateStatic3D();
  VecSet(&v, 0, 2.0);
  VecSet(&v, 1, 3.0);
  VecSet(&w, 0, 4.0);
  VecSet(&w, 1, 5.0);
  VecSet(&w, 2, 6.0);
  MatFloat* mat = MatGetProdVecVecTranspose(&v, &w);
  VecShort2D pos = VecShortCreateStatic2D();
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 3);
  VecSet(&dim, 1, 2);
  float check[6] = {8.0, 12.0, 10.0, 15.0, 12.0, 18.0};
  int i = 0;
  do {
    if (!ISEQUALF(MatGet(mat, &pos), check[i])) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "MatGetProdVecVecTranspose NOK");
      PBErrCatch(PBMathErr);
    }
    ++i;
  } while (VecStep(&pos, &dim));
  MatFree(&mat);
  printf("UnitTestMatFloatProdVecVecTranspose OK\n");
}

void UnitTestMatFloatGetEigenValues() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 3);
  VecSet(&dim, 1, 3);
  MatFloat* mat = MatFloatCreate(&dim);
  VecShort2D pos = VecShortCreateStatic2D();
  float check[3][3] = {
    { 2.92, 0.86, -1.15},
    { 0.86, 6.51,  3.32},
    {-1.15, 3.32,  4.57}
  };
  do {
    MatSet(mat, &pos, check[VecGet(&pos, 1)][VecGet(&pos, 0)]);
  } while (VecStep(&pos, &dim));
  printf("mat:\n"); MatPrintln(mat, stdout);
  GSetVecFloat set = MatGetEigenValues(mat);
  printf("Eigen values: ");
  VecPrint(GSetGet(&set, 0), stdout);printf("\n");
  VecFloat3D checkValues = VecFloatCreateStatic3D();
  VecSet(&checkValues, 0, 8.998802);
  VecSet(&checkValues, 1, 3.996595);
  VecSet(&checkValues, 2, 1.004607);
  if (!VecIsEqual(GSetGet(&set, 0), &checkValues)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "MatGetEigenValues NOK");
    PBErrCatch(PBMathErr);
  }
  printf("Eigen vector 1: ");
  VecPrint(GSetGet(&set, 1), stdout);printf("\n");
  printf("Eigen vector 2: ");
  VecPrint(GSetGet(&set, 2), stdout);printf("\n");
  printf("Eigen vector 3: ");
  VecPrint(GSetGet(&set, 3), stdout);printf("\n");
  VecFloat3D checkVecA = VecFloatCreateStatic3D();
  VecSet(&checkVecA, 0, 0.000290);
  VecSet(&checkVecA, 1, -0.800102);
  VecSet(&checkVecA, 2, -0.599864);
  if (!VecIsEqual(GSetGet(&set, 1), &checkVecA)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "MatGetEigenValues NOK");
    PBErrCatch(PBMathErr);
  }
  VecFloat3D checkVecB = VecFloatCreateStatic3D();
  VecSet(&checkVecB, 0, 0.800110);
  VecSet(&checkVecB, 1, 0.360017);
  VecSet(&checkVecB, 2, -0.479806);
  if (!VecIsEqual(GSetGet(&set, 2), &checkVecB)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "MatGetEigenValues NOK");
    PBErrCatch(PBMathErr);
  }
  VecFloat3D checkVecC = VecFloatCreateStatic3D();
  VecSet(&checkVecC, 0, 0.599855);
  VecSet(&checkVecC, 1, -0.479817);
  VecSet(&checkVecC, 2, 0.640273);
  if (!VecIsEqual(GSetGet(&set, 3), &checkVecC)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "MatGetEigenValues NOK");
    PBErrCatch(PBMathErr);
  }
  do {
    VecFloat* v = GSetPop(&set);
    VecFree(&v);
  } while (GSetNbElem(&set) > 0);
  MatFree(&mat);
  printf("UnitTestMatFloatGetEigenValues OK\n");
}

void UnitTestSpeedMatFloat() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 3);
  VecSet(&dim, 1, 3);
  MatFloat* mat = MatFloatCreate(&dim);
  int nbTest = 100000;
  srandom(RANDOMSEED);
  int i = nbTest;
  clock_t clockBefore = clock();
  VecShort2D j = VecShortCreateStatic2D();
  for (; i--;) {
    float val = 1.0;
    MatSet(mat, &j, val);
    float valb = MatGet(mat, &j);
    valb = valb;
    VecStep(&j, &dim);
  }
  clock_t clockAfter = clock();
  double timeV = ((double)(clockAfter - clockBefore)) / 
    CLOCKS_PER_SEC * 1000.0;
  srandom(RANDOMSEED);
  i = nbTest;
  clockBefore = clock();
  float* array = malloc(sizeof(float) * 9);
  short *ptr = j._val;
  for (; i--;) {
    float val = 1.0;
    int k = ptr[1] * 3 + ptr[0];
    array[k] = val;
    float valb = array[k];
    valb = valb;
    VecStep(&j, &dim);
  }
  clockAfter = clock();
  double timeRef = ((double)(clockAfter - clockBefore)) / 
    CLOCKS_PER_SEC * 1000.0;
  printf("MatFloat: %fms, array: %fms\n", 
    timeV / (float)nbTest, timeRef / (float)nbTest);
  if (timeV / (float)nbTest > 2.0 * timeRef / (float)nbTest) {
#if BUILDMODE == 0 
    PBMathErr->_fatal = false;
#endif
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "UnitTestSpeedMatFloat NOK");
    PBErrCatch(PBMathErr);
  }
  MatFree(&mat);
  free(array);
  printf("UnitTestSpeedMatFloat OK\n");
}

void UnitTestMatFloatGetQR() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 3);
  VecSet(&dim, 1, 4);
  MatFloat* mat = MatFloatCreate(&dim);
  VecShort2D pos = VecShortCreateStatic2D();
  float val[4][3] = {
      {-1.0, -1.0, 1.0},
      { 1.0,  3.0, 3.0}, 
      {-1.0, -1.0, 5.0}, 
      { 1.0,  3.0, 7.0} 
    };
  do {
    MatSet(mat, &pos, val[VecGet(&pos, 1)][VecGet(&pos, 0)]);
  } while (VecStep(&pos, &dim));
  QRDecomp qr = MatGetQR(mat);
  MatFloat* QR = MatGetProdMat(qr._Q, qr._R);

  printf("mat:\n");
  MatPrintln(mat, stdout);
  printf("Q:\n");
  MatPrintln(qr._Q, stdout);
  printf("R:\n");
  MatPrintln(qr._R, stdout);
  printf("QR:\n");
  MatPrintln(QR, stdout);

  MatFloat* Q = MatFloatCreate(&dim);
  VecSetNull(&pos);
  float checkQ[4][3] = {
      {-0.5, -0.5,  0.5},
      { 0.5, -0.5,  0.5}, 
      {-0.5, -0.5, -0.5}, 
      { 0.5, -0.5, -0.5} 
    };
  do {
    MatSet(Q, &pos, checkQ[VecGet(&pos, 1)][VecGet(&pos, 0)]);
  } while (VecStep(&pos, &dim));
  VecSet(&dim, 1, 3);
  MatFloat* R = MatFloatCreate(&dim);
  VecSetNull(&pos);
  float checkR[3][3] = {
      {2.0,  4.0,  2.0},
      {0.0, -2.0, -8.0}, 
      {0.0,  0.0, -4.0}
    };
  do {
    MatSet(R, &pos, checkR[VecGet(&pos, 1)][VecGet(&pos, 0)]);
  } while (VecStep(&pos, &dim));
  if (!MatIsEqual(Q, qr._Q) || !MatIsEqual(R, qr._R) || 
    !MatIsEqual(QR, mat)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "MatGetQR NOK");
    PBErrCatch(PBMathErr);
  }
  MatFree(&mat);
  MatFree(&Q);
  MatFree(&R);
  MatFree(&QR);
  QRDecompFreeStatic(&qr);
  printf("UnitTestMatFloatGetQR OK\n");
}

void UnitTestMatFloat() {
  UnitTestMatFloatCreateFree();
  UnitTestMatFloatGetSetDim();
  UnitTestMatFloatCloneIsEqual();
  UnitTestMatFloatLoadSave();
  UnitTestMatFloatInv();
  UnitTestMatFloatTransposeScale();
  UnitTestMatFloatProdVecFloat();
  UnitTestMatFloatProdMatFloat();
  UnitTestMatFloatGetQR();
  UnitTestMatFloatProdVecVecTranspose();
  UnitTestMatFloatGetEigenValues();
  UnitTestSpeedMatFloat();
  printf("UnitTestMatFloat OK\n");
}

void UnitTestSysLinEq() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 3);
  VecSet(&dim, 1, 3);
  MatFloat* mat = MatFloatCreate(&dim);
  float a[9] = {2.0, 2.0, 6.0, 1.0, 6.0, 8.0, 3.0, 8.0, 18.0};
  VecShort2D index = VecShortCreateStatic2D();
  int j = 0;
  do {
    MatSet(mat, &index, a[j]);
    ++j;
  } while(VecStep(&index, &dim));
  VecFloat3D v = VecFloatCreateStatic3D();
  float b[3] = {1.0, 3.0, 5.0};
  for (int i = 3; i--;)
    VecSet(&v, i, b[i]);
  SysLinEq* sys = SysLinEqCreate(mat, &v);
  VecFloat* res = SysLinEqSolve(sys);
  float c[3] = {0.3, 0.4, 0};
  for (int i = 3; i--;) {
    if (!ISEQUALF(c[i], VecGet(res, i))) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "SysLinEqSolve NOK");
      PBErrCatch(PBMathErr);
    }
  }
  float ab[9] = {3.0, 2.0, -1.0, 2.0, -2.0, 0.5, -1.0, 4.0, -1.0};
  VecSetNull(&index);
  j = 0;
  do {
    MatSet(mat, &index, ab[j]);
    ++j;
  } while(VecStep(&index, &dim));
  SysLinEqSetM(sys, mat);
  float bb[3] = {1.0, -2.0, 0.0};
  for (int i = 3; i--;)
    VecSet(&v, i, bb[i]);
  SysLinEqSetV(sys, &v);
  VecFree(&res);
  res = SysLinEqSolve(sys);
  float cb[3] = {1.0, -2.0, -2.0};
  for (int i = 3; i--;) {
    if (!ISEQUALF(cb[i], VecGet(res, i))) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "SysLinEqSolve NOK");
      PBErrCatch(PBMathErr);
    }
  }
  VecFree(&res);
  SysLinEqFree(&sys);
  if (sys != NULL) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "sys is not null after free");
    PBErrCatch(PBMathErr);
  }
  MatFree(&mat);
  printf("UnitTestSysLinEq OK\n");
}

void UnitTestGauss() {
  srandom(RANDOMSEED);
  float mean = 1.0;
  float sigma = 0.5;
  Gauss *gauss = GaussCreate(mean, sigma);
  if (!ISEQUALF(gauss->_mean, mean) ||
    !ISEQUALF(gauss->_sigma, sigma)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "UnitTestGaussCreate NOK");
    PBErrCatch(PBMathErr);
  }
  float a[22] = {0.000268, 0.001224, 0.004768, 0.015831, 0.044789, 
    0.107982, 0.221842, 0.388372, 0.579383, 0.736540, 0.797885, 
    0.736540, 0.579383, 0.388372, 0.221842, 0.107982, 0.044789, 
    0.015831, 0.004768, 0.001224, 0.000268};
  for (int i = -5; i<= 15; ++i) {
    if (!ISEQUALF(GaussGet(gauss, (float)i * 0.2), a[i + 5])) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "UnitTestGaussGet NOK");
      PBErrCatch(PBMathErr);
    }
  }
  int nbsample = 1000000;
  double sum = 0.0;
  double sumsquare = 0.0;
  for (int i = nbsample; i--;) {
    float v = GaussRnd(gauss);
    sum += v;
    sumsquare += fsquare(v);
  }
  double avg = sum / (double)nbsample;
  double sig = sqrtf(sumsquare / (double)nbsample - fsquare(avg));
  if (fabs(avg - mean) > 0.001 ||
    fabs(sig - sigma) > 0.001) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "UnitTestGaussRnd NOK");
    PBErrCatch(PBMathErr);
  }
  GaussFree(&gauss);
  if (gauss != NULL) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "gauss is not null after free");
    PBErrCatch(PBMathErr);
  }
  printf("UnitTestGauss OK\n");
}

void UnitTestSmoother() {
  float smooth[11] = {0.0, 0.028, 0.104, 0.216, 0.352, 0.5, 0.648, 
    0.784, 0.896, 0.972, 1.0};
  float smoother[11] = {0.0, 0.00856, 0.05792, 0.16308, 0.31744, 0.5, 
    0.68256, 0.83692, 0.94208, 0.99144, 1.0};
  for (int i = 0; i <= 10; ++i) {
    if (!ISEQUALF(SmoothStep((float)i * 0.1), smooth[i])) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "UnitTestSmooth NOK");
      PBErrCatch(PBMathErr);
    }
    if (!ISEQUALF(SmootherStep((float)i * 0.1), smoother[i])) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "UnitTestSmoother NOK");
      PBErrCatch(PBMathErr);
    }
  }
  printf("UnitTestSmoother OK\n");
}

void UnitTestConv() {
  float rad[5] = {0.0, PBMATH_TWOPI, PBMATH_PI, PBMATH_HALFPI, 3.0 * PBMATH_HALFPI};
  float deg[5] = {0.0, 360.0, 180.0, 90.0, 270.0};
  for (int i = 5; i--;) {
    if (!ISEQUALF(ConvRad2Deg(rad[i]), deg[i])) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "UnitTestConvRad2Deg NOK");
      PBErrCatch(PBMathErr);
    }
    if (!ISEQUALF(ConvDeg2Rad(deg[i]), rad[i])) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "UnitTestConvDeg2Rad NOK");
      PBErrCatch(PBMathErr);
    }
  }
  printf("UnitTestConv OK\n");
}

void UnitTestThueMorseSeq() {
  long seq_2[16] = {0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0};
  long seq_3[27] = {0,1,2,1,2,0,2,0,1,1,2,0,2,0,1,0,
    1,2,2,0,1,0,1,2,1,2,0};
  long seq_4[64] = {0,1,2,3,1,2,3,0,2,3,0,1,3,0,1,2,
    1,2,3,0,2,3,0,1,3,0,1,2,0,1,2,3,2,3,0,1,3,0,1,2,
    0,1,2,3,1,2,3,0,3,0,1,2,0,1,2,3,1,2,3,0,2,3,0,1};
  for (long iElem = 0; iElem < 16; ++iElem) {
    long thuemorse = ThueMorseSeqGetNthElem(iElem, 2);
    if (thuemorse != seq_2[iElem]) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "ThueMorseSeqGetNthElem NOK (%ld,2)",
        iElem);
      PBErrCatch(PBMathErr);
    }
  }
  for (long iElem = 0; iElem < 27; ++iElem) {
    long thuemorse = ThueMorseSeqGetNthElem(iElem, 3);
    if (thuemorse != seq_3[iElem]) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "ThueMorseSeqGetNthElem NOK (%ld,3)",
        iElem);
      PBErrCatch(PBMathErr);
    }
  }
  for (long iElem = 0; iElem < 64; ++iElem) {
    long thuemorse = ThueMorseSeqGetNthElem(iElem, 4);
    if (thuemorse != seq_4[iElem]) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "ThueMorseSeqGetNthElem NOK (%ld,4)",
        iElem);
      PBErrCatch(PBMathErr);
    }
  }
  printf("UnitTestThueMorseSeq OK\n");
}

void UnitTestBasicFunctions() {
  UnitTestConv();
  UnitTestPowi();
  UnitTestFastPow();
  UnitTestSpeedFastPow();
  UnitTestFSquare();
  UnitTestConv();
  UnitTestThueMorseSeq();
  printf("UnitTestBasicFunctions OK\n");
}

void UnitTestAll() {
  UnitTestVecShort();
  UnitTestVecLong();
  UnitTestVecFloat();
  UnitTestMatFloat();
  UnitTestSysLinEq();
  UnitTestGauss();
  UnitTestSmoother();
  UnitTestBasicFunctions();
  printf("UnitTestAll OK\n");
}

int main() {
  UnitTestAll();
  // Return success code
  return 0;
}

