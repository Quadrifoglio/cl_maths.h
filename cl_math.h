/*
 * cl_math.h
 * Minimal C math utilities
 *
 * By quadrifoglio <quadrifoglio.clement@gmail.com>
 * Public Domain
 */

// --------------------------
// DECLARATION
// --------------------------

typedef struct {
	float x, y;

} v2;

typedef struct {
	float x, y, z;

} v3;

typedef struct {
	float r, g, b, a;

} c4;

typedef struct {
	float m11, m12, m13, m14;
	float m21, m22, m23, m24;
	float m31, m32, m33, m34;
	float m41, m42, m43, m44;
} cl_mat4;

v2 clV2Add(v2 v, v2 vv);
v2 clV2Multiplyf(v2 v, float k);

cl_mat4 clMat4Null();
cl_mat4 clMat4Identity();
cl_mat4 clMat4Multiply(cl_mat4* m1, cl_mat4* m2);

cl_mat4 clMat4OrthoProjection(float left, float right, float bot, float top, float zNear, float zFar);

cl_mat4 clMat4Translate2(v2 v);
cl_mat4 clMat4Translate3(v3 v);
cl_mat4 clMat4Scale2(v2 v);
cl_mat4 clMat4Scale3(v3 v);
cl_mat4 clMat4RotateX(float angle);
cl_mat4 clMat4RotateY(float angle);
cl_mat4 clMat4RotateZ(float angle);

void clMat4Print(cl_mat4* mat);


// --------------------------
// IMPLEMENTATION
// --------------------------

#ifdef CL_MATH_IMPLEMENTATION

#include <string.h>
#include <stdio.h>
#include <math.h>

v2 clV2Add(v2 v, v2 vv) {
	return (v2){v.x + vv.x, v.y + vv.y};
}

v2 clV2Multiplyf(v2 v, float k) {
	return (v2){v.x * k, v.y * k};
}

cl_mat4 clMat4Null() {
	cl_mat4 m;
	memset(&m, 0, sizeof(cl_mat4));

	return m;
}

cl_mat4 clMat4Identity() {
	cl_mat4 mat = clMat4Null();
	mat.m11 = 1.f;
	mat.m22 = 1.f;
	mat.m33 = 1.f;
	mat.m44 = 1.f;

	return mat;
}

cl_mat4 clMat4Multiply(cl_mat4* m1, cl_mat4* m2) {
	cl_mat4 res = clMat4Null();

	res.m11 = m1->m11 * m2->m11 + m1->m12 * m2->m21 + m1->m13 * m2->m31 + m1->m14 * m2->m41;
	res.m12 = m1->m11 * m2->m12 + m1->m12 * m2->m22 + m1->m13 * m2->m32 + m1->m14 * m2->m42;
	res.m13 = m1->m11 * m2->m13 + m1->m12 * m2->m23 + m1->m13 * m2->m33 + m1->m14 * m2->m43;
	res.m14 = m1->m11 * m2->m14 + m1->m12 * m2->m24 + m1->m13 * m2->m34 + m1->m14 * m2->m44;

	res.m21 = m1->m21 * m2->m11 + m1->m22 * m2->m21 + m1->m23 * m2->m31 + m1->m24 * m2->m41;
	res.m22 = m1->m21 * m2->m12 + m1->m22 * m2->m22 + m1->m23 * m2->m32 + m1->m24 * m2->m42;
	res.m23 = m1->m21 * m2->m13 + m1->m22 * m2->m23 + m1->m23 * m2->m33 + m1->m24 * m2->m43;
	res.m24 = m1->m21 * m2->m14 + m1->m22 * m2->m24 + m1->m23 * m2->m34 + m1->m24 * m2->m44;

	res.m31 = m1->m31 * m2->m11 + m1->m32 * m2->m21 + m1->m33 * m2->m31 + m1->m34 * m2->m41;
	res.m32 = m1->m31 * m2->m12 + m1->m32 * m2->m22 + m1->m33 * m2->m32 + m1->m34 * m2->m42;
	res.m33 = m1->m31 * m2->m13 + m1->m32 * m2->m23 + m1->m33 * m2->m33 + m1->m34 * m2->m43;
	res.m34 = m1->m31 * m2->m14 + m1->m32 * m2->m24 + m1->m33 * m2->m34 + m1->m34 * m2->m44;

	res.m41 = m1->m41 * m2->m11 + m1->m42 * m2->m21 + m1->m43 * m2->m31 + m1->m44 * m2->m41;
	res.m42 = m1->m41 * m2->m12 + m1->m42 * m2->m22 + m1->m43 * m2->m32 + m1->m44 * m2->m42;
	res.m43 = m1->m41 * m2->m13 + m1->m42 * m2->m23 + m1->m43 * m2->m33 + m1->m44 * m2->m43;
	res.m44 = m1->m41 * m2->m14 + m1->m42 * m2->m24 + m1->m43 * m2->m34 + m1->m44 * m2->m44;

	return res;
}

