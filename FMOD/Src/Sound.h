#ifndef __Sound_h_
#define __Sound_h_
#include <list>
#include "fmod.hpp"

//Controla par�metros del canal de reproducci�n
//Tiene una posici�n en el espacio
class Sound {
protected:
	enum SoundState { READY, PLAYING, PAUSED };		//Diferentes estados de reproducci�n

	FMOD::Sound* _sound; // Unifica el tratamiento de los diferentes formatos de sonido
	FMOD::Channel* _channel;	//Controlador de los par�metros del canal

	std::string _name; 	/// nombre del archivo de audio
	SoundState currentState;

	//Atributos del canal
	bool _mute = false;
	int _loopCount = 0;

	float _volume = 1.0f; //(0-1)
	float _pan = 0.0f; // (-1, +1)
	float _pitch = 1.0f; // (0-6)
	float _frequency;

	std::list<FMOD::DSP*> DSPList;

public:
	Sound(std::string name, FMOD_MODE mode = NULL, FMOD_CREATESOUNDEXINFO *exinfo = nullptr);
	virtual ~Sound();

	//Metodos de flujo
	void Play();
	void Stop();
	void Pause();
	void Resume();
	void TogglePaused();

	void Update();

	//M�todos de comprobaci�n de estado
	bool IsPlaying();
	bool IsPaused();
	bool HasEnded();

	//M�todos de modificaci�n de atributos
	void SetMuted(bool muted);
	void SetLoopCount(int loopCount);
	void SetVolume(float volume);
	void SetPan(float pan);
	void SetPitch(float pitch);
	void SetFrequency(float newFrequency);
	void AddDSP(FMOD::DSP *DSP);
	//TODO: SetMixLevelsOutput: diapo 18

	//Efectos sobre la reproducci�n del canal
	void SetMSPosition(int position);
	void Fade(float time, float volume);

protected:
	virtual void ResetChannel();

	void CheckState();
	
};
#endif // #ifndef __Sound_h_
