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


/// <summary>
/// Creación del LowLevelSystem
/// </summary>
LowLevelSystem::LowLevelSystem()
{
	// Creamos el objeto system
	ERRCHECK(System_Create(&system));

	// 128 canales (numero maximo que podremos utilizar simultaneamente)
	ERRCHECK(system->init(128, FMOD_INIT_NORMAL, 0));	// Inicializacion de FMOD

	//TODO: CHANNEL GROUP
}

LowLevelSystem::~LowLevelSystem()
{
	//Cierra el sistema
	ERRCHECK(system->release());
}

/// <summary>
/// Update del system. 
/// </summary>
void LowLevelSystem::Update()
{
	ERRCHECK(system->update());
}

// <summary>
/// Crea un sonido 2D
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
Sound* LowLevelSystem::Create2DSound(string name)
{
	Sound * sound = nullptr;

	char aux[100];//TODO: 100?
	strcpy_s(aux, AUDIOPATH); // copy string one into the result.
	strcat_s(aux, sizeof aux, name.c_str());

	ERRCHECK(system->createSound(aux, FMOD_2D | FMOD_LOOP_NORMAL, 0, &sound));

	return sound;
}

/// <summary>
/// Crea un sonido 3D
/// </summary>
/// <param name="name"></param>
/// <returns></returns>
Sound* LowLevelSystem::Create3DSound(string name)
{
	Sound * sound = nullptr;

	char aux[100];
	strcpy_s(aux, AUDIOPATH); // copy string one into the result.
	strcat_s(aux, sizeof aux, name.c_str());

	ERRCHECK(system->createSound(aux, FMOD_3D | FMOD_LOOP_NORMAL, 0, &sound));

	return sound;
}


/// <summary>
   /// Crea un canal asociado al sonido
   /// Arranca en pause para dejarlo disponible en memoria
   /// </summary>
   /// <param name="sound"></param>
   /// <returns></returns>
Channel* LowLevelSystem::CreateChannel(Sound *sound)
{
	Channel *channel = nullptr;

	//Se crea el canal
	ERRCHECK(system->playSound(
		sound,
		0, // grupo de canales, 0 sin agrupar (agrupado en el master)
		true, // arranca con "pause" 
		&channel));

	ERRCHECK(channel->setLoopCount(0));

	return channel;
}

//
///// <summary>
///// Crea un grupo de canales con un nombre
///// TODO:
///// </summary>
///// <param name="name"></param>
///// <returns></returns>
//ChannelGroup LowLevelSystem::CreateChannelGroup(string name)
//{
//	FMOD.ChannelGroup channelGroup;
//	ERRCHECK(system.createChannelGroup(name, out channelGroup));
//	return channelGroup;
//} 

/// <summary>
/// Crea una reverb
/// </summary>
/// <returns></returns>
Reverb3D* LowLevelSystem::CreateReverb()
{
	Reverb3D* reverb;
	ERRCHECK(system->createReverb3D(&reverb));
	return reverb;
}

/// <summary>
/// Crea geometria
/// </summary>
/// <param name="maxPoligons"></param>
/// <param name="maxVertex"></param>
/// <returns></returns>
Geometry* LowLevelSystem::CreateGeometry(int maxPoligons, int maxVertex)
{
	Geometry* geometry;
	ERRCHECK(system->createGeometry(maxPoligons, maxVertex, &geometry));
	return geometry;
}
/// <summary>
/// Crea un DSP
/// </summary>
/// <param name="DSPType"></param>
/// <returns></returns>
DSP* LowLevelSystem::CreateDSPByType(FMOD_DSP_TYPE DSPType)
{
	DSP *dsp;
	ERRCHECK(system->createDSPByType(DSPType, &dsp));
	return dsp;
}

