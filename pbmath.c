// ============ PBMATH.C ================

// ================= Include =================

#include "pbmath.h"
#if BUILDMODE == 0
#include "pbmath-inline.c"
#endif

// -------------- VecShort

// ================ Functions implementation ====================

// Create a new Vec of dimension 'dim'
// Values are initalized to 0.0
VecShort* VecShortCreate(int dim) {
#if BUILDMODE == 0
  if (dim <= 0) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "invalid 'dim' (%d)", dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // Allocate memory
  VecShort* that = PBErrMalloc(PBMathErr, 
    sizeof(VecShort) + sizeof(short) * dim);
  // Set the default values
  that->_dim = dim;
  for (int i = dim; i--;)
    that->_val[i] = 0;
  // Return the new VecShort
  return that;
}

// Clone the VecShort
// Return NULL if we couldn't clone the VecShort
VecShort* VecShortClone(VecShort* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Create a clone
  VecShort* clone = VecShortCreate(that->_dim);
  // Copy the values
  memcpy(clone, that, sizeof(VecShort) + sizeof(short) * that->_dim);
  // Return the clone
  return clone;
}

// Load the VecShort from the stream
// If the VecShort is already allocated, it is freed before loading
// Return true in case of success, else false
bool VecShortLoad(VecShort** that, FILE* stream) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (stream == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'stream' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // If 'that' is already allocated
  if (*that != NULL)
    // Free memory
    VecShortFree(that);
  // Read the number of dimension
  int dim;
  int ret = fscanf(stream, "%d", &dim);
  // If we coudln't fscanf
  if (ret == EOF)
    return false;
  // Check the dimension
  if (dim <= 0)
    return false;
  // Allocate memory
  *that = VecShortCreate(dim);
  // Read the values
  for (int i = 0; i < dim; ++i) {
    ret = fscanf(stream, "%hi", (*that)->_val + i);
    // If we coudln't fscanf
    if (ret == EOF)
      return false;
  }
  // Return success code
  return true;
}

// Save the VecShort to the stream
// Return true in case of success, else false
bool VecShortSave(VecShort* that, FILE* stream) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (stream == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'stream' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Save the dimension
  int ret = fprintf(stream, "%d ", that->_dim);
  // If we coudln't fprintf
  if (ret < 0)
    return false;
  // Save the values
  for (int i = 0; i < that->_dim; ++i) {
    ret = fprintf(stream, "%hi ", that->_val[i]);
    // If we coudln't fprintf
    if (ret < 0)
      return false;
  }
  fprintf(stream, "\n");
  // If we coudln't fprintf
  if (ret < 0)
    return false;
  // Return success code
  return true;
}

// Free the memory used by a VecShort
// Do nothing if arguments are invalid
void VecShortFree(VecShort** that) {
  // Check argument
  if (that == NULL || *that == NULL)
    return;
  // Free memory
  free(*that);
  *that = NULL;
}

// Print the VecShort on 'stream' with 'prec' digit precision
void VecShortPrint(VecShort* that, FILE* stream) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (stream == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'stream' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Print the values
  fprintf(stream, "<");
  for (int i = 0; i < that->_dim; ++i) {
    fprintf(stream, "%hi", that->_val[i]);
    if (i < that->_dim - 1)
      fprintf(stream, ",");
  }
  fprintf(stream, ">");
}

// Step the values of the vector incrementally by 1 from 0
// in the following order (for example) : 
// (0,0,0)->(0,0,1)->(0,0,2)->(0,1,0)->(0,1,1)->...
// The upper limit for each value is given by 'bound' (val[i] < dim[i])
// Return false if all values of 'that' have reached their upper limit 
// (in which case 'that''s values are all set back to 0)
// Return true else
bool VecShortStep(VecShort* that, VecShort* bound) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (bound == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'bound' is null");
    PBErrCatch(PBMathErr);
  }
  if (that->_dim != bound->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "dimensions don't match (%d==%d)", 
      that->_dim, bound->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable for the returned flag
  bool ret = true;
  // Declare a variable to memorise the dimension currently increasing
  int iDim = that->_dim - 1;
  // Declare a flag for the loop condition 
  bool flag = true;
  // Increment
  do {
    ++(that->_val[iDim]);
    if (that->_val[iDim] >= bound->_val[iDim]) {
      that->_val[iDim] = 0;
      --iDim;
    } else {
      flag = false;
    }
  } while (iDim >= 0 && flag == true);
  if (iDim == -1)
    ret = false;
  // Return the flag
  return ret;
}