cl_mat4 clMat4OrthoProjection(float left, float right, float bot, float top, float zNear, float zFar) {
	cl_mat4 mat = clMat4Identity();

	mat.m11 = 2.f / (right - left);
	mat.m22 = 2.f / (top - bot);
	mat.m33 = -2.f / (zFar - zNear);
	mat.m14 = -(right + left) / (right - left);
	mat.m24 = -(top + bot) / (top - bot);
	mat.m34 = -(zFar + zNear) / (zFar - zNear);

	return mat;
}

cl_mat4 clMat4Translate2(v2 v) {
	cl_mat4 res = clMat4Identity();

	res.m14 = v.x;
	res.m24 = v.y;
	res.m34 = 0.f;
	res.m44 = 1.f;

	return res;
}

cl_mat4 clMat4Transalte3(v3 v) {
	cl_mat4 res = clMat4Identity();

	res.m14 = v.x;
	res.m24 = v.y;
	res.m34 = v.z;
	res.m44 = 1.f;

	return res;
}

cl_mat4 clMat4Scale2(v2 v) {
	cl_mat4 res = clMat4Null();

	res.m11 = v.x;
	res.m22 = v.y;
	res.m33 = 1.f;
	res.m44 = 1.f;

	return res;
}

cl_mat4 clMat4Scale3(v3 v) {
	cl_mat4 res = clMat4Null();

	res.m11 = v.x;
	res.m22 = v.y;
	res.m33 = v.z;
	res.m44 = 1.f;

	return res;
}

cl_mat4 clMat4RotateX(float angle) {
	cl_mat4 res = clMat4Identity();

	res.m22 = cos(angle);
	res.m23 = -sin(angle);
	res.m32 = sin(angle);
	res.m33 = cos(angle);

	return res;
}

cl_mat4 clMat4RotateY(float angle) {
	cl_mat4 res = clMat4Identity();

	res.m11 = cos(angle);
	res.m13 = sin(angle);
	res.m31 = -sin(angle);
	res.m33 = cos(angle);

	return res;
}

cl_mat4 clMat4RotateZ(float angle) {
	cl_mat4 res = clMat4Identity();

	res.m11 = cos(angle);
	res.m12 = -sin(angle);
	res.m21 = sin(angle);
	res.m22 = cos(angle);

	return res;
}

void clMat4Print(cl_mat4* mat) {
	printf("| %f %f %f %f |\n", mat->m11, mat->m12, mat->m13, mat->m14);
	printf("| %f %f %f %f |\n", mat->m21, mat->m22, mat->m23, mat->m24);
	printf("| %f %f %f %f |\n", mat->m31, mat->m32, mat->m33, mat->m34);
	printf("| %f %f %f %f |\n", mat->m41, mat->m42, mat->m43, mat->m44);
}

#endif
