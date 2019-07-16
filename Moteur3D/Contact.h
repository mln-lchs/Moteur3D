#ifndef CONTACT_H
#define CONTACT_H

#include "Vecteur3D.h"

class Contact
{
	public:
		Contact();
		Contact(Vecteur3D contactPoint, Vecteur3D contactNormal, float penetration);
		virtual ~Contact();
		Vecteur3D getContactPoint();
		void setContactPoint(Vecteur3D contactPoint);
		Vecteur3D getContactNormal();
		void setContactNormal(Vecteur3D contactNormal);
		float getPenetration();
		void setPenetration(float penetration);
		//void addContacts

	private:
		Vecteur3D contactPoint;
		Vecteur3D contactNormal;
		float penetration;
};

#endif