#ifndef __Sound_h_
#define __Sound_h_
#include <list>
#include "fmod.hpp"
#include "LowLevelSystem.h"
#include "fmod_errors.h" // para manejo de errores

/// <summary>
/// Controla parámetros del canal de reproducción
/// Tiene una posición en el espacio
/// </summary>
class Sound {
private:
	enum SoundState { READY, PLAYING, PAUSED };

	//Atributos del canal
	bool _mute = false;
	int _loopCount = 0;

	float _volume = 1.0; //(0-1)
	float _pitch = 1.0; // (0-6)

	float _pan;
	float _frequency;

	std::list<FMOD::DSP*> DSPList;


	/// <summary>
	/// Unifica el tratamiento de los diferentes formatos de sonido
	/// </summary>
	FMOD::Sound* sound;

	/// <summary>
	/// Controla parámetros del canal
	/// </summary>
	FMOD::Channel* channel;

	/// <summary>
	/// Estado actual de la reproducción
	/// </summary>
	SoundState currentState;

	std::string _name;

	void CheckState();

public:

	Sound(std::string name);
	virtual ~Sound();


	bool IsPaused();
	bool HasEnded();
	void ResetChannel();
	void SetFrequency(float newFrequency);
	void SetMuted(bool muted);
	void SetLoopCount(int loopCount);
	void SetVolume(float volume);
	void SetPitch(float pitch);
	void AddDSP(FMOD::DSP *DSP);
	void SetPan(float pan);
	void SetMSPosition(int position);


	/// <summary>
	/// Reproduce el sonido
	/// </summary>
	void Play();

	/// <summary>
	/// Para el sonido si está reproduciendose o pausado
	/// Se libera el canal 
	/// </summary>
	void Stop();

	/// <summary>
	/// Pausa el sonido si está reproduciendose
	/// </summary>
	void Pause();

	/// <summary>
	/// Despausa el sonido si está pausado
	/// </summary>
	void Resume();




protected:
	virtual void InitAttributes();

	/// <summary>
	/// Controla el flujo de estados
	/// Además, si ha acabado un sonido, lo carga de nuevo
	/// </summary>
	virtual void Update();

};
#endif // #ifndef __Sound3D_h_
