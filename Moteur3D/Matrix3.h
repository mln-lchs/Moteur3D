#ifndef MATRIX3_h
#define MATRIX3_h

#include "Vecteur3D.h"

class Vecteur3D;

class Matrix3
{
	public:
		Matrix3();
		Matrix3(Vecteur3D x, Vecteur3D y, Vecteur3D z);
		Matrix3(float a, float b, float c, float d, float e, float f, float g, float h, float i);
		virtual ~Matrix3();
		Vecteur3D multiplicationVect(Vecteur3D v);
		Matrix3 multiplicationMat(Matrix3 m);
		Matrix3 multiplicationScal(float k);
		Matrix3 inverse();
		Matrix3 transpose();
		float getA();
		float getB();
		float getC();
		float getD();
		float getE();
		float getF();
		float getG();
		float getH();
		float getI();

	private:
		float a,b,c,d,e,f,g,h,i;

};

#endif