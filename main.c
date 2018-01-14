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
  VecShort *v = VecShortCreate(5);
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
  VecShort *v = VecShortCreate(5);
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  VecShort *w = VecClone(v);
  if (memcmp(v, w, sizeof(VecShort) + sizeof(short) * 5) != 0) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortClone NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  VecFree(&w);
  printf("VecShortClone OK\n");
}

void UnitTestVecShortLoadSave() {
  VecShort *v = VecShortCreate(5);
  VecShort2D v2 = VecShortCreateStatic2D();
  VecShort3D v3 = VecShortCreateStatic3D();
  VecShort4D v4 = VecShortCreateStatic4D();
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  for (int i = 2; i--;) VecSet(&v2, i, i + 1);
  for (int i = 3; i--;) VecSet(&v3, i, i + 1);
  for (int i = 4; i--;) VecSet(&v4, i, i + 1);
  FILE *f = fopen("./UnitTestVecShortLoadSave.txt", "w");
  if (f == NULL) {
    PBMathErr->_type = PBErrTypeOther;
    sprintf(PBMathErr->_msg, 
      "Can't open ./UnitTestVecShortLoadSave.txt for writing");
    PBErrCatch(PBMathErr);
  }
  if (!VecSave(v, f)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortSave NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecSave(&v2, f)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortSave NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecSave(&v3, f)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortSave NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecSave(&v4, f)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortSave NOK");
    PBErrCatch(PBMathErr);
  }
  fclose(f);
  VecShort *w = VecShortCreate(2);
  f = fopen("./UnitTestVecShortLoadSave.txt", "r");
  if (f == NULL) {
    PBMathErr->_type = PBErrTypeOther;
    sprintf(PBMathErr->_msg, 
      "Can't open ./UnitTestVecShortLoadSave.txt for reading");
    PBErrCatch(PBMathErr);
  }
  if (!VecLoad(&w, f)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortLoad NOK");
    PBErrCatch(PBMathErr);
  }
  if (memcmp(v, w, sizeof(VecShort) + sizeof(short) * 5) != 0) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortLoadSave NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecLoad(&w, f)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortLoad NOK");
    PBErrCatch(PBMathErr);
  }
  if (memcmp(&v2, w, sizeof(VecShort) + sizeof(short) * 2) != 0) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortLoadSave NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecLoad(&w, f)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortLoad NOK");
    PBErrCatch(PBMathErr);
  }
  if (memcmp(&v3, w, sizeof(VecShort) + sizeof(short) * 3) != 0) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortLoadSave NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecLoad(&w, f)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortLoad NOK");
    PBErrCatch(PBMathErr);
  }
  if (memcmp(&v4, w, sizeof(VecShort) + sizeof(short) * 4) != 0) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortLoadSave NOK");
    PBErrCatch(PBMathErr);
  }
  fclose(f);
  VecFree(&v);
  VecFree(&w);
  int ret = system("cat ./UnitTestVecShortLoadSave.txt");
  printf("VecShortLoadSave OK\n");
  ret = system("rm ./UnitTestVecShortLoadSave.txt");
  ret = ret;
}

void UnitTestVecShortGetSetDim() {
  VecShort *v = VecShortCreate(5);
  VecShort2D v2 = VecShortCreateStatic2D();
  VecShort3D v3 = VecShortCreateStatic3D();
  VecShort4D v4 = VecShortCreateStatic4D();
  if (VecDim(v) != 5) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortDim NOK");
    PBErrCatch(PBMathErr);
  }
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  for (int i = 2; i--;) VecSet(&v2, i, i + 1);
  for (int i = 3; i--;) VecSet(&v3, i, i + 1);
  for (int i = 4; i--;) VecSet(&v4, i, i + 1);
  for (int i = 5; i--;)
    if (v->_val[i] != i + 1) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecShortSet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 2; i--;)
    if (v2._val[i] != i + 1) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecShortSet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 3; i--;)
    if (v3._val[i] != i + 1) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecShortSet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 4; i--;)
    if (v4._val[i] != i + 1) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecShortSet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 5; i--;)
    if (VecGet(v, i) != i + 1) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecShortGet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 2; i--;)
    if (VecGet(&v2, i) != i + 1) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecShortGet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 3; i--;)
    if (VecGet(&v3, i) != i + 1) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecShortGet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 4; i--;)
    if (VecGet(&v4, i) != i + 1) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecShortGet NOK");
      PBErrCatch(PBMathErr);
    }
  VecSetNull(v);
  VecSetNull(&v2);
  VecSetNull(&v3);
  VecSetNull(&v4);
  for (int i = 5; i--;)
    if (VecGet(v, i) != 0) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecShortGet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 2; i--;)
    if (VecGet(&v2, i) != 0) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecShortGet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 3; i--;)
    if (VecGet(&v3, i) != 0) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecShortGet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 4; i--;)
    if (VecGet(&v4, i) != 0) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecShortGet NOK");
      PBErrCatch(PBMathErr);
    }
  VecFree(&v);
  printf("VecShortGetSetDim OK\n");
}

