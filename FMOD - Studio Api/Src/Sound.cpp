#include "Sound.h"
#include "fmod_errors.h" // para manejo de errores



Sound::Sound(std::string name) {
	_name = name;
	currentState = SoundState::READY;

	//?????
	LowLevelSystem::ERRCHECK(channel->getFrequency(&_frequency)); //Inicializa el valor de frequency

}

Sound::~Sound() {
	LowLevelSystem::ERRCHECK(_sound->release());
}



/// <summary>
/// Reproduce el sonido
/// </summary>
void Sound::Play()
{
	CheckState();

	if (currentState == SoundState::PLAYING)
		SetMSPosition(0);

	else //PAUSE O READY
		LowLevelSystem::ERRCHECK(channel->setPaused(false));

}
#pragma region Flow
/// <summary>
/// Para el sonido si está reproduciendose o pausado
/// Se libera el canal 
/// </summary>
void Sound::Stop()
{
	CheckState();

	if (currentState != SoundState::READY)
		LowLevelSystem::ERRCHECK(channel->stop());
}


/// <summary>
/// Pausa el sonido si está reproduciendose
/// </summary>
void Sound::Pause()
{
	CheckState();

	if (currentState == SoundState::PLAYING)
		LowLevelSystem::ERRCHECK(channel->setPaused(true));
}

/// <summary>
/// Despausa el sonido si está pausado
/// </summary>
void Sound::Resume()
{
	CheckState();

	if (currentState == SoundState::PAUSED)
		LowLevelSystem::ERRCHECK(channel->setPaused(false));
}
#pragma endregion


/// <summary>
/// Actualiza el estado actual del sonido
/// </summary>
void Sound::CheckState() {

	switch (currentState) {
	case SoundState::READY:
		if (!IsPaused())
			currentState = SoundState::PLAYING;

		break;

	case SoundState::PLAYING:
		if (HasEnded())
			ResetChannel();
		else if (IsPaused())
			currentState = SoundState::PAUSED;

		break;
	case SoundState::PAUSED:
		if (HasEnded())
			ResetChannel();
		else if (!IsPaused())
			currentState = SoundState::PLAYING;

		break;
	}
}

#pragma region CheckStateMethods
/// <summary>
/// Devuelve si el sonido está reproduciendose
/// </summary>
/// <returns></returns>
bool Sound::IsPlaying()
{
	bool isPlaying;
	LowLevelSystem::ERRCHECK(channel->getPaused(&isPlaying));
	return isPlaying;
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
#pragma endregion  CheckStateMethods


#pragma region SetAtributtes
/// <summary>
/// Silencia el sonido o le pone volumen previo a ser muteado
/// </summary>
/// <param name="muted"></param>
void Sound::SetMuted(bool muted)
{
	CheckState();
	_mute = muted;
	LowLevelSystem::ERRCHECK(channel->setMute(_mute));
}


/// <summary>
/// Establece el número de veces que tiene que reproducirse en loop
/// -1 para infinito | 0 una vez | 2 3 veces
/// </summary>
/// <param name="loop"></param>
void Sound::SetLoopCount(int loopCount)
{
	CheckState();
	_loopCount = loopCount;
	LowLevelSystem::ERRCHECK(channel->setLoopCount(loopCount));
}

/// <summary>
/// Establece el volumen del sonido
/// Valor entre 0.0 y 1.0
/// </summary>
/// <param name="volume"></param>
void Sound::SetVolume(float volume)
{
	CheckState();
	_volume = volume;
	LowLevelSystem::ERRCHECK(channel->setVolume(_volume));
}


/// <summary>
/// Establece el pitch del sonido
/// </summary>
/// <param name="pitch"></param>
void  Sound::SetPitch(float pitch)
{
	CheckState();
	_pitch = pitch;
	LowLevelSystem::ERRCHECK(channel->setPitch(_pitch));
}


/// <summary>
/// Establece la frecuencia del sonido
/// </summary>
/// <param name="newFrequency"></param>
void Sound::SetFrequency(float newFrequency)
{
	CheckState(); // 1.
	_frequency = newFrequency; // 2.
	LowLevelSystem::ERRCHECK(channel->setFrequency(_frequency)); // 3.
	//4. reset
}

/// <summary>
///  Añade un DSP al canal
/// </summary>
/// <param name="newFrequency"></param>
void Sound::AddDSP(FMOD::DSP* DSP) {
	CheckState();
	DSPList.push_back(DSP);//Se añade a la lista de DSP
	channel->addDSP(DSPList.size(), DSP); //Se añade el DSP al canal 
}

/// <summary>
/// Establece la panorámica del sound 
/// </summary>
/// <param name="newFrequency"></param>
void Sound::SetPan(float pan) {
	CheckState();
	_pan = pan;
	LowLevelSystem::ERRCHECK(channel->setPan(pan));
}

/// <summary>
/// Establece la posición de reproducción de la pista en milisegundos
/// </summary>
/// <param name="position"></param>
void Sound::SetMSPosition(int position)
{
	LowLevelSystem::ERRCHECK(channel->setPosition(position, FMOD_TIMEUNIT_MS));
}

#pragma endregion SetAtributtes


/// <summary>
/// Crea un nuevo canal con los parámetros del anterior
/// </summary>
void Sound::ResetChannel()
{
	//channel->clearHandle();
	channel = LowLevelSystem::GetInstance()->CreateChannel(_sound);
	currentState = SoundState::READY;

	SetFrequency(_frequency);
	SetMuted(_mute);
	SetLoopCount(_loopCount);
	SetVolume(_volume);
	SetPitch(_pitch);
	SetPan(_pan);

	int i = 0;

	//Se vuelven a añadir todos los efectos al canal
	for (auto it = DSPList.begin(); it != DSPList.end(); ++it)
	{
		LowLevelSystem::ERRCHECK(channel->addDSP(i, (*it)));
		i++;
	}
}

/// <summary>
/// Controla el flujo de estados
/// Además, si ha acabado un sonido, lo carga de nuevo
/// </summary>
void Sound::Update() {
	CheckState();
}