// Step the values of the vector incrementally by 1 from 0
// in the following order (for example) : 
// (0,0,0)->(1,0,0)->(2,0,0)->(0,1,0)->(1,1,0)->...
// The upper limit for each value is given by 'bound' (val[i] < dim[i])
// Return false if all values of 'that' have reached their upper limit 
// (in which case 'that''s values are all set back to 0)
// Return true else
bool VecShortPStep(VecShort* that, VecShort* bound) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (bound == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'bound' is null");
    PBErrCatch(PBMathErr);
  }
  if (that->_dim != bound->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "dimensions don't match (%d==%d)", 
      that->_dim, bound->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable for the returned flag
  bool ret = true;
  // Declare a variable to memorise the dimension currently increasing
  int iDim = 0;
  // Declare a flag for the loop condition 
  bool flag = true;
  // Increment
  do {
    ++(that->_val[iDim]);
    if (that->_val[iDim] >= bound->_val[iDim]) {
      that->_val[iDim] = 0;
      ++iDim;
    } else {
      flag = false;
    }
  } while (iDim < that->_dim && flag == true);
  if (iDim == that->_dim)
    ret = false;
  // Return the flag
  return ret;
}

// Step the values of the vector incrementally by 1
// in the following order (for example) : 
// (0,0,0)->(0,0,1)->(0,0,2)->(0,1,0)->(0,1,1)->...
// The lower limit for each value is given by 'from' (val[i] >= from[i])
// The upper limit for each value is given by 'to' (val[i] < to[i])
// 'that' must be initialised to 'from' before the first call of this
// function
// Return false if all values of 'that' have reached their upper limit 
// (in which case 'that''s values are all set back to 0)
// Return true else
bool VecShortShiftStep(VecShort* that, VecShort* from, VecShort* to) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (from == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'from' is null");
    PBErrCatch(PBMathErr);
  }
  if (that->_dim != from->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'from' dimensions don't match (%d==%d)", 
      that->_dim, from->_dim);
    PBErrCatch(PBMathErr);
  }
  if (to == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'to' is null");
    PBErrCatch(PBMathErr);
  }
  if (that->_dim != to->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'to' dimensions don't match (%d==%d)", 
      that->_dim, to->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable for the returned flag
  bool ret = true;
  // Declare a variable to memorise the dimension currently increasing
  int iDim = that->_dim - 1;
  // Declare a flag for the loop condition 
  bool flag = true;
  // Increment
  do {
    ++(that->_val[iDim]);
    if (that->_val[iDim] >= to->_val[iDim]) {
      that->_val[iDim] = from->_val[iDim];
      --iDim;
    } else {
      flag = false;
    }
  } while (iDim >= 0 && flag == true);
  if (iDim == -1)
    ret = false;
  // Return the flag
  return ret;
}

// -------------- VecFloat

// ================ Functions implementation ====================

// Create a new Vec of dimension 'dim'
// Values are initalized to 0.0
VecFloat* VecFloatCreate(int dim) {
#if BUILDMODE == 0
  if (dim <= 0) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "invalid 'dim' (%d)", dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // Allocate memory
  VecFloat* that = PBErrMalloc(PBMathErr, 
    sizeof(VecFloat) + sizeof(float) * dim);
  // Set the default values
  that->_dim = dim;
  for (int i = dim; i--;)
    that->_val[i] = 0.0;
  // Return the new VecFloat
  return that;
}

// Clone the VecFloat
VecFloat* VecFloatClone(VecFloat* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Create a clone
  VecFloat* clone = VecFloatCreate(that->_dim);
  // Clone the properties
  memcpy(clone, that, sizeof(VecFloat) + sizeof(float) * that->_dim);
  // Return the clone
  return clone;
}

