#include "pch.h"
#include "RigidBody.h"
#include <math.h>


/* Constructeur */
RigidBody::RigidBody()
{
	inverseMass = 0;
	linearDamping = 0;
	position = Vecteur3D();
	velocity = Vecteur3D();
	orientation = Quaternion();
	rotation = Vecteur3D();
	transformMatrix = Matrix4();
	inverseInertiaTensor = Matrix3();
	forceAccum = Vecteur3D();
	torqueAccum = Vecteur3D();
}

/* Constructeur */
RigidBody::RigidBody(float inverseMass, float linearDamping, float angularDamping, Vecteur3D position, Vecteur3D velocity, Quaternion orientation, Vecteur3D rotation, Matrix3 inverseInertiaTensor)
{
	this->inverseMass = inverseMass;
	this->linearDamping = linearDamping;
	this->angularDamping = angularDamping;
	this->position = position;
	this->velocity = velocity;
	this->orientation = orientation;
	this->rotation = rotation;
	this->transformMatrix = Matrix4();
	this->inverseInertiaTensor = inverseInertiaTensor;
	computeDerivedData();
}

/* Destructeur */
RigidBody::~RigidBody()
{
}


/* Renvoie la masse du corps rigide */
float RigidBody::getMass()
{
	return 1.0f/inverseMass;
}

/* Renvoie l'inverse de la masse du corps rigide */
float RigidBody::getInverseMass()
{
	return inverseMass;
}

/* Renvoie la matrice de transformation */
Matrix4 RigidBody::getTransformMatrix()
{
	return transformMatrix;
}

/* Calcule l'inverse du nouveau tenseur d'inertie */
void RigidBody::computeDerivedData() {
	transformMatrix = Matrix4();
	transformMatrix.setOrientation(orientation);
	transformMatrix.setTranslation(position);
	Matrix3 transformMatrix3 = transformMatrix.extractMatrix3();
	inverseInertiaTensorUpdated = transformMatrix3.multiplicationMat(inverseInertiaTensor.multiplicationMat(transformMatrix3.inverse()));
}

/* Vide les accumulateurs de forces et de torques */
void RigidBody::clearAccumulators()
{
	forceAccum.setCoordonnees(0, 0, 0);
	torqueAccum.setCoordonnees(0, 0, 0);
}

/* Ajoute une force à un point dans le repère du monde */
void RigidBody::addForceAtPoint(Vecteur3D force, Vecteur3D point)
{
	forceAccum.addition(force);
	Vecteur3D torque = position.soustractionFun(point).produitVectoriel(force);
	torqueAccum.addition(torque);
}

/* Ajoute une force à un point dans le repère du corps */
void RigidBody::addForceAtBodyPoint(Vecteur3D force, Vecteur3D point)
{
	Vecteur3D newPoint = transformMatrix.inverse().multiplicationVect(point);
	addForceAtPoint(force, newPoint);
}

/* Cette méthode met à jour les vélocités, la position et l'orientation à partir des accélérations */
void RigidBody::integrate(float duration)
{
	// Computing acceleration and angular acceleration
	Vecteur3D acceleration = forceAccum.multiplicationFun(inverseMass);
	Vecteur3D angularAcceleration = inverseInertiaTensorUpdated.multiplicationVect(torqueAccum);

	// Updating velocity
	acceleration.multiplication(duration);
	velocity.multiplication(pow(linearDamping,duration));
	velocity.addition(acceleration);

	// Updating rotation
	angularAcceleration.multiplication(duration);
	rotation.multiplication(pow(angularDamping, duration));
	rotation.addition(angularAcceleration);

	// Updating position
	Vecteur3D aux = velocity.multiplicationFun(duration);
	position.addition(aux);

	// Updating orientation
	orientation.updateAngularVelocity(rotation, duration);
	orientation.normalize();
	
	// Computing transformation matrix and inertia tensor
	computeDerivedData();

	// Clearing accumulators
	clearAccumulators();
}


/* Renvoie la position du corps rigide */
Vecteur3D RigidBody::getPosition()
{
	return position;
}


