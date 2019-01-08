#ifndef __AudioGeometry_h_
#define __AudioGeometry_h_
#include "fmod.hpp"

//Simulaci�n de recintos ac�sticos con obstrucci�n, oclusi�n, etc.
class AudioGeometry
{
private:
	FMOD::Geometry * geometry;

public:
	AudioGeometry(int maxPoligons, int maxVertex, float directOcclusion, float reverbOcclusion, bool doubleSided, FMOD_VECTOR poligons[]);
	~AudioGeometry();
};
#endif // #ifndef __AudioGeometry_h_

