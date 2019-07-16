#include "pch.h"
#include "Quaternion.h"
#include <math.h>

/* Constructeur */
Quaternion::Quaternion() {
	r = 0;
	i = 0;
	j = 0;
	k = 0;
}

/* Constructeur */
Quaternion::Quaternion(float r, float i, float j, float k)
{
	this->r = r;
	this->i = i;
	this->j = j;
	this->k = k;
}

/* Constructeur */
Quaternion::Quaternion(Vecteur3D v) {
	this->r = 0;
	this->i = v.getX();
	this->j = v.getY();
	this->k = v.getZ();
}

/* Destructeur */
Quaternion::~Quaternion()
{
}

/* Méthode qui normalise un quaternion */
void Quaternion::normalize()
{
	float d = r * r + i * i + j * j + k * k;
	if (d == 0) {
		r = 1;
		i = 0;
		j = 0;
		k = 0;
	}
	else {
		d = 1 / sqrt(d);
		r = d * r;
		i = d * i;
		j = d * j;
		k = d * k;
	}

}

/* Renvoie la première valeur du quaternion */
float Quaternion::getR() {
	return r;
}

/* Renvoie la deuxième valeur du quaternion */
float Quaternion::getI() {
	return i;
}

/* Renvoie la troisième valeur du quaternion */
float Quaternion::getJ() {
	return j;
}

/* Renvoie la quatrième valeur du quaternion */
float Quaternion::getK() {
	return k;
}

/* Définit un opérateur multiplicatif pour les quaternions */
Quaternion Quaternion::operator*(const Quaternion & q)
{
	float w = this->r * q.r - this->i * q.i - this->j * q.j - this->k * q.k;
	float x = this->r*q.i + q.r*this->i + this->j*q.k - this->k*q.j;
	float y = this->r*q.j + q.r*this->j + this->k * q.i - this->i*q.k;
	float z = this->r*q.k + q.r*this->k + this->i*q.j - this->j*q.i;
	return Quaternion(w, x, y, z);
}

/* Définit un opérateur additif pour les quaternions */
Quaternion Quaternion::operator+(const Quaternion & q)
{
	float w = this->r + q.r;
	float x = this->i + q.i;
	float y = this->j + q.j;
	float z = this->k + q.k;
	return Quaternion(w, x, y, z);
}

/* Applique une rotation au quaternion */
void Quaternion::applyRotation(Vecteur3D v) {
	Quaternion q = Quaternion(0, v.getX(), v.getY(), v.getZ());
	*this = (*this) * q;
}


/* Multiplie le quaternion par un scalaire */
Quaternion Quaternion::scalar(float s)
{
	return Quaternion(s*r, s*i, s*j, s*k);
}

/* Met à jour la vélocité angulaire */
void Quaternion::updateAngularVelocity(Vecteur3D v, float temps)
{
	*this = (*this) + (Quaternion(v)*(*this)).scalar(temps / 2);
}

/* Additionne le quaternion avec un vecteur 3 */
void Quaternion::addVector(Vecteur3D v)
{
	i += v.getX();
	j += v.getY();
	k += v.getZ();
}


