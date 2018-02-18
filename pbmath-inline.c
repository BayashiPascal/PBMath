// ============ PBMATH_INLINE.C ================

// ================ Functions implementation ====================

// Static constructors for VecShort
#if BUILDMODE != 0
inline
#endif 
VecShort2D VecShortCreateStatic2D() {
  VecShort2D v = {._val = {0, 0}, ._dim = 2};
  return v;
}
#if BUILDMODE != 0
inline
#endif 
VecShort3D VecShortCreateStatic3D() {
  VecShort3D v = {._val = {0, 0, 0}, ._dim = 3};
  return v;
}
#if BUILDMODE != 0
inline
#endif 
VecShort4D VecShortCreateStatic4D() {
  VecShort4D v = {._val = {0, 0, 0, 0}, ._dim = 4};
  return v;
}

// Return the i-th value of the VecShort
#if BUILDMODE != 0
inline
#endif 
short _VecShortGet(VecShort* that, int i) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (i < 0 || i >= that->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'i' is invalid (0<=%d<%d)", i, 
      that->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  return ((short*)(((void*)that) + sizeof(int)))[i];
}
#if BUILDMODE != 0
inline
#endif 
short _VecShortGet2D(VecShort2D* that, int i) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (i < 0 || i >= 2) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'i' is invalid (0<=%d<2)", i);
    PBErrCatch(PBMathErr);
  }
#endif
  return that->_val[i];
}
#if BUILDMODE != 0
inline
#endif 
short _VecShortGet3D(VecShort3D* that, int i) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (i < 0 || i >= 3) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'i' is invalid (0<=%d<3)", i);
    PBErrCatch(PBMathErr);
  }
#endif
  return that->_val[i];
}
#if BUILDMODE != 0
inline
#endif 
short _VecShortGet4D(VecShort4D* that, int i) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (i < 0 || i >= 4) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'i' is invalid (0<=%d<4)", i);
    PBErrCatch(PBMathErr);
  }
#endif
  return that->_val[i];
}

// Set the i-th value of the VecShort to v
#if BUILDMODE != 0
inline
#endif 
void _VecShortSet(VecShort* that, int i, short v) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (i < 0 || i >= that->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'i' is invalid (0<=%d<%d)", i, 
      that->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  ((short*)(((void*)that) + sizeof(int)))[i] = v;
}
#if BUILDMODE != 0
inline
#endif 
void _VecShortSet2D(VecShort2D* that, int i, short v) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (i < 0 || i >= 2) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'i' is invalid (0<=%d<2)", i);
    PBErrCatch(PBMathErr);
  }
#endif
  that->_val[i] = v;
}
#if BUILDMODE != 0
inline
#endif 
void _VecShortSet3D(VecShort3D* that, int i, short v) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (i < 0 || i >= 3) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'i' is invalid (0<=%d<3)", i);
    PBErrCatch(PBMathErr);
  }
#endif
  that->_val[i] = v;
}
#if BUILDMODE != 0
inline
#endif 
void _VecShortSet4D(VecShort4D* that, int i, short v) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (i < 0 || i >= 4) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'i' is invalid (0<=%d<4)", i);
    PBErrCatch(PBMathErr);
  }
#endif
  that->_val[i] = v;
}

// Set all values of the vector 'that' to 0
#if BUILDMODE != 0
inline
#endif 
void _VecShortSetNull(VecShort* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Set values
  for (int iDim = that->_dim; iDim--;)
    that->_val[iDim] = 0;
}

