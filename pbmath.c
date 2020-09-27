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
VecShort* VecShortCreate(const long dim) {
#if BUILDMODE == 0
  if (dim <= 0) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "invalid 'dim' (%ld)", dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // Allocate memory
  VecShort* that = PBErrMalloc(PBMathErr, 
    offsetof(VecShort, _val) + sizeof(short) * dim);
  // Set the default values
  that->_dim = dim;
  for (long i = dim; i--;)
    that->_val[i] = 0;
  // Return the new VecShort
  return that;
}

// Clone the VecShort
// Return NULL if we couldn't clone the VecShort
VecShort* _VecShortClone(const VecShort* const that) {
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

// Function which return the JSON encoding of 'that' 
JSONNode* _VecShortEncodeAsJSON(const VecShort* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Create the JSON structure
  JSONNode* json = JSONCreate();
  // Declare a buffer to convert value into string
  char val[100];
  // Encode the dimension
  sprintf(val, "%ld", VecGetDim(that));
  JSONAddProp(json, "_dim", val);
  // Encode the values
  JSONArrayVal setVal = JSONArrayValCreateStatic();
  for (long i = 0; i < VecGetDim(that); ++i) {
    sprintf(val, "%d", VecGet(that, i));
    JSONArrayValAdd(&setVal, val);
  }
  JSONAddProp(json, "_val", &setVal);
  // Free memory
  JSONArrayValFlush(&setVal);
  // Return the created JSON 
  return json;
}

// Function which decode from JSON encoding 'json' to 'that'
bool _VecShortDecodeAsJSON(VecShort** that, const JSONNode* const json) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (json == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'json' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // If 'that' is already allocated
  if (*that != NULL)
    // Free memory
    _VecShortFree(that);
  // Get the dimension from the JSON
  JSONNode* prop = JSONProperty(json, "_dim");
  if (prop == NULL) {
    return false;
  }
  long dim = atol(JSONLblVal(prop));
  // If data are invalid
  if (dim < 1)
    return false;
  // Allocate memory
  *that = VecShortCreate(dim);
  // Get the values
  prop = JSONProperty(json, "_val");
  if (prop == NULL) {
    return false;
  }
  for (long i = 0; i < dim; ++i) {
    long val = atol(JSONLabel(JSONValue(prop, i)));
    VecSet(*that, i, val);
  }
  // Return the success code
  return true;
}

// Load the VecShort from the stream
// If the VecShort is already allocated, it is freed before loading
// Return true in case of success, else false
bool _VecShortLoad(VecShort** that, FILE* const stream) {
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
  // Declare a json to load the encoded data
  JSONNode* json = JSONCreate();
  // Load the whole encoded data
  if (!JSONLoad(json, stream)) {
    return false;
  }
  // Decode the data from the JSON
  if (!VecDecodeAsJSON(that, json)) {
    return false;
  }
  // Free the memory used by the JSON
  JSONFree(&json);
  // Return the success code
  return true;
}

// Save the VecShort to the stream
// If 'compact' equals true it saves in compact form, else it saves in 
// readable form
// Return true in case of success, else false
bool _VecShortSave(const VecShort* const that, 
  FILE* const stream, const bool compact) {
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
  // Get the JSON encoding
  JSONNode* json = VecEncodeAsJSON(that);
  // Save the JSON
  if (!JSONSave(json, stream, compact)) {
    return false;
  }
  // Free memory
  JSONFree(&json);
  // Return success code
  return true;
}

// Free the memory used by a VecShort
// Do nothing if arguments are invalid
void _VecShortFree(VecShort** that) {
  // Check argument
  if (that == NULL || *that == NULL)
    return;
  // Free memory
  free(*that);
  *that = NULL;
}

// Print the VecShort on 'stream' with 'prec' digit precision
void _VecShortPrint(const VecShort* const that, 
  FILE* const stream) {
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
  for (long i = 0; i < that->_dim; ++i) {
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
bool _VecShortStep(VecShort* const that, const VecShort* const bound) {
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
    sprintf(PBMathErr->_msg, "dimensions don't match (%ld==%ld)", 
      that->_dim, bound->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable for the returned flag
  bool ret = true;
  // Declare a variable to memorise the dimension currently increasing
  long iDim = that->_dim - 1;
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
bool _VecShortPStep(VecShort* const that, const VecShort* const bound) {
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
    sprintf(PBMathErr->_msg, "dimensions don't match (%ld==%ld)", 
      that->_dim, bound->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable for the returned flag
  bool ret = true;
  // Declare a variable to memorise the dimension currently increasing
  long iDim = 0;
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
// (in which case 'that''s values are all set back to from)
// Return true else
bool _VecShortShiftStep(VecShort* const that, 
  const VecShort* const from, const VecShort* const to) {
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
    sprintf(PBMathErr->_msg, "'from' dimensions don't match (%ld==%ld)", 
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
    sprintf(PBMathErr->_msg, "'to' dimensions don't match (%ld==%ld)", 
      that->_dim, to->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable for the returned flag
  bool ret = true;
  // Declare a variable to memorise the dimension currently increasing
  long iDim = that->_dim - 1;
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

// Step the values of the vector incrementally by delta from 0
// in the following order (for example) : 
// (0,0,0)->(0,0,1)->(0,0,2)->(0,1,0)->(0,1,1)->...
// The upper limit for each value is given by 'bound' (val[i] <= dim[i])
// Return false after all values of 'that' have reached their upper 
// limit (in which case 'that''s values are all set back to 0)
// Return true else
bool _VecShortStepDelta(VecShort* const that, 
  const VecShort* const bound, const VecShort* const delta) {
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
  if (delta == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'delta' is null");
    PBErrCatch(PBMathErr);
  }
  if (that->_dim != bound->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "dimensions don't match (%ld==%ld)", 
      that->_dim, bound->_dim);
    PBErrCatch(PBMathErr);
  }
  if (that->_dim != delta->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "dimensions don't match (%ld==%ld)", 
      that->_dim, delta->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable for the returned flag
  bool ret = true;
  // Declare a variable to memorise the dimension currently increasing
  long iDim = that->_dim - 1;
  // Declare a flag for the loop condition 
  bool flag = true;
  // Increment
  do {
    that->_val[iDim] += delta->_val[iDim];
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

// Step the values of the vector incrementally by delta from 0
// in the following order (for example) : 
// (0,0,0)->(1,0,0)->(2,0,0)->(0,1,0)->(1,1,0)->...
// The upper limit for each value is given by 'bound' (val[i] <= dim[i])
// Return false after all values of 'that' have reached their upper 
// limit (in which case 'that''s values are all set back to 0)
// Return true else
bool _VecShortPStepDelta(VecShort* const that, 
  const VecShort* const bound, const VecShort* const delta) {
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
  if (delta == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'delta' is null");
    PBErrCatch(PBMathErr);
  }
  if (that->_dim != bound->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "dimensions don't match (%ld==%ld)", 
      that->_dim, bound->_dim);
    PBErrCatch(PBMathErr);
  }
  if (that->_dim != delta->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "dimensions don't match (%ld==%ld)", 
      that->_dim, delta->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable for the returned flag
  bool ret = true;
  // Declare a variable to memorise the dimension currently increasing
  long iDim = 0;
  // Declare a flag for the loop condition 
  bool flag = true;
  // Increment
  do {
    that->_val[iDim] += delta->_val[iDim];
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

// -------------- VecLong

// ================ Functions implementation ====================

// Create a new Vec of dimension 'dim'
// Values are initalized to 0.0
VecLong* VecLongCreate(const long dim) {
#if BUILDMODE == 0
  if (dim <= 0) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "invalid 'dim' (%ld)", dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // Allocate memory
  VecLong* that = PBErrMalloc(PBMathErr, 
    offsetof(VecLong, _val) + sizeof(long) * dim);
  // Set the default values
  that->_dim = dim;
  for (long i = dim; i--;)
    that->_val[i] = 0;
  // Return the new VecLong
  return that;
}

// Clone the VecLong
// Return NULL if we couldn't clone the VecLong
VecLong* _VecLongClone(const VecLong* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Create a clone
  VecLong* clone = VecLongCreate(that->_dim);
  // Copy the values
  memcpy(clone, that, sizeof(VecLong) + sizeof(long) * that->_dim);
  // Return the clone
  return clone;
}

// Function which return the JSON encoding of 'that' 
JSONNode* _VecLongEncodeAsJSON(const VecLong* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Create the JSON structure
  JSONNode* json = JSONCreate();
  // Declare a buffer to convert value into string
  char val[100];
  // Encode the dimension
  sprintf(val, "%ld", VecGetDim(that));
  JSONAddProp(json, "_dim", val);
  // Encode the values
  JSONArrayVal setVal = JSONArrayValCreateStatic();
  for (long i = 0; i < VecGetDim(that); ++i) {
    sprintf(val, "%ld", VecGet(that, i));
    JSONArrayValAdd(&setVal, val);
  }
  JSONAddProp(json, "_val", &setVal);
  // Free memory
  JSONArrayValFlush(&setVal);
  // Return the created JSON 
  return json;
}

// Function which decode from JSON encoding 'json' to 'that'
bool _VecLongDecodeAsJSON(VecLong** that, const JSONNode* const json) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (json == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'json' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // If 'that' is already allocated
  if (*that != NULL)
    // Free memory
    _VecLongFree(that);
  // Get the dimension from the JSON
  JSONNode* prop = JSONProperty(json, "_dim");
  if (prop == NULL) {
    return false;
  }
  long dim = atol(JSONLblVal(prop));
  // If data are invalid
  if (dim < 1)
    return false;
  // Allocate memory
  *that = VecLongCreate(dim);
  // Get the values
  prop = JSONProperty(json, "_val");
  if (prop == NULL) {
    return false;
  }
  for (long i = 0; i < dim; ++i) {
    long val = atol(JSONLabel(JSONValue(prop, i)));
    VecSet(*that, i, val);
  }
  // Return the success code
  return true;
}

// Load the VecLong from the stream
// If the VecLong is already allocated, it is freed before loading
// Return true in case of success, else false
bool _VecLongLoad(VecLong** that, FILE* const stream) {
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
  // Declare a json to load the encoded data
  JSONNode* json = JSONCreate();
  // Load the whole encoded data
  if (!JSONLoad(json, stream)) {
    return false;
  }
  // Decode the data from the JSON
  if (!VecDecodeAsJSON(that, json)) {
    return false;
  }
  // Free the memory used by the JSON
  JSONFree(&json);
  // Return the success code
  return true;
}

// Save the VecLong to the stream
// If 'compact' equals true it saves in compact form, else it saves in 
// readable form
// Return true in case of success, else false
bool _VecLongSave(const VecLong* const that, 
  FILE* const stream, const bool compact) {
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
  // Get the JSON encoding
  JSONNode* json = VecEncodeAsJSON(that);
  // Save the JSON
  if (!JSONSave(json, stream, compact)) {
    return false;
  }
  // Free memory
  JSONFree(&json);
  // Return success code
  return true;
}

// Free the memory used by a VecLong
// Do nothing if arguments are invalid
void _VecLongFree(VecLong** that) {
  // Check argument
  if (that == NULL || *that == NULL)
    return;
  // Free memory
  free(*that);
  *that = NULL;
}

// Print the VecLong on 'stream' with 'prec' digit precision
void _VecLongPrint(const VecLong* const that, 
  FILE* const stream) {
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
  for (long i = 0; i < that->_dim; ++i) {
    fprintf(stream, "%ld", that->_val[i]);
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
bool _VecLongStep(VecLong* const that, const VecLong* const bound) {
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
    sprintf(PBMathErr->_msg, "dimensions don't match (%ld==%ld)", 
      that->_dim, bound->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable for the returned flag
  bool ret = true;
  // Declare a variable to memorise the dimension currently increasing
  long iDim = that->_dim - 1;
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
bool _VecLongPStep(VecLong* const that, const VecLong* const bound) {
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
    sprintf(PBMathErr->_msg, "dimensions don't match (%ld==%ld)", 
      that->_dim, bound->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable for the returned flag
  bool ret = true;
  // Declare a variable to memorise the dimension currently increasing
  long iDim = 0;
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
// (in which case 'that''s values are all set back to from)
// Return true else
bool _VecLongShiftStep(VecLong* const that, 
  const VecLong* const from, const VecLong* const to) {
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
    sprintf(PBMathErr->_msg, "'from' dimensions don't match (%ld==%ld)", 
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
    sprintf(PBMathErr->_msg, "'to' dimensions don't match (%ld==%ld)", 
      that->_dim, to->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable for the returned flag
  bool ret = true;
  // Declare a variable to memorise the dimension currently increasing
  long iDim = that->_dim - 1;
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

// Step the values of the vector incrementally by delta from 0
// in the following order (for example) : 
// (0,0,0)->(0,0,1)->(0,0,2)->(0,1,0)->(0,1,1)->...
// The upper limit for each value is given by 'bound' (val[i] <= dim[i])
// Return false after all values of 'that' have reached their upper 
// limit (in which case 'that''s values are all set back to 0)
// Return true else
bool _VecLongStepDelta(VecLong* const that, 
  const VecLong* const bound, const VecLong* const delta) {
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
  if (delta == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'delta' is null");
    PBErrCatch(PBMathErr);
  }
  if (that->_dim != bound->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "dimensions don't match (%ld==%ld)", 
      that->_dim, bound->_dim);
    PBErrCatch(PBMathErr);
  }
  if (that->_dim != delta->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "dimensions don't match (%ld==%ld)", 
      that->_dim, delta->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable for the returned flag
  bool ret = true;
  // Declare a variable to memorise the dimension currently increasing
  long iDim = that->_dim - 1;
  // Declare a flag for the loop condition 
  bool flag = true;
  // Increment
  do {
    that->_val[iDim] += delta->_val[iDim];
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

// Step the values of the vector incrementally by delta from 0
// in the following order (for example) : 
// (0,0,0)->(1,0,0)->(2,0,0)->(0,1,0)->(1,1,0)->...
// The upper limit for each value is given by 'bound' (val[i] <= dim[i])
// Return false after all values of 'that' have reached their upper 
// limit (in which case 'that''s values are all set back to 0)
// Return true else
bool _VecLongPStepDelta(VecLong* const that, 
  const VecLong* const bound, const VecLong* const delta) {
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
  if (delta == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'delta' is null");
    PBErrCatch(PBMathErr);
  }
  if (that->_dim != bound->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "dimensions don't match (%ld==%ld)", 
      that->_dim, bound->_dim);
    PBErrCatch(PBMathErr);
  }
  if (that->_dim != delta->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "dimensions don't match (%ld==%ld)", 
      that->_dim, delta->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable for the returned flag
  bool ret = true;
  // Declare a variable to memorise the dimension currently increasing
  long iDim = 0;
  // Declare a flag for the loop condition 
  bool flag = true;
  // Increment
  do {
    that->_val[iDim] += delta->_val[iDim];
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

// Return a new VecLong as a copy of the VecLong 'that' with 
// dimension changed to 'dim'
// if it is extended, the values of new components are 0
// If it is shrinked, values are discarded from the end of the vector
VecLong* _VecLongGetNewDim(const VecLong* const that, const long dim) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (dim <= 0) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'dim' is invalid match (%ld>0)", dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // If the new dimension is the same as the current one
  if (dim == VecGetDim(that)) {
    // Return the clone of the vector
    return VecClone(that);
  // Else, the new dimension is actually different
  } else {
    // Declare the returned vector
    VecLong* ret = VecLongCreate(dim);
    // Copy the components
    for (long iAxis = MIN(VecGetDim(that), dim); iAxis--;)
      VecSet(ret, iAxis, VecGet(that, iAxis));
    // Return the new vector
    return ret;
  }
}

// -------------- VecFloat

// ================ Functions implementation ====================

// Create a new Vec of dimension 'dim'
// Values are initalized to 0.0
VecFloat* VecFloatCreate(const long dim) {
#if BUILDMODE == 0
  if (dim <= 0) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "invalid 'dim' (%ld)", dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // Allocate memory
  VecFloat* that = PBErrMalloc(PBMathErr, 
    offsetof(VecFloat, _val) + sizeof(float) * dim);
  // Set the default values
  that->_dim = dim;
  for (long i = dim; i--;)
    that->_val[i] = 0.0;
  // Return the new VecFloat
  return that;
}

// Clone the VecFloat
VecFloat* _VecFloatClone(const VecFloat* const that) {
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

// Function which return the JSON encoding of 'that' 
JSONNode* _VecFloatEncodeAsJSON(const VecFloat* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Create the JSON structure
  JSONNode* json = JSONCreate();
  // Declare a buffer to convert value into string
  char val[100];
  // Encode the dimension
  sprintf(val, "%ld", VecGetDim(that));
  JSONAddProp(json, "_dim", val);
  // Encode the values
  JSONArrayVal setVal = JSONArrayValCreateStatic();
  for (long i = 0; i < VecGetDim(that); ++i) {
    sprintf(val, "%f", VecGet(that, i));
    JSONArrayValAdd(&setVal, val);
  }
  JSONAddProp(json, "_val", &setVal);
  // Free memory
  JSONArrayValFlush(&setVal);
  // Return the created JSON 
  return json;
}

// Function which decode from JSON encoding 'json' to 'that'
bool _VecFloatDecodeAsJSON(VecFloat** that, const JSONNode* const json) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (json == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'json' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // If 'that' is already allocated
  if (*that != NULL)
    // Free memory
    _VecFloatFree(that);
  // Get the dimension from the JSON
  JSONNode* prop = JSONProperty(json, "_dim");
  if (prop == NULL) {
    return false;
  }
  long dim = atol(JSONLblVal(prop));
  // If data are invalid
  if (dim < 1)
    return false;
  // Allocate memory
  *that = VecFloatCreate(dim);
  // Get the values
  prop = JSONProperty(json, "_val");
  if (prop == NULL) {
    return false;
  }
  for (long i = 0; i < dim; ++i) {
    float val = atof(JSONLabel(JSONValue(prop, i)));
    VecSet(*that, i, val);
  }
  // Return the success code
  return true;
}

// Load the VecFloat from the stream
// If the VecFloat is already allocated, it is freed before loading
bool _VecFloatLoad(VecFloat** that, FILE* const stream) {
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
  // Declare a json to load the encoded data
  JSONNode* json = JSONCreate();
  // Load the whole encoded data
  if (!JSONLoad(json, stream)) {
    return false;
  }
  // Decode the data from the JSON
  if (!VecDecodeAsJSON(that, json)) {
    return false;
  }
  // Free the memory used by the JSON
  JSONFree(&json);
  // Return the success code
  return true;
}

// Save the VecFloat to the stream
// If 'compact' equals true it saves in compact form, else it saves in 
// readable form
// Return true in case of success, else false
bool _VecFloatSave(const VecFloat* const that, 
  FILE* const stream, const bool compact) {
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
  // Get the JSON encoding
  JSONNode* json = VecEncodeAsJSON(that);
  // Save the JSON
  if (!JSONSave(json, stream, compact)) {
    return false;
  }
  // Free memory
  JSONFree(&json);
  // Return success code
  return true;
}

// Free the memory used by a VecFloat
// Do nothing if arguments are invalid
void _VecFloatFree(VecFloat** that) {
  // Check argument
  if (that == NULL || *that == NULL)
    return;
  // Free memory
  free(*that);
  *that = NULL;
}

// Print the VecFloat on 'stream' with 'prec' digit precision
// Do nothing if arguments are invalid
void VecFloatPrint(const VecFloat* const that, FILE* const stream, 
  const unsigned int prec) {
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
  for (long i = 0; i < that->_dim; ++i) {
    fprintf(stream, format, that->_val[i]);
    if (i < that->_dim - 1)
      fprintf(stream, ",");
  }
  fprintf(stream, ">");
}

// Return the angle of the rotation making 'that' colinear to 'tho'
// 'that' and 'tho' must be normalised
// Return a value in [-PI,PI]
float _VecFloatAngleTo2D(const VecFloat2D* const that, 
  const VecFloat2D* const tho) {
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

// Return a VecFloat3D equal to 'that' rotated right-hand by 'theta' 
// radians around 'axis'
// 'axis' must be normalized
// https://en.wikipedia.org/wiki/Rotation_matrix
VecFloat3D _VecFloatGetRotAxis(const VecFloat3D* const that, 
  const VecFloat3D* const axis, const float theta) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (axis == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'axis' is null");
    PBErrCatch(PBMathErr);
  }
  if (VecGetDim(that) != 3) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'that' 's dimension is invalid (%ld=3)",
      VecGetDim(that));
    PBErrCatch(PBMathErr);
  }
  if (VecGetDim(axis) != 3) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'axis' 's dimension is invalid (%ld=3)",
      VecGetDim(axis));
    PBErrCatch(PBMathErr);
  }
  if (ISEQUALF(VecNorm(axis), 1.0) == false) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'axis' is not normalized");
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare variable for optimisation
  float cosTheta = cos(theta);
  float sinTheta = sin(theta);
  // Create the rotation matrix
  VecShort2D d = VecShortCreateStatic2D();
  VecSet(&d, 0, 3); VecSet(&d, 1, 3); 
  MatFloat* rot = MatFloatCreate(&d);
  VecSet(&d, 0, 0); VecSet(&d, 1, 0); 
  float v = cosTheta + fastpow(VecGet(axis, 0), 2) * (1.0 - cosTheta);
  MatSet(rot, &d, v);
  VecSet(&d, 0, 1); VecSet(&d, 1, 0); 
  v = VecGet(axis, 0) * VecGet(axis, 1) * (1.0 - cosTheta) - 
    VecGet(axis, 2) * sinTheta;
  MatSet(rot, &d, v);
  VecSet(&d, 0, 2); VecSet(&d, 1, 0); 
  v = VecGet(axis, 0) * VecGet(axis, 2) * (1.0 - cosTheta) + 
    VecGet(axis, 1) * sinTheta;
  MatSet(rot, &d, v);
  VecSet(&d, 0, 0); VecSet(&d, 1, 1); 
  v = VecGet(axis, 0) * VecGet(axis, 1) * (1.0 - cosTheta) + 
    VecGet(axis, 2) * sinTheta;
  MatSet(rot, &d, v);
  VecSet(&d, 0, 1); VecSet(&d, 1, 1); 
  v = cosTheta + fastpow(VecGet(axis, 1), 2) * (1.0 - cosTheta);
  MatSet(rot, &d, v);
  VecSet(&d, 0, 2); VecSet(&d, 1, 1); 
  v = VecGet(axis, 1) * VecGet(axis, 2) * (1.0 - cosTheta) - 
    VecGet(axis, 0) * sinTheta;
  MatSet(rot, &d, v);
  VecSet(&d, 0, 0); VecSet(&d, 1, 2); 
  v = VecGet(axis, 0) * VecGet(axis, 2) * (1.0 - cosTheta) - 
    VecGet(axis, 1) * sinTheta;
  MatSet(rot, &d, v);
  VecSet(&d, 0, 1); VecSet(&d, 1, 2); 
  v = VecGet(axis, 1) * VecGet(axis, 2) * (1.0 - cosTheta) + 
    VecGet(axis, 0) * sinTheta;
  MatSet(rot, &d, v);
  VecSet(&d, 0, 2); VecSet(&d, 1, 2); 
  v = cosTheta + fastpow(VecGet(axis, 2), 2) * (1.0 - cosTheta);
  MatSet(rot, &d, v);
  // Calculate the result vector
  VecFloat* w = MatGetProdVec(rot, that);
  VecFloat3D res = VecFloatCreateStatic3D();
  VecCopy(&res, w);
  // Free memory
  VecFree(&w);
  MatFree(&rot);
  // Return the result
  return res;
}

// Return a VecFloat3D equal to 'that' rotated right-hand by 'theta' 
// radians around X
VecFloat3D _VecFloatGetRotX(const VecFloat3D* const that, 
  const float theta) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (VecGetDim(that) != 3) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'that' 's dimension is invalid (%ld=3)",
      VecGetDim(that));
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare variable for optimisation
  float cosTheta = cos(theta);
  float sinTheta = sin(theta);
  // Create the rotation matrix
  VecShort2D d = VecShortCreateStatic2D();
  VecSet(&d, 0, 3); VecSet(&d, 1, 3); 
  MatFloat* rot = MatFloatCreate(&d);
  VecSet(&d, 0, 0); VecSet(&d, 1, 0); 
  float v = 1.0;
  MatSet(rot, &d, v);
  VecSet(&d, 0, 1); VecSet(&d, 1, 0); 
  v = 0.0;
  MatSet(rot, &d, v);
  VecSet(&d, 0, 2); VecSet(&d, 1, 0); 
  v = 0.0;
  MatSet(rot, &d, v);
  VecSet(&d, 0, 0); VecSet(&d, 1, 1); 
  v = 0.0;
  MatSet(rot, &d, v);
  VecSet(&d, 0, 1); VecSet(&d, 1, 1); 
  v = cosTheta;
  MatSet(rot, &d, v);
  VecSet(&d, 0, 2); VecSet(&d, 1, 1); 
  v = -sinTheta;
  MatSet(rot, &d, v);
  VecSet(&d, 0, 0); VecSet(&d, 1, 2); 
  v = 0.0;
  MatSet(rot, &d, v);
  VecSet(&d, 0, 1); VecSet(&d, 1, 2); 
  v = sinTheta;
  MatSet(rot, &d, v);
  VecSet(&d, 0, 2); VecSet(&d, 1, 2); 
  v = cosTheta;
  MatSet(rot, &d, v);
  // Calculate the result vector
  VecFloat* w = MatGetProdVec(rot, that);
  VecFloat3D res = VecFloatCreateStatic3D();
  VecCopy(&res, w);
  // Free memory
  VecFree(&w);
  MatFree(&rot);
  // Return the result
  return res;
}

// Return a VecFloat3D equal to 'that' rotated right-hand by 'theta' 
// radians around Y
VecFloat3D _VecFloatGetRotY(const VecFloat3D* const that, 
  const float theta) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (VecGetDim(that) != 3) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'that' 's dimension is invalid (%ld=3)",
      VecGetDim(that));
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare variable for optimisation
  float cosTheta = cos(theta);
  float sinTheta = sin(theta);
  // Create the rotation matrix
  VecShort2D d = VecShortCreateStatic2D();
  VecSet(&d, 0, 3); VecSet(&d, 1, 3); 
  MatFloat* rot = MatFloatCreate(&d);
  VecSet(&d, 0, 0); VecSet(&d, 1, 0); 
  float v = cosTheta;
  MatSet(rot, &d, v);
  VecSet(&d, 0, 1); VecSet(&d, 1, 0); 
  v = 0.0;
  MatSet(rot, &d, v);
  VecSet(&d, 0, 2); VecSet(&d, 1, 0); 
  v = sinTheta;
  MatSet(rot, &d, v);
  VecSet(&d, 0, 0); VecSet(&d, 1, 1); 
  v = 0.0;
  MatSet(rot, &d, v);
  VecSet(&d, 0, 1); VecSet(&d, 1, 1); 
  v = 1.0;
  MatSet(rot, &d, v);
  VecSet(&d, 0, 2); VecSet(&d, 1, 1); 
  v = 0.0;
  MatSet(rot, &d, v);
  VecSet(&d, 0, 0); VecSet(&d, 1, 2); 
  v = -sinTheta;
  MatSet(rot, &d, v);
  VecSet(&d, 0, 1); VecSet(&d, 1, 2); 
  v = 0.0;
  MatSet(rot, &d, v);
  VecSet(&d, 0, 2); VecSet(&d, 1, 2); 
  v = cosTheta;
  MatSet(rot, &d, v);
  // Calculate the result vector
  VecFloat* w = MatGetProdVec(rot, that);
  VecFloat3D res = VecFloatCreateStatic3D();
  VecCopy(&res, w);
  // Free memory
  VecFree(&w);
  MatFree(&rot);
  // Return the result
  return res;
}

// Return a VecFloat3D equal to 'that' rotated right-hand by 'theta' 
// radians around Z
VecFloat3D _VecFloatGetRotZ(const VecFloat3D* const that, 
  const float theta) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (VecGetDim(that) != 3) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'that' 's dimension is invalid (%ld=3)",
      VecGetDim(that));
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare variable for optimisation
  float cosTheta = cos(theta);
  float sinTheta = sin(theta);
  // Create the rotation matrix
  VecShort2D d = VecShortCreateStatic2D();
  VecSet(&d, 0, 3); VecSet(&d, 1, 3); 
  MatFloat* rot = MatFloatCreate(&d);
  VecSet(&d, 0, 0); VecSet(&d, 1, 0); 
  float v = cosTheta;
  MatSet(rot, &d, v);
  VecSet(&d, 0, 1); VecSet(&d, 1, 0); 
  v = -sinTheta;
  MatSet(rot, &d, v);
  VecSet(&d, 0, 2); VecSet(&d, 1, 0); 
  v = 0.0;
  MatSet(rot, &d, v);
  VecSet(&d, 0, 0); VecSet(&d, 1, 1); 
  v = sinTheta;
  MatSet(rot, &d, v);
  VecSet(&d, 0, 1); VecSet(&d, 1, 1); 
  v = cosTheta;
  MatSet(rot, &d, v);
  VecSet(&d, 0, 2); VecSet(&d, 1, 1); 
  v = 0.0;
  MatSet(rot, &d, v);
  VecSet(&d, 0, 0); VecSet(&d, 1, 2); 
  v = 0.0;
  MatSet(rot, &d, v);
  VecSet(&d, 0, 1); VecSet(&d, 1, 2); 
  v = 0.0;
  MatSet(rot, &d, v);
  VecSet(&d, 0, 2); VecSet(&d, 1, 2); 
  v = 1.0;
  MatSet(rot, &d, v);
  // Calculate the result vector
  VecFloat* w = MatGetProdVec(rot, that);
  VecFloat3D res = VecFloatCreateStatic3D();
  VecCopy(&res, w);
  // Free memory
  VecFree(&w);
  MatFree(&rot);
  // Return the result
  return res;
}

// Step the values of the vector incrementally by delta from 0
// in the following order (for example) : 
// (0.,0.,0.)->(0.,0.,1.)->(0.,0.,2.)->(0.,1.,0.)->(0.,1.,1.)->...
// The upper limit for each value is given by 'bound' (val[i] <= dim[i])
// Return false after all values of 'that' have reached their upper 
// limit (in which case 'that''s values are all set back to 0.)
// Return true else
bool _VecFloatStepDelta(VecFloat* const that, 
  const VecFloat* const bound, const VecFloat* const delta) {
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
  if (delta == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'delta' is null");
    PBErrCatch(PBMathErr);
  }
  if (that->_dim != bound->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, 
      "'bound' 's dimensions don't match (%ld==%ld)", 
      that->_dim, bound->_dim);
    PBErrCatch(PBMathErr);
  }
  if (that->_dim != delta->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, 
      "'delta' 's dimensions don't match (%ld==%ld)", 
      that->_dim, delta->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable for the returned flag
  bool ret = true;
  // Declare a variable to memorise the dimension currently increasing
  long iDim = that->_dim - 1;
  // Declare a flag for the loop condition 
  bool flag = true;
  // Increment
  do {
    that->_val[iDim] += delta->_val[iDim];
    if (that->_val[iDim] > bound->_val[iDim] + PBMATH_EPSILON) {
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
  const VecFloat* const delta) {
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
    sprintf(PBMathErr->_msg, "'from' dimensions don't match (%ld==%ld)", 
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
    sprintf(PBMathErr->_msg, "'to' dimensions don't match (%ld==%ld)", 
      that->_dim, to->_dim);
    PBErrCatch(PBMathErr);
  }
  if (delta == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'delta' is null");
    PBErrCatch(PBMathErr);
  }
  if (that->_dim != delta->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'delta' dimensions don't match (%ld==%ld)", 
      that->_dim, delta->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable for the returned flag
  bool ret = true;
  // Declare a variable to memorise the dimension currently increasing
  long iDim = that->_dim - 1;
  // Declare a flag for the loop condition 
  bool flag = true;
  // Increment
  do {
    that->_val[iDim] += delta->_val[iDim];
    if (that->_val[iDim] > to->_val[iDim] + PBMATH_EPSILON) {
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

// Return a new VecFloat as a copy of the VecFloat 'that' with 
// dimension changed to 'dim'
// if it is extended, the values of new components are 0.0
// If it is shrinked, values are discarded from the end of the vector
VecFloat* _VecFloatGetNewDim(const VecFloat* const that, const long dim) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (dim <= 0) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'dim' is invalid match (%ld>0)", dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // If the new dimension is the same as the current one
  if (dim == VecGetDim(that)) {
    // Return the clone of the vector
    return VecClone(that);
  // Else, the new dimension is actually different
  } else {
    // Declare the returned vector
    VecFloat* ret = VecFloatCreate(dim);
    // Copy the components
    for (long iAxis = MIN(VecGetDim(that), dim); iAxis--;)
      VecSet(ret, iAxis, VecGet(that, iAxis));
    // Return the new vector
    return ret;
  }
}

// -------------- MatFloat

// ================= Define ==================

// ================ Functions implementation ====================

// Create a new MatFloat of dimension 'dim' (nbcol, nbline)
// Values are initalized to 0.0
MatFloat* MatFloatCreate(const VecShort2D* const dim) {
#if BUILDMODE == 0
  if (dim == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'dim' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Allocate memory
  long d = VecGet(dim, 0) * VecGet(dim, 1);
  MatFloat* that = PBErrMalloc(PBMathErr, offsetof(MatFloat, _val) + 
    sizeof(float) * d);
  // Set the dimensions
  *(VecShort2D*)&(that->_dim) = *dim;
  // Set the default values
  for (long i = d; i--;)
    that->_val[i] = 0.0;
  // Return the new MatFloat
  return that;
}

// Clone the MatFloat
MatFloat* _MatFloatClone(const MatFloat* const that) {
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
  long d = VecGet(&(that->_dim), 0) * VecGet(&(that->_dim), 1);
  for (long i = d; i--;)
    clone->_val[i] = that->_val[i];
  // Return the clone
  return clone;
}

// Function which return the JSON encoding of 'that' 
JSONNode* _MatFloatEncodeAsJSON(MatFloat* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Create the JSON structure
  JSONNode* json = JSONCreate();
  // Declare a buffer to convert value into string
  char val[100];
  // Encode the dimensions
  sprintf(val, "%d", VecGet(&(that->_dim), 0));
  JSONAddProp(json, "_nbRow", val);
  sprintf(val, "%d", VecGet(&(that->_dim), 1));
  JSONAddProp(json, "_nbCol", val);
  // Encode the values
  JSONArrayVal setVal = JSONArrayValCreateStatic();
  VecShort2D index = VecShortCreateStatic2D();
  do {
    sprintf(val, "%f", MatGet(that, &index));
    JSONArrayValAdd(&setVal, val);
  } while (VecStep(&index, &(that->_dim)));
  JSONAddProp(json, "_val", &setVal);
  // Free memory
  JSONArrayValFlush(&setVal);
  // Return the created JSON 
  return json;
}

// Function which decode from JSON encoding 'json' to 'that'
bool _MatFloatDecodeAsJSON(MatFloat** that, JSONNode* json) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (json == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'json' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // If 'that' is already allocated
  if (*that != NULL)
    // Free memory
    _MatFloatFree(that);
  // Get the dimensions from the JSON
  JSONNode* prop = JSONProperty(json, "_nbRow");
  if (prop == NULL) {
    return false;
  }
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, atoi(JSONLblVal(prop)));
  prop = JSONProperty(json, "_nbCol");
  if (prop == NULL) {
    return false;
  }
  VecSet(&dim, 1, atoi(JSONLblVal(prop)));
  // If data are invalid
  if (VecGet(&dim, 0) < 1 || VecGet(&dim, 1) < 1)
    return false;
  // Allocate memory
  *that = MatFloatCreate(&dim);
  // Get the values
  prop = JSONProperty(json, "_val");
  if (prop == NULL) {
    return false;
  }
  VecShort2D index = VecShortCreateStatic2D();
  int i = 0;
  do {
    MatSet(*that, &index, atof(JSONLabel(JSONValue(prop, i))));
    ++i;
  } while (VecStep(&index, &dim));
  // Return the success code
  return true;
}

// Load the MatFloat from the stream
// If the MatFloat is already allocated, it is freed before loading
// Return true upon success, else false
bool _MatFloatLoad(MatFloat** that, FILE* stream) {
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
  // Declare a json to load the encoded data
  JSONNode* json = JSONCreate();
  // Load the whole encoded data
  if (!JSONLoad(json, stream)) {
    return false;
  }
  // Decode the data from the JSON
  if (!MatDecodeAsJSON(that, json)) {
    return false;
  }
  // Free the memory used by the JSON
  JSONFree(&json);
  // Return the success code
  return true;
}

// Save the MatFloat to the stream
// If 'compact' equals true it saves in compact form, else it saves in 
// readable form
// Return true upon success, else false
bool _MatFloatSave(MatFloat* const that, FILE* stream, bool compact) {
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
  // Get the JSON encoding
  JSONNode* json = MatEncodeAsJSON(that);
  // Save the JSON
  if (!JSONSave(json, stream, compact)) {
    return false;
  }
  // Free memory
  JSONFree(&json);
  // Return success code
  return true;
}

// Free the memory used by a MatFloat
// Do nothing if arguments are invalid
void _MatFloatFree(MatFloat** that) {
  // Check argument
  if (that == NULL || *that == NULL)
    return;
  // Free memory
  free(*that);
  *that = NULL;
}

// Print the MatFloat on 'stream' with 'prec' digit precision
// Do nothing if arguments are invalid
void MatFloatPrintln(MatFloat* const that, FILE* stream, unsigned int prec) {
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
  sprintf(format, "%% .%df", prec);
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
// Return NULL if the matrix is not invertible, or in some case when
// the matrix's diagonal contains null values and the matrix's size
// is greater than 3
MatFloat* _MatFloatGetInv(const MatFloat* const that) {
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
#endif
  // Allocate memory for the result
  MatFloat* res = NULL;
  // If the matrix is of dimension 1x1
  if (VecGet(&(that->_dim), 0) == 1) {
    if (fabs(that->_val[0]) > PBMATH_EPSILON) {
      // Allocate memory for the result
      res = MatFloatCreate(&(that->_dim));
      res->_val[0] = 1.0 / that->_val[0];
    }
  // If the matrix is of dimension 2x2
  } else if (VecGet(&(that->_dim), 0) == 2) {
    float det = that->_val[0] * that->_val[3] - 
      that->_val[2] * that->_val[1];
    if (!ISEQUALF(det, 0.0)) {
      // Allocate memory for the result
      res = MatFloatCreate(&(that->_dim));
      res->_val[0] = that->_val[3] / det;
      res->_val[1] = -1.0 * that->_val[1] / det;
      res->_val[2] = -1.0 * that->_val[2] / det;
      res->_val[3] = that->_val[0] / det;
    }
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
    if (!ISEQUALF(det, 0.0)) {
      // Allocate memory for the result
      res = MatFloatCreate(&(that->_dim));
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
  } else {
    // Clone the matrix to be inverted
    res = MatClone(that);
    // Farooq Hamid algorithm (modified to handle some matrix with null
    // values on the diagonal)
    // https://www.researchgate.net/publication/
    //   220337322_An_Efficient_and_Simple_Algorithm_for_Matrix_Inversion
    //float det = 1.0;
    short size = VecGet(&(that->_dim), 0);
    float* mat = res->_val;
    bool flagHasChanged = true;
    short nbRemaining = size;
    bool* hasPivotChanged = PBErrMalloc(PBMathErr, size * sizeof(bool));
    for(short p = 0; p < size; ++p) {
      hasPivotChanged[p] = false;
    }
    while (flagHasChanged == true && nbRemaining > 0) {
      flagHasChanged = false;
      for(short p = 0; p < size; ++p) {
        float pivot = mat[p * size + p];
        if (!ISEQUALF(pivot, 0.0) && !(hasPivotChanged[p])) {
          flagHasChanged = true;
          --nbRemaining;
          hasPivotChanged[p] = true;
          //det *= pivot;
          for (short i = 0; i < size; ++i) {
            mat[i * size + p] = -1.0 * mat[i * size + p] / pivot;
          }
          for (short i = 0; i < size; ++i) {
            if (i != p) {
              for (short j = 0; j < size; ++j) {
                if (j != p) {
                  mat[i * size + j] =
                    mat[i * size + j] + mat[p * size + j] * mat[i * size + p];
                }
              }
            }
          }
          for (short j = 0; j < size; ++j) {
            mat[p * size + j] =  mat[p * size + j] / pivot;
          }
          mat[p * size + p] = 1.0 / pivot;
        }
      }
    }
    free(hasPivotChanged);
    if (nbRemaining > 0) {
      MatFree(&res);
      return NULL;
    }
  }
  // Return the result
  return res;
}

// Return the product of matrix 'that' and vector 'v'
// Number of colum of 'that' must equal dimension of 'v'
VecFloat* _MatFloatGetProdVecFloat(
  const MatFloat* const that, const VecFloat* v) {
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
  if (VecGet(&(that->_dim), 0) != VecGetDim(v)) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, 
      "the matrix and vector have incompatible dimensions (%d==%ld)",
      VecGet(&(that->_dim), 0), VecGetDim(v));
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable to memorize the index in the matrix
  VecShort2D i = VecShortCreateStatic2D();
  // Allocate memory for the solution
  VecFloat* ret = VecFloatCreate(VecGet(&(that->_dim), 1));
  // If we could allocate memory
  if (ret != NULL)
    for (VecSet(&i, 0, 0); VecGet(&i, 0) < VecGet(&(that->_dim), 0); VecSetAdd(&i, 0, 1))
      for (VecSet(&i, 1, 0); VecGet(&i, 1) < VecGet(&(that->_dim), 1); VecSetAdd(&i, 1, 1))
        VecSetAdd(ret, VecGet(&i, 1), 
          VecGet(v, VecGet(&i, 0)) * MatGet(that, &i));
  // Return the result
  return ret;
}

// Return the product of vector 'v' and transpose of vector 'w'
MatFloat* _MatFloatGetProdVecVecTransposeFloat(
  const VecFloat* const v, 
  const VecFloat* const w) {
#if BUILDMODE == 0
  if (v == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'v' is null");
    PBErrCatch(PBMathErr);
  }
  if (w == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'w' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable to memorize the position in the matrix
  VecShort2D pos = VecShortCreateStatic2D();
  // Allocate memory for the solution
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, VecGetDim(w));
  VecSet(&dim, 1, VecGetDim(v));
  MatFloat* ret = MatFloatCreate(&dim);
  // Calculate the result
  do {
    MatSet(ret, &pos, 
      VecGet(v, VecGet(&pos, 1)) * VecGet(w, VecGet(&pos, 0)));
  } while(VecStep(&pos, &dim));
  // Return the result
  return ret;    
}

// Return the product of matrix 'that' by matrix 'tho'
// Number of columns of 'that' must equal number of line of 'tho'
MatFloat* _MatFloatGetProdMatFloat(const MatFloat* const that, const MatFloat* tho) {
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
  for (VecSet(&i, 0, 0); VecGet(&i, 0) < VecGet(&(tho->_dim), 0); VecSetAdd(&i, 0, 1))
    for (VecSet(&i, 1, 0); VecGet(&i, 1) < VecGet(&(that->_dim), 1); VecSetAdd(&i, 1, 1))
      for (VecSet(&j, 0, 0), VecSet(&j, 1, VecGet(&i, 1)),
        VecSet(&k, 0, VecGet(&i, 0)), VecSet(&k, 1, 0); 
        VecGet(&j, 0) < VecGet(&(that->_dim), 0);
        VecSetAdd(&j, 0, 1), 
        VecSetAdd(&k, 1, 1)) {
        MatSet(ret, &i, MatGet(ret, &i) + 
          MatGet(that, &j) * MatGet(tho, &k));
      }
  // Return the result
  return ret;
}

// Return true if 'that' is equal to 'tho', false else
bool _MatFloatIsEqual(MatFloat* const that, MatFloat* tho) {
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

// Calculate the Eigen values and vectors of the MatFloat 'that'
// Return a set of VecFloat. The first VecFloat of the set contains 
// the Eigen values, with values sorted from biggest to 
// smallest (in absolute value). The following VecFloat are the 
// respectiev Eigen vectors
// 'that' must be a 2D square matrix
// Return the identity if the QR decompostion fails
// http://madrury.github.io/jekyll/update/statistics/2017/10/04/qr-algorithm.html
// TODO: should be improved with the Hessenberg QR method
// https://www.math.kth.se/na/SF2524/matber15/qrmethod.pdf
GSetVecFloat _MatFloatGetEigenValues(const MatFloat* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (VecGet(MatDim(that), 0) != VecGet(MatDim(that), 1)) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'that' is not squared");
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare the result set
  GSetVecFloat set = GSetVecFloatCreateStatic();
  // Clone the original matrix
  MatFloat* A = MatClone(that);
  // Create a matrix to compute the Eigen vectors
  MatFloat* Q = MatFloatCreate(MatDim(that));
  MatSetIdentity(Q);
  // Apply the QR algorithm
  VecShort2D pos = VecShortCreateStatic2D();
  float err = 0.0;
  do {
    QRDecomp QR = MatGetQR(A);
    if (QR._Q != NULL) {
      MatFloat* RQ = MatGetProdMat(QR._R, QR._Q);
      MatFree(&A);
      A = RQ;
      MatFloat* M = MatGetProdMat(Q, QR._Q);
      MatFree(&Q);
      Q = M;
      err = 0.0;
      do {
        if (VecGet(&pos, 0) != VecGet(&pos, 1))
          err = MAX(err, fabs(MatGet(A, &pos)));
      } while (VecStep(&pos, MatDim(A)));
      QRDecompFreeStatic(&QR);
    } else {
      MatSetIdentity(A);
      MatSetIdentity(Q);
      err = 0.0;
    }
  } while (err > PBMATH_EPSILON);
  // Extract the results
  VecFloat* values = VecFloatCreate(MatGetNbCol(that));
  GSetPush(&set, values);
  for (int i = 0; i < MatGetNbCol(that); ++i) {
    VecSet(&pos, 0, i);
    VecSet(&pos, 1, i);
    VecSet(values, i, MatGet(A, &pos));
    GSetAppend(&set, VecFloatCreate(MatGetNbCol(that)));
  }
  VecSetNull(&pos);
  do {
    VecSet(GSetGet(&set, 1 + VecGet(&pos, 0)), VecGet(&pos, 1),
      MatGet(Q, &pos));
  } while (VecStep(&pos, MatDim(Q)));
  // Free memory
  MatFree(&A);
  MatFree(&Q);
  // Return the result
  return set;
}

// Calculate the QR decomposition of the MatFloat 'that' using the 
// Householder algorithm
// Return {NULL, NULL} if the MatFloat couldn't be decomposed
// http://www.seas.ucla.edu/~vandenbe/133A/lectures/qr.pdf
QRDecomp _MatFloatGetQR(const MatFloat* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (MatGetNbCol(that) > MatGetNbRow(that)) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, 
      "'that' must have at least as many rows as columns (%d<=%d)",
      MatGetNbCol(that), MatGetNbRow(that));
    PBErrCatch(PBMathErr);
  }
#endif

  // Allocate memory for the final R matrix
  VecShort2D dimR = VecShortCreateStatic2D();
  VecSet(&dimR, 0, MatGetNbCol(that));
  VecSet(&dimR, 1, MatGetNbCol(that));
  MatFloat* R = MatFloatCreate(&dimR);

  // Allocate memory for the final Q matrix
  MatFloat* Q = MatFloatCreate(MatDim(that));
  
  // Allocate memory for the QQ~ matrix
  VecShort2D dimQQtilde = VecShortCreateStatic2D();
  VecSet(&dimQQtilde, 0, MatGetNbRow(that));
  VecSet(&dimQQtilde, 1, MatGetNbRow(that));
  MatFloat* QQtilde = MatFloatCreate(&dimQQtilde);
  MatSetIdentity(QQtilde);
  
  // Create a clone of that to be overwritten during computation
  MatFloat* A = MatClone(that);

  // Declare two vectors to access value in the arrays
  VecShort2D pos = VecShortCreateStatic2D();
  VecShort2D shiftPos = VecShortCreateStatic2D();
  
  // Householder algorithm
  for (short k = 0; k < MatGetNbCol(that); ++k) {

    // Calculate w 
    VecFloat* w = VecFloatCreate(MatGetNbRow(that) - k);
    VecSet(&pos, 0, k);
    for (short i = 0; i < VecGetDim(w); ++i) {
      VecSet(&pos, 1, k + i);
      VecSet(w, i, MatGet(A, &pos));
    }
    if(ISEQUALF(VecNorm(w), 0.0)) {
      MatFree(&R);
      MatFree(&Q);
      MatFree(&QQtilde);
      MatFree(&A);
      VecFree(&w);
      return (QRDecomp){._Q = NULL, ._R = NULL};
    }
    float sign = (VecGet(w, 0) >= 0.0 ? 1.0 : -1.0);
    VecSet(w, 0, VecGet(w, 0) + sign * VecNorm(w));

    // Calculate v = w / ||w||
    VecFloat* v = VecClone(w);
    VecNormalise(v);

    //                         I 0
    // Calculate the reflector 0 H where H = I - 2vv^t
    VecShort2D dimH = VecShortCreateStatic2D();
    VecSet(&dimH, 0, VecGetDim(v));
    VecSet(&dimH, 1, VecGetDim(v));
    MatFloat* H = MatFloatCreate(&dimH);
    MatSetIdentity(H);
    MatFloat* vvt = MatGetProdVecVecTranspose(v, v);
    MatScale(vvt, -2.0);
    MatAdd(H, vvt);
    MatFloat* reflector = MatFloatCreate(&dimQQtilde);
    MatSetIdentity(reflector);
    VecSetNull(&pos);
    do {
      VecSet(&shiftPos, 0, VecGet(&pos, 0) + k);
      VecSet(&shiftPos, 1, VecGet(&pos, 1) + k);
      MatSet(reflector, &shiftPos, MatGet(H, &pos));
    } while (VecStep(&pos, &dimH));

    // Update A := reflector . A
    MatFloat* M = MatGetProdMat(reflector, A);
    MatFree(&A);
    A = M;

    // Update QQtilde := QQtilde.reflector
    M = MatGetProdMat(QQtilde, reflector);
    MatFree(&QQtilde);
    QQtilde = M;

    // Free memory
    MatFree(&reflector);
    MatFree(&H);
    MatFree(&vvt);
    VecFree(&v);
    VecFree(&w);
  }

  // Extract R from the final A
  VecSetNull(&pos);
  do {
    MatSet(R, &pos, MatGet(A, &pos));
  } while (VecStep(&pos, &dimR));

  // Extract Q from the final QQtilde
  VecSetNull(&pos);
  do {
    MatSet(Q, &pos, MatGet(QQtilde, &pos));
  } while (VecStep(&pos, MatDim(that)));

  // Create the result QR decomposition
  QRDecomp qr = {._Q = Q, ._R = R};
  
  // Free memory
  MatFree(&A);
  MatFree(&QQtilde);
  
  // Return the decomposition 
  return qr;
}

// Calculate the transposed of the MatFloat 'that'
MatFloat* _MatFloatGetTranspose(const MatFloat* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Allocate memory for the result matrix
  VecShort2D dim = VecShortCreateStatic2D();
  VecSet(&dim, 0, VecGet(MatDim(that), 1));
  VecSet(&dim, 1, VecGet(MatDim(that), 0));
  MatFloat* res = MatFloatCreate(&dim);
  // Calculate the transposed matrix
  VecShort2D pos = VecShortCreateStatic2D();
  VecShort2D posB = VecShortCreateStatic2D();
  do {
    VecSet(&posB, 0, VecGet(&pos, 1));
    VecSet(&posB, 1, VecGet(&pos, 0));
    MatSet(res, &pos, MatGet(that, &posB));
  } while (VecStep(&pos, &dim));
  // Return the transposed matrix
  return res;
}


// -------------- Gauss

// ================= Define ==================

// ================ Functions implementation ====================

// Create a new Gauss of mean 'mean' and sigma 'sigma'
// Return NULL if we couldn't create the Gauss
Gauss* GaussCreate(const float mean, const float sigma) {
  // Allocate memory
  Gauss *that = PBErrMalloc(PBMathErr, sizeof(Gauss));
  // Set properties
  that->_mean = mean;
  that->_sigma = sigma;
  // Return the new Gauss
  return that;
}
Gauss GaussCreateStatic(const float mean, const float sigma) {
  // Allocate memory
  Gauss that = {._mean = mean, ._sigma = sigma};
  // Return the new Gauss
  return that;
}

// Free the memory used by a Gauss
// Do nothing if arguments are invalid
void GaussFree(Gauss** that) {
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
SysLinEq* _SLECreate(const MatFloat* const m, const VecFloat* const v) {
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
    if (VecGet(&(m->_dim), 0) != VecGetDim(v)) {
      PBMathErr->_type = PBErrTypeInvalidArg;
      sprintf(PBMathErr->_msg, 
        "the matrix and vector have incompatible dimensions (%d==%ld)",
        VecGet(&(m->_dim), 0), VecGetDim(v));
      PBErrCatch(PBMathErr);
    }
  }
#endif
  // Allocate memory
  SysLinEq* that = PBErrMalloc(PBMathErr, sizeof(SysLinEq));
  that->_M = MatClone(m);
  that->_Minv = MatGetInv(that->_M);
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
SysLinEq* SysLinEqClone(const SysLinEq* const that) {
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

// -------------- Ratio

// ================ Functions implementation ====================

// Create a new static Ratio
Ratio RatioCreateStatic(long b, unsigned int n, unsigned int d) {
#if BUILDMODE == 0
  if (d == 0) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'d' is invalid (%u > 0)", d);
    PBErrCatch(PBMathErr);
  }
#endif
  
  // Create the Ratio
  Ratio ratio = {
    ._base = b,
    ._numerator = n,
    ._denominator = d
  };

  // Return the Ratio
  return ratio;

}

// Convert the float 'v' into the nearest Ratio using the Farey's algorithm
// given the precision 'prec'
Ratio RatioFromFloatPrec(float v, float prec) {

  // Create the two bounding Ratio
  Ratio ratioLow = RatioCreateStatic(0, 0, 1);
  Ratio ratioHigh = RatioCreateStatic(0, 1, 1);

  // Create the result ratio
  Ratio ratio = RatioCreateStatic(floor(v), 0, 1);

  // Get the decimals of 'v'
  float dec = v - RatioGetBase(&ratio);
  
  // Loop until the bounding Ratio reachs the requested precision
  Ratio mediant;
  while(
    RatioToFloat(&ratioHigh) - RatioToFloat(&ratioLow) > prec &&
    fabs(RatioToFloat(&ratioHigh) - dec) > prec &&
    fabs(RatioToFloat(&ratioLow) - dec) > prec) {

    mediant = RatioCreateStatic(0, 
      RatioGetNumerator(&ratioLow) + RatioGetNumerator(&ratioHigh),
      RatioGetDenominator(&ratioLow) + RatioGetDenominator(&ratioHigh));

    if (RatioToFloat(&mediant) > dec) {

      ratioHigh = mediant;

    } else {

      ratioLow = mediant;

    }

  }

  // Update the fractional part of the result
  if (fabs(RatioToFloat(&ratioHigh) - dec) <= prec) {

    RatioSetNumerator(&ratio, RatioGetNumerator(&ratioHigh));
    RatioSetDenominator(&ratio, RatioGetDenominator(&ratioHigh));

  } else if (fabs(RatioToFloat(&ratioLow) - dec) <= prec) {

    RatioSetNumerator(&ratio, RatioGetNumerator(&ratioLow));
    RatioSetDenominator(&ratio, RatioGetDenominator(&ratioLow));

  } else {

    RatioSetNumerator(&ratio, RatioGetNumerator(&mediant));
    RatioSetDenominator(&ratio, RatioGetDenominator(&mediant));

  }

  // Reduce the result
  RatioReduce(&ratio);

  // Return the result
  return ratio;

}

// Convert the Ratio 'that' into a float
float RatioToFloat(const Ratio* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Return the Ratio converted to float
  return (float)RatioGetBase(that) + 
    (float)RatioGetNumerator(that) / (float)RatioGetDenominator(that);
}

// Reduce the fractional part of the Ratio 'that' and update the base such as
// numerator < denominator
void RatioReduce(Ratio* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif

  // If the numerator is greater than the denominator
  if (RatioGetNumerator(that) >= RatioGetDenominator(that)) {

    // Update the component to keep the fractional part less than 1.0
    unsigned int delta = RatioGetNumerator(that) / RatioGetDenominator(that);
    RatioSetBase(that, RatioGetBase(that) + delta);
    RatioSetNumerator(that, 
      RatioGetNumerator(that) - delta * RatioGetDenominator(that));

  }

  // Get the GCD of the numerator and denominator
  unsigned int div = GetGCD(
    RatioGetNumerator(that), RatioGetDenominator(that));
  // Divide the numerator and denominator by the gcd
  RatioSetNumerator(that, RatioGetNumerator(that) / div);
  RatioSetDenominator(that, RatioGetDenominator(that) / div);

}

// Print the Ratio on 'stream' as a+b/c
void RatioPrint(const Ratio* that, FILE* stream) {
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

  fprintf(stream, "%ld+%u/%u", 
    RatioGetBase(that), RatioGetNumerator(that), RatioGetDenominator(that));

}

// -------------- Usefull basic functions

// ================ Functions implementation ====================

// Compute the 'iElem'-th element of the 'base'-ary version of the 
// Thue-Morse sequence
// 'iElem' >= 0
// 'base' >= 2
long ThueMorseSeqGetNthElem(long iElem, long base) {
#if BUILDMODE == 0
  if (iElem < 0) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'iElem' is invalid (%ld>=0)", iElem);
    PBErrCatch(PBMathErr);
  }
  if (base < 2) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'base' is invalid (%ld>=2)", base);
    PBErrCatch(PBMathErr);
  }
#endif
  if (base > iElem) {
    return iElem;
  } else {
    ldiv_t d = ldiv(iElem, base);
    return (ThueMorseSeqGetNthElem(d.quot, base) + d.rem) % base;
  }
}

// Return a set of two vectors containing the bounds of the vectors in 
// the GSet 'that'
// The set must have at least one element
// The returned set is ordered as follow: (boundMin, boundMax)
GSetVecFloat _GSetVecFloatGetBounds(const GSetVecFloat* const that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (GSetNbElem(that) < 1) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'that' is empty");
    PBErrCatch(PBMathErr);
  }
#endif
  // Create the set containing the bounds
  GSetVecFloat bounds = GSetVecFloatCreateStatic();
  // Create the two bounds vector, initialised with the first vector of 
  // the set
  VecFloat* boundMin = _VecFloatClone(GSetGet(that, 0));
  VecFloat* boundMax = _VecFloatClone(GSetGet(that, 0));
  GSetAppend(&bounds, boundMin);
  GSetAppend(&bounds, boundMax);
  // Get the dimension of the vectors, supposes they are all with same 
  // dimension
  long dim = _VecFloatGetDim(boundMin);
  // Loop on the vectors of the set, expect the first one
  GSetIterForward iter = GSetIterForwardCreateStatic(that);
  while (GSetIterStep(&iter)) {
    VecFloat* v = GSetIterGet(&iter);
    // Loop on dimension
    for (int iDim = dim; iDim--;) {
      // Update bounds
      if (_VecFloatGet(boundMin, iDim) > _VecFloatGet(v, iDim))
        _VecFloatSet(boundMin, iDim, _VecFloatGet(v, iDim));
      if (_VecFloatGet(boundMax, iDim) < _VecFloatGet(v, iDim))
        _VecFloatSet(boundMax, iDim, _VecFloatGet(v, iDim));
    }
  }
  // Return the set containing the bounds
  return bounds;
}

// Compute the area of a triangle knowing its 3 sides length 'a', 'b', 'c'
// using the Hero's formula
double GetAreaTriangleHero(
  const double a,
  const double b,
  const double c) {

  double s = 0.5 * (a + b + c);
  double area = sqrt(s * (s - a) * (s - b) * (s - c));
  return area;

}

// Return the Fibonacci sequence up to the 'n'-th element in a dynamically
// allocated array of unsigned long
unsigned long* GetFibonacciSeq(unsigned int n) {

  if (n == 0) {

    return NULL;

  } else {

    unsigned long* seq =
      PBErrMalloc(
        PBMathErr,
        sizeof(unsigned long) * n);
    for (
      unsigned int i = 0;
      i < n && i < 2;
      ++i) {

      seq[i] = 1L;

    }
    for (
      unsigned int i = 2;
      i < n;
      ++i) {

      seq[i] = seq[i - 1] + seq[i - 2];

    }

    return seq;

  }

}

// Return the Fibonacci grid lattice for the 'n'-th Fibonacci number in a
// dynamically allocated array of pairs of float in [0,1]
// Stores the nb of points in 'nbPoints'
float* GetFibonacciGridLattice(
    unsigned int n,
  unsigned long* nbPoints) {

#if BUILDMODE == 0

  if (nbPoints == NULL) {

    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'nbPoints' is null");
    PBErrCatch(PBMathErr);

  }

#endif

  if (n == 0) {

    *nbPoints = 0;
    return NULL;

  } else {

    // Get the Fibonacci sequence
    unsigned long* seq = GetFibonacciSeq(n);

    // Update the number of points
    *nbPoints = seq[n - 1];

    // Allocate memory for the result
    float* lattice =
      PBErrMalloc(
        PBMathErr,
        sizeof(float) * 2L * (*nbPoints));

    // Generate the lattice points
    for (
      unsigned long iPoint = 0;
      iPoint < *nbPoints;
      ++iPoint) {

      lattice[iPoint * 2L] =
        fmodf(
          (float)iPoint / (float)seq[n > 1 ? n - 1 : 0],
          1.0);
      lattice[iPoint * 2L + 1L] =
        fmodf(
          (float)iPoint * (float)seq[n > 2 ? n - 2 : 0] /
            (float)seq[n > 1 ? n - 1 : 0],
          1.0);

    }

    // Free memory
    free(seq);

    // Return the lattice
    return lattice;

  }

}

// Return the Fibonacci polar lattice for the 'n'-th Fibonacci number in a
// dynamically allocated array of pairs of float in [-1,1]
// Stores the nb of points in 'nbPoints'
float* GetFibonacciPolarLattice(
    unsigned int n,
  unsigned long* nbPoints) {

#if BUILDMODE == 0

  if (nbPoints == NULL) {

    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'nbPoints' is null");
    PBErrCatch(PBMathErr);

  }

#endif

  // Get the grid lattice
  float* lattice =
    GetFibonacciGridLattice(
      n,
      nbPoints);

  // Convert each points to polar coordinates
  for (
    unsigned long iPoint = *nbPoints;
    iPoint--;) {

    lattice[iPoint * 2L] = sqrt(lattice[iPoint * 2L]);
    lattice[iPoint * 2L + 1L] = 2.0 * PBMATH_PI * lattice[iPoint * 2L + 1L];

  }

  // Return the lattice
  return lattice;

}

// Return the greatest common divisor using the Stein's algorithm
// https://en.wikipedia.org/wiki/Binary_GCD_algorithm
unsigned int GetGCD(unsigned int u, unsigned int v) {

    unsigned int shift = 0;
    if (u == 0) 
      return v;
    if (v == 0) 
      return u;
    while (((u | v) & 1) == 0) {
        ++shift;
        u >>= 1;
        v >>= 1;
    }
    while ((u & 1) == 0)
        u >>= 1;
    do {
        while ((v & 1) == 0)
            v >>= 1;
        if (u > v) {
            unsigned int t = v; 
            v = u; 
            u = t;
        }
        v -= u;
    } while (v != 0);
    return u << shift;

}

// -------------- LeastSquareLinReg

// ================ Functions implementation ====================

// Create a new static LeastSquareLinReg
LeastSquareLinReg LeastSquareLinRegCreateStatic(MatFloat* X) {

#if BUILDMODE == 0

  if (X == NULL) {

    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'X' is null");
    PBErrCatch(PBMathErr);

  }

#endif

  // Declare the new LeastSquareLin
  LeastSquareLinReg that;

  // Set the properties
  that.Xp = NULL;
  LSLRSetComp(
    &that,
    X);
  that.bias = 0.0;

  // Return the new LeastSquareLin
  return that;

}

// Free the static LeastSquareLinReg 'that'
void LeastSquareLinRegFreeStatic(LeastSquareLinReg* that) {

  if (that == NULL) {

    return;

  }

  // Free memory
  MatFree(&(that->Xp));

}

// Compute the solution of the LeastSquareLinReg 'that' for 'Y'
VecFloat* LSLRSolve(LeastSquareLinReg* that, const VecFloat* Y) {

#if BUILDMODE == 0

  if (that == NULL) {

    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);

  }

  if (that->X == NULL) {

    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that->X' is null");
    PBErrCatch(PBMathErr);

  }

  if (that->Xp == NULL) {

    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that->Xp' is null");
    PBErrCatch(PBMathErr);

  }

  if (Y == NULL) {

    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'Y' is null");
    PBErrCatch(PBMathErr);

  }

#endif

  // Get the result
  VecFloat* beta =
    MatGetProdVec(
      that->Xp,
      Y);

  // Calculate the bias
  VecFloat* Ybeta =
    MatGetProdVec(
      that->X,
      beta);
  VecOp(
    Ybeta,
    1.0,
    Y,
    -1.0);
  that->bias = VecNorm(Ybeta);
  VecFree(&Ybeta);

  // Return the result
  return beta;

}
