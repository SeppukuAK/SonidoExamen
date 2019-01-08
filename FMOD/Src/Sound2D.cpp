#include "Sound2D.h"
#include "LowLevelSystem.h"

Sound2D::Sound2D(std::string name, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo) : Sound(name) {
	_sound = LowLevelSystem::GetInstance()->Create2DSound(_name, mode, exinfo);
	_channel = LowLevelSystem::GetInstance()->CreateChannel(_sound);

	LowLevelSystem::ERRCHECK(_channel->getFrequency(&_frequency)); //Inicializa el valor de frequency
}

Sound2D::~Sound2D() {} //Lla a la constructora padre para liberar el sonido
