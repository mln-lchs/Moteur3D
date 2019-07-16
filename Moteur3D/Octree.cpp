#include "pch.h"
#include "Octree.h"
#include <iostream>

/* Constructeur */
Octree::Octree()
{
	nbMax = 4;
	profondeurMax = 4;
	centre = Vecteur3D();
	isLeaf = true;
	this->liste = std::vector<Sphere*>();
}

/* Constructeur */
Octree::Octree(int nbMax, int profondeurMax, Vecteur3D centre, Vecteur3D ubounds, Vecteur3D lbounds)
{
	this->nbMax = nbMax;
	this->profondeurMax = profondeurMax;
	this->centre = centre;
	this->lbounds = lbounds;
	this->ubounds = ubounds;
	this->liste = std::vector<Sphere*>();
	isLeaf = true;
}

/* Destructeur */
Octree::~Octree()
{

}

/* Ajoute un élément dans l'octree */
 void Octree::addElement(Sphere* s)
{
	 // Si l'octree a atteint le nombre maximal d'éléments qu'il peut contenir, on le divise
	if (liste.size() > nbMax - 1 && isLeaf && profondeurMax > 0) {
		this->divide();
		isLeaf = false;
		this->addElement(s);
	}
	// Si l'octree n'est pas plein mais qu'il s'agit d'une feuille, on y ajoute l'élément
	else if (isLeaf) {
		liste.push_back(s);
	}
	// L'octree est déjà divisé, on cherche dans quelle partie placer l'élément
	else {
		bool left1 = s->getCenter().getX() - s->getRadius() < centre.getX();
		bool right1 = s->getCenter().getX() + s->getRadius() > centre.getX();
		bool left2 = s->getCenter().getY() - s->getRadius() < centre.getY();
		bool right2 = s->getCenter().getY() + s->getRadius() > centre.getY();
		bool down = s->getCenter().getZ() - s->getRadius() < centre.getZ();
		bool up = s->getCenter().getZ() + s->getRadius() > centre.getZ();
		if (left1 && left2 && down) {
			subTrees[0]->addElement(s);
		}
		if (right1 && left2 && down) {
			subTrees[1]->addElement(s);
		}
		if (left1 && right2 && down) {
			subTrees[2]->addElement(s);
		}
		if (right1 && right2 && down) {
			subTrees[3]->addElement(s);
		}
		if (left1 && left2 && up) {
			subTrees[4]->addElement(s);
		}
		if (right1 && left2 && up) {
			subTrees[5]->addElement(s);
		}
		if (left1 && right2 && up) {
			subTrees[6]->addElement(s);
		}
		if (right1 && right2 && up) {
			subTrees[7]->addElement(s);
		}
	}
}

 /* L'algorithme de l'octree adapté à la démonstration avec les plans de la boîte */
std::vector<int> Octree::collisionsForExample()
{
	divide();
	std::vector<int> planes;
	bool b1, b2, b3, b4, b5, b6;
	b1 = false;
	b2 = false;
	b3 = false;
	b4 = false;
	b5 = false;
	b6 = false;

	// Chaque sous-arbre correspond à l'un des huit coins de la boîte
	// Un élément situé dans un sous-arbre particulier peut entrer en collision
	// avec trois plans potentiels représentés par des booléens
	// S'il se trouve dans plusieurs sous-arbres simultanément, on fait l'union des plans
	if (!subTrees[0]->vide()) {
		b1 = true;
		b2 = true;
		b3 = true;
		
	}
	if (!subTrees[1]->vide()) {
		b4 = true;
		b2 = true;
		b3 = true;
		
	}
	if (!subTrees[2]->vide()) {
		b1 = true;
		b5 = true;
		b3 = true;
		
	}
	if (!subTrees[3]->vide()) {
		b4 = true;
		b5 = true;
		b3 = true;
		
	}
	if (!subTrees[4]->vide()) {
		b1 = true;
		b2 = true;
		b6 = true;
		
	}
	if (!subTrees[5]->vide()) {
		b4 = true;
		b2 = true;
		b6 = true;
		
	}
	if (!subTrees[6]->vide()) {
		b1 = true;
		b5 = true;
		b6 = true;
		
	}
	if (!subTrees[7]->vide()) {
		b4 = true;
		b5 = true;
		b6 = true;
	}

	// On ajoute à la liste *planes* les plans en éventuelle collision
	if (b1) {
		planes.push_back(0);
	}
	if (b2) {
		planes.push_back(1);
	}
	if (b3) {
		planes.push_back(2);
	}
	if (b4) {
		planes.push_back(3);
	}
	if (b5) {
		planes.push_back(4);
	}
	if (b6) {
		planes.push_back(5);
	}
	return planes;
}