// Return the dimension of the VecShort
#if BUILDMODE != 0
inline
#endif 
int _VecShortGetDim(VecShort* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  return that->_dim;
}
// Return the Hamiltonian distance between the VecShort 'that' and 'tho'
#if BUILDMODE != 0
inline
#endif 
short _VecShortHamiltonDist(VecShort* that, VecShort* tho) {
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
  if (that->_dim != tho->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "dimensions don't match (%d==%d)", 
      that->_dim, tho->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable to calculate the distance
  short ret = 0;
  for (int iDim = VecGetDim(that); iDim--;)
    ret += abs(VecGet(that, iDim) - VecGet(tho, iDim));
  // Return the distance
  return ret;
}
#if BUILDMODE != 0
inline
#endif 
short _VecShortHamiltonDist2D(VecShort2D* that, VecShort2D* tho) {
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
  // Return the distance
  return abs(VecGet(that, 0) - VecGet(tho, 0)) + 
    abs(VecGet(that, 1) - VecGet(tho, 1));
}
#if BUILDMODE != 0
inline
#endif 
short _VecShortHamiltonDist3D(VecShort3D* that, VecShort3D* tho) {
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
  // Return the distance
  return abs(VecGet(that, 0) - VecGet(tho, 0)) + 
    abs(VecGet(that, 1) - VecGet(tho, 1)) +
    abs(VecGet(that, 2) - VecGet(tho, 2));
}
#if BUILDMODE != 0
inline
#endif 
short _VecShortHamiltonDist4D(VecShort4D* that, VecShort4D* tho) {
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
  // Return the distance
  return abs(VecGet(that, 0) - VecGet(tho, 0)) + 
    abs(VecGet(that, 1) - VecGet(tho, 1)) +
    abs(VecGet(that, 2) - VecGet(tho, 2)) +
    abs(VecGet(that, 3) - VecGet(tho, 3));
}

// Return true if the VecShort 'that' is equal to 'tho', else false
#if BUILDMODE != 0
inline
#endif 
bool _VecShortIsEqual(VecShort* that, VecShort* tho) {
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
  if (that->_dim != tho->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "dimensions don't match (%d==%d)", 
      that->_dim, tho->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  return 
    (memcmp(that->_val, tho->_val, sizeof(short) * that->_dim) == 0);
}

// Copy the values of 'tho' in 'that'
#if BUILDMODE != 0
inline
#endif 
void _VecShortCopy(VecShort* that, VecShort* tho) {
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
  if (that->_dim != tho->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "dimensions don't match (%d==%d)", 
      that->_dim, tho->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // Copy the values
  memcpy(that->_val, tho->_val, sizeof(short) * that->_dim);
}

// Return the dot product of 'that' and 'tho'
#if BUILDMODE != 0
inline
#endif 
short _VecShortDotProd(VecShort* that, VecShort* tho) {
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
  if (that->_dim != tho->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "dimensions don't match (%d==%d)", 
      that->_dim, tho->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable ot memorise the result
  short res = 0;
  // For each component
  for (int iDim = that->_dim; iDim--;)
    // Calculate the product
    res += VecGet(that, iDim) * VecGet(tho, iDim);
  // Return the result
  return res;
}
#if BUILDMODE != 0
inline
#endif 
short _VecShortDotProd2D(VecShort2D* that, VecShort2D* tho) {
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
  return VecGet(that, 0) * VecGet(tho, 0) +
    VecGet(that, 1) * VecGet(tho, 1);
}
#if BUILDMODE != 0
inline
#endif 
short _VecShortDotProd3D(VecShort3D* that, VecShort3D* tho) {
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
  return VecGet(that, 0) * VecGet(tho, 0) +
    VecGet(that, 1) * VecGet(tho, 1) +
    VecGet(that, 2) * VecGet(tho, 2);
}
#if BUILDMODE != 0
inline
#endif 
short _VecShortDotProd4D(VecShort4D* that, VecShort4D* tho) {
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
  return VecGet(that, 0) * VecGet(tho, 0) +
    VecGet(that, 1) * VecGet(tho, 1) +
    VecGet(that, 2) * VecGet(tho, 2) +
    VecGet(that, 3) * VecGet(tho, 3);
}

// Static constructors for VecFloat
#if BUILDMODE != 0
inline
#endif 
VecFloat2D VecFloatCreateStatic2D() {
  VecFloat2D v = {._val = {0.0, 0.0}, ._dim = 2};
  return v;
}
#if BUILDMODE != 0
inline
#endif 
VecFloat3D VecFloatCreateStatic3D() {
  VecFloat3D v = {._val = {0.0, 0.0, 0.0}, ._dim = 3};
  return v;
}

// Return the i-th value of the VecFloat
#if BUILDMODE != 0
inline
#endif 
float _VecFloatGet(VecFloat* that, int i) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (i < 0 || i >= that->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, 
      "'i' is invalid (0<=%d<%d)", i, that->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // Return the value
  return that->_val[i];
}
#if BUILDMODE != 0
inline
#endif 
float _VecFloatGet2D(VecFloat2D* that, int i) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (i < 0 || i >= 2) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'i' is invalid (0<=%d<2)", i);
    PBErrCatch(PBMathErr);
  }
#endif
  // Return the value
  return that->_val[i];
}
#if BUILDMODE != 0
inline
#endif 
float _VecFloatGet3D(VecFloat3D* that, int i) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (i < 0 || i >= 3) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'i' is invalid (0<=%d<3)", i);
    PBErrCatch(PBMathErr);
  }
#endif
  // Return the value
  return that->_val[i];
}

// Set the i-th value of the VecFloat to v
#if BUILDMODE != 0
inline
#endif 
void _VecFloatSet(VecFloat* that, int i, float v) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (i < 0 || i >= that->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, 
      "'i' is invalid (0<=%d<%d)", i, that->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // Set the value
  that->_val[i] = v;
}
#if BUILDMODE != 0
inline
#endif 
void _VecFloatSet2D(VecFloat2D* that, int i, float v) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (i < 0 || i >= 2) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'i' is invalid (0<=%d<2)", i);
    PBErrCatch(PBMathErr);
  }
#endif
  // Set the value
  that->_val[i] = v;
}
#if BUILDMODE != 0
inline
#endif 
void _VecFloatSet3D(VecFloat3D* that, int i, float v) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (i < 0 || i >= 3) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'i' is invalid (0<=%d<3)", i);
    PBErrCatch(PBMathErr);
  }
#endif
  // Set the value
  that->_val[i] = v;
}

// Set all values of the vector 'that' to 0.0
#if BUILDMODE != 0
inline
#endif 
void _VecFloatSetNull(VecFloat* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Set values
  for (int iDim = that->_dim; iDim--;)
    that->_val[iDim] = 0.0;
}
#if BUILDMODE != 0
inline
#endif 
void _VecFloatSetNull2D(VecFloat2D* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Set values
  that->_val[0] = 0.0;
  that->_val[1] = 0.0;
}
#if BUILDMODE != 0
inline
#endif 
void _VecFloatSetNull3D(VecFloat3D* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Set values
  that->_val[0] = 0.0;
  that->_val[1] = 0.0;
  that->_val[2] = 0.0;
}

// Return the dimension of the VecFloat
#if BUILDMODE != 0
inline
#endif 
int _VecFloatGetDim(VecFloat* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  return that->_dim;
}

