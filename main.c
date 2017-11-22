#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "pbmath.h"

int main(int argc, char **argv) {
  // Initialise the random generator
  srandom(time(NULL));

  // -------------- VecShort
  fprintf(stdout, "-------- VecShort\n");
  // Create a vector of dimension 3
  VecShort *a = VecShortCreate(3);
  // If we couldn't create the vector
  if (a == NULL) {
    fprintf(stderr, "VecCreate failed\n");
    return 1;
  }
  // Print the vector
  fprintf(stdout, "a: ");
  VecPrint(a, stdout);
  fprintf(stdout, "\n");
  // Set the 2nd value to 1
  VecSet(a, 1, 1);
  // Print the vector
  fprintf(stdout, "a: ");
  VecPrint(a, stdout);
  fprintf(stdout, "\n");
  // Clone the vector
  VecShort *cloneShort = VecClone(a);
  if (cloneShort == NULL) {
    fprintf(stderr, "VecClone failed\n");
    return 2;
  }
  // Print the vector
  fprintf(stdout, "cloneShort: ");
  VecPrint(cloneShort, stdout);
  fprintf(stdout, "\n");
  VecFree(&cloneShort);
  // Save the vector
  FILE *f = fopen("./vecshort.txt", "w");
  if (f == NULL) {
    fprintf(stderr, "fopen failed\n");
    return 3;
  }
  int ret = VecSave(a, f);
  if (ret != 0) {
    fprintf(stderr, "VecSave failed (%d)\n", ret);
    return 4;
  }
  fclose(f);
  // Load the vector
  f = fopen("./vecshort.txt", "r");
  if (f == NULL) {
    fprintf(stderr, "fopen failed\n");
    return 5;
  }
  VecShort *b = NULL;
  ret = VecLoad(&b, f);
  if (ret != 0) {
    fprintf(stderr, "VecLoad failed (%d)\n", ret);
    return 6;
  }
  fclose(f);
  // Get the dimension and values of the loaded vector
  fprintf(stdout, "b: %d ", VecDim(b));
  for (int i = 0; i < VecDim(b); ++i)
    fprintf(stdout, "%d ", VecGet(b, i));
  fprintf(stdout, "\n");
  // Change the values of the loaded vector and print it
  VecSet(b, 0, 2);
  VecSet(b, 2, 3);
  fprintf(stdout, "b: ");
  VecPrint(b, stdout);
  fprintf(stdout, "\n");
  // VecProd
  short prod = VecDotProd(a, b);
  fprintf(stdout,"VecProd(a,b): %d\n",prod);
  // Copy the loaded vector into the first one and print the first one
  VecCopy(a, b);
  fprintf(stdout, "a: ");
  VecPrint(a, stdout);
  fprintf(stdout, "\n");
  // Reset a
  fprintf(stdout,"Reset a:");
  VecSetNull(a);
  VecPrint(a, stdout);
  fprintf(stdout, "\n");
  // step a up to b
  fprintf(stdout,"Step a up to b:\n");
  do {
    VecPrint(a, stdout);
    fprintf(stdout, "\n");
  } while(VecStep(a, b));
  // Free memory
  VecFree(&a);
  VecFree(&b);

  // -------------- VecFloat
  fprintf(stdout, "-------- VecFloat\n");
  // Create a vector of dimension 3
  VecFloat *v = VecFloatCreate(3);
  // If we couldn't create the vector
  if (v == NULL) {
    fprintf(stderr, "VecCreate failed\n");
    return 7;
  }
  // Print the vector
  fprintf(stdout, "v: ");
  VecPrint(v, stdout);
  fprintf(stdout, "\n");
  // Set the 2nd value to 1.0
  VecSet(v, 1, 1.0);
  // Print the vector
  fprintf(stdout, "v: ");
  VecPrint(v, stdout);
  fprintf(stdout, "\n");
  // Clone the vector
  VecFloat *cloneFloat = VecClone(v);
  if (cloneFloat == NULL) {
    fprintf(stderr, "VecClone failed\n");
    return 8;
  }
  // Print the vector
  fprintf(stdout, "cloneFloat: ");
  VecPrint(cloneFloat, stdout);
  fprintf(stdout, "\n");
  VecFree(&cloneFloat);
  // Save the vector
  f = fopen("./vecfloat.txt", "w");
  if (f == NULL) {
    fprintf(stderr, "fopen failed\n");
    return 9;
  }
  ret = VecSave(v, f);
  if (ret != 0) {
    fprintf(stderr, "VecSave failed (%d)\n", ret);
    return 10;
  }
  fclose(f);
  // Load the vector
  f = fopen("./vecfloat.txt", "r");
  if (f == NULL) {
    fprintf(stderr, "fopen failed\n");
    return 11;
  }
  VecFloat *w = NULL;
  ret = VecLoad(&w, f);
  if (ret != 0) {
    fprintf(stderr, "VecLoad failed (%d)\n", ret);
    return 12;
  }
  fclose(f);
  // Get the dimension and values of the loaded vector
  fprintf(stdout, "w: %d ", VecDim(w));
  for (int i = 0; i < VecDim(w); ++i)
    fprintf(stdout, "%f ", VecGet(w, i));
  fprintf(stdout, "\n");
  // Change the values of the loaded vector and print it
  VecSet(w, 0, 2.0);
  VecSet(w, 2, 3.0);
  fprintf(stdout, "w: ");
  VecPrint(w, stdout);
  fprintf(stdout, "\n");
  // Copy the loaded vector into the first one and print the first one
  VecCopy(v, w);
  fprintf(stdout, "v: ");
  VecPrint(v, stdout);
  fprintf(stdout, "\n");
  // Get the norm
  float norm = VecNorm(v);
  fprintf(stdout, "Norm of v: %.3f\n", norm);
  // Normalise
  VecNormalise(v);
  fprintf(stdout, "Normalized v: ");
  VecPrint(v, stdout);
  fprintf(stdout, "\n");
  // Distance between v and w  
  fprintf(stdout, "Distance between v and w: %.3f\n", VecDist(v, w));
  fprintf(stdout, "Hamiltonian distance between v and w: %.3f\n",
    VecHamiltonDist(v, w));
  fprintf(stdout, "Pixel distance between v and w: %.3f\n",
    VecPixelDist(v, w));
  // Equality
  if (VecIsEqual(v, w) == true)
    fprintf(stdout, "v = w\n");
  else
    fprintf(stdout, "v != w\n");
  if (VecIsEqual(v, v) == true)
    fprintf(stdout, "v = v\n");
  else
    fprintf(stdout, "v != v\n");
  // Op
  VecFloat *x = VecGetOp(v, norm, w, 2.0);
  if (x == NULL) {
    fprintf(stderr, "VecGetOp failed\n");
    return 13;
  }
  fprintf(stdout, "x: ");
  VecPrint(x, stdout);
  fprintf(stdout, "\n");
  VecOp(v, norm, NULL, 0.0);
  fprintf(stdout, "v: ");
  VecPrint(v, stdout);
  fprintf(stdout, "\n");
  // Dot prod
  fprintf(stdout, "dot prod v.x: %.3f\n", VecDotProd(v, x));
  // Rotate
  VecFree(&v);
  v = VecFloatCreate(2);
  if (v == NULL) {
    fprintf(stderr, "malloc failed\n");
    return 14;
  }
  VecSet(v, 0, 1.0);
  fprintf(stdout, "v: ");
  VecPrint(v, stdout);
  fprintf(stdout, "\n");
  VecRot2D(v, PBMATH_QUARTERPI);
  fprintf(stdout, "v: ");
  VecPrint(v, stdout);
  fprintf(stdout, "\n");
  VecFree(&x);
  x = VecGetRot2D(v, PBMATH_QUARTERPI);
  if (v == NULL) {
    fprintf(stderr, "VecGetRot2D failed\n");
    return 15;
  }
  fprintf(stdout, "x: ");
  VecPrint(x, stdout);
  fprintf(stdout, "\n");
  // AngleTo
  fprintf(stdout, "Angle between vector:\n");
  float dtheta = PBMATH_PI / 6.0;
  VecSet(x, 0, 1.0); VecSet(x, 1, 0.0); 
  for (int i = 0; i < 12; ++i) {
    VecSet(v, 0, 1.0); VecSet(v, 1, 0.0); 
    for (int j = 0; j < 12; ++j) {
      VecPrint(x, stdout);
      fprintf(stdout, " ");
      VecPrint(v, stdout);
      fprintf(stdout, " %.3f\n", ConvRad2Deg(VecAngleTo2D(x, v)));
      VecRot2D(v, dtheta);
    }
    VecRot2D(x, dtheta);
  }
  // Free memory
  VecFree(&x);
  VecFree(&w);
  VecFree(&v);

  // -------------- MatFloat
  fprintf(stdout, "-------- MatFloat\n");
  // Create a matrix of dimension 3,2
  VecShort *dimMat = VecShortCreate(2);
  VecSet(dimMat, 0, 3);
  VecSet(dimMat, 1, 2);
  MatFloat *mat = MatFloatCreate(dimMat);
  // If we couldn't create the matrix
  if (mat == NULL) {
    fprintf(stderr, "MatCreate failed\n");
    return 16;
  }
  // Print the matrix
  fprintf(stdout, "mat: \n");
  MatPrint(mat, stdout);
  fprintf(stdout, "\n");
  // Set some values
  VecSet(dimMat, 0, 0);
  VecSet(dimMat, 1, 0);
  MatSet(mat, dimMat, 0.5);
  VecSet(dimMat, 0, 0);
  VecSet(dimMat, 1, 1);
  MatSet(mat, dimMat, 2.0);
  VecSet(dimMat, 0, 0);
  VecSet(dimMat, 1, 2);
  MatSet(mat, dimMat, 1.0);
  VecSet(dimMat, 0, 1);
  VecSet(dimMat, 1, 0);
  MatSet(mat, dimMat, 2.0);
  VecSet(dimMat, 0, 2);
  VecSet(dimMat, 1, 1);
  MatSet(mat, dimMat, 1.0);
  // Print the matrix
  fprintf(stdout, "mat: \n");
  MatPrint(mat, stdout);
  fprintf(stdout, "\n");
  // Clone the matrix
  MatFloat *cloneMatFloat = MatClone(mat);
  if (cloneMatFloat == NULL) {
    fprintf(stderr, "MatClone failed\n");
    return 17;
  }
  // Print the matrix
  fprintf(stdout, "cloneMatFloat:\n");
  MatPrint(cloneMatFloat, stdout);
  fprintf(stdout, "\n");
  MatFree(&cloneMatFloat);
  // Save the matrix
  f = fopen("./matfloat.txt", "w");
  if (f == NULL) {
    fprintf(stderr, "fopen failed\n");
    return 18;
  }
  ret = MatSave(mat, f);
  if (ret != 0) {
    fprintf(stderr, "MatSave failed (%d)\n", ret);
    return 19;
  }
  fclose(f);
  // Load the matrix
  f = fopen("./matfloat.txt", "r");
  if (f == NULL) {
    fprintf(stderr, "fopen failed\n");
    return 20;
  }
  MatFloat *matb = NULL;
  ret = MatLoad(&matb, f);
  if (ret != 0) {
    fprintf(stderr, "MatLoad failed (%d)\n", ret);
    return 21;
  }
  fclose(f);
  // Get the dimension and values of the loaded matrix
  VecShort *dimMatb = MatDim(matb);
  fprintf(stdout, "dim loaded matrix: ");
  VecPrint(dimMatb, stdout);
  fprintf(stdout, "\n");
  for (VecSet(dimMat, 1, 0); VecGet(dimMat, 1) < VecGet(dimMatb, 1); 
    VecSet(dimMat, 1, VecGet(dimMat, 1) + 1)) {
    for (VecSet(dimMat, 0, 0); VecGet(dimMat, 0) < VecGet(dimMatb, 0); 
      VecSet(dimMat, 0, VecGet(dimMat, 0) + 1))
      fprintf(stdout, "%f ", MatGet(matb, dimMat));
    fprintf(stdout, "\n");
  }
  // MatProdVec
  v = VecFloatCreate(3);
  if (v == NULL) {
    fprintf(stderr, "VecFloatCreate failed\n");
    return 22;
  }
  VecSet(v, 0, 2.0);
  VecSet(v, 1, 3.0);
  VecSet(v, 2, 4.0);
  w = MatProd(matb, v);
  if (w == NULL) {
    fprintf(stderr, "MatProd failed\n");
    return 23;
  }
  fprintf(stdout, "Mat prod of\n");
  MatPrint(matb, stdout);
  fprintf(stdout, "\nand\n");
  VecPrint(v, stdout);
  fprintf(stdout, "\nequals\n");
  VecPrint(w, stdout);
  fprintf(stdout, "\n");
  VecFree(&v);
  VecFree(&w);
  // MatProdMat
  VecSet(dimMat, 0, VecGet(dimMatb, 1));
  VecSet(dimMat, 1, VecGet(dimMatb, 0));
  MatFloat *matc = MatFloatCreate(dimMat);
  if (matc == NULL) {
    fprintf(stderr, "MatFloatCreate failed\n");
    return 24;
  }
  VecSet(dimMat, 0, 0);
  VecSet(dimMat, 1, 0);
  MatSet(matc, dimMat, 1.0);
  VecSet(dimMat, 0, 0);
  VecSet(dimMat, 1, 1);
  MatSet(matc, dimMat, 2.0);
  VecSet(dimMat, 0, 0);
  VecSet(dimMat, 1, 2);
  MatSet(matc, dimMat, 3.0);
  VecSet(dimMat, 0, 1);
  VecSet(dimMat, 1, 0);
  MatSet(matc, dimMat, 4.0);
  VecSet(dimMat, 0, 1);
  VecSet(dimMat, 1, 1);
  MatSet(matc, dimMat, 5.0);
  VecSet(dimMat, 0, 1);
  VecSet(dimMat, 1, 2);
  MatSet(matc, dimMat, 6.0);
  fprintf(stdout, "Mat prod of\n");
  MatPrint(mat, stdout);
  fprintf(stdout, "\nand\n");
  MatPrint(matc, stdout);
  fprintf(stdout, "\nequals\n");
  MatFloat *matd = MatProd(mat, matc);
  if (matd == NULL) {
    fprintf(stderr, "MatProd failed\n");
    return 25;
  }
  MatPrint(matd, stdout);
  fprintf(stdout, "\n");  
  // Create a matrix and set it to identity
  VecSet(dimMat, 0, 3);
  VecSet(dimMat, 1, 3);
  MatFloat *squareMat = MatFloatCreate(dimMat);
  MatSetIdentity(squareMat);
  fprintf(stdout, "identity:\n");
  MatPrint(squareMat, stdout);
  fprintf(stdout, "\n");
  // Matrix inverse
  VecSet(dimMat, 0, 0);
  VecSet(dimMat, 1, 0);
  MatSet(squareMat, dimMat, 3.0);
  VecSet(dimMat, 0, 1);
  VecSet(dimMat, 1, 0);
  MatSet(squareMat, dimMat, 0.0);
  VecSet(dimMat, 0, 2);
  VecSet(dimMat, 1, 0);
  MatSet(squareMat, dimMat, 2.0);
  VecSet(dimMat, 0, 0);
  VecSet(dimMat, 1, 1);
  MatSet(squareMat, dimMat, 2.0);
  VecSet(dimMat, 0, 1);
  VecSet(dimMat, 1, 1);
  MatSet(squareMat, dimMat, 0.0);
  VecSet(dimMat, 0, 2);
  VecSet(dimMat, 1, 1);
  MatSet(squareMat, dimMat, -2.0);
  VecSet(dimMat, 0, 0);
  VecSet(dimMat, 1, 2);
  MatSet(squareMat, dimMat, 0.0);
  VecSet(dimMat, 0, 1);
  VecSet(dimMat, 1, 2);
  MatSet(squareMat, dimMat, 1.0);
  VecSet(dimMat, 0, 2);
  VecSet(dimMat, 1, 2);
  MatSet(squareMat, dimMat, 1.0);
  MatFloat *matinv = MatInv(squareMat);
  if (matinv == NULL) {
    fprintf(stderr, "MatInv failed\n");
    return 26;
  }
  fprintf(stdout, "inverse of:\n");
  MatPrint(squareMat, stdout);
  fprintf(stdout, "\nequals\n");
  MatPrint(matinv, stdout);
  fprintf(stdout, "\n");
  MatFloat *checkinv = MatProd(squareMat, matinv);
  fprintf(stdout, "check of inverse:\n");
  MatPrint(checkinv, stdout);
  fprintf(stdout, "\n");
  // Free memory
  VecFree(&dimMat);
  VecFree(&dimMatb);
  MatFree(&mat);
  MatFree(&matb);
  MatFree(&matc);
  MatFree(&matd);
  MatFree(&checkinv);
  MatFree(&squareMat);
  MatFree(&matinv);

  // -------------- Gauss
  fprintf(stdout, "-------- Gauss\n");
  // Create a Gauss function
  float mean = 0.0;
  float sigma = 1.0;
  Gauss *gauss = GaussCreate(mean, sigma);
  // If we couldn't create the Gauss
  if (gauss == NULL) {
    fprintf(stderr, "Couldn't create the Gauss\n");
    return 27;
  }
  // Get some values of the Gauss function
  fprintf(stdout, "Gauss function (mean:0.0, sigma:1.0):\n");
  for (float x = -2.0; x <= 2.01; x += 0.2)
    fprintf(stdout, "%.3f %.3f\n", x, GaussGet(gauss, x));
  // Change the mean
  gauss->_mean = 1.0;
  gauss->_sigma = 0.5;
  // Get some random values according to the Gauss function
  fprintf(stdout, "Gauss rnd (mean:1.0, sigma:0.5):\n");
  for (int iVal = 0; iVal < 10; ++iVal)
    fprintf(stdout, "%.3f %.3f\n", GaussRnd(gauss), GaussRnd(gauss));
  //Free memory
  GaussFree(&gauss);
  
  // -------------- Smoother
  fprintf(stdout, "-------- Smoother\n");
  for (float x = 0.0; x <= 1.01; x += 0.1)
    fprintf(stdout, "%.3f %.3f %.3f\n", x, SmoothStep(x), 
      SmootherStep(x));

  // -------------- Conversion functions
  fprintf(stdout, "-------- Conversion functions\n");
  fprintf(stdout, "%f radians -> %f degrees\n", PBMATH_QUARTERPI, 
    ConvRad2Deg(PBMATH_QUARTERPI));
  fprintf(stdout, "%f radians -> %f degrees\n", 90.0, 
    ConvDeg2Rad(90.0));

  // -------------- Usefull basic functions
  fprintf(stdout, "-------- Usefull basic functions\n");
  fprintf(stdout, "10^2 = %d\n", powi(10, 2));

  // Return success code
  return 0;
}

