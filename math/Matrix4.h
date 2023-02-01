#pragma once
#include "Vector3.h"

struct Matrix4 {
	float m[4][4];
};

//単位行列
Matrix4 Matrix4Identity();

//スケーリング行列
Matrix4 Matrix4Scale(const Vector3& s);

//回転行列
Matrix4 Matrix4Rotation(const Vector3& r);
//回転行列X
Matrix4 Matrix4RotationX(float angle);
//回転行列Y
Matrix4 Matrix4RotationY(float angle);
//回転行列Z
Matrix4 Matrix4RotationZ(float angle);

//平行移動行列
Matrix4 Matrix4Translation(const Vector3& t);

//転置行列
Matrix4 Matrix4Transposed(const Matrix4& m);

//逆行列
Matrix4 Matrix4Inverse(const Matrix4& m);

//ベクトル変換
Vector3 Vector3Transform(const Vector3& v, const Matrix4& m);

Matrix4& operator*=(Matrix4& m1, const Matrix4& m2);

const Matrix4 operator* (const Matrix4& m1, const Matrix4& m2);
const Vector3 operator* (const Vector3& v, const Matrix4& m);