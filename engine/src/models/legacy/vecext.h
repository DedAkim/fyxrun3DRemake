/*
	SORRY
	I'M SO LAZY

	vecext - костыль
*/

#pragma once
#include "../../defext.h"

#include <math.h>

/*
    -== VECTOR 2 ==-
*/

// Short aliases:
// pVec2 — preferred engine style
// vec2  — GLSL-like style
// pv2   — shorthand for compact code

#define pVec2 pgm_vector2
#define pv2 pgm_vector2

// Platform Graphics Math (PGM)
// Simple vector 3 structure
typedef struct pgm_vector32
{
	float x, y;
} pgm_vector2;

/*
    -== VECTOR 3 ==-
*/

// Short aliases:
// pVec3 — preferred engine style
// vec3  — GLSL-like style
// pv3   — shorthand for compact code

#define pVec3 pgm_vector3
#define pv3 pgm_vector3

// Platform Graphics Math (PGM)
// Simple vector 3 structure
typedef struct pgm_vector3
{
	float x, y, z;
} pgm_vector3;

// This thing normalize fucking vector
ENGINE_API pv3 pgmNormalizeVec3(pv3 v);

// SCALE UR FUCKING VECTOR
ENGINE_API pv3 pgmScaleVec3(pv3 v, float s);

// Ar u ok?
ENGINE_API pv3 pgmSubVec3(pv3 a, pv3 b);

// Ar u ok?
ENGINE_API pv3 pgmAddVec3(pv3 a, pv3 b);

// Good. Just cross.
ENGINE_API pv3 pgmCrossVec3(pv3 a, pv3 b);

// Fuck you.
ENGINE_API float pgmDotVec3(pv3 a, pv3 b);

/*
    -== VECTOR 4 ==-
*/

// Short aliases:
// pVec4 — preferred engine style
// vec4  — GLSL-like style
// pv4   — shorthand for compact code

#define pVec4 pgm_vector4
#define pv4 pgm_vector4

// Platform Graphics Math (PGM)
// Simple vector 4 structure
typedef struct pgm_vector4
{
	float x, y, z, w;
} pgm_vector4;