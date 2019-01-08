#ifndef __LowLevelSystem_h_
#define __LowLevelSystem_h_
#include "fmod.hpp"
#include <iostream>
#include "fmod_errors.h" // para manejo de errores

/// <summary>
/// Motor de audio que permite el posicionamiento 3D, geometría y reverbs
/// Inicializa la librería. Se encarga de cargar y reproducir sonidos.
/// </summary>
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
	/// <summary>
	/// Instancia de LowLevelSystem
	/// </summary>
	FMOD::System *system;

	/// <summary>
	/// Ruta donde se encuentran los archivos de audio de la escena
	/// </summary>
	const char* AUDIOPATH = "../../Media/";

	//TODO: MASTER CHANNEL

public:

	LowLevelSystem();
	~LowLevelSystem();

	/// <summary>
	/// Update del system. 
	/// </summary>
	void Update();

	FMOD::Sound* Create2DSound(std::string name);
	FMOD::Sound* Create3DSound(std::string name);

	FMOD::Channel* CreateChannel(FMOD::Sound *sound);
	//TODO: CHANNEL GROUP
	FMOD::Reverb3D* CreateReverb();
	FMOD::Geometry* CreateGeometry(int maxPoligons, int maxVertex);
	FMOD::DSP* CreateDSPByType(FMOD_DSP_TYPE DSPType);

#pragma region SYSTEM_PARAMETERS
	/// <summary>
	/// Devuelve la variación de frecuencia por la velocidad
	/// 1.0 = valor natural
	/// 0.0 = Lo anula
	/// >1.0 => Exagera el fenómeno 
	/// </summary>
	/// <returns></returns>
	float GetDopplerScale()
	{
		float dopplerScale, distanceFactor, rollOffScale;
		ERRCHECK(system->get3DSettings(&dopplerScale, &distanceFactor, &rollOffScale));
		return dopplerScale;
	}

	/// <summary>
	/// Devuelve las dimensiones del escenario de cara al motor de sonido
	/// 1.0 = valor natural
	/// 0.0 = Lo anula
	/// >1.0 => Exagera el fenómeno 
	/// </summary>
	/// <returns></returns>
	float GetDistanceFactor()
	{
		float dopplerScale, distanceFactor, rollOffScale;
		ERRCHECK(system->get3DSettings(&dopplerScale, &distanceFactor, &rollOffScale));
		return distanceFactor;
	}

	/// <summary>
	/// Devuelve la atenuación con la distancia
	/// 1.0 = valor natural
	/// 0.0 = Lo anula
	/// >1.0 => Exagera el fenómeno 
	/// </summary>
	/// <returns></returns>
	float GetRollOffScale()
	{
		float dopplerScale, distanceFactor, rollOffScale;
		ERRCHECK(system->get3DSettings(&dopplerScale, &distanceFactor, &rollOffScale));
		return rollOffScale;
	}

	/// <summary>
	/// Establece la variación de frecuencia por la velocidad
	/// </summary>
	/// <param name="dopplerScale">   
	/// 1.0 = valor natural
	/// 0.0 = Lo anula
	/// >1.0 => Exagera el fenómeno 
	/// </param>
	void SetDopplerScale(float dopplerScale)
	{
		ERRCHECK(system->set3DSettings(dopplerScale, GetDistanceFactor(), GetRollOffScale()));
	}

	/// <summary>
	/// Establece las dimensiones del escenario de cara al motor de sonido
	/// </summary>
	/// <param name="rollOffScale">   
	/// 1.0 = valor natural
	/// 0.0 = Lo anula
	/// >1.0 => Exagera el fenómeno 
	/// </param>
	void SetDistanceFactor(float distanceFactor)
	{
		ERRCHECK(system->set3DSettings(GetDopplerScale(), distanceFactor, GetRollOffScale()));
	}

	/// <summary>
	/// Establece la atenuación con la distancia
	/// </summary>
	/// <param name="rollOffScale">   
	/// 1.0 = valor natural
	/// 0.0 = Lo anula
	/// >1.0 => Exagera el fenómeno 
	/// </param>
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
