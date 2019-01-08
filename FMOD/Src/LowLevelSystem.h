#ifndef __LowLevelSystem_h_
#define __LowLevelSystem_h_
#include <iostream>
#include "fmod.hpp"
#include "fmod_errors.h" // para manejo de errores

//Motor de audio que permite el posicionamiento 3D, geometría y reverbs
//Inicializa la librería.Se encarga de cargar y reproducir sonidos.
//Controla el Listener
class LowLevelSystem
{
#pragma region Singleton  
private:
	/* Here will be the instance stored. */
	static LowLevelSystem *instance;

public:
	/* Static access method. */
	static LowLevelSystem * GetInstance();
	static void ResetInstance();

#pragma endregion Singleton

private:
	FMOD::System *system; //Instancia de LowLevelSystem

	const char* AUDIOPATH = "../../Media/";	//Ruta donde se encuentran los archivos de audio de la escena

	//TODO: MASTER CHANNEL

public:
	LowLevelSystem();
	~LowLevelSystem();

	void SetListener(int listener, FMOD_VECTOR pos, FMOD_VECTOR vel, FMOD_VECTOR up, FMOD_VECTOR at);
	void SetNumListeners(int num);

	void Update();

	FMOD::Sound* Create2DSound(std::string name, FMOD_MODE mode = NULL, FMOD_CREATESOUNDEXINFO *exinfo = nullptr);
	FMOD::Sound* Create3DSound(std::string name, FMOD_MODE mode = NULL, FMOD_CREATESOUNDEXINFO *exinfo = nullptr);

	FMOD::Channel* CreateChannel(FMOD::Sound *sound, FMOD::ChannelGroup * channelGroup = nullptr);
	//TODO: CHANNEL GROUP

	FMOD::Reverb3D* CreateReverb();
	FMOD::Geometry* CreateGeometry(int maxPoligons, int maxVertex);
	FMOD::DSP* CreateDSPByType(FMOD_DSP_TYPE DSPType);

#pragma region SYSTEM_PARAMETERS

	//Devuelve la variación de frecuencia por la velocidad
	//1.0 = valor natural
	//0.0 = Lo anula
	//>1.0 => Exagera el fenómeno 
	float GetDopplerScale()
	{
		float dopplerScale, distanceFactor, rollOffScale;
		ERRCHECK(system->get3DSettings(&dopplerScale, &distanceFactor, &rollOffScale));
		return dopplerScale;
	}

	//Devuelve las dimensiones del escenario de cara al motor de sonido
	//1.0 = valor natural
	//0.0 = Lo anula
	//>1.0 => Exagera el fenómeno 
	float GetDistanceFactor()
	{
		float dopplerScale, distanceFactor, rollOffScale;
		ERRCHECK(system->get3DSettings(&dopplerScale, &distanceFactor, &rollOffScale));
		return distanceFactor;
	}

	//Devuelve la atenuación con la distancia
	//1.0 = valor natural
	//0.0 = Lo anula
	//>1.0 => Exagera el fenómeno 
	float GetRollOffScale()
	{
		float dopplerScale, distanceFactor, rollOffScale;
		ERRCHECK(system->get3DSettings(&dopplerScale, &distanceFactor, &rollOffScale));
		return rollOffScale;
	}

	//Establece la variación de frecuencia por la velocidad
	//1.0 = valor natural
	//0.0 = Lo anula
	//>1.0 => Exagera el fenómeno 
	void SetDopplerScale(float dopplerScale)
	{
		ERRCHECK(system->set3DSettings(dopplerScale, GetDistanceFactor(), GetRollOffScale()));
	}

	//Establece las dimensiones del escenario de cara al motor de sonido
	//1.0 = valor natural
	//0.0 = Lo anula
	//>1.0 => Exagera el fenómeno 
	void SetDistanceFactor(float distanceFactor)
	{
		ERRCHECK(system->set3DSettings(GetDopplerScale(), distanceFactor, GetRollOffScale()));
	}

	//Establece la atenuación con la distancia
	//1.0 = valor natural
	//0.0 = Lo anula
	//>1.0 => Exagera el fenómeno 
	void SetRollOffScale(float rollOffScale)
	{
		ERRCHECK(system->set3DSettings(GetDopplerScale(), GetDistanceFactor(), rollOffScale));
	}

#pragma endregion SYSTEM_PARAMETERS

	//Facilita la gestión de errores
	static void ERRCHECK(FMOD_RESULT result) {
		if (result != FMOD_OK) { //TODO: result != FMOD.RESULT.ERR_CHANNEL_STOLEN
			std::cout << FMOD_ErrorString(result) << std::endl;
			exit(-1);
		}
	}
};
#endif // #ifndef __LowLevelSystem_h_