// Load the VecFloat from the stream
// If the VecFloat is already allocated, it is freed before loading
bool VecFloatLoad(VecFloat** that, FILE* stream) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (stream == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'stream' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // If 'that' is already allocated
  if (*that != NULL) {
    // Free memory
    VecFloatFree(that);
  }
  // Read the number of dimension
  int dim;
  int ret = fscanf(stream, "%d", &dim);
  // If we coudln't fscanf
  if (ret == EOF)
    return false;
  // Check the dimension
  if (dim <= 0)
    return false;
  // Allocate memory
  *that = VecFloatCreate(dim);
  // Read the values
  for (int i = 0; i < dim; ++i) {
    ret = fscanf(stream, "%f", (*that)->_val + i);
    // If we coudln't fscanf
    if (ret == EOF)
      return false;
  }
  // Return success code
  return true;
}

// Save the VecFloat to the stream
// Return true in case of success, else false
bool VecFloatSave(VecFloat* that, FILE* stream) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (stream == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'stream' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Save the dimension
  int ret = fprintf(stream, "%d ", that->_dim);
  // If we coudln't fprintf
  if (ret < 0)
    return false;
  // Save the values
  for (int i = 0; i < that->_dim; ++i) {
    ret = fprintf(stream, "%f ", that->_val[i]);
    // If we coudln't fprintf
    if (ret < 0)
      return false;
  }
  fprintf(stream, "\n");
  // If we coudln't fprintf
  if (ret < 0)
    return false;
  // Return success code
  return true;
}

// Free the memory used by a VecFloat
// Do nothing if arguments are invalid
void VecFloatFree(VecFloat** that) {
  // Check argument
  if (that == NULL || *that == NULL)
    return;
  // Free memory
  free(*that);
  *that = NULL;
}

// Print the VecFloat on 'stream' with 'prec' digit precision
// Do nothing if arguments are invalid
void VecFloatPrint(VecFloat* that, FILE* stream, unsigned int prec) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (stream == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'stream' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Create the format string
  char format[100] = {'\0'};
  sprintf(format, "%%.%df", prec);
  // Print the values
  fprintf(stream, "<");
  for (int i = 0; i < that->_dim; ++i) {
    fprintf(stream, format, that->_val[i]);
    if (i < that->_dim - 1)
      fprintf(stream, ",");
  }
  fprintf(stream, ">");
}

// Return the angle of the rotation making 'that' colinear to 'tho'
// 'that' and 'tho' must be normalised
// Return a value in [-PI,PI]
float VecFloatAngleTo2D(VecFloat2D* that, VecFloat2D* tho) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (tho == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'tho' is null");
    PBErrCatch(PBMathErr);
  }
  if (!ISEQUALF(VecNorm(that), 1.0)) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'that' is not a normed vector");
    PBErrCatch(PBMathErr);
  }
  if (!ISEQUALF(VecNorm(tho), 1.0)) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'tho' is not a normed vector");
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable to memorize the result
  float theta = 0.0;
  // Calculate the angle
  VecFloat2D m = VecFloatCreateStatic2D();
  if (fabs(VecGet(that, 0)) > fabs(VecGet(that, 1))) {
    VecSet(&m, 0, 
      (VecGet(tho, 0) + VecGet(tho, 1) * VecGet(that, 1) / 
      VecGet(that, 0)) /
      (VecGet(that, 0) + fsquare(VecGet(that, 1)) / VecGet(that, 0)));
    VecSet(&m, 1, 
      (VecGet(&m, 0) * VecGet(that, 1) - VecGet(tho, 1)) / 
      VecGet(that, 0));
  } else {
    VecSet(&m, 1,
      (VecGet(tho, 0) - VecGet(tho, 1) * VecGet(that, 0) / 
      VecGet(that, 1)) /
      (VecGet(that, 1) + fsquare(VecGet(that, 0)) / VecGet(that, 1)));
    VecSet(&m, 0, 
      (VecGet(tho, 1) + VecGet(&m, 1) * VecGet(that, 0)) / 
      VecGet(that, 1));
  }
  // Due to numerical imprecision m[0] may be slightly out of [-1,1]
  // which makes acos return NaN, prevent this
  if (VecGet(&m, 0) < -1.0)
    theta = PBMATH_PI;
  else if (VecGet(&m, 0) > 1.0)
    theta = 0.0;
  else
    theta = acos(VecGet(&m, 0));
  if (sin(theta) * VecGet(&m, 1) > 0.0)
    theta *= -1.0;
  // Return the result
  return theta;
}

