#ifndef __Sound3D_h_
#define __Sound3D_h_
#include "Sound.h"
#include "fmod.hpp"

// Controla parámetros del canal de reproducción
// Tiene una posición en el espacio
class Sound3D : public Sound {
private:
	//Atributos del canal 3D
	FMOD_VECTOR _pos;
	FMOD_VECTOR _lastPos;
	FMOD_VECTOR _dir;

	float _minDistance = 1.0;
	float _maxDistance = 10000.0;

	float _insideConeAngle = 360.0;
	float _outsideConeAngle = 360.0;
	float _outsideVolume = 1.0;

	float _spread;
	float _reverbWet;

	void ResetChannel();
public:
	Sound3D(std::string _name, FMOD_MODE mode = NULL, FMOD_CREATESOUNDEXINFO *exinfo = nullptr);
	~Sound3D();

	void SetPos(FMOD_VECTOR pos);

	void SetMinDistance(float min);
	void SetMaxDistance(float max);

	void SetConeOrientation(FMOD_VECTOR dir);
	void SetInsideConeAngle(float insideConeAngle);
	void SetOutsideConeAngle(float outsideConeAngle);
	void SetOutsideVolume(float outsideVolume);

	void SetReverbWet(float reverbWet);
	void Set3DSpread(float degrees);

	virtual void Update(double elapsed = 0);
};
#endif // #ifndef __Sound3D_h_
