#ifndef __Sound3D_h_
#define __Sound3D_h_
#include "Sound.h"
#include "fmod.hpp"
#include "fmod_studio.h"

/// <summary>
/// Controla parámetros del canal de reproducción
/// Tiene una posición en el espacio
/// </summary>
class Sound3D : public Sound{

private:
	float _minDistance = 1.0;     //Distancia a partir de la cual el sonido empieza a atenuarse
	float _maxDistance = 10000.0; //Distancia a partir de la cual el sonido no se atenúa más

	float _insideConeAngle = 360.0;
	float _outsideConeAngle = 360.0;
	float _outsideVolume = 1.0;

	float _reverbWet;

	FMOD_VECTOR *_pos;

	void SetPos(FMOD_VECTOR *pos);

	void SetMinDistance(int min);
	void SetMaxDistance(int max);
	void SetReverbWet(float reverbWet);

	void SetInsideConeAngle(float insideConeAngle);
	void SetOutsideConeAngle(float outsideConeAngle);
	void SetOutsideVolume(float outsideVolume);
	void ResetChannel();

public:
	Sound3D(std::string _name);
	~Sound3D();

};
#endif // #ifndef __Sound3D_h_