// -------------- MatFloat

// ================= Define ==================

// ================ Functions implementation ====================

// Create a new MatFloat of dimension 'dim' (nbcol, nbline)
// Values are initalized to 0.0
MatFloat* MatFloatCreate(VecShort2D* dim) {
#if BUILDMODE == 0
  if (dim == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'dim' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Allocate memory
  int d = VecGet(dim, 0) * VecGet(dim, 1);
  MatFloat* that = PBErrMalloc(PBMathErr, sizeof(MatFloat) + 
    sizeof(float) * d);
  // Set the dimension
  that->_dim = *dim;
  // Set the default values
  for (int i = d; i--;)
    that->_val[i] = 0.0;
  // Return the new MatFloat
  return that;
}

// Clone the MatFloat
MatFloat* MatFloatClone(MatFloat* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Create a clone
  MatFloat* clone = MatFloatCreate(&(that->_dim));
  // Copy the values
  int d = VecGet(&(that->_dim), 0) * VecGet(&(that->_dim), 1);
  for (int i = d; i--;)
    clone->_val[i] = that->_val[i];
  // Return the clone
  return clone;
}

// Load the MatFloat from the stream
// If the MatFloat is already allocated, it is freed before loading
// Return true upon success, else false
bool MatFloatLoad(MatFloat** that, FILE* stream) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (stream == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'stream' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // If 'that' is already allocated
  if (*that != NULL)
    // Free memory
    MatFloatFree(that);
  // Read the number of dimension
  VecShort2D dim = VecShortCreateStatic2D();
  int ret = fscanf(stream, "%hi %hi", dim._val , dim._val + 1);
  // If we coudln't fscanf
  if (ret == EOF)
    return false;
  if (VecGet(&dim, 0) <= 0 || VecGet(&dim, 1) <= 0)
    return false;
  // Allocate memory
  *that = MatFloatCreate(&dim);
  // Read the values
  VecShort2D index = VecShortCreateStatic2D();
  do {
    float v;
    ret = fscanf(stream, "%f", &v);
    // If we coudln't fscanf
    if (ret == EOF)
      return false;
    MatSet(*that, &index, v);
  } while (VecPStep(&index, &dim));
  // Return success code
  return true;
}

// Save the MatFloat to the stream
// Return true upon success, else false
bool MatFloatSave(MatFloat* that, FILE* stream) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (stream == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'stream' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Save the dimension
  int ret = fprintf(stream, "%hi %hi\n", 
    VecGet(&(that->_dim), 0), VecGet(&(that->_dim), 1));
  if (ret < 0)
    return false;
  // Save the values
  VecShort2D index = VecShortCreateStatic2D();
  do {
    ret = fprintf(stream, "%f ", MatGet(that, &index));
    // If we coudln't fprintf
    if (ret < 0)
      return false;
    if (VecGet(&index, 0) == VecGet(&(that->_dim), 0) - 1) {
      ret = fprintf(stream, "\n");
      // If we coudln't fprintf
      if (ret < 0)
        return false;
    }
  } while (VecPStep(&index, &(that->_dim)));
  // Return success code
  return true;
}

// Free the memory used by a MatFloat
// Do nothing if arguments are invalid
void MatFloatFree(MatFloat** that) {
  // Check argument
  if (that == NULL || *that == NULL)
    return;
  // Free memory
  free(*that);
  *that = NULL;
}

// Print the MatFloat on 'stream' with 'prec' digit precision
// Do nothing if arguments are invalid
void MatFloatPrintln(MatFloat* that, FILE* stream, unsigned int prec) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (stream == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'stream' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Create the format string
  char format[100] = {'\0'};
  sprintf(format, "%%.%df", prec);
  // Print the values
  fprintf(stream, "[");
  VecShort2D index = VecShortCreateStatic2D();
  do {
    if (VecGet(&index, 1) != 0 || VecGet(&index, 0) != 0)
      fprintf(stream, " ");
    fprintf(stream, format, MatGet(that, &index));
    if (VecGet(&index, 0) < VecGet(&(that->_dim), 0) - 1)
      fprintf(stream, ",");
    if (VecGet(&index, 0) == VecGet(&(that->_dim), 0) - 1) {
      if (VecGet(&index, 1) == VecGet(&(that->_dim), 1) - 1)
        fprintf(stream, "]");
      fprintf(stream, "\n");
    }
  } while (VecPStep(&index, &(that->_dim)));
}

// Return the inverse matrix of 'that'
// The matrix must be a square matrix
MatFloat* MatFloatInv(MatFloat* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (VecGet(&(that->_dim), 0) != VecGet(&(that->_dim), 1)) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "the matrix is not square (%dx%d)",
      VecGet(&(that->_dim), 0), VecGet(&(that->_dim), 1));
    PBErrCatch(PBMathErr);
  }
  if (VecGet(&(that->_dim), 0) > 3) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, 
      "MatFloatInv is defined only for matrix of dim <= 3x3 (%dx%d)",
      VecGet(&(that->_dim), 0), VecGet(&(that->_dim), 1));
    PBErrCatch(PBMathErr);
  }