void UnitTestVecShortStep() {
  VecShort *v = VecShortCreate(5);
  VecShort2D v2 = VecShortCreateStatic2D();
  VecShort3D v3 = VecShortCreateStatic3D();
  VecShort4D v4 = VecShortCreateStatic4D();
  VecShort *bv = VecShortCreate(5);
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
    for (int i = 1; i < VecDim(v); ++i)
      a = a * b[i] + VecGet(v, i);
    if (a != acheck[iCheck]) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecShortStep NOK");
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
      sprintf(PBMathErr->_msg, "VecShortStep NOK");
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
      sprintf(PBMathErr->_msg, "VecShortStep NOK");
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
      sprintf(PBMathErr->_msg, "VecShortStep NOK");
      PBErrCatch(PBMathErr);
    }
    ++iCheck;
  } while (VecStep(&v4, &bv4));
  iCheck = 0;
  do {
    int a = VecGet(v, VecDim(v) - 1);
    for (int i = VecDim(v) - 2; i >= 0; --i)
      a = a * b[i] + VecGet(v, i);
    if (a != acheck[iCheck]) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecShortPStep NOK");
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
      sprintf(PBMathErr->_msg, "VecShortPStep NOK");
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
      sprintf(PBMathErr->_msg, "VecShortPStep NOK");
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
      sprintf(PBMathErr->_msg, "VecShortPStep NOK");
      PBErrCatch(PBMathErr);
    }
    ++iCheck;
  } while (VecPStep(&v4, &bv4));
  VecFree(&v);
  VecFree(&bv);
  printf("UnitTestVecShortStep OK\n");
}

void UnitTestVecShortHamiltonDist() {
  VecShort *v = VecShortCreate(5);
  VecShort2D v2 = VecShortCreateStatic2D();
  VecShort3D v3 = VecShortCreateStatic3D();
  VecShort4D v4 = VecShortCreateStatic4D();
  VecShort *w = VecShortCreate(5);
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
    sprintf(PBMathErr->_msg, "VecShortHamiltonDist NOK");
    PBErrCatch(PBMathErr);
  }
  dist = VecHamiltonDist(&v2, &w2);
  if (dist != 2) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortHamiltonDist NOK");
    PBErrCatch(PBMathErr);
  }
  dist = VecHamiltonDist(&v3, &w3);
  if (dist != 5) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortHamiltonDist NOK");
    PBErrCatch(PBMathErr);
  }
  dist = VecHamiltonDist(&v4, &w4);
  if (dist != 8) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortHamiltonDist NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  VecFree(&w);
  printf("UnitTestVecShortHamiltonDist OK\n");
}

