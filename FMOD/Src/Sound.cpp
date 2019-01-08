#include "Sound.h"
#include "LowLevelSystem.h"

/*
Por defecto son samples. Puede pasarse que sean Streams o Samples Comprimidos.
Samples: Efectos de sonido.
Streams: Musica, pistas de voz, sonido ambiente.
Comprimidos. Ocupan menos memoria
*/
Sound::Sound(std::string name, FMOD_MODE mode, FMOD_CREATESOUNDEXINFO *exinfo) {
	_name = name;
	currentState = SoundState::READY;
}

//Libera el sonido
Sound::~Sound() {
	LowLevelSystem::ERRCHECK(_sound->release());
}

#pragma region Flow

//Reproduce el sonido
//Si está reproduciendo, se vuelve a reproducir desde el inicio.
//Si está pausado o ready, lo despausa
void Sound::Play()
{
	CheckState();

	if (currentState == SoundState::PLAYING)
		SetMSPosition(0);

	else //PAUSE O READY
		LowLevelSystem::ERRCHECK(_channel->setPaused(false));

}

// Para el sonido si está reproduciendose o pausado
// Se libera el canal 
void Sound::Stop()
{
	CheckState();

	if (currentState != SoundState::READY)
		LowLevelSystem::ERRCHECK(_channel->stop());
}

//Pausa el sonido si está reproduciendose
void Sound::Pause()
{
	CheckState();

	if (currentState == SoundState::PLAYING)
		LowLevelSystem::ERRCHECK(_channel->setPaused(true));
}

//Despausa el sonido si está pausado
void Sound::Resume()
{
	CheckState();

	if (currentState == SoundState::PAUSED)
		LowLevelSystem::ERRCHECK(_channel->setPaused(false));
}

//Pausa el sonido si está reproduciendose y reanuda la pausa si estaba pausado
void Sound::TogglePaused()
{
	CheckState();

	if (currentState == SoundState::PLAYING)
		Pause();
	else
		Resume();
}

#pragma endregion Flow

#pragma region CheckStateMethods

//Devuelve si el sonido está reproduciendose
bool Sound::IsPlaying()
{
	bool isPlaying;
	LowLevelSystem::ERRCHECK(_channel->getPaused(&isPlaying));
	return isPlaying;
}

// Devuelve si el sonido está pausado
bool Sound::IsPaused()
{
	bool isPaused;
	LowLevelSystem::ERRCHECK(_channel->getPaused(&isPaused));
	return isPaused;
}

// Devuelve si el sonido ha acabado
bool Sound::HasEnded()
{
	bool playing;
	return _channel->isPlaying(&playing) == FMOD_ERR_INVALID_HANDLE;
}

#pragma endregion  CheckStateMethods

#pragma region SetAtributtes

//Silencia el sonido o le pone volumen previo a ser muteado
void Sound::SetMuted(bool muted)
{
	CheckState();
	_mute = muted;
	LowLevelSystem::ERRCHECK(_channel->setMute(_mute));
}

//Establece el número de veces que tiene que reproducirse en loop
//-1 para infinito | 0 una vez | 2 3 veces
void Sound::SetLoopCount(int loopCount)
{
	CheckState();
	_loopCount = loopCount;
	LowLevelSystem::ERRCHECK(_channel->setLoopCount(loopCount));
}

//Establece el volumen del sonido
//Valor entre 0.0 y 1.0
void Sound::SetVolume(float volume)
{
	CheckState();
	_volume = volume;
	LowLevelSystem::ERRCHECK(_channel->setVolume(_volume));
}

//Establece la panorámica del sound 
//-1 a la izquierda, 0 Centrado, 1 a la derecha
void Sound::SetPan(float pan) {
	CheckState();
	_pan = pan;
	LowLevelSystem::ERRCHECK(_channel->setPan(pan));
}

//Establece el pitch del sonido
void  Sound::SetPitch(float pitch)
{
	CheckState();
	_pitch = pitch;
	LowLevelSystem::ERRCHECK(_channel->setPitch(_pitch));
}

//Establece la frecuencia del sonido
void Sound::SetFrequency(float newFrequency)
{
	CheckState(); // 1.
	_frequency = newFrequency; // 2.
	LowLevelSystem::ERRCHECK(_channel->setFrequency(_frequency)); // 3.
	//4. reset
}

//Añade un DSP al canal
void Sound::AddDSP(FMOD::DSP* DSP) {
	CheckState();
	DSPList.push_back(DSP);//Se añade a la lista de DSP
	_channel->addDSP(DSPList.size(), DSP); //Se añade el DSP al canal //TODO: SIZE?
}

#pragma endregion SetAtributtes

#pragma region ChannelEffects

void Sound::FadeIn(float time, float volume) {
	unsigned long long dspclock;
	LowLevelSystem::ERRCHECK(_channel->getDSPClock(0, &dspclock));
	int rate;
	LowLevelSystem::ERRCHECK(LowLevelSystem::GetInstance()->GetSystem()->getSoftwareFormat(&rate, 0, 0));                // Get mixer rate

	_channel->addFadePoint(dspclock + (rate * time), volume);    // Add a fade point 5 seconds later at 0 volume.
}

void Sound::FadeOut(float time, float volume)
{
	unsigned long long dspclock;
	LowLevelSystem::ERRCHECK(_channel->getDSPClock(0, &dspclock));
	int rate;
	LowLevelSystem::ERRCHECK(LowLevelSystem::GetInstance()->GetSystem()->getSoftwareFormat(&rate, 0, 0));                // Get mixer rate

	_channel->addFadePoint(dspclock + (rate * time), volume);    // Add a fade point 5 seconds later at 0 volume.
}

// Establece la posición de reproducción de la pista en milisegundos
void Sound::SetMSPosition(int position)
{
	LowLevelSystem::ERRCHECK(_channel->setPosition(position, FMOD_TIMEUNIT_MS));
}

#pragma endregion ChannelEffects

//Crea un nuevo canal con los parámetros del anterior
void Sound::ResetChannel()
{
	_channel = LowLevelSystem::GetInstance()->CreateChannel(_sound);
	currentState = SoundState::READY;

	SetMuted(_mute);
	SetLoopCount(_loopCount);
	SetPan(_pan);
	SetVolume(_volume);
	SetPitch(_pitch);
	SetFrequency(_frequency);

	int i = 0;

	//Se vuelven a añadir todos los efectos al canal
	for (auto it = DSPList.begin(); it != DSPList.end(); ++it)
	{
		LowLevelSystem::ERRCHECK(_channel->addDSP(i, (*it)));
		i++;
	}
}

// Actualiza el estado actual del sonido
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

 //Controla el flujo de estados
 //Además, si ha acabado un sonido, lo carga de nuevo
void Sound::Update() {
	CheckState();
}
