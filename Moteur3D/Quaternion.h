#ifndef QUATERNION_H
#define QUATERNION_H

#include "Vecteur3D.h"

class Vecteur3D;

class Quaternion{
	public :
		Quaternion();
		Quaternion(float r, float i, float j, float k);
		Quaternion(Vecteur3D v);
		virtual ~Quaternion();
		float getR();
		float getI();
		float getJ();
		float getK();
		void normalize();
		void applyRotation(Vecteur3D v);
		Quaternion scalar(float s);
		Quaternion operator*(const Quaternion& q);
		Quaternion operator+(const Quaternion& q);
		void updateAngularVelocity(Vecteur3D v, float temps);
		void addVector(Vecteur3D v);
	
	
	private :
		float r, i, j, k;
	   
};

#endif