void UnitTestVecShortIsEqual() {
  VecShort *v = VecShortCreate(5);
  VecShort2D v2 = VecShortCreateStatic2D();
  VecShort3D v3 = VecShortCreateStatic3D();
  VecShort4D v4 = VecShortCreateStatic4D();
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  for (int i = 2; i--;) VecSet(&v2, i, i + 1);
  for (int i = 3; i--;) VecSet(&v3, i, i + 1);
  for (int i = 4; i--;) VecSet(&v4, i, i + 1);
  VecShort *w = VecShortCreate(5);
  VecShort2D w2 = VecShortCreateStatic2D();
  VecShort3D w3 = VecShortCreateStatic3D();
  VecShort4D w4 = VecShortCreateStatic4D();
  if (VecIsEqual(v, w)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  if (VecIsEqual(&v2, &w2)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  if (VecIsEqual(&v3, &w3)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  if (VecIsEqual(&v4, &w4)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  for (int i = 5; i--;) VecSet(w, i, i + 1);
  for (int i = 2; i--;) VecSet(&w2, i, i + 1);
  for (int i = 3; i--;) VecSet(&w3, i, i + 1);
  for (int i = 4; i--;) VecSet(&w4, i, i + 1);
  if (!VecIsEqual(v, w)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v2, &w2)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v3, &w3)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v4, &w4)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  VecFree(&w);
  printf("UnitTestVecShortIsEqual OK\n");
}

void UnitTestVecShortCopy() {
  VecShort *v = VecShortCreate(5);
  VecShort2D v2 = VecShortCreateStatic2D();
  VecShort3D v3 = VecShortCreateStatic3D();
  VecShort4D v4 = VecShortCreateStatic4D();
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  for (int i = 2; i--;) VecSet(&v2, i, i + 1);
  for (int i = 3; i--;) VecSet(&v3, i, i + 1);
  for (int i = 4; i--;) VecSet(&v4, i, i + 1);
  VecShort *w = VecShortCreate(5);
  VecShort2D w2 = VecShortCreateStatic2D();
  VecShort3D w3 = VecShortCreateStatic3D();
  VecShort4D w4 = VecShortCreateStatic4D();
  VecCopy(w, v);
  VecCopy(&w2, &v2);
  VecCopy(&w3, &v3);
  VecCopy(&w4, &v4);
  if (!VecIsEqual(v, w)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortCopy NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v2, &w2)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortCopy NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v3, &w3)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortCopy NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v4, &w4)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortCopy NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  VecFree(&w);
  printf("UnitTestVecShortCopy OK\n");
}

void UnitTestVecShortDotProd() {
  VecShort *v = VecShortCreate(5);
  VecShort2D v2 = VecShortCreateStatic2D();
  VecShort3D v3 = VecShortCreateStatic3D();
  VecShort4D v4 = VecShortCreateStatic4D();
  VecShort *w = VecShortCreate(5);
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
    sprintf(PBMathErr->_msg, "VecShortDotProd NOK");
    PBErrCatch(PBMathErr);
  }
  prod = VecDotProd(&v2, &w2);
  if (prod != 1) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortDotProd NOK");
    PBErrCatch(PBMathErr);
  }
  prod = VecDotProd(&v3, &w3);
  if (prod != -2) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortDotProd NOK");
    PBErrCatch(PBMathErr);
  }
  prod = VecDotProd(&v4, &w4);
  if (prod != -6) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecShortDotProd NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  VecFree(&w);
  printf("UnitTestVecShortDotProd OK\n");
}

void UnitTestSpeedVecShort() {
  VecShort *v = VecShortCreate(5);
  VecShort2D v2 = VecShortCreateStatic2D();
  VecShort3D v3 = VecShortCreateStatic3D();
  VecShort4D v4 = VecShortCreateStatic4D();
  int nbTest = 100000;

  srandom(RANDOMSEED);
  int i = nbTest;
  clock_t clockBefore = clock();
  for (; i--;) {
    int j = INT(rnd() * ((float)(VecDim(v) - 1) - PBMATH_EPSILON));
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
    int j = INT(rnd() * ((float)(VecDim(v) - 1) - PBMATH_EPSILON));
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
  VecShort *v = VecShortCreate(5);
  VecShort2D v2 = VecShortCreateStatic2D();
  VecShort3D v3 = VecShortCreateStatic3D();
  VecShort4D v4 = VecShortCreateStatic4D();
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  for (int i = 2; i--;) VecSet(&v2, i, i + 1);
  for (int i = 3; i--;) VecSet(&v3, i, i + 1);
  for (int i = 4; i--;) VecSet(&v4, i, i + 1);
  VecFloat *w = VecShortToFloat(v);
  VecFloat2D w2 = VecShortToFloat2D(&v2);
  VecFloat3D w3 = VecShortToFloat3D(&v3);
  VecPrint(w, stdout); printf("\n");
  VecPrint(&w2, stdout); printf("\n");
  VecPrint(&w3, stdout); printf("\n");
  VecFree(&v);
  VecFree(&w);
  printf("UnitTestVecShortToFloat OK\n");
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
  printf("UnitTestVecShort OK\n");
}

void UnitTestVecFloatCreateFree() {
  VecFloat *v = VecFloatCreate(5);
  VecFloat2D v2 = VecFloatCreateStatic2D();
  VecFloat3D v3 = VecFloatCreateStatic3D();
  VecPrint(v, stdout);printf("\n");
  VecPrint(&v2, stdout);printf("\n");
  VecPrint(&v3, stdout);printf("\n");
  VecFloatFree(&v);
  if (v != NULL) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloat is not null after VecFloatFree");
    PBErrCatch(PBMathErr);
  }
  printf("VecFloatCreateFree OK\n");
}