#endif
  // Allocate memory for the result
  MatFloat* res = MatFloatCreate(&(that->_dim));
  // If the matrix is of dimension 1x1
  if (VecGet(&(that->_dim), 0) == 1) {
#if BUILDMODE == 0
    if (that->_val[0] < PBMATH_EPSILON) {
      PBMathErr->_type = PBErrTypeOther;
      sprintf(PBMathErr->_msg, "the matrix is not inversible");
      PBErrCatch(PBMathErr);
    }
#endif 
    res->_val[0] = 1.0 / that->_val[0];
  // If the matrix is of dimension 2x2
  } else if (VecGet(&(that->_dim), 0) == 2) {
    float det = that->_val[0] * that->_val[3] - 
      that->_val[2] * that->_val[1];
#if BUILDMODE == 0
    if (ISEQUALF(det, 0.0)) {
      PBMathErr->_type = PBErrTypeOther;
      sprintf(PBMathErr->_msg, "the matrix is not inversible");
      PBErrCatch(PBMathErr);
    }
#endif 
    res->_val[0] = that->_val[3] / det;
    res->_val[1] = -1.0 * that->_val[1] / det;
    res->_val[2] = -1.0 * that->_val[2] / det;
    res->_val[3] = that->_val[0] / det;
  // Else, the matrix dimension is 3x3
  } else if (VecGet(&(that->_dim), 0) == 3) {
    float det = 
      that->_val[0] * 
        (that->_val[4] * that->_val[8] - 
        that->_val[5] * that->_val[7]) -
      that->_val[3] * 
        (that->_val[1] * that->_val[8] - 
        that->_val[2] * that->_val[7]) +
      that->_val[6] * 
        (that->_val[1] * that->_val[5] - 
        that->_val[2] * that->_val[4]);
#if BUILDMODE == 0
    if (ISEQUALF(det, 0.0)) {
      PBMathErr->_type = PBErrTypeOther;
      sprintf(PBMathErr->_msg, "the matrix is not inversible");
      PBErrCatch(PBMathErr);
    }
#endif 
    res->_val[0] = (that->_val[4] * that->_val[8] - 
        that->_val[5] * that->_val[7]) / det;
    res->_val[1] = -(that->_val[1] * that->_val[8] - 
        that->_val[2] * that->_val[7]) / det;
    res->_val[2] = (that->_val[1] * that->_val[5] - 
        that->_val[2] * that->_val[4]) / det;
    res->_val[3] = -(that->_val[3] * that->_val[8] - 
        that->_val[5] * that->_val[6]) / det;
    res->_val[4] = (that->_val[0] * that->_val[8] - 
        that->_val[2] * that->_val[6]) / det;
    res->_val[5] = -(that->_val[0] * that->_val[5] - 
        that->_val[2] * that->_val[3]) / det;
    res->_val[6] = (that->_val[3] * that->_val[7] - 
        that->_val[4] * that->_val[6]) / det;
    res->_val[7] = -(that->_val[0] * that->_val[7] - 
        that->_val[1] * that->_val[6]) / det;
    res->_val[8] = (that->_val[0] * that->_val[4] - 
        that->_val[1] * that->_val[3]) / det;
  }
  // Return the result
  return res;
}

