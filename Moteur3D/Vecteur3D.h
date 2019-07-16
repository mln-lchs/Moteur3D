#ifndef VECTEUR3D_H
#define VECTEUR3D_H

#include "Matrix3.h"
#include "Matrix4.h"

class Matrix3;
class Matrix4;

class Vecteur3D 
{

	public:
		Vecteur3D();
		Vecteur3D(float x, float y, float z);
		virtual ~Vecteur3D();

		float getX();
		float getY();
		float getZ();
		void setX(float newX);
		void setY(float newY);
		void setZ(float newZ);
		void setCoordonnees(float newX, float newY, float newZ);

		void addition(Vecteur3D &vecteur);
		void addition(float x, float y, float z);
		Vecteur3D additionFun(Vecteur3D v);
		void soustraction(Vecteur3D &vecteur);
		Vecteur3D soustractionFun(Vecteur3D v);
		void multiplication(float k);
		Vecteur3D multiplicationFun(float k);
		void produitComposantes(Vecteur3D &vecteur);
		Vecteur3D produitComposantesFun(Vecteur3D v);
		float produitScalaire(Vecteur3D &vecteur);
		float norme();
		void normalize();
		Vecteur3D normalizeFun();
		float cosAngle(Vecteur3D &vecteur);
		float sinAngle(Vecteur3D &vecteur);

		Vecteur3D projection(Vecteur3D &vecteur);
		float distance(Vecteur3D vecteur);
		Vecteur3D produitVectoriel(Vecteur3D &vecteur);
		float produitMixte(Vecteur3D &vecteur1, Vecteur3D &vecteur2);
		Vecteur3D localToWorld(Matrix3 p);
		Vecteur3D worldToLocal(Matrix3 p);
		Vecteur3D localToWorld4(Matrix4 p);
		Vecteur3D worldToLocal4(Matrix4 p);

	private:
		float x, y, z;

};

#endif