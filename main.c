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
  // Save the vector
  FILE *f = fopen("./vecshort.txt", "w");
  if (f == NULL) {
    fprintf(stderr, "fopen failed\n");
    return 2;
  }
  int ret = VecSave(a, f);
  if (ret != 0) {
    fprintf(stderr, "VecSave failed (%d)\n", ret);
    return 3;
  }
  fclose(f);
  // Load the vector
  f = fopen("./vecshort.txt", "r");
  if (f == NULL) {
    fprintf(stderr, "fopen failed\n");
    return 4;
  }
  VecShort *b = NULL;
  ret = VecLoad(&b, f);
  if (ret != 0) {
    fprintf(stderr, "VecLoad failed (%d)\n", ret);
    return 5;
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
  // Copy the loaded vector into the first one and print the first one
  VecCopy(a, b);
  fprintf(stdout, "a: ");
  VecPrint(a, stdout);
  fprintf(stdout, "\n");
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
    return 1;
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
  // Save the vector
  f = fopen("./vecfloat.txt", "w");
  if (f == NULL) {
    fprintf(stderr, "fopen failed\n");
    return 2;
  }
  ret = VecSave(v, f);
  if (ret != 0) {
    fprintf(stderr, "VecSave failed (%d)\n", ret);
    return 3;
  }
  fclose(f);
  // Load the vector
  f = fopen("./vecfloat.txt", "r");
  if (f == NULL) {
    fprintf(stderr, "fopen failed\n");
    return 4;
  }
  VecFloat *w = NULL;
  ret = VecLoad(&w, f);
  if (ret != 0) {
    fprintf(stderr, "VecLoad failed (%d)\n", ret);
    return 5;
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
    return 6;
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
    return 7;
  }
  VecSet(v, 0, 1.0);
  fprintf(stdout, "v: ");
  VecPrint(v, stdout);
  fprintf(stdout, "\n");
  VecRot2D(v, 0.5 * PBMATH_PI);
  fprintf(stdout, "v: ");
  VecPrint(v, stdout);
  fprintf(stdout, "\n");
  VecFree(&x);
  x = VecGetRot2D(v, 0.5 * PBMATH_PI);
  if (v == NULL) {
    fprintf(stderr, "VecGetRot2D failed\n");
    return 8;
  }
  fprintf(stdout, "x: ");
  VecPrint(x, stdout);
  fprintf(stdout, "\n");
  // Free memory
  VecFree(&x);
  VecFree(&w);
  VecFree(&v);
  // -------------- Gauss
  fprintf(stdout, "-------- Gauss\n");
  // Create a Gauss function
  float mean = 0.0;
  float sigma = 1.0;
  Gauss *gauss = GaussCreate(mean, sigma);
  // If we couldn't create the Gauss
  if (gauss == NULL) {
    fprintf(stderr, "Couldn't create the Gauss\n");
    return 9;
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

  // Return success code
  return 0;
}

