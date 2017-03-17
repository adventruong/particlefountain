#ifndef __PARTICLE_H__	//guard against cyclic dependancy
#define __PARTICLE_H__
#include <list>
struct particle{
	float px, py, pz;
	float dx, dy, dz;
	float rx, ry, rz;
	float age;
	int colour;
};

#endif