// Copy the values of 'tho' in 'that'
#if BUILDMODE != 0
inline
#endif 
void _VecFloatCopy(VecFloat* that, VecFloat* tho) {
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
  if (that->_dim != tho->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "dimensions don't match (%d==%d)", 
      that->_dim, tho->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // Copy the values
  memcpy(that->_val, tho->_val, sizeof(float) * that->_dim);
}

// Return the norm of the VecFloat
#if BUILDMODE != 0
inline
#endif 
float _VecFloatNorm(VecFloat* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable to calculate the norm
  float ret = 0.0;
  // Calculate the norm
  for (int iDim = that->_dim; iDim--;)
    ret += fsquare(VecGet(that, iDim));
  ret = sqrt(ret);
  // Return the result
  return ret;
}
#if BUILDMODE != 0
inline
#endif 
float _VecFloatNorm2D(VecFloat2D* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Return the result
  return sqrt(fsquare(VecGet(that, 0)) + fsquare(VecGet(that, 1)));
}
#if BUILDMODE != 0
inline
#endif 
float _VecFloatNorm3D(VecFloat3D* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Return the result
  return sqrt(fsquare(VecGet(that, 0)) + fsquare(VecGet(that, 1)) + 
    fsquare(VecGet(that, 2)));
}

// Normalise the VecFloat
#if BUILDMODE != 0
inline
#endif 
void _VecFloatNormalise(VecFloat* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Normalise
  float norm = VecNorm(that);
  for (int iDim = that->_dim; iDim--;)
    VecSet(that, iDim, VecGet(that, iDim) / norm);
}

#if BUILDMODE != 0
inline
#endif 
void _VecFloatNormalise2D(VecFloat2D* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Normalise
  float norm = _VecFloatNorm2D(that);
  VecSet(that, 0, VecGet(that, 0) / norm);
  VecSet(that, 1, VecGet(that, 1) / norm);
}
#if BUILDMODE != 0
inline
#endif 
void _VecFloatNormalise3D(VecFloat3D* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Normalise
  float norm = _VecFloatNorm3D(that);
  VecSet(that, 0, VecGet(that, 0) / norm);
  VecSet(that, 1, VecGet(that, 1) / norm);
  VecSet(that, 2, VecGet(that, 2) / norm);
}

// Return the distance between the VecFloat 'that' and 'tho'
#if BUILDMODE != 0
inline
#endif 
float _VecFloatDist(VecFloat* that, VecFloat* tho) {
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
  if (that->_dim != tho->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "dimensions don't match (%d==%d)", 
      that->_dim, tho->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable to calculate the distance
  float ret = 0.0;
  for (int iDim = that->_dim; iDim--;)
    ret += fsquare(VecGet(that, iDim) - VecGet(tho, iDim));
  ret = sqrt(ret);
  // Return the distance
  return ret;
}
#if BUILDMODE != 0
inline
#endif 
float _VecFloatDist2D(VecFloat2D* that, VecFloat2D* tho) {
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
  // Return the distance
  return sqrt(fsquare(VecGet(that, 0) - VecGet(tho, 0)) +
    fsquare(VecGet(that, 1) - VecGet(tho, 1)));
}
#if BUILDMODE != 0
inline
#endif 
float _VecFloatDist3D(VecFloat3D* that, VecFloat3D* tho) {
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
  // Return the distance
  return sqrt(fsquare(VecGet(that, 0) - VecGet(tho, 0)) +
    fsquare(VecGet(that, 1) - VecGet(tho, 1)) +
    fsquare(VecGet(that, 2) - VecGet(tho, 2)));
}

// Return the Hamiltonian distance between the VecFloat 'that' and 'tho'
#if BUILDMODE != 0
inline
#endif 
float _VecFloatHamiltonDist(VecFloat* that, VecFloat* tho) {
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
  if (that->_dim != tho->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "dimensions don't match (%d==%d)", 
      that->_dim, tho->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable to calculate the distance
  float ret = 0.0;
  for (int iDim = that->_dim; iDim--;)
    ret += fabs(VecGet(that, iDim) - VecGet(tho, iDim));
  // Return the distance
  return ret;
}
#if BUILDMODE != 0
inline
#endif 
float _VecFloatHamiltonDist2D(VecFloat2D* that, VecFloat2D* tho) {
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
  // Return the distance
  return fabs(VecGet(that, 0) - VecGet(tho, 0)) + 
    fabs(VecGet(that, 1) - VecGet(tho, 1));
}
#if BUILDMODE != 0
inline
#endif 
float _VecFloatHamiltonDist3D(VecFloat3D* that, VecFloat3D* tho) {
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
  // Return the distance
  return fabs(VecGet(that, 0) - VecGet(tho, 0)) + 
    fabs(VecGet(that, 1) - VecGet(tho, 1)) +
    fabs(VecGet(that, 2) - VecGet(tho, 2));
}

// Return the Pixel distance between the VecFloat 'that' and 'tho'
#if BUILDMODE != 0
inline
#endif 
float _VecFloatPixelDist(VecFloat* that, VecFloat* tho) {
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
  if (that->_dim != tho->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "dimensions don't match (%d==%d)", 
      that->_dim, tho->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable to calculate the distance
  float ret = 0.0;
  for (int iDim = that->_dim; iDim--;)
    ret += fabs(floor(VecGet(that, iDim)) - floor(VecGet(tho, iDim)));
  // Return the distance
  return ret;
}
#if BUILDMODE != 0
inline
#endif 
float _VecFloatPixelDist2D(VecFloat2D* that, VecFloat2D* tho) {
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
  // Return the distance
  return fabs(floor(VecGet(that, 0)) - floor(VecGet(tho, 0))) +
    fabs(floor(VecGet(that, 1)) - floor(VecGet(tho, 1)));
}
#if BUILDMODE != 0
inline
#endif 
float _VecFloatPixelDist3D(VecFloat3D* that, VecFloat3D* tho) {
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
  // Return the distance
  return fabs(floor(VecGet(that, 0)) - floor(VecGet(tho, 0))) +
    fabs(floor(VecGet(that, 1)) - floor(VecGet(tho, 1))) +
    fabs(floor(VecGet(that, 2)) - floor(VecGet(tho, 2)));
}

// Return true if the VecFloat 'that' is equal to 'tho', else false
#if BUILDMODE != 0
inline
#endif 
bool _VecFloatIsEqual(VecFloat* that, VecFloat* tho) {
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
  if (that->_dim != tho->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "dimensions don't match (%d==%d)", 
      that->_dim, tho->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // For each component
  for (int iDim = that->_dim; iDim--;)
    // If the values of this components are different
    if (!ISEQUALF(VecGet(that, iDim), VecGet(tho, iDim)))
      // Return false
      return false;
  // Return true
  return true;
}

// Calculate (that * a + tho * b) and store the result in 'that'
#if BUILDMODE != 0
inline
#endif 
void _VecFloatOp(VecFloat* that, float a, VecFloat* tho, float b) {
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
  if (that->_dim != tho->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "dimensions don't match (%d==%d)", 
      that->_dim, tho->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  for (int iDim = that->_dim; iDim--;)
    VecSet(that, iDim, 
      a * VecGet(that, iDim) + b * VecGet(tho, iDim));
}
#if BUILDMODE != 0
inline
#endif 
void _VecFloatOp2D(VecFloat2D* that, float a, VecFloat2D* tho, float b) {
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
  VecSet(that, 0, a * VecGet(that, 0) + b * VecGet(tho, 0));
  VecSet(that, 1, a * VecGet(that, 1) + b * VecGet(tho, 1));
}
#if BUILDMODE != 0
inline
#endif 
void _VecFloatOp3D(VecFloat3D* that, float a, VecFloat3D* tho, float b) {
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
  VecSet(that, 0, a * VecGet(that, 0) + b * VecGet(tho, 0));
  VecSet(that, 1, a * VecGet(that, 1) + b * VecGet(tho, 1));
  VecSet(that, 2, a * VecGet(that, 2) + b * VecGet(tho, 2));
}

// Return a VecFloat equal to (that * a + tho * b)
#if BUILDMODE != 0
inline
#endif 
VecFloat* _VecFloatGetOp(VecFloat* that, float a, 
  VecFloat* tho, float b) {
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
  if (that->_dim != tho->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "dimensions don't match (%d==%d)", 
      that->_dim, tho->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  VecFloat* res = VecFloatCreate(that->_dim);
  for (int iDim = that->_dim; iDim--;)
    VecSet(res, iDim, 
      a * VecGet(that, iDim) + b * VecGet(tho, iDim));
  return res;
}
#if BUILDMODE != 0
inline
#endif 
VecFloat2D _VecFloatGetOp2D(VecFloat2D* that, float a, 
  VecFloat2D* tho, float b) {
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
  VecFloat2D res = VecFloatCreateStatic2D();
  VecSet(&res, 0, a * VecGet(that, 0) + b * VecGet(tho, 0));
  VecSet(&res, 1, a * VecGet(that, 1) + b * VecGet(tho, 1));
  return res;
}
#if BUILDMODE != 0
inline
#endif 
VecFloat3D _VecFloatGetOp3D(VecFloat3D* that, float a, 
  VecFloat3D* tho, float b) {
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
  VecFloat3D res = VecFloatCreateStatic3D();
  VecSet(&res, 0, a * VecGet(that, 0) + b * VecGet(tho, 0));
  VecSet(&res, 1, a * VecGet(that, 1) + b * VecGet(tho, 1));
  VecSet(&res, 2, a * VecGet(that, 2) + b * VecGet(tho, 2));
  return res;
}

// Calculate (that * a) and store the result in 'that'
#if BUILDMODE != 0
inline
#endif 
void _VecFloatScale(VecFloat* that, float a) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  for (int iDim = that->_dim; iDim--;)
    VecSet(that, iDim, a * VecGet(that, iDim));
}
#if BUILDMODE != 0
inline
#endif 
void _VecFloatScale2D(VecFloat2D* that, float a) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  VecSet(that, 0, a * VecGet(that, 0));
  VecSet(that, 1, a * VecGet(that, 1));
}
#if BUILDMODE != 0
inline
#endif 
void _VecFloatScale3D(VecFloat3D* that, float a) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  VecSet(that, 0, a * VecGet(that, 0));
  VecSet(that, 1, a * VecGet(that, 1));
  VecSet(that, 2, a * VecGet(that, 2));
}

// Return a VecFloat equal to (that * a)
#if BUILDMODE != 0
inline
#endif 
VecFloat* _VecFloatGetScale(VecFloat* that, float a) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  VecFloat* res = VecFloatCreate(that->_dim);
  for (int iDim = that->_dim; iDim--;)
    VecSet(res, iDim, a * VecGet(that, iDim));
  return res;
}
#if BUILDMODE != 0
inline
#endif 
VecFloat2D _VecFloatGetScale2D(VecFloat2D* that, float a) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  VecFloat2D res = VecFloatCreateStatic2D();
  VecSet(&res, 0, a * VecGet(that, 0));
  VecSet(&res, 1, a * VecGet(that, 1));
  return res;
}
#if BUILDMODE != 0
inline
#endif 
VecFloat3D _VecFloatGetScale3D(VecFloat3D* that, float a) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  VecFloat3D res = VecFloatCreateStatic3D();
  VecSet(&res, 0, a * VecGet(that, 0));
  VecSet(&res, 1, a * VecGet(that, 1));
  VecSet(&res, 2, a * VecGet(that, 2));
  return res;
}

// Rotate CCW 'that' by 'theta' radians and store the result in 'that'
#if BUILDMODE != 0
inline
#endif 
void _VecFloatRot2D(VecFloat2D* that, float theta) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (VecGetDim(that) != 2) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'that' 's dimension is invalid (%d=2)",
      VecGetDim(that));
    PBErrCatch(PBMathErr);
  }
