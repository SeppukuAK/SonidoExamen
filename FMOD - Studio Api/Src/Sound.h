#ifndef __Sound_h_
#define __Sound_h_
#include <list>
#include "fmod.hpp"
#include "LowLevelSystem.h"
#include "fmod_errors.h" // para manejo de errores

/// <summary>
/// Controla par�metros del canal de reproducci�n
/// Tiene una posici�n en el espacio
/// </summary>
class Sound {
private:
	enum SoundState { READY, PLAYING, PAUSED };

	//Atributos del canal
	bool mute = false;
	bool loop = false;

	float volume = 1.0; //(0-1)
	float pitch = 1.0; // (0-6)

	float pan;
	float frequency;

	std::list<FMOD::DSP> DSPList;


	/// <summary>
	/// Unifica el tratamiento de los diferentes formatos de sonido
	/// </summary>
	FMOD::Sound* sound;

	/// <summary>
	/// Controla par�metros del canal
	/// </summary>
	FMOD::Channel* channel;

	/// <summary>
	/// Estado actual de la reproducci�n
	/// </summary>
	SoundState currentState;

	std::string _name;

	void CheckState();

public:

	Sound(std::string name) {
		_name = name;
		currentState = SoundState::READY;
	}

	virtual ~Sound() {
		LowLevelSystem::ERRCHECK(sound->release());
	}

	void SetPan(float pan);

	bool IsPaused();
	bool HasEnded();
	void ResetChannel();
	void SetFrequency(float newFrequency);



	/// <summary>
	/// Reproduce el sonido
	/// </summary>
	void Play();

	/// <summary>
	/// Para el sonido si est� reproduciendose o pausado
	/// Se libera el canal 
	/// </summary>
	void Stop();

	/// <summary>
	/// Pausa el sonido si est� reproduciendose
	/// </summary>
	void Pause();

	/// <summary>
	/// Despausa el sonido si est� pausado
	/// </summary>
	void Resume();



};
#endif // #ifndef __Sound3D_h_
