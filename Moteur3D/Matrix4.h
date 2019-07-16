#ifndef MATRIX4_H
#define MATRIX4_H

#include "Vecteur3D.h"
#include "Quaternion.h"
#include "Matrix3.h"

class Vecteur3D;
class Quaternion;
class Matrix3;

class Matrix4 {
public :
	Matrix4();
	Matrix4(float a0, float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, float a10, float a11);
	virtual ~Matrix4();
	Vecteur3D multiplicationVect(Vecteur3D v);
	Matrix4 multiplicationMat(Matrix4 mat);
	Matrix4 inverse();
	void setOrientation(Quaternion q);
	void setTranslation(Vecteur3D v);
	Matrix3 extractMatrix3();

private :
	float a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11;

};


#endif