#endif
  *that = _VecFloatGetRot2D(that, theta);
}

// Return a VecFloat2D equal to 'that' rotated CCW by 'theta' radians
#if BUILDMODE != 0
inline
#endif 
VecFloat2D _VecFloatGetRot2D(VecFloat2D* that, float theta) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (VecGetDim(that) != 2) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'that' 's dimension is invalid (%d=2)",
      VecGetDim(that));
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable to memorize the result 
  VecFloat2D res = VecFloatCreateStatic2D();
  // Declare variable for optimization
  float cosTheta = cos(theta);
  float sinTheta = sin(theta);
  // Calculate the rotation
  VecSet(&res, 0, 
    cosTheta * VecGet(that, 0) - sinTheta * VecGet(that, 1));
  VecSet(&res, 1, 
    sinTheta * VecGet(that, 0) + cosTheta * VecGet(that, 1));
  // Return the result
  return res;
}

// Return the dot product of 'that' and 'tho'
#if BUILDMODE != 0
inline
#endif 
float _VecFloatDotProd(VecFloat* that, VecFloat* tho) {
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
  if (that->_dim != tho->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "dimensions don't match (%d==%d)", 
      that->_dim, tho->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable to memorize the result
  float res = 0.0;
  // Calculate
  for (int iDim = that->_dim; iDim--;)
    res += that->_val[iDim] * tho->_val[iDim];
  // Return the result
  return res;
}
#if BUILDMODE != 0
inline
#endif 
float _VecFloatDotProd2D(VecFloat2D* that, VecFloat2D* tho) {
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
  return that->_val[0] * tho->_val[0] + that->_val[1] * tho->_val[1];
}
#if BUILDMODE != 0
inline
#endif 
float _VecFloatDotProd3D(VecFloat3D* that, VecFloat3D* tho) {
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
  return that->_val[0] * tho->_val[0] + that->_val[1] * tho->_val[1] +
    that->_val[2] * tho->_val[2];
}

// Return the conversion of VecFloat 'that' to a VecShort using round()
#if BUILDMODE != 0
inline
#endif 
VecShort* VecFloatToShort(VecFloat* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Create the result
  VecShort* res = VecShortCreate(that->_dim);
  for (int iDim = that->_dim; iDim--;)
    VecSet(res, iDim, SHORT(VecGet(that, iDim)));
  // Return the result
  return res;
}
#if BUILDMODE != 0
inline
#endif 
VecShort2D VecFloatToShort2D(VecFloat2D* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Create the result
  VecShort2D res = VecShortCreateStatic2D();
  VecSet(&res, 0, SHORT(VecGet(that, 0)));
  VecSet(&res, 1, SHORT(VecGet(that, 1)));
  // Return the result
  return res;
}
#if BUILDMODE != 0
inline
#endif 
VecShort3D VecFloatToShort3D(VecFloat3D* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Create the result
  VecShort3D res = VecShortCreateStatic3D();
  VecSet(&res, 0, SHORT(VecGet(that, 0)));
  VecSet(&res, 1, SHORT(VecGet(that, 1)));
  VecSet(&res, 2, SHORT(VecGet(that, 2)));
  // Return the result
  return res;
}

// Return the conversion of VecShort 'that' to a VecFloat
#if BUILDMODE != 0
inline
#endif 
VecFloat* VecShortToFloat(VecShort* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Create the result
  VecFloat* res = VecFloatCreate(that->_dim);
  for (int iDim = that->_dim; iDim--;)
    VecSet(res, iDim, (float)VecGet(that, iDim));
  // Return the result
  return res;
}
#if BUILDMODE != 0
inline
#endif 
VecFloat2D VecShortToFloat2D(VecShort2D* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Create the result
  VecFloat2D res = VecFloatCreateStatic2D();
  VecSet(&res, 0, (float)VecGet(that, 0));
  VecSet(&res, 1, (float)VecGet(that, 1));
  // Return the result
  return res;
}
#if BUILDMODE != 0
inline
#endif 
VecFloat3D VecShortToFloat3D(VecShort3D* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Create the result
  VecFloat3D res = VecFloatCreateStatic3D();
  VecSet(&res, 0, (float)VecGet(that, 0));
  VecSet(&res, 1, (float)VecGet(that, 1));
  VecSet(&res, 2, (float)VecGet(that, 2));
  // Return the result
  return res;
}

// Get the max value in components of the vector 'that'
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatGetMaxVal(VecFloat* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable to memorize the result
  float max = VecGet(that, 0);
  // Search for the maximum value
  for (int i = VecGetDim(that); i-- && i != 0;)
    max = MAX(max, VecGet(that, i));
  // Return the result
  return max;
}

// Get the min value in components of the vector 'that'
#if BUILDMODE != 0 
inline 
#endif 
float _VecFloatGetMinVal(VecFloat* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable to memorize the result
  float min = VecGet(that, 0);
  // Search for the minimum value
  for (int i = VecGetDim(that); i-- && i != 0;)
    min = MIN(min, VecGet(that, i));
  // Return the result
  return min;
}

// Set the MatFloat to the identity matrix
// The matrix must be a square matrix
#if BUILDMODE != 0
inline
#endif 
void _MatFloatSetIdentity(MatFloat* that) {
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
  // Set the values
  VecShort2D i = VecShortCreateStatic2D();
  do {
    if (VecGet(&i, 0) == VecGet(&i, 1))
      MatSet(that, &i, 1.0);
    else
      MatSet(that, &i, 0.0);
  } while (VecStep(&i, &(that->_dim)));
}

// Return the addition of matrix 'that' with matrix 'tho'
// 'that' and 'tho' must have same dimensions
#if BUILDMODE != 0 
inline 
#endif 
MatFloat* _MatFloatGetAdd(MatFloat* that, MatFloat* tho) {
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
  if (VecIsEqual(MatDim(that), MatDim(tho)) == false) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, 
      "'that' and 'tho' have different dimensions");
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable for the result
  MatFloat* res = MatFloatCreate(MatDim(that));
  // Add each values
  VecShort2D i = VecShortCreateStatic2D();
  do {
    MatSet(res, &i, MatGet(that, &i) + MatGet(tho, &i));
  } while (VecStep(&i, MatDim(that)));
  // Return the result
  return res;
}

