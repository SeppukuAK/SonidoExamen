#include "Sound3D.h"
#include "LowLevelSystem.h"

Sound3D::Sound3D(std::string name, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo) : Sound(name) {
	_sound = LowLevelSystem::GetInstance()->Create3DSound(_name, mode, exinfo);
	_channel = LowLevelSystem::GetInstance()->CreateChannel(_sound);

	LowLevelSystem::ERRCHECK(_channel->getFrequency(&_frequency)); //Inicializa el valor de frequency
	LowLevelSystem::ERRCHECK(_channel->get3DSpread(&_spread));
	LowLevelSystem::ERRCHECK(_channel->get3DAttributes(&_pos, nullptr));
	LowLevelSystem::ERRCHECK(_channel->get3DConeOrientation(&_dir));

	_lastPos = _pos;
}

Sound3D::~Sound3D() {} //Lla a la constructora padre para liberar el sonido

//Establece la posición del sonido
void Sound3D::SetPos(FMOD_VECTOR pos) {
	CheckState();
	_lastPos = _pos;
	_pos = pos;

	LowLevelSystem::ERRCHECK(_channel->set3DAttributes(&_pos, nullptr));
}

// Establece la Distancia a partir de la cual el sonido empieza a atenuarse
void Sound3D::SetMinDistance(float min) {
	CheckState();
	_minDistance = min;
	LowLevelSystem::ERRCHECK(_channel->set3DMinMaxDistance(_minDistance, _maxDistance));
}

//Establece la Distancia a partir de la cual el sonido no se atenúa más
void Sound3D::SetMaxDistance(float max) {
	CheckState();
	_maxDistance = max;
	LowLevelSystem::ERRCHECK(_channel->set3DMinMaxDistance(_minDistance, _maxDistance));
}

//Establece la dirección del cono
void Sound3D::SetConeOrientation(FMOD_VECTOR dir) {
	CheckState();
	_dir = dir;
	LowLevelSystem::ERRCHECK(_channel->set3DConeOrientation(&_dir));
}

// Establece el angulo del cono interior: donde no hay atenuación por dirección
void Sound3D::SetInsideConeAngle(float insideConeAngle) {
	CheckState();
	_insideConeAngle = insideConeAngle;
	LowLevelSystem::ERRCHECK(_channel->set3DConeSettings(_insideConeAngle, _outsideConeAngle, _outsideVolume));
}

// Establece el ángulo del cono exterior: donde el sonido se atenúa
void Sound3D::SetOutsideConeAngle(float outsideConeAngle) {
	CheckState();
	_outsideConeAngle = outsideConeAngle;
	LowLevelSystem::ERRCHECK(_channel->set3DConeSettings(_insideConeAngle, _outsideConeAngle, _outsideVolume));
}

//Establece el volumen fuera del cono exterior
void Sound3D::SetOutsideVolume(float outsideVolume) {
	CheckState();
	_outsideVolume = outsideVolume;
	LowLevelSystem::ERRCHECK(_channel->set3DConeSettings(_insideConeAngle, _outsideConeAngle, _outsideVolume));
}

//Establece el reverWet
void Sound3D::SetReverbWet(float reverbWet)
{
	CheckState();
	_reverbWet = reverbWet;
	LowLevelSystem::ERRCHECK(_channel->setReverbProperties(0, _reverbWet));
}

/*
	Posiciona en 3D un sonido estereo.
	Se separa en 2 voces mono. Controla su amplitud
	0º suena en mono.
	90º: canal izquierdo 45º, canal derecho 45º
	360º: sonido mono situado en la posición opuesta
*/
void Sound3D::Set3DSpread(float degrees)
{
	CheckState();
	_spread = degrees;
	LowLevelSystem::ERRCHECK(_channel->set3DSpread(_spread));
}

void Sound3D::ResetChannel() {
	Sound::ResetChannel();//Llamada al método de Sound
	SetPos(_pos);
	SetMinDistance(_minDistance);
	SetMaxDistance(_maxDistance);
	SetConeOrientation(_dir);
	SetInsideConeAngle(_insideConeAngle);
	SetOutsideConeAngle(_outsideConeAngle);
	SetOutsideVolume(_outsideVolume);
	SetReverbWet(_reverbWet);
	Set3DSpread(_spread);
}

//Calcula la velocidad del sonido
void Sound3D::Update(double elapsed) {
	Sound::Update(elapsed);

	FMOD_VECTOR vel;
	vel.x = (_pos.x - _lastPos.x) * elapsed;
	vel.y = (_pos.y - _lastPos.y) * elapsed;
	vel.z = (_pos.z - _lastPos.z) * elapsed;

	LowLevelSystem::ERRCHECK(_channel->set3DAttributes(&_pos, &vel));

}