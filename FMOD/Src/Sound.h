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

	std::list<FMOD::DSP*> DSPList;

	/// Estado actual de la reproducción
	SoundState currentState;

public:
	Sound(std::string name, FMOD_MODE mode = NULL, FMOD_CREATESOUNDEXINFO *exinfo = nullptr);
	virtual ~Sound();

	//Métodos de comprobación de estado
	bool IsPlaying();
	bool IsPaused();
	bool HasEnded();

	//Métodos de modificación de atributos
	void SetFrequency(float newFrequency);
	void SetMuted(bool muted);
	void SetLoopCount(int loopCount);
	void SetVolume(float volume);
	void SetPitch(float pitch);
	void AddDSP(FMOD::DSP *DSP);
	void SetPan(float pan);
	void SetMSPosition(int position);
	//TODO: SetMixLevelsOutput: diapo 18

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

	void FadeIn(float time, float volume);
	void FadeOut(float time, float volume);

	void TogglePaused();


protected:

	//Atributos

	/// <summary>
	/// Controla parámetros del canal
	/// </summary>
	FMOD::Channel* _channel;

	/// <summary>
	/// Unifica el tratamiento de los diferentes formatos de sonido
	/// </summary>
	FMOD::Sound* _sound;

	/// nombre del archivo de audio
	std::string _name;

	//Métodos
	float _frequency;


	/// <summary>
	/// Actualiza el estado actual del sonido
	/// </summary>
	virtual void CheckState();

	/// <summary>
	/// Controla el flujo de estados
	/// Además, si ha acabado un sonido, lo carga de nuevo
	/// </summary>
	virtual void Update();

	//Establece los atributos de nuevo al sonido cuando se vuelve a crear el canal
	void ResetChannel();

};
#endif // #ifndef __Sound_h_