// Add matrix 'that' with matrix 'tho' and store the result in 'that'
// 'that' and 'tho' must have same dimensions
#if BUILDMODE != 0 
inline 
#endif 
void _MatFloatAdd(MatFloat* that, MatFloat* tho) {
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
  if (VecIsEqual(MatDim(that), MatDim(tho)) == false) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, 
      "'that' and 'tho' have different dimensions");
    PBErrCatch(PBMathErr);
  }
#endif
  // Add each values
  VecShort2D i = VecShortCreateStatic2D();
  do {
    MatSet(that, &i, MatGet(that, &i) + MatGet(tho, &i));
  } while (VecStep(&i, MatDim(that)));
}

// Copy the values of 'w' in 'that' (must have same dimensions)
#if BUILDMODE != 0
inline
#endif 
void _MatFloatCopy(MatFloat* that, MatFloat* tho) {
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
  if (!VecIsEqual(&(that->_dim), &(tho->_dim))) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, 
      "'that' and 'tho' have different dimensions (%dx%d==%dx%d)",
      VecGet(&(that->_dim), 0), VecGet(&(that->_dim), 1), 
      VecGet(&(tho->_dim), 0), VecGet(&(tho->_dim), 1));
    PBErrCatch(PBMathErr);
  }
#endif
  // Copy the matrix values
  int d = VecGet(&(that->_dim), 0) * VecGet(&(that->_dim), 1);
  memcpy(that->_val, tho->_val, d * sizeof(float));
}

