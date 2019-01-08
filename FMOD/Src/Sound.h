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
	bool _mute = false;
	int _loopCount = 0;

	float _volume = 1.0; //(0-1)
	float _pitch = 1.0; // (0-6)

	float _pan;
	float _frequency;

	std::list<FMOD::DSP*> DSPList;

	/// Estado actual de la reproducci�n
	SoundState currentState;

	/// nombre del archivo de audio
	std::string _name;

public:

	Sound(std::string name);
	virtual ~Sound();

	//M�todos de comprobaci�n de estado
	bool IsPlaying();
	bool IsPaused();
	bool HasEnded();

	//M�todos de modificaci�n de atributos
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




protected:

	//Atributos

	/// <summary>
	/// Controla par�metros del canal
	/// </summary>
	FMOD::Channel* channel;

	/// <summary>
	/// Unifica el tratamiento de los diferentes formatos de sonido
	/// </summary>
	FMOD::Sound* _sound;


	//M�todos

	/// <summary>
	/// Actualiza el estado actual del sonido
	/// </summary>
	virtual void CheckState();

	/// <summary>
	/// Controla el flujo de estados
	/// Adem�s, si ha acabado un sonido, lo carga de nuevo
	/// </summary>
	virtual void Update();

	//Establece los atributos de nuevo al sonido cuando se vuelve a crear el canal
	void ResetChannel();

};
#endif // #ifndef __Sound3D_h_
