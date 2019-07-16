#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vecteur3D.h"
#include "Quaternion.h"
#include "Matrix4.h"

class RigidBody
{
public:
	RigidBody();
	RigidBody(float inverseMass, float linearDamping,float angularDamping, Vecteur3D position, Vecteur3D velocity,
		Quaternion orientation, Vecteur3D rotation, Matrix3 inverseInertiaTensor);
	virtual ~RigidBody();
	float getMass();
	float getInverseMass();
	Matrix4 getTransformMatrix();
	void computeDerivedData();
	void addForceAtPoint(Vecteur3D force, Vecteur3D point);
	void addForceAtBodyPoint(Vecteur3D force, Vecteur3D point);
	void clearAccumulators();
	void integrate(float duration);
	Vecteur3D getPosition();


private:
	float inverseMass;
	float linearDamping;
	float angularDamping;
	Vecteur3D position;
	Vecteur3D velocity;
	Quaternion orientation;
	Vecteur3D rotation;
	Matrix4 transformMatrix;
	Matrix3 inverseInertiaTensor;
	Matrix3 inverseInertiaTensorUpdated;
	Vecteur3D forceAccum;
	Vecteur3D torqueAccum;
};

#endif