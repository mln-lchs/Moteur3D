#ifndef OCTREE_H
#define OCTREE_H

#include "Vecteur3D.h"
#include <vector>
#include "Sphere.h"

class Octree {
public:
	Octree();
	Octree(int nbMax, int profondeurMax, Vecteur3D centre, Vecteur3D ubounds, Vecteur3D lbounds);
	virtual ~Octree();
	void addElement(Sphere* s);
	std::vector<int> collisionsForExample();
	bool vide();

private:
	void divide();
	int nbMax, profondeurMax;
	float length;
	bool isLeaf;
	Vecteur3D centre;
	std::vector<Sphere*> liste;
	Octree* subTrees[8];
	Vecteur3D ubounds, lbounds;

};

#endif
