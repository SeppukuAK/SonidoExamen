#include "Sound3D.h"
#include "fmod_errors.h" // para manejo de errores
#include "LowLevelSystem.h"

Sound3D::Sound3D(std::string name, FMOD_MODE mode = NULL, FMOD_CREATESOUNDEXINFO *exinfo = nullptr) : Sound2D(name){

	LowLevelSystem::ERRCHECK(_channel->get3DSpread(&_spread));

	//Se inicializa la posicion a 0
	_pos = new FMOD_VECTOR();
	_pos->x = 0;
	_pos->y = 0;
	_pos->z = 0;

}

Sound3D::~Sound3D() {} //Lla a la constructora padre para liberar el sonido

void Sound3D::Init(FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo) {
	_sound = LowLevelSystem::GetInstance()->Create3DSound(_name, mode, exinfo);

}

void Sound3D::SetPos(FMOD_VECTOR* pos) {
	FMOD_VECTOR *vel = 0;

	CheckState();

	_pos->x = pos->x;
	_pos->y = pos->y;
	_pos->z = pos->z;

	LowLevelSystem::ERRCHECK(_channel->set3DAttributes(_pos, vel));
}


/// <summary>
/// Establece la Distancia a partir de la cual el sonido empieza a atenuarse
/// </summary>
/// <param name="minDistance"></param>
void Sound3D::SetMinDistance(int min) {
	CheckState();
	_minDistance = min;
	LowLevelSystem::ERRCHECK(_channel->set3DMinMaxDistance(_minDistance, _maxDistance));

}

/// <summary>
/// Establece la Distancia a partir de la cual el sonido no se atenúa más
/// </summary>
/// <param name="maxDistance"></param>
void Sound3D::SetMaxDistance(int max) {
	CheckState();
	_maxDistance = max;
	LowLevelSystem::ERRCHECK(_channel->set3DMinMaxDistance(_minDistance, _maxDistance));

}

/// <summary>
/// Establece el reverWet
/// </summary>
/// <param name="maxDistance"></param>
void Sound3D::SetReverbWet(float reverbWet)
{
	CheckState();
	_reverbWet = reverbWet;
	LowLevelSystem::ERRCHECK(_channel->setReverbProperties(0, _reverbWet));
}


/// <summary>
/// Establece el angulo del cono interior: donde no hay atenuación por dirección
/// </summary>
/// <param name="insideConeAngle"></param>
void Sound3D::SetInsideConeAngle(float insideConeAngle) {
	CheckState();
	_insideConeAngle = insideConeAngle;
	LowLevelSystem::ERRCHECK(_channel->set3DConeSettings(_insideConeAngle, _outsideConeAngle, _outsideVolume));

}


/// <summary>
/// Establece el ángulo del cono exterior: donde el sonido se atenúa
/// </summary>
/// <param name="insideConeAngle"></param>
void Sound3D::SetOutsideConeAngle(float outsideConeAngle) {
	CheckState();
	_outsideConeAngle = outsideConeAngle;
	LowLevelSystem::ERRCHECK(_channel->set3DConeSettings(_insideConeAngle, _outsideConeAngle, _outsideVolume));

}

/// <summary>
/// Establece el volumen fuera del cono exterior
/// </summary>
/// <param name="insideConeAngle"></param>
void Sound3D::SetOutsideVolume(float outsideVolume) {
	CheckState();
	_outsideVolume = outsideVolume;
	LowLevelSystem::ERRCHECK(_channel->set3DConeSettings(_insideConeAngle, _outsideConeAngle, _outsideVolume));

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
	Sound2D::ResetChannel();//Llamada al método de Sound
	SetPos(_pos);
	SetMinDistance(_minDistance);
	SetMaxDistance(_maxDistance);
	SetReverbWet(_reverbWet);
	SetInsideConeAngle(_insideConeAngle);
	SetOutsideConeAngle(_outsideConeAngle);
	SetOutsideVolume(_outsideVolume);

}