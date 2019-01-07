#include "Sound.h"
#include "fmod_errors.h" // para manejo de errores



Sound::Sound(std::string name) {
	_name = name;
	currentState = SoundState::READY;
}

Sound::~Sound() {
	LowLevelSystem::ERRCHECK(sound->release());
}

void Sound::InitAttributes() { //Frecuencia
	LowLevelSystem::ERRCHECK(channel->getFrequency(&_frequency)); //Inicializa el valor de frequency

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
	SetFrequency(_frequency);

	int i = 0;

	//Se vuelven a añadir todos los efectos al canal
	for (auto it = DSPList.begin(); it != DSPList.end(); ++it)
	{
		LowLevelSystem::ERRCHECK(channel->addDSP(i, (*it)));
		i++;
	}
}
#pragma region Atributtes
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
/// Establece la posición de reproducción de la pista en milisegundos
/// </summary>
/// <param name="position"></param>
void Sound::SetMSPosition(int position)
{
	CheckState();
	LowLevelSystem::ERRCHECK(channel->setPosition(position, FMOD_TIMEUNIT_MS));
}

/// <summary>
/// Establece la panorámica del sound 
/// </summary>
/// <param name="newFrequency"></param>
void Sound::SetPan(float pan) {
	LowLevelSystem::ERRCHECK(channel->setPan(pan));
}

#pragma endregion Atributtes




/// <summary>
/// Controla el flujo de estados
/// Además, si ha acabado un sonido, lo carga de nuevo
/// </summary>
void Sound::Update() {
	CheckState();
}
