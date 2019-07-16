#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "Vecteur3D.h"
#include "RigidBody.h"
#include "Matrix4.h"

class Primitive
{
	public:
		Primitive();
		Primitive(RigidBody *body, Matrix4 offset);
		virtual ~Primitive();
		RigidBody* getBody();
		void setBody(RigidBody* body);
		Matrix4 getOffset();
		void setOffset(Matrix4 offset);
		
	private:
		RigidBody *body;
		Matrix4 offset;
};

#endif