// Return the value at index 'i' (col, line) of the MatFloat
// Index starts at 0, index in matrix = line * nbCol + col
#if BUILDMODE != 0
inline
#endif 
float _MatFloatGet(MatFloat* that, VecShort2D* index) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (index == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'index' is null");
    PBErrCatch(PBMathErr);
  }
  if (VecGet(index, 0) < 0 || 
    VecGet(index, 0) >= VecGet(&(that->_dim), 0) ||
    VecGet(index, 1) < 0 || 
    VecGet(index, 1) >= VecGet(&(that->_dim), 1)) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, 
      "'index' is invalid (0,0 <= %d,%d < %d,%d)",
      VecGet(index, 0), VecGet(index, 1), 
      VecGet(&(that->_dim), 0), VecGet(&(that->_dim), 1));
    PBErrCatch(PBMathErr);
  }
#endif
  // Return the value
  return that->_val[VecGet(index, 1) * VecGet(&(that->_dim), 0) + 
    VecGet(index, 0)];
}

// Set the value at index 'i' (col, line) of the MatFloat to 'v'
// Index starts at 0, index in matrix = line * nbCol + col
#if BUILDMODE != 0
inline
#endif 
void _MatFloatSet(MatFloat* that, VecShort2D* index, float v) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (index == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'index' is null");
    PBErrCatch(PBMathErr);
  }
  if (VecGet(index, 0) < 0 || 
    VecGet(index, 0) >= VecGet(&(that->_dim), 0) ||
    VecGet(index, 1) < 0 || 
    VecGet(index, 1) >= VecGet(&(that->_dim), 1)) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, 
      "'index' is invalid (0,0 <= %d,%d < %d,%d)",
      VecGet(index, 0), VecGet(index, 1), 
      VecGet(&(that->_dim), 0), VecGet(&(that->_dim), 1));
    PBErrCatch(PBMathErr);
  }
#endif
  // Set the value
  that->_val[VecGet(index, 1) * VecGet(&(that->_dim), 0) + 
    VecGet(index, 0)] = v;
}

// Return the dimension of the MatFloat
#if BUILDMODE != 0
inline
#endif 
VecShort2D* _MatFloatDim(MatFloat* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Return the dimension
  return &(that->_dim);
}

// Return a VecShort2D containing the dimension of the MatFloat
#if BUILDMODE != 0
inline
#endif 
VecShort2D _MatFloatGetDim(MatFloat* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Return the dimension
  return that->_dim;
}

// Return the value of the Gauss 'that' at 'x'
#if BUILDMODE != 0
inline
#endif 
float GaussGet(Gauss *that, float x) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Calculate the value
  float a = 1.0 / (that->_sigma * sqrt(2.0 * PBMATH_PI));
  float ret = a * exp(-1.0 * fsquare(x - that->_mean) / 
    (2.0 * fsquare(that->_sigma)));
  // Return the value
  return ret;
}

// Return a random value (in ]0.0, 1.0[)according to the 
// Gauss distribution 'that'
// random() must have been called before calling this function
#if BUILDMODE != 0
inline
#endif 
float GaussRnd(Gauss *that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare variable for calcul
  float v1,v2,s;
  // Calculate the value
  do {
    v1 = (rnd() - 0.5) * 2.0;
    v2 = (rnd() - 0.5) * 2.0;
    s = v1 * v1 + v2 * v2;
  } while (s >= 1.0);
  // Return the value
  float ret = 0.0;
  if (s > PBMATH_EPSILON)
    ret = v1 * sqrt(-2.0 * log(s) / s);
  return ret * that->_sigma + that->_mean;
}