void UnitTestVecFloatClone() {
  VecFloat *v = VecFloatCreate(5);
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  VecFloat *w = VecClone(v);
  if (memcmp(v, w, sizeof(VecFloat) + sizeof(float) * 5) != 0) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatClone NOK");
    PBErrCatch(PBMathErr);
  }
  VecFloatFree(&v);
  VecFloatFree(&w);
  printf("VecFloatClone OK\n");
}

void UnitTestVecFloatLoadSave() {
  VecFloat *v = VecFloatCreate(5);
  VecFloat2D v2 = VecFloatCreateStatic2D();
  VecFloat3D v3 = VecFloatCreateStatic3D();
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  for (int i = 2; i--;) VecSet(&v2, i, i + 1);
  for (int i = 3; i--;) VecSet(&v3, i, i + 1);
  FILE *f = fopen("./UnitTestVecFloatLoadSave.txt", "w");
  if (f == NULL) {
    PBMathErr->_type = PBErrTypeOther;
    sprintf(PBMathErr->_msg, 
      "Can't open ./UnitTestVecFloatLoadSave.txt for writing");
    PBErrCatch(PBMathErr);
  }
  if (!VecSave(v, f)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatSave NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecSave(&v2, f)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatSave NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecSave(&v3, f)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatSave NOK");
    PBErrCatch(PBMathErr);
  }
  fclose(f);
  VecFloat *w = VecFloatCreate(2);
  f = fopen("./UnitTestVecFloatLoadSave.txt", "r");
  if (f == NULL) {
    PBMathErr->_type = PBErrTypeOther;
    sprintf(PBMathErr->_msg, 
      "Can't open ./UnitTestVecFloatLoadSave.txt for reading");
    PBErrCatch(PBMathErr);
  }
  if (!VecLoad(&w, f)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatLoad NOK");
    PBErrCatch(PBMathErr);
  }
  if (memcmp(v, w, sizeof(VecFloat) + sizeof(float) * 5) != 0) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatLoadSave NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecLoad(&w, f)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatLoad NOK");
    PBErrCatch(PBMathErr);
  }
  if (memcmp(&v2, w, sizeof(VecFloat) + sizeof(float) * 2) != 0) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatLoadSave NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecLoad(&w, f)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatLoad NOK");
    PBErrCatch(PBMathErr);
  }
  if (memcmp(&v3, w, sizeof(VecFloat) + sizeof(float) * 3) != 0) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatLoadSave NOK");
    PBErrCatch(PBMathErr);
  }
  fclose(f);
  VecFree(&v);
  VecFree(&w);
  int ret = system("cat ./UnitTestVecFloatLoadSave.txt");
  printf("VecFloatLoadSave OK\n");
  ret = system("rm ./UnitTestVecFloatLoadSave.txt");
  ret = ret;
}

void UnitTestVecFloatGetSetDim() {
  VecFloat *v = VecFloatCreate(5);
  VecFloat2D v2 = VecFloatCreateStatic2D();
  VecFloat3D v3 = VecFloatCreateStatic3D();
  if (VecDim(v) != 5) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatDim NOK");
    PBErrCatch(PBMathErr);
  }
  for (int i = 5; i--;) VecSet(v, i, (float)(i + 1));
  for (int i = 2; i--;) VecSet(&v2, i, (float)(i + 1));
  for (int i = 3; i--;) VecSet(&v3, i, (float)(i + 1));
  for (int i = 5; i--;)
    if (!ISEQUALF(v->_val[i], (float)(i + 1))) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecFloatSet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 2; i--;)
    if (!ISEQUALF(v2._val[i], (float)(i + 1))) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecFloatSet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 3; i--;)
    if (!ISEQUALF(v3._val[i], (float)(i + 1))) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecFloatSet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 5; i--;)
    if (!ISEQUALF(VecGet(v, i), (float)(i + 1))) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecFloatGet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 2; i--;)
    if (!ISEQUALF(VecGet(&v2, i), (float)(i + 1))) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecFloatGet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 3; i--;)
    if (!ISEQUALF(VecGet(&v3, i), (float)(i + 1))) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecFloatGet NOK");
      PBErrCatch(PBMathErr);
    }
  VecSetNull(v);
  VecSetNull(&v2);
  VecSetNull(&v3);
  for (int i = 5; i--;)
    if (!ISEQUALF(VecGet(v, i), 0.0)) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecFloatGet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 2; i--;)
    if (!ISEQUALF(VecGet(&v2, i), 0.0)) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecFloatGet NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 3; i--;)
    if (!ISEQUALF(VecGet(&v3, i), 0.0)) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecFloatGet NOK");
      PBErrCatch(PBMathErr);
    }
  VecFree(&v);
  printf("VecFloatGetSetDim OK\n");
}

