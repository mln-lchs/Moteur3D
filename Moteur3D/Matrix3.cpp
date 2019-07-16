#include "pch.h"
#include "Matrix3.h"


/* Constructeur */
Matrix3::Matrix3() {
	this->a = 0;
	this->b = 0;
	this->c = 0;
	this->d = 0;
	this->e = 0;
	this->f = 0;
	this->g = 0;
	this->h = 0;
	this->i = 0;
}

/* Constructeur */
Matrix3::Matrix3(Vecteur3D x, Vecteur3D y, Vecteur3D z) {
	this->a = x.getX();
	this->b = x.getY();
	this->c = x.getZ();
	this->d = y.getX();
	this->e = y.getY();
	this->f = y.getZ();
	this->g = z.getX();
	this->h = z.getY();
	this->i = z.getZ();
}

/* Constructeur */
Matrix3::Matrix3(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;
	this->e = e;
	this->f = f;
	this->g = g;
	this->h = h;
	this->i = i;
}

/* Destructeur */
Matrix3::~Matrix3()
{
}

/* Multiplie la matrice 3 par un vecteur 3 */
Vecteur3D Matrix3::multiplicationVect(Vecteur3D v) {
	Vecteur3D res;
	float x = v.getX();
	float y = v.getY();
	float z = v.getZ();
	res.setX(a * x + b * y + c * z);
	res.setY(d * x + e * y + f * z);
	res.setZ(g * x + h * y + i * z);
	return res;
}

/* Multiplie matriciellement deux matrices 3 */
Matrix3 Matrix3::multiplicationMat(Matrix3 m) {
	float ares, bres, cres, dres, eres, fres, gres, hres, ires;
	ares = a * m.a + b * m.d + c * m.g;
	bres = a * m.b + b * m.e + c * m.h;
	cres = a * m.c + b * m.f + c * m.i;
	dres = d * m.a + e * m.d + f * m.g;
	eres = d * m.b + e * m.e + f * m.h;
	fres = d * m.c + e * m.f + f * m.i;
	gres = g * m.a + h * m.d + i * m.g;
	hres = g * m.b + h * m.e + i * m.h;
	ires = g * m.c + h * m.f + i * m.i;
	return Matrix3(ares, bres, cres, dres, eres, fres, gres, hres, ires);
}

/* Multiplie la matrice par un scalaire */
Matrix3 Matrix3::multiplicationScal(float k) {
	Matrix3 res;
	res.a = k * a;
	res.b = k * b;
	res.c = k * c;
	res.d = k * d;
	res.e = k * e;
	res.f = k * f;
	res.g = k * g;
	res.h = k * h;
	res.i = k * i;
	return res;
}


/* Calcule l'inverse de la matrice */
Matrix3 Matrix3::inverse() {
	float det;
	Matrix3 inv;
	det = a * e*i + d * h*c + g * h*f - a * h*f - g * e*c - d * b*i;
	inv.a = (e * i - f * h) / det;
	inv.b = (c * h - b * i) / det;
	inv.c = (b * f - c * e) / det;
	inv.d = (f * g - d * i) / det;
	inv.e = (a * i - c * g) / det;
	inv.f = (c * d - a * f) / det;
	inv.g = (d * h - e * g) / det;
	inv.h = (b * g - a * h) / det;
	inv.i = (a * e - b * d) / det;
	return inv;
}


/* Calcule la transposée de la matrice */
Matrix3 Matrix3::transpose() {
	Matrix3 tp;
	tp.a = a;
	tp.b = d;
	tp.c = g;
	tp.d = b;
	tp.e = e;
	tp.f = h;
	tp.g = c;
	tp.h = f;
	tp.i = i;
	return tp;
}


/* Ensemble de getters pour les éléments de la matrice */
float Matrix3::getA()
{
	return a;
}

float Matrix3::getB()
{
	return b;
}

float Matrix3::getC()
{
	return c;
}

float Matrix3::getD()
{
	return d;
}

float Matrix3::getE()
{
	return e;
}

float Matrix3::getF()
{
	return f;
}

float Matrix3::getG()
{
	return g;
}

float Matrix3::getH()
{
	return h;
}

float Matrix3::getI()
{
	return i;
}

