#include "Sound.h"
#include "fmod_errors.h" // para manejo de errores


/// <summary>
/// Reproduce el sonido
/// </summary>
void Sound::Play()
{
	CheckState();
}

void Sound::CheckState() {

	switch (currentState) {
	case SoundState::READY:
		if (!IsPaused())
			currentState = SoundState.PLAYING;

		break;

	case SoundState::PLAYING:
		if (HasEnded())
			ResetChannel();
		else if (IsPaused())
			currentState = SoundState.PAUSED;

		break;
	case SoundState::PAUSED:
		if (HasEnded())
			ResetChannel();
		else if (!IsPaused())
			currentState = SoundState.PLAYING;

		break;
	}
}

/// <summary>
/// Devuelve si el sonido está pausado
/// </summary>
/// <returns></returns>
bool Sound::IsPaused()
{
	bool isPaused;
	LowLevelSystem::ERRCHECK(channel->getPaused(&isPaused));
	return isPaused;
}

/// <summary>
/// Devuelve si el sonido ha acabado
/// </summary>
/// <returns></returns>
bool Sound::HasEnded()
{
	bool playing;
	return channel->isPlaying(&playing) == FMOD_ERR_INVALID_HANDLE;
}

/// <summary>
/// Crea un nuevo canal con los parámetros del anterior
/// </summary>
void Sound::ResetChannel()
{
	//channel->clearHandle();
	channel = LowLevelSystem::GetInstance()->CreateChannel(sound);
	currentState = SoundState::READY;
	SetFrequency(frequency);

	int i = 0;

	//Se vuelven a añadir todos los efectos al canal
	for (auto it = DSPList.begin(); it != DSPList.end(); ++it)
	{
		LowLevelSystem::ERRCHECK(channel->addDSP(i, &(*it)));
		i++;
	}
}

/// <summary>
/// Establece la frecuencia del sonido
/// </summary>
/// <param name="newFrequency"></param>
void Sound::SetFrequency(float newFrequency)
{
	CheckState();
	frequency = newFrequency;
	LowLevelSystem::ERRCHECK(channel->setFrequency(frequency));
}

/// <summary>
/// Establece la panorámica del sound
/// </summary>
/// <param name="newFrequency"></param>
void Sound::SetPan(float pan) {
	LowLevelSystem::ERRCHECK(channel->setPan(pan));
}