void UnitTestVecFloatCopy() {
  VecFloat *v = VecFloatCreate(5);
  VecFloat2D v2 = VecFloatCreateStatic2D();
  VecFloat3D v3 = VecFloatCreateStatic3D();
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  for (int i = 2; i--;) VecSet(&v2, i, i + 1);
  for (int i = 3; i--;) VecSet(&v3, i, i + 1);
  VecFloat *w = VecFloatCreate(5);
  VecFloat2D w2 = VecFloatCreateStatic2D();
  VecFloat3D w3 = VecFloatCreateStatic3D();
  VecCopy(w, v);
  VecCopy(&w2, &v2);
  VecCopy(&w3, &v3);
  if (!VecIsEqual(v, w)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatCopy NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v2, &w2)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatCopy NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v3, &w3)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatCopy NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  VecFree(&w);
  printf("UnitTestVecFloatCopy OK\n");
}

void UnitTestVecFloatNorm() {
  VecFloat *v = VecFloatCreate(5);
  VecFloat2D v2 = VecFloatCreateStatic2D();
  VecFloat3D v3 = VecFloatCreateStatic3D();
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  for (int i = 2; i--;) VecSet(&v2, i, i + 1);
  for (int i = 3; i--;) VecSet(&v3, i, i + 1);
  if (!ISEQUALF(VecNorm(v), 7.416198)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatNorm NOK");
    PBErrCatch(PBMathErr);
  }
  if (!ISEQUALF(VecNorm(&v2), 2.236068)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatNorm NOK");
    PBErrCatch(PBMathErr);
  }
  if (!ISEQUALF(VecNorm(&v3), 3.741657)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatNorm NOK");
    PBErrCatch(PBMathErr);
  }
  VecNormalise(v);
  VecNormalise(&v2);
  VecNormalise(&v3);
  if (!ISEQUALF(VecNorm(v), 1.0)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatNormalise NOK");
    PBErrCatch(PBMathErr);
  }
  if (!ISEQUALF(VecNorm(&v2), 1.0)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatNormalise NOK");
    PBErrCatch(PBMathErr);
  }
  if (!ISEQUALF(VecNorm(&v3), 1.0)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatNormalise NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  printf("UnitTestVecFloatNorm OK\n");
}

void UnitTestVecFloatDist() {
  VecFloat *v = VecFloatCreate(5);
  VecFloat2D v2 = VecFloatCreateStatic2D();
  VecFloat3D v3 = VecFloatCreateStatic3D();
  VecFloat *w = VecFloatCreate(5);
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
    sprintf(PBMathErr->_msg, "VecFloatDist NOK");
    PBErrCatch(PBMathErr);
  }
  if (!ISEQUALF(VecDist(&v2, &w2), 2.549510)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatDist NOK");
    PBErrCatch(PBMathErr);
  }
  if (!ISEQUALF(VecDist(&v3, &w3), 3.840573)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatDist NOK");
    PBErrCatch(PBMathErr);
  }
  if (!ISEQUALF(VecHamiltonDist(v, w), 13.5)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatHamiltonDist NOK");
    PBErrCatch(PBMathErr);
  }
  if (!ISEQUALF(VecHamiltonDist(&v2, &w2), 3.0)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatHamiltonDist NOK");
    PBErrCatch(PBMathErr);
  }
  if (!ISEQUALF(VecHamiltonDist(&v3, &w3), 5.5)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatHamiltonDist NOK");
    PBErrCatch(PBMathErr);
  }
  if (!ISEQUALF(VecPixelDist(v, w), 13.0)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatPixelDist NOK");
    PBErrCatch(PBMathErr);
  }
  if (!ISEQUALF(VecPixelDist(&v2, &w2), 2.0)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatPixelDist NOK");
    PBErrCatch(PBMathErr);
  }
  if (!ISEQUALF(VecPixelDist(&v3, &w3), 5.0)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatPixelDist NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  VecFree(&w);
  printf("UnitTestVecFloatDist OK\n");
}

void UnitTestVecFloatIsEqual() {
  VecFloat *v = VecFloatCreate(5);
  VecFloat2D v2 = VecFloatCreateStatic2D();
  VecFloat3D v3 = VecFloatCreateStatic3D();
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  for (int i = 2; i--;) VecSet(&v2, i, i + 1);
  for (int i = 3; i--;) VecSet(&v3, i, i + 1);
  VecFloat *w = VecFloatCreate(5);
  VecFloat2D w2 = VecFloatCreateStatic2D();
  VecFloat3D w3 = VecFloatCreateStatic3D();
  if (VecIsEqual(v, w)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  if (VecIsEqual(&v2, &w2)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  if (VecIsEqual(&v3, &w3)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  for (int i = 5; i--;) VecSet(w, i, i + 1);
  for (int i = 2; i--;) VecSet(&w2, i, i + 1);
  for (int i = 3; i--;) VecSet(&w3, i, i + 1);
  if (!VecIsEqual(v, w)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v2, &w2)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v3, &w3)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatIsEqual NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  VecFree(&w);
  printf("UnitTestVecFloatIsEqual OK\n");
}

void UnitTestVecFloatScale() {
  VecFloat *v = VecFloatCreate(5);
  VecFloat2D v2 = VecFloatCreateStatic2D();
  VecFloat3D v3 = VecFloatCreateStatic3D();
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  for (int i = 2; i--;) VecSet(&v2, i, i + 1);
  for (int i = 3; i--;) VecSet(&v3, i, i + 1);
  float a = 0.1;
  VecFloat *w = VecGetScale(v, a);
  VecFloat2D w2 = VecGetScale(&v2, a);
  VecFloat3D w3 = VecGetScale(&v3, a);
  VecScale(v, a);
  VecScale(&v2, a);
  VecScale(&v3, a);
  for (int i = 5; i--;)
    if (!ISEQUALF(VecGet(w, i), (float)(i + 1) * a)) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecFloatGetScale NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 2; i--;)
    if (!ISEQUALF(VecGet(&w2, i), (float)(i + 1) * a)) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecFloatGetScale NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 3; i--;)
    if (!ISEQUALF(VecGet(&w3, i), (float)(i + 1) * a)) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecFloatGetScale NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 5; i--;)
    if (!ISEQUALF(VecGet(v, i), (float)(i + 1) * a)) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecFloatScale NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 2; i--;)
    if (!ISEQUALF(VecGet(&v2, i), (float)(i + 1) * a)) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecFloatScale NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 3; i--;)
    if (!ISEQUALF(VecGet(&v3, i), (float)(i + 1) * a)) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecFloatScale NOK");
      PBErrCatch(PBMathErr);
    }
  VecFree(&v);
  VecFree(&w);
  printf("UnitTestVecFloatScale OK\n");
}