// Return the order 1 smooth value of 'x'
// if x < 0.0 return 0.0
// if x > 1.0 return 1.0
#if BUILDMODE != 0
inline
#endif 
float SmoothStep(float x) {
  if (x > 0.0)
    if (x < 1.0)
      return x * x * (3.0 - 2.0 * x);
    else
      return 1.0;
  else
    return 0.0;
}

// Return the order 2 smooth value of 'x'
// if x < 0.0 return 0.0
// if x > 1.0 return 1.0
#if BUILDMODE != 0
inline
#endif 
float SmootherStep(float x) {
  if (x > 0.0)
    if (x < 1.0)
    return x * x * x * (x * (x * 6.0 - 15.0) + 10.0);
    else
      return 1.0;
  else
    return 0.0;
}

// Solve the SysLinEq _M.x = _V
// Return the solution vector, or null if there is no solution or the 
// arguments are invalid
#if BUILDMODE != 0
inline
#endif 
VecFloat* SysLinEqSolve(SysLinEq* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable to memorize the solution
  VecFloat* ret = NULL;
  // Calculate the solution
  ret = MatGetProdVec(that->_Minv, that->_V);
  // Return the solution vector
  return ret;
}

// Set the matrix of the SysLinEq to a copy of 'm'
// 'm' must have same dimensions has the current matrix
// Do nothing if arguments are invalid
#if BUILDMODE != 0
inline
#endif 
void SysLinEqSetM(SysLinEq* that, MatFloat* m) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (m == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'m' is null");
    PBErrCatch(PBMathErr);
  }
  if (!VecIsEqual(&(m->_dim), &(that->_M->_dim))) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'m' has invalid dimension (%dx%d==%dx%d)",
      VecGet(&(m->_dim), 0), VecGet(&(m->_dim), 1), 
      VecGet(&(that->_M->_dim), 0), VecGet(&(that->_M->_dim), 1));
    PBErrCatch(PBMathErr);
  }
#endif
  // Update the matrix values
  MatCopy(that->_M, m);
  // Update the inverse matrix
  MatFree(&(that->_Minv));
  that->_Minv = MatInv(that->_M);
#if BUILDMODE == 0
  if (that->_Minv == NULL) {
    PBMathErr->_type = PBErrTypeOther;
    sprintf(PBMathErr->_msg, "couldn't inverse the matrix");
    PBErrCatch(PBMathErr);
  }
#endif
}

// Set the vector of the SysLinEq to a copy of 'v'
// 'v' must have same dimensions has the current vector
// Do nothing if arguments are invalid
#if BUILDMODE != 0
inline
#endif 
void _SLESetV(SysLinEq* that, VecFloat* v) {
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
  if (VecGetDim(v) != VecGetDim(that->_V)) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'v' has invalid dimension (%d==%d)",
      VecGetDim(v), VecGetDim(that->_V));
    PBErrCatch(PBMathErr);
  }
#endif
  // Update the vector values
  VecCopy(that->_V, v);
}

// Return x^y when x and y are int
// to avoid numerical imprecision from (pow(double,double)
// From https://stackoverflow.com/questions/29787310/
// does-pow-work-for-int-data-type-in-c
#if BUILDMODE != 0
inline
#endif 
int powi(int base, int exp) {
  // Declare a variable to memorize the result and init to 1
  int res = 1;
  // Loop on exponent
  while (exp) {
    // Do some magic trick
    if (exp & 1)
      res *= base;
    exp /= 2;
    base *= base;
  }
  // Return the result
  return res;
}

// Calculate (that * a + tho * b) and store the result in 'that'
#if BUILDMODE != 0
inline
#endif 
void _VecShortOp(VecShort* that, short a, VecShort* tho, short b) {
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
  if (that->_dim != tho->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "dimensions don't match (%d==%d)", 
      that->_dim, tho->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  for (int iDim = that->_dim; iDim--;)
    VecSet(that, iDim, 
      a * VecGet(that, iDim) + b * VecGet(tho, iDim));
}
#if BUILDMODE != 0
inline
#endif 
void _VecShortOp2D(VecShort2D* that, short a, VecShort2D* tho, short b) {
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
  VecSet(that, 0, a * VecGet(that, 0) + b * VecGet(tho, 0));
  VecSet(that, 1, a * VecGet(that, 1) + b * VecGet(tho, 1));
}
#if BUILDMODE != 0
inline
#endif 
void _VecShortOp3D(VecShort3D* that, short a, VecShort3D* tho, short b) {
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
  VecSet(that, 0, a * VecGet(that, 0) + b * VecGet(tho, 0));
  VecSet(that, 1, a * VecGet(that, 1) + b * VecGet(tho, 1));
  VecSet(that, 2, a * VecGet(that, 2) + b * VecGet(tho, 2));
}
#if BUILDMODE != 0
inline
#endif 
void _VecShortOp4D(VecShort4D* that, short a, VecShort4D* tho, short b) {
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
  VecSet(that, 0, a * VecGet(that, 0) + b * VecGet(tho, 0));
  VecSet(that, 1, a * VecGet(that, 1) + b * VecGet(tho, 1));
  VecSet(that, 2, a * VecGet(that, 2) + b * VecGet(tho, 2));
  VecSet(that, 3, a * VecGet(that, 3) + b * VecGet(tho, 3));
}

// Return a VecShort equal to (that * a + tho * b)
#if BUILDMODE != 0
inline
#endif 
VecShort* _VecShortGetOp(VecShort* that, short a, 
  VecShort* tho, short b) {
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
  if (that->_dim != tho->_dim) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "dimensions don't match (%d==%d)", 
      that->_dim, tho->_dim);
    PBErrCatch(PBMathErr);
  }
