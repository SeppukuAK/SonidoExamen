#include "LowLevelSystem.h"

using namespace std;
using namespace FMOD;

#pragma region Singleton  

/* Null, because instance will be initialized on demand. */
LowLevelSystem* LowLevelSystem::instance = 0;

LowLevelSystem* LowLevelSystem::GetInstance()
{
	if (instance == 0)
		instance = new LowLevelSystem();

	return instance;
}

void LowLevelSystem::ResetInstance() {
	delete instance;
	instance = nullptr;
}

#pragma endregion Singleton


// Creación del LowLevelSystem
LowLevelSystem::LowLevelSystem()
{
	// Creamos el objeto system
	ERRCHECK(System_Create(&system));

	// 128 canales (numero maximo que podremos utilizar simultaneamente)
	ERRCHECK(system->init(128, FMOD_INIT_NORMAL, 0));	// Inicializacion de FMOD

	//TODO: CHANNEL GROUP
}

//Destruye el LowLevelSystem
LowLevelSystem::~LowLevelSystem()
{
	//Cierra el sistema
	ERRCHECK(system->release());
}

//listener que se modifica. 0 el por defecto
void LowLevelSystem::SetListener(int listener, FMOD_VECTOR pos, FMOD_VECTOR vel, FMOD_VECTOR up, FMOD_VECTOR at)
{
	ERRCHECK(system->set3DListenerAttributes(0, &pos, &vel, &up, &at));
}

//Establece el número de listeners
void LowLevelSystem::SetNumListeners(int num)
{
	ERRCHECK(system->set3DNumListeners(num));
}

//Update del system. 
void LowLevelSystem::Update()
{
	ERRCHECK(system->update());
}

//Crea un sonido 2D
//Se le puede pasar información adicional
Sound* LowLevelSystem::Create2DSound(string name, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo)
{
	Sound * sound = nullptr;

	char aux[100];
	strcpy_s(aux, AUDIOPATH); // copy string one into the result.
	strcat_s(aux, sizeof aux, name.c_str());

	ERRCHECK(system->createSound(aux, FMOD_2D | FMOD_LOOP_NORMAL | mode, exinfo, &sound));

	return sound;
}

//Crea un sonido 3D
//Se le puede pasar información adicional
Sound* LowLevelSystem::Create3DSound(string name, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo)
{
	Sound * sound = nullptr;

	//TODO: REVISAR
	//const char * a = AUDIOPATH + *name;
	char aux[100];
	strcpy_s(aux, AUDIOPATH); // copy string one into the result.
	strcat_s(aux, sizeof aux, name.c_str());

	ERRCHECK(system->createSound(aux, FMOD_3D | FMOD_LOOP_NORMAL | mode, exinfo, &sound));

	return sound;
}

//Crea un canal asociado al sonido
//Arranca en pause para dejarlo disponible en memoria
Channel* LowLevelSystem::CreateChannel(Sound *sound, ChannelGroup * channelGroup)
{
	Channel *channel = nullptr;

	//Se crea el canal
	ERRCHECK(system->playSound(
		sound,
		channelGroup, // grupo de canales, 0 sin agrupar (agrupado en el master)
		true, // arranca con "pause" 
		&channel));

	ERRCHECK(channel->setLoopCount(0));

	return channel;
}

//Crea un grupo de canales con un nombre
//TODO:
//ChannelGroup LowLevelSystem::CreateChannelGroup(string name)
//{
//	FMOD.ChannelGroup channelGroup;
//	ERRCHECK(system.createChannelGroup(name, out channelGroup));
//	return channelGroup;
//} 

//Crea una reverb

Reverb3D* LowLevelSystem::CreateReverb()
{
	Reverb3D* reverb;
	ERRCHECK(system->createReverb3D(&reverb));
	return reverb;
}

//Crea geometria
Geometry* LowLevelSystem::CreateGeometry(int maxPoligons, int maxVertex)
{
	Geometry* geometry;
	ERRCHECK(system->createGeometry(maxPoligons, maxVertex, &geometry));
	return geometry;
}

//Crea un DSP
DSP* LowLevelSystem::CreateDSPByType(FMOD_DSP_TYPE DSPType)
{
	DSP *dsp;
	ERRCHECK(system->createDSPByType(DSPType, &dsp));
	return dsp;
}