void UnitTestVecFloatOp() {
  VecFloat *v = VecFloatCreate(5);
  VecFloat2D v2 = VecFloatCreateStatic2D();
  VecFloat3D v3 = VecFloatCreateStatic3D();
  VecFloat *w = VecFloatCreate(5);
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
  VecFloat *u = VecGetOp(v, a[0], w, a[1]);
  VecFloat2D u2 = VecGetOp(&v2, a[0], &w2, a[1]);
  VecFloat3D u3 = VecGetOp(&v3, a[0], &w3, a[1]);
  float checku[5] = {5.2,3.1,1.0,-1.1,-3.2};
  float checku2[2] = {-0.8,-2.9};
  float checku3[3] = {1.2,-0.9,-3.0};
  for (int i = 5; i--;)
    if (!ISEQUALF(VecGet(u, i), checku[i])) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecFloatGetOp NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 2; i--;)
    if (!ISEQUALF(VecGet(&u2, i), checku2[i])) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecFloatGetOp NOK");
      PBErrCatch(PBMathErr);
    }
  for (int i = 3; i--;)
    if (!ISEQUALF(VecGet(&u3, i), checku3[i])) {
      PBMathErr->_type = PBErrTypeUnitTestFailed;
      sprintf(PBMathErr->_msg, "VecFloatGetOp NOK");
      PBErrCatch(PBMathErr);
    }
  VecOp(v, a[0], w, a[1]);
  VecOp(&v2, a[0], &w2, a[1]);
  VecOp(&v3, a[0], &w3, a[1]);
  if (!VecIsEqual(v, u)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatOp NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v2, &u2)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatOp NOK");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&v3, &u3)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatOp NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  VecFree(&w);
  VecFree(&u);
  printf("UnitTestVecFloatOp OK\n");
}

