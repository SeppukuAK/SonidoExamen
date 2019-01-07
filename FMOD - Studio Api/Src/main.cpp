#include "fmod.hpp"
#include "LowLevelSystem.h"
#include "Sound.h"
#include "fmod_dsp.h"
#include "fmod_dsp_effects.h"
#include "fmod_common.h"

//La reverberación es un fenómeno acústico que permite que el sonido persista en el tiempo cuando la fuente sonora ha dejado de producirlo.
//Es como una sucesión de ecos producido por el rebote de las superficies del recinto. Depende del recinto.
void ReverbExample()
{
	FMOD::Reverb3D *reverb = LowLevelSystem::GetInstance()->CreateReverb();

	//Propiedades de la reverb
	FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_CONCERTHALL; //Muchos más en FMOD_PRESET_
	reverb->setProperties(&prop);

	//Posición y zonas de influencia
	FMOD_VECTOR pos = { -10.0f, 0.0f, 0.0f };
	float mindist = 10.0f;//Escucha la reverb sin atenuación
	float maxdist = 20.0f;//Radio en el que escucha la reverb atenuandose
	reverb->set3DAttributes(&pos, mindist, maxdist);

	//Puede activarse o desactivarse
	reverb->setActive(true);

	//Debe liberarse el objeto
	reverb->release();

	//Afectan al canal por Channel::SetReverbProperties
	//Se escuchará una mezcla ponderada de los reverb que afecten al listener
	
	//TODO: COsas raras de reverb por convolución
}

//Aplicación de efectos lowlevel effects: Sonido de radio: distorsion + filtro paso por alto
//TODO: Tutorial FMOD DSP Architecture and Usage
void DSPExample()
{
	// parametros del efecto
	FMOD::DSP* distorsion = LowLevelSystem::GetInstance()->CreateDSPByType(FMOD_DSP_TYPE_DISTORTION);
	distorsion->setParameterFloat(FMOD_DSP_DISTORTION_LEVEL, 0.85f);

	FMOD::DSP* highpass = LowLevelSystem::GetInstance()->CreateDSPByType(FMOD_DSP_TYPE_HIGHPASS);
	highpass->setParameterFloat(FMOD_DSP_HIGHPASS_CUTOFF, 2000.0f);

	// apliacion a un canal (puede aplicarse a un grupo o al sistema)
	Sound * sound = new Sound("TODO: PONER UN NOMBRE");
	sound->AddDSP(distorsion);
	sound->AddDSP(highpass); //TODO: REVISAR QUE FUNCIONA. EL LE PASA UN 0 EN EL INDICE
}

int main()
{
	return 0;
}