/* Méthode qui subdivise l'octree en huit */
void Octree::divide()
{
	isLeaf = false;
	subTrees[0] = new Octree(nbMax, profondeurMax - 1, Vecteur3D((centre.getX() + lbounds.getX()) / 2, (centre.getY() + lbounds.getY()) / 2, (centre.getZ() + lbounds.getZ()) / 2), centre, lbounds);
	subTrees[1] = new Octree(nbMax, profondeurMax - 1, Vecteur3D((centre.getX() + ubounds.getX()) / 2, (centre.getY() + lbounds.getY()) / 2, (centre.getZ() + lbounds.getZ()) / 2), Vecteur3D(ubounds.getX(),centre.getY(),centre.getZ()), Vecteur3D(centre.getX(),lbounds.getY(),lbounds.getZ()));
	subTrees[2] = new Octree(nbMax, profondeurMax - 1, Vecteur3D((centre.getX() + lbounds.getX()) / 2, (centre.getY() + ubounds.getY()) / 2, (centre.getZ() + lbounds.getZ()) / 2), Vecteur3D(centre.getX(), ubounds.getY(), centre.getZ()), Vecteur3D(lbounds.getX(), centre.getY(), lbounds.getZ()));
	subTrees[3] = new Octree(nbMax, profondeurMax - 1, Vecteur3D((centre.getX() + ubounds.getX()) / 2, (centre.getY() + ubounds.getY()) / 2, (centre.getZ() + lbounds.getZ()) / 2), Vecteur3D(ubounds.getX(), ubounds.getY(), centre.getZ()), Vecteur3D(centre.getX(), centre.getY(), lbounds.getZ()));
	subTrees[4] = new Octree(nbMax, profondeurMax - 1, Vecteur3D((centre.getX() + lbounds.getX()) / 2, (centre.getY() + lbounds.getY()) / 2, (centre.getZ() + ubounds.getZ()) / 2), Vecteur3D(centre.getX(), centre.getY(), ubounds.getZ()), Vecteur3D(lbounds.getX(), lbounds.getY(), centre.getZ()));
	subTrees[5] = new Octree(nbMax, profondeurMax - 1, Vecteur3D((centre.getX() + ubounds.getX()) / 2, (centre.getY() + lbounds.getY()) / 2, (centre.getZ() + ubounds.getZ()) / 2), Vecteur3D(ubounds.getX(), centre.getY(), centre.getZ()), Vecteur3D(centre.getX(), lbounds.getY(), lbounds.getZ()));
	subTrees[6] = new Octree(nbMax, profondeurMax - 1, Vecteur3D((centre.getX() + lbounds.getX()) / 2, (centre.getY() + ubounds.getY()) / 2, (centre.getZ() + ubounds.getZ()) / 2), Vecteur3D(centre.getX(), ubounds.getY(), centre.getZ()), Vecteur3D(lbounds.getX(), centre.getY(), lbounds.getZ()));
	subTrees[7] = new Octree(nbMax, profondeurMax - 1, Vecteur3D((centre.getX() + ubounds.getX()) / 2, (centre.getY() + ubounds.getY()) / 2, (centre.getZ() + ubounds.getZ()) / 2), ubounds, centre);
	Sphere* s;
	while (!liste.empty()) {
		s = liste.back();
		liste.pop_back();
		addElement(s);
	}
}

/* Renvoie si l'octree est vide ou non */
bool Octree::vide()
{
	return liste.empty();
}