void UnitTestVecFloatDotProd() {
  VecFloat *v = VecFloatCreate(5);
  VecFloat2D v2 = VecFloatCreateStatic2D();
  VecFloat3D v3 = VecFloatCreateStatic3D();
  VecFloat *w = VecFloatCreate(5);
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
    sprintf(PBMathErr->_msg, "VecFloatDotProd NOK");
    PBErrCatch(PBMathErr);
  }
  prod = VecDotProd(&v2, &w2);
  if (!ISEQUALF(prod, -0.5)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatDotProd NOK");
    PBErrCatch(PBMathErr);
  }
  prod = VecDotProd(&v3, &w3);
  if (!ISEQUALF(prod, -3.5)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatDotProd NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  VecFree(&w);
  printf("UnitTestVecFloatDotProd OK\n");
}

void UnitTestVecFloatRotAngleTo() {
  VecFloat *v = VecFloatCreate(2);
  VecFloat2D v2 = VecFloatCreateStatic2D();
  VecFloat *w = VecFloatCreate(2);
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
        sprintf(PBMathErr->_msg, "VecFloatAngleTo NOK");
        PBErrCatch(PBMathErr);
      }
      if (!ISEQUALF(fabs(VecAngleTo(&w2, &v2)), fabs(a))) {
        PBMathErr->_type = PBErrTypeUnitTestFailed;
        sprintf(PBMathErr->_msg, "VecFloatAngleTo NOK");
        PBErrCatch(PBMathErr);
      }
    } else {
      if (!ISEQUALF(VecAngleTo(w, v), a)) {
        PBMathErr->_type = PBErrTypeUnitTestFailed;
        sprintf(PBMathErr->_msg, "VecFloatAngleTo NOK");
        PBErrCatch(PBMathErr);
      }
      if (!ISEQUALF(VecAngleTo(&w2, &v2), a)) {
        PBMathErr->_type = PBErrTypeUnitTestFailed;
        sprintf(PBMathErr->_msg, "VecFloatAngleTo NOK");
        PBErrCatch(PBMathErr);
      }
    }
  }
  VecSet(v, 0, 1.0);
  VecSet(v, 1, 0.0);
  VecRot(v, PBMATH_QUARTERPI);
  VecNormalise(v);
  VecPrint(v,stdout);printf("\n");
  if (!ISEQUALF(VecGet(v, 0), 0.70711) ||
    !ISEQUALF(VecGet(v, 1), 0.70711)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "VecFloatRot NOK");
    PBErrCatch(PBMathErr);
  }
  VecFree(&v);
  VecFree(&w);
  printf("UnitTestVecFloatAngleTo OK\n");
}

void UnitTestVecFloatToShort() {
  VecFloat *v = VecFloatCreate(5);
  VecFloat2D v2 = VecFloatCreateStatic2D();
  VecFloat3D v3 = VecFloatCreateStatic3D();
  for (int i = 5; i--;) VecSet(v, i, i + 1);
  for (int i = 2; i--;) VecSet(&v2, i, i + 1);
  for (int i = 3; i--;) VecSet(&v3, i, i + 1);
  VecShort *w = VecFloatToShort(v);
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
  VecFloat *v = VecFloatCreate(5);
  VecFloat2D v2 = VecFloatCreateStatic2D();
  VecFloat3D v3 = VecFloatCreateStatic3D();
  int nbTest = 100000;

  srandom(RANDOMSEED);
  int i = nbTest;
  clock_t clockBefore = clock();
  for (; i--;) {
    int j = INT(rnd() * ((float)(VecDim(v) - 1) - PBMATH_EPSILON));
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
    int j = INT(rnd() * ((float)(VecDim(v) - 1) - PBMATH_EPSILON));
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
  UnitTestVecFloatRotAngleTo();
  UnitTestVecFloatToShort();
  UnitTestSpeedVecFloat();
  printf("UnitTestVecFloat OK\n");
}

void UnitTestMatFloatCreateFree() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 2);
  VecSet(&dim, 1, 3);
  MatFloat *mat = MatFloatCreate(&dim);
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
  MatFloat *mat = MatFloatCreate(&dim);
  if (!VecIsEqual(&(mat->_dim), &dim)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "UnitTestMatFloatGetSetDim NOK");
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
  MatFloat *mat = MatFloatCreate(&dim);
  VecShort2D i = VecShortCreateStatic2D();
  float v = 1.0;
  do {
    MatSet(mat, &i, v);
    v += 1.0;
  } while(VecStep(&i, &dim));
  MatFloat *clone = MatClone(mat);
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
  MatFloat *mat = MatFloatCreate(&dim);
  VecShort2D i = VecShortCreateStatic2D();
  float v = 1.0;
  do {
    MatSet(mat, &i, v);
    v += 1.0;
  } while(VecStep(&i, &dim));
  FILE *f = fopen("./UnitTestMatFloatLoadSave.txt", "w");
  if (f == NULL) {
    PBMathErr->_type = PBErrTypeOther;
    sprintf(PBMathErr->_msg, 
      "Can't open ./UnitTestMatFloatLoadSave.txt for writing");
    PBErrCatch(PBMathErr);
  }
  if (!MatSave(mat, f)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "MatFloatSave NOK");
    PBErrCatch(PBMathErr);
  }
  fclose(f);
  MatFloat *clone = MatFloatCreate(&dim);
  f = fopen("./UnitTestMatFloatLoadSave.txt", "r");
  if (f == NULL) {
    PBMathErr->_type = PBErrTypeOther;
    sprintf(PBMathErr->_msg, 
      "Can't open ./UnitTestMatFloatLoadSave.txt for reading");
    PBErrCatch(PBMathErr);
  }
  if (!MatLoad(&clone, f)) {
    PBMathErr->_type = PBErrTypeUnitTestFailed;
    sprintf(PBMathErr->_msg, "MatFloatLoad NOK");
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
  ret = system("rm ./UnitTestMatFloatLoadSave.txt");
  ret = ret;
  printf("UnitTestMatFloatLoadSave OK\n");
}

