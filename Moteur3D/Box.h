#ifndef BOX_H
#define BOX_H

#include "Primitive.h"
#include "Vecteur3D.h"

class Box :
	public Primitive
{
	public:
		Box();
		Box(Vecteur3D halfSizes, RigidBody *body, Matrix4 offset);
		virtual ~Box();
		Vecteur3D getHalfSizes();
		void setHalfSizes(Vecteur3D halfSizes);
		float getA();
		float getB();
		float getC();

	private:
		Vecteur3D halfSizes;
};

#endif