// Return the product of matrix 'that' and vector 'v'
// Number of colum of 'that' must equal dimension of 'v'
VecFloat* MatFloatProdVecFloat(MatFloat* that, VecFloat* v) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (v == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'v' is null");
    PBErrCatch(PBMathErr);
  }
  if (VecGet(&(that->_dim), 0) != VecDim(v)) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, 
      "the matrix and vector have incompatible dimensions (%d==%d)",
      VecGet(&(that->_dim), 0), VecDim(v));
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable to memorize the index in the matrix
  VecShort2D i = VecShortCreateStatic2D();
  // Allocate memory for the solution
  VecFloat* ret = VecFloatCreate(VecGet(&(that->_dim), 1));
  // If we could allocate memory
  if (ret != NULL)
    for (VecSet(&i, 0, 0); VecGet(&i, 0) < VecGet(&(that->_dim), 0);
      VecSet(&i, 0, VecGet(&i, 0) + 1))
      for (VecSet(&i, 1, 0); VecGet(&i, 1) < VecGet(&(that->_dim), 1);
        VecSet(&i, 1, VecGet(&i, 1) + 1))
        VecSet(ret, VecGet(&i, 1), VecGet(ret, 
          VecGet(&i, 1)) + VecGet(v, VecGet(&i, 0)) * MatGet(that, &i));
  // Return the result
  return ret;
}

// Return the product of matrix 'that' by matrix 'tho'
// Number of columns of 'that' must equal number of line of 'tho'
MatFloat* MatFloatProdMatFloat(MatFloat* that, MatFloat* tho) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (tho == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'tho' is null");
    PBErrCatch(PBMathErr);
  }
  if (VecGet(&(that->_dim), 0) != VecGet(&(tho->_dim), 1)) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, 
      "the matrices have incompatible dimensions (%d==%d)",
      VecGet(&(that->_dim), 0), VecGet(&(tho->_dim), 1));
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare 3 variables to memorize the index in the matrix
  VecShort2D i = VecShortCreateStatic2D();
  VecShort2D j = VecShortCreateStatic2D();
  VecShort2D k = VecShortCreateStatic2D();
  // Allocate memory for the solution
  VecSet(&i, 0, VecGet(&(tho->_dim), 0));
  VecSet(&i, 1, VecGet(&(that->_dim), 1));
  MatFloat* ret = MatFloatCreate(&i);
  for (VecSet(&i, 0, 0); VecGet(&i, 0) < VecGet(&(tho->_dim), 0);
    VecSet(&i, 0, VecGet(&i, 0) + 1))
    for (VecSet(&i, 1, 0); VecGet(&i, 1) < VecGet(&(that->_dim), 1);
      VecSet(&i, 1, VecGet(&i, 1) + 1))
      for (VecSet(&j, 0, 0), VecSet(&j, 1, VecGet(&i, 1)),
        VecSet(&k, 0, VecGet(&i, 0)), VecSet(&k, 1, 0); 
        VecGet(&j, 0) < VecGet(&(that->_dim), 0);
        VecSet(&j, 0, VecGet(&j, 0) + 1), 
        VecSet(&k, 1, VecGet(&k, 1) + 1)) {
        MatSet(ret, &i, MatGet(ret, &i) + 
          MatGet(that, &j) * MatGet(tho, &k));
      }
  // Return the result
  return ret;
}

// Return true if 'that' is equal to 'tho', false else
bool MatFloatIsEqual(MatFloat* that, MatFloat* tho) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (tho == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'tho' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  if (!VecIsEqual(&(that->_dim), &(tho->_dim)))
    return false;
  VecShort2D v = VecShortCreateStatic2D();
  do {
    if (!ISEQUALF(MatGet(that, &v), MatGet(tho, &v)))
      return false;
  } while (VecStep(&v, &(that->_dim)));
  return true;
}

// -------------- Gauss

// ================= Define ==================

// ================ Functions implementation ====================