#endif
  VecShort* res = VecShortCreate(that->_dim);
  for (int iDim = that->_dim; iDim--;)
    VecSet(res, iDim, 
      a * VecGet(that, iDim) + b * VecGet(tho, iDim));
  return res;
}
#if BUILDMODE != 0
inline
#endif 
VecShort2D _VecShortGetOp2D(VecShort2D* that, short a, 
  VecShort2D* tho, short b) {
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
  VecShort2D res = VecShortCreateStatic2D();
  VecSet(&res, 0, a * VecGet(that, 0) + b * VecGet(tho, 0));
  VecSet(&res, 1, a * VecGet(that, 1) + b * VecGet(tho, 1));
  return res;
}
#if BUILDMODE != 0
inline
#endif 
VecShort3D _VecShortGetOp3D(VecShort3D* that, short a, 
  VecShort3D* tho, short b) {
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
  VecShort3D res = VecShortCreateStatic3D();
  VecSet(&res, 0, a * VecGet(that, 0) + b * VecGet(tho, 0));
  VecSet(&res, 1, a * VecGet(that, 1) + b * VecGet(tho, 1));
  VecSet(&res, 2, a * VecGet(that, 2) + b * VecGet(tho, 2));
  return res;
}
#if BUILDMODE != 0
inline
#endif 
VecShort4D _VecShortGetOp4D(VecShort4D* that, short a, 
  VecShort4D* tho, short b) {
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
  VecShort4D res = VecShortCreateStatic4D();
  VecSet(&res, 0, a * VecGet(that, 0) + b * VecGet(tho, 0));
  VecSet(&res, 1, a * VecGet(that, 1) + b * VecGet(tho, 1));
  VecSet(&res, 2, a * VecGet(that, 2) + b * VecGet(tho, 2));
  VecSet(&res, 3, a * VecGet(that, 3) + b * VecGet(tho, 3));
  return res;
}

// Get the max value in components of the vector 'that'
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortGetMaxVal(VecShort* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable to memorize the result
  short max = VecGet(that, 0);
  // Search for the maximum value
  for (int i = VecGetDim(that); i-- && i != 0;)
    max = MAX(max, VecGet(that, i));
  // Return the result
  return max;
}

// Get the min value in components of the vector 'that'
#if BUILDMODE != 0 
inline 
#endif 
short _VecShortGetMinVal(VecShort* that) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
#endif
  // Declare a variable to memorize the result
  short min = VecGet(that, 0);
  // Search for the minimum value
  for (int i = VecGetDim(that); i-- && i != 0;)
    min = MIN(min, VecGet(that, i));
  // Return the result
  return min;
}

// Rotate right-hand 'that' by 'theta' radians around 'axis' and 
// store the result in 'that'
// 'axis' must be normalized
// https://en.wikipedia.org/wiki/Rotation_matrix
#if BUILDMODE != 0
inline
#endif 
void _VecFloatRotAxis(VecFloat3D* that, VecFloat3D* axis, float theta) {
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
    sprintf(PBMathErr->_msg, "'that' 's dimension is invalid (%d=3)",
      VecGetDim(that));
    PBErrCatch(PBMathErr);
  }
  if (VecGetDim(axis) != 3) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'axis' 's dimension is invalid (%d=3)",
      VecGetDim(axis));
    PBErrCatch(PBMathErr);
  }
  if (ISEQUALF(VecNorm(axis), 1.0) == false) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'axis' is not normalized");
    PBErrCatch(PBMathErr);
  }
#endif
  *that = _VecFloatGetRotAxis(that, axis, theta);
}

// Rotate right-hand 'that' by 'theta' radians around X and 
// store the result in 'that'
#if BUILDMODE != 0
inline
#endif 
void _VecFloatRotX(VecFloat3D* that, float theta) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (VecGetDim(that) != 3) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'that' 's dimension is invalid (%d=3)",
      VecGetDim(that));
    PBErrCatch(PBMathErr);
  }
#endif
  *that = _VecFloatGetRotX(that, theta);
}

// Rotate right-hand 'that' by 'theta' radians around Y and 
// store the result in 'that'
#if BUILDMODE != 0
inline
#endif 
void _VecFloatRotY(VecFloat3D* that, float theta) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (VecGetDim(that) != 3) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'that' 's dimension is invalid (%d=3)",
      VecGetDim(that));
    PBErrCatch(PBMathErr);
  }
#endif
  *that = _VecFloatGetRotY(that, theta);
}

// Rotate right-hand 'that' by 'theta' radians around Z and 
// store the result in 'that'
#if BUILDMODE != 0
inline
#endif 
void _VecFloatRotZ(VecFloat3D* that, float theta) {
#if BUILDMODE == 0
  if (that == NULL) {
    PBMathErr->_type = PBErrTypeNullPointer;
    sprintf(PBMathErr->_msg, "'that' is null");
    PBErrCatch(PBMathErr);
  }
  if (VecGetDim(that) != 3) {
    PBMathErr->_type = PBErrTypeInvalidArg;
    sprintf(PBMathErr->_msg, "'that' 's dimension is invalid (%d=3)",
      VecGetDim(that));
    PBErrCatch(PBMathErr);
  }
#endif
  *that = _VecFloatGetRotZ(that, theta);
}

