#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "pbmath.h"

int main(int argc, char **argv) {
  // Create a vector of dimension 3
  VecFloat *v = VecFloatCreate(3);
  // If we couldn't create the vector
  if (v == NULL) {
    fprintf(stderr, "VecCreate failed\n");
    return 1;
  }
  // Print the vector
  VecPrint(v, stdout);
  fprintf(stdout, "\n");
  // Set the 2nd value to 1.0
  VecSet(v, 1, 1.0);
  // Print the vector
  VecPrint(v, stdout);
  fprintf(stdout, "\n");
  // Save the vector
  FILE *f = fopen("./vec.txt", "w");
  if (f == NULL) {
    fprintf(stderr, "fopen failed\n");
    return 2;
  }
  int ret = VecSave(v, f);
  if (ret != 0) {
    fprintf(stderr, "VecSave failed (%d)\n", ret);
    return 3;
  }
  fclose(f);
  // Load the vector
  f = fopen("./vec.txt", "r");
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
  fprintf(stdout, "%d ", VecDim(w));
  for (int i = 0; i < VecDim(w); ++i)
    fprintf(stdout, "%f ", VecGet(w, i));
  fprintf(stdout, "\n");
  // Change the values of the loaded vector and print it
  VecSet(w, 0, 2.0);
  VecSet(w, 2, 3.0);
  VecPrint(w, stdout);
  fprintf(stdout, "\n");
  // Copy the loaded vector into the first one and print th first one
  VecCopy(v, w);
  VecPrint(v, stdout);
  fprintf(stdout, "\n");
  // Free memory
  VecFree(&w);
  VecFree(&v);
  // Return success code
  return 0;
}