// Create a new Gauss of mean 'mean' and sigma 'sigma'
// Return NULL if we couldn't create the Gauss
Gauss* GaussCreate(float mean, float sigma) {
  // Allocate memory
  Gauss *that = PBErrMalloc(PBMathErr, sizeof(Gauss));
  // Set properties
  that->_mean = mean;
  that->_sigma = sigma;
  // Return the new Gauss
  return that;
}
Gauss GaussCreateStatic(float mean, float sigma) {
  // Allocate memory
  Gauss that = {._mean = mean, ._sigma = sigma};
  // Return the new Gauss
  return that;
}

// Free the memory used by a Gauss
// Do nothing if arguments are invalid
void GaussFree(Gauss **that) {
  // Check argument
  if (that == NULL || *that == NULL)
    return;
  // Free memory
  free(*that);
  *that = NULL;
}

// -------------- SysLinEq

// ================ Functions implementation ====================

// Create a new SysLinEq with matrix 'm' and vector 'v'
// The dimension of 'v' must be equal to the number of column of 'm'
// If 'v' is null the vector null is used instead
// The matrix 'm' must be a square matrix
// Return NULL if we couldn't create the SysLinEq
SysLinEq* SLECreate(MatFloat* m, VecFloat* v) {
#if BUILDMODE == 0
  if (m == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'m' is null");
    PBErrCatch(PBMathErr);
  }
  if (VecGet(&(m->_dim), 0) != VecGet(&(m->_dim), 1)) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "the matrix is not square (%dx%d)",
      VecGet(&(m->_dim), 0), VecGet(&(m->_dim), 1));
    PBErrCatch(PBMathErr);
  }
  if (v != NULL) {
    if (VecGet(&(m->_dim), 0) != VecDim(v)) {
      PBMathErr->_type = PBErrTypeInvalidArg;
      sprintf(PBMathErr->_msg, 
        "the matrix and vector have incompatible dimensions (%d==%d)",
        VecGet(&(m->_dim), 0), VecDim(v));
      PBErrCatch(PBMathErr);
    }
  }
#endif
  // Allocate memory
  SysLinEq* that = PBErrMalloc(PBMathErr, sizeof(SysLinEq));
  that->_M = MatClone(m);
  that->_Minv = MatInv(that->_M);
  if (v != NULL)
    that->_V = VecClone(v);
  else
    that->_V = VecFloatCreate(VecGet(&(m->_dim), 0));
  if (that->_M == NULL || that->_V == NULL || that->_Minv == NULL) {
#if BUILDMODE == 0
    if (that->_M == NULL) {
      PBMathErr->_type = PBErrTypeOther;
      sprintf(PBMathErr->_msg, "couldn't create the matrix");
      PBErrCatch(PBMathErr);
    }
    if (that->_Minv == NULL) {
      PBMathErr->_type = PBErrTypeOther;
      sprintf(PBMathErr->_msg, "couldn't inverse the matrix");
      PBErrCatch(PBMathErr);
    }
    if (that->_V == NULL) {
      PBMathErr->_type = PBErrTypeOther;
      sprintf(PBMathErr->_msg, "couldn't create the vector");
      PBErrCatch(PBMathErr);
    }
#endif
    SysLinEqFree(&that);
  }
  // Return the new SysLinEq
  return that;
}

// Free the memory used by the SysLinEq
// Do nothing if arguments are invalid
void SysLinEqFree(SysLinEq** that) {
  // Check arguments
  if (that == NULL || *that == NULL)
    return;
  // Free memory
  MatFree(&((*that)->_M));
  MatFree(&((*that)->_Minv));
  VecFree(&((*that)->_V));
  free(*that);
  *that = NULL;
}

// Clone the SysLinEq 'that'
// Return NULL if we couldn't clone the SysLinEq
SysLinEq* SysLinEqClone(SysLinEq* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable for the result
  SysLinEq* ret = PBErrMalloc(PBMathErr, sizeof(SysLinEq));
  ret->_M = MatClone(that->_M);
  ret->_Minv = MatClone(that->_Minv);
  ret->_V = VecClone(that->_V);
  if (ret->_M == NULL || ret->_V == NULL || ret->_Minv == NULL)
    SysLinEqFree(&ret);
  // Return the new SysLinEq
  return ret;
}

