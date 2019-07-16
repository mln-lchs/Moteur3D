#include "pch.h"
#include "Matrix4.h"

/* Constructeur */
Matrix4::Matrix4()
{
	this->a0 = 0;
	this->a1 = 0;
	this->a2 = 0;
	this->a3 = 0;
	this->a4 = 0;
	this->a5 = 0;
	this->a6 = 0;
	this->a7 = 0;
	this->a8 = 0;
	this->a9 = 0;
	this->a10 = 0;
	this->a11 = 0;
}

/* Constructeur */
Matrix4::Matrix4(float a0, float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8, float a9, float a10, float a11) {
	this->a0 = a0;
	this->a1 = a1;
	this->a2 = a2;
	this->a3 = a3;
	this->a4 = a4;
	this->a5 = a5;
	this->a6 = a6;
	this->a7 = a7;
	this->a8 = a8;
	this->a9 = a9;
	this->a10 = a10;
	this->a11 = a11;
}

/* Destructeur */
Matrix4::~Matrix4()
{

}

/* Multiplie la matrice avec un vecteur 3 */
Vecteur3D Matrix4::multiplicationVect(Vecteur3D v)
{
	return Vecteur3D(a0*v.getX() + a1*v.getY() + a2*v.getZ() + a3, a4*v.getX() + a5 * v.getY() + a6 * v.getZ() + a7, a8*v.getX() + a9 * v.getY() + a10 * v.getZ() + a11);
}

/* Multiplie la matrice 4 avec une autre matrice 4 */
Matrix4 Matrix4::multiplicationMat(Matrix4 mat)
{
	float b0 = a0 * mat.a0 + a1 * mat.a4 + a2 * mat.a8;
	float b1 = a0 * mat.a1 + a1 * mat.a5 + a2 * mat.a9;
	float b2 = a0 * mat.a2 + a1 * mat.a6 + a2 * mat.a10;
	float b3 = a0 * mat.a3 + a1 * mat.a7 + a2 * mat.a11 + a4;
	float b4 = a4 * mat.a0 + a5 * mat.a4 + a6 * mat.a8;
	float b5 = a4 * mat.a1 + a5 * mat.a5 + a6 * mat.a9;
	float b6 = a4 * mat.a2 + a5 * mat.a6 + a6 * mat.a10;
	float b7 = a4 * mat.a3 + a5 * mat.a7 + a6 * mat.a11 + a7;
	float b8 = a8 * mat.a0 + a9 * mat.a4 + a10 * mat.a8;
	float b9 = a8 * mat.a1 + a9 * mat.a5 + a10 * mat.a9;
	float b10 = a8 * mat.a2 + a9 * mat.a6 + a10 * mat.a10;
	float b11 = a8 * mat.a3 + a9 * mat.a7 + a10 * mat.a11;

	return Matrix4(b0,b1,b2,b3,b4,b5,b6,b7,b8,b9,b10,b11);
}

/* Calcule l'inverse de la matrice */
Matrix4 Matrix4::inverse()
{
	float b0 = -a9 * a6 + a5 * a10;
	float b1 = a9 * a2 - a1 * a10;
	float b2 = -a5 * a2 + a1 * a6;
	float b3 = a9 * a6*a3 - a5 * a10*a3 - a9 * a2*a7 + a1 * a10*a7 + a5 * a2*a11 - a1 * a6*a11;
	float b4 = a8 * a6 - a4 * a10;
	float b5 = -a8 * a2 + a0 * a10;
	float b6 = a4 * a2 - a0 * a6;
	float b7 = -a8 * a6*a3 + a4 * a10*a3 + a8 * a2*a7 - a0 * a10*a7 - a4 * a2*a11 + a0 * a6*a11;
	float b8 = -a8 * a5 + a4 * a9;
	float b9 = a8 * a1 - a0 * a9;
	float b10 = -a4 * a1 + a0 * a5;
	float b11 = a8 * a5*a3 - a4 * a9*a3 - a8 * a1*a7 + a0 * a9*a7 + a4 * a1*a11 - a0 * a5*a11;
	float b12 = 0;
	float b13 = 0;
	float b14 = 0;
	float b15 = 1;

	return Matrix4(b0, b1, b2, b3, b4, b5, b6, b7, b8, b9, b10, b11);
}

/* Affecte un quaternion à l'orientation */
void Matrix4::setOrientation(Quaternion q)
{
	float w = q.getR();
	float x = q.getI();
	float y = q.getJ();
	float z = q.getK();
	a0 = 1 - (2 * y*y + 2 * z*z);
	a1 = 2 * x*y + 2 * z*w;
	a2 = 2 * x*z - 2 * y*w;
	a3 = x;
	a4 = 2 * x*y - 2 * z*w;
	a5 = 1 - (2 * x*x + 2 * z*z);
	a6 = 2 * y*z + 2 * x*w;
	a7 = y;
	a8 = 2 * x*z + 2 * y*w;
	a9 = 2 * y*z - 2 * x*w;
	a10 = 1 - (2 * x*x + 2 * y*y);
	a11 = z;
}

/* Affecte un vecteur de translation */
void Matrix4::setTranslation(Vecteur3D v)
{
	a3 = v.getX();
	a7 = v.getY();
	a11 = v.getZ();
}

/* Extrait une matrice 3 de la matrice 4 */
Matrix3 Matrix4::extractMatrix3()
{
	return Matrix3(a0,a1,a2,a4,a5,a6,a8,a9,a10);
}