void UnitTestMatFloatInv() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 3);
  VecSet(&dim, 1, 3);
  MatFloat *mat = MatFloatCreate(&dim);
  VecShort2D i = VecShortCreateStatic2D();
  float v[9] = {3.0, 2.0, 0.0, 0.0, 0.0, 1.0, 2.0, -2.0, 1.0};
  int j = 0;
  do {
    MatSet(mat, &i, v[j]);
    ++j;
  } while(VecStep(&i, &dim));
  MatFloat *inv = MatInv(mat);
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
  inv = MatInv(mat);
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
  MatFloat *mat = MatFloatCreate(&dim);
  VecShort2D i = VecShortCreateStatic2D();
  float v = 1.0;
  do {
    MatSet(mat, &i, v);
    v += 1.0;
  } while(VecStep(&i, &dim));
  VecFloat2D u = VecFloatCreateStatic2D();
  for (int j = 2; j--;)
    VecSet(&u, j, (float)j + 1.0);
  VecFloat *w = MatProdVec(mat, &u);
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
  MatFloat *mat = MatFloatCreate(&dim);
  VecShort2D i = VecShortCreateStatic2D();
  float v = 1.0;
  do {
    MatSet(mat, &i, v);
    v += 1.0;
  } while(VecStep(&i, &dim));
  VecSet(&dim, 0, 2);
  VecSet(&dim, 1, 3);
  MatFloat *matb = MatFloatCreate(&dim);
  VecSetNull(&i);
  v = 1.0;
  do {
    MatSet(matb, &i, v);
    v += 1.0;
  } while(VecStep(&i, &dim));
  MatFloat *matc = MatProdMat(mat, matb);
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

void UnitTestSpeedMatFloat() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 3);
  VecSet(&dim, 1, 3);
  MatFloat *mat = MatFloatCreate(&dim);
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

void UnitTestMatFloat() {
  UnitTestMatFloatCreateFree();
  UnitTestMatFloatGetSetDim();
  UnitTestMatFloatCloneIsEqual();
  UnitTestMatFloatLoadSave();
  UnitTestMatFloatInv();
  UnitTestMatFloatProdVecFloat();
  UnitTestMatFloatProdMatFloat();
  UnitTestSpeedMatFloat();
  printf("UnitTestMatFloat OK\n");
}

void UnitTestSysLinEq() {
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, 3);
  VecSet(&dim, 1, 3);
  MatFloat *mat = MatFloatCreate(&dim);
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
  SysLinEq *sys = SysLinEqCreate(mat, &v);
  VecFloat *res = SysLinEqSolve(sys);
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

void UnitTestBasicFunctions() {
  UnitTestConv();
  UnitTestPowi();
  UnitTestFastPow();
  UnitTestSpeedFastPow();
  UnitTestFSquare();
  UnitTestConv();
  printf("UnitTestBasicFunctions OK\n");
}

void UnitTestAll() {
  UnitTestVecShort();
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

