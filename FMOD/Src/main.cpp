#include "fmod.hpp"
#include "LowLevelSystem.h"
#include "Sound3D.h"
#include "Sound2D.h"

#include <conio.h>

//Ejemplo de un pequeño reproductor
void SimplePlayer()
{
	LowLevelSystem::GetInstance();

	Sound2D * sound3D = new Sound2D("Battle.wav");
	sound3D->Play();
	printf("[P] Pausar/Despausar\n[V/v] Subir/bajar volumen\n[Q] Salir\n");

	bool paused; float volume = 1.0;
	while (true)
	{
		if (_kbhit())
		{
			int key = _getch();

			//PAUSAR SONIDO
			if ((key == 'P') || (key == 'p'))
				sound3D->TogglePaused();

			//PARAR SONIDO
			else if (key == 'S' || key == 's')
				sound3D->Stop();

			//REPRODUCIR SONIDO
			else if (key == 'R' || key == 'r')
				sound3D->Play();

			//SUBIR VOLUMEN
			else if (key == 'V' || key == 'v')
			{
				if (volume < 1.0)
				{
					volume = volume + 0.1;
					sound3D->SetVolume(volume);
					printf("Volume: %f\n", volume);
				}
			}
			//BAJAR VOLUMEN
			else if (key == 'B' || key == 'b')
			{
				if (volume > 0)
				{
					volume = volume - 0.1;
					sound3D->SetVolume(volume);
					printf("Volume: %f\n", volume);
				}
			}
			//FADE IN
			else if (key == 'A' || key == 'a')
			{

				float time = 2.0;
				float volumeFadeIn = 0.7;
				sound3D->FadeIn(time, volumeFadeIn);
				printf("Fade in after %f seconds\n", time);
			}
			//FADE OUT
			else if (key == 'Z' || key == 'z')
			{

				float time = 2.0;
				float volumeFadeOut = 0.2;
				sound3D->FadeOut(time, volumeFadeOut);
				printf("Fade out after %f seconds\n", time);
			}
			//PAN -1 Izq, O por defecto, 1 derecha
			else if (key == 'N' || key == 'n') {
				int n = -1.0;
				sound3D->SetPan(n);
				printf("Pan: %f\n ", n);
			}
			//SALIR DE LA APLICACIÓN
			else if ((key == 'Q') || (key == 'q'))
				break;

			LowLevelSystem::GetInstance()->Update();
		}
	}

	delete sound3D;
	LowLevelSystem::ResetInstance();
}

void SimplePiano() {
	LowLevelSystem::GetInstance();

	//Bucle principal
	bool paused;
	float volume = 1.0;
	float currentOctave = 1.0f;

	Sound2D * doNote = new Sound2D("piano.ogg");
	doNote->SetPitch(currentOctave);

	Sound2D * doSharpNote = new Sound2D("piano.ogg");
	doSharpNote->SetPitch(currentOctave * pow(2, (1.0f / 12.0f)));

	Sound2D * reNote = new Sound2D("piano.ogg");
	reNote->SetPitch(currentOctave * pow(2, (2.0f / 12.0f)));

	Sound2D * miFlatNote = new Sound2D("piano.ogg");
	miFlatNote->SetPitch(currentOctave * pow(2, (3.0f / 12.0f)));

	Sound2D * miNote = new Sound2D("piano.ogg");
	miNote->SetPitch(currentOctave * pow(2, (4.0f / 12.0f)));

	Sound2D * faNote = new Sound2D("piano.ogg");
	faNote->SetPitch(currentOctave * pow(2, (5.0f / 12.0f)));

	Sound2D * faSharpNote = new Sound2D("piano.ogg");
	faSharpNote->SetPitch(currentOctave * pow(2, (6.0f / 12.0f)));

	Sound2D * solNote = new Sound2D("piano.ogg");
	solNote->SetPitch(currentOctave * pow(2, (7.0f / 12.0f)));

	Sound2D * solSharpNote = new Sound2D("piano.ogg");
	solSharpNote->SetPitch(currentOctave * pow(2, 8.0f / 12.0f));

	Sound2D * laNote = new Sound2D("piano.ogg");
	laNote->SetPitch(currentOctave * pow(2, (9.0f / 12.0f)));

	Sound2D * siFlatNote = new Sound2D("piano.ogg");
	siFlatNote->SetPitch(currentOctave * pow(2, (10.0f / 12.0f)));

	Sound2D * siNote = new Sound2D("piano.ogg");
	siNote->SetPitch(currentOctave * pow(2, (11.0f / 12.0f)));



	while (true)
	{
		

		if (_kbhit())
		{
			int key = _getche();
			//sdghj

			//Do
			if ((key == 'Z') || (key == 'z'))	
				doNote->Play();
			
			//Do sostenido
			else if ((key == 'S') || (key == 's'))
				doSharpNote->Play();

			//Re
			else if ((key == 'X') || (key == 'x'))			
				reNote->Play();
			

			//Mi
			else if ((key == 'C') || (key == 'c'))			
				miNote->Play();

			//Mi bemol
			else if ((key == 'D') || (key == 'd'))
				miFlatNote->Play();
			

			//Fa
			else if ((key == 'V') || (key == 'v'))			
				faNote->Play();

			//Fa sostenido
			else if ((key == 'G') || (key == 'g'))
				faSharpNote->Play();
			

			//Sol
			else if ((key == 'B') || (key == 'b'))			
			solNote->Play();

			//Sol sostenido
			else if ((key == 'H') || (key == 'h'))
				solSharpNote->Play();
			

			//La
			else if ((key == 'N') || (key == 'n'))		
				laNote->Play();
			

			//Si
			else if ((key == 'M') || (key == 'm'))		
				siNote->Play();

			//Si bemol
			else if ((key == 'J') || (key == 'j'))
				siFlatNote->Play();
			
			//+ Escala superior
			else if (key == ',')
			{

				currentOctave *= 2;
				doNote->SetPitch(currentOctave);
				doSharpNote->SetPitch(currentOctave * pow(2, (1.0f / 12.0f)));
				reNote->SetPitch(currentOctave * pow(2, (2.0f / 12.0f)));
				miFlatNote->SetPitch(currentOctave * pow(2, (3.0f / 12.0f)));
				miNote->SetPitch(currentOctave * pow(2, (4.0f / 12.0f)));
				faNote->SetPitch(currentOctave * pow(2, (5.0f / 12.0f)));
				faSharpNote->SetPitch(currentOctave * pow(2, (6.0f / 12.0f)));
				solNote->SetPitch(currentOctave * pow(2, (7.0f / 12.0f)));
				solSharpNote->SetPitch(currentOctave * pow(2, 8.0f / 12.0f));
				laNote->SetPitch(currentOctave * pow(2, (9.0f / 12.0f)));
				siFlatNote->SetPitch(currentOctave * pow(2, (10.0f / 12.0f)));
				siNote->SetPitch(currentOctave * pow(2, (11.0f / 12.0f)));

			}

			//- Escala inferior
			else if (key == '.')
			{
				currentOctave /= 2;
				doNote->SetPitch(currentOctave);
				doSharpNote->SetPitch(currentOctave * pow(2, (1.0f / 12.0f)));
				reNote->SetPitch(currentOctave * pow(2, (2.0f / 12.0f)));
				miFlatNote->SetPitch(currentOctave * pow(2, (3.0f / 12.0f)));
				miNote->SetPitch(currentOctave * pow(2, (4.0f / 12.0f)));
				faNote->SetPitch(currentOctave * pow(2, (5.0f / 12.0f)));
				faSharpNote->SetPitch(currentOctave * pow(2, (6.0f / 12.0f)));
				solNote->SetPitch(currentOctave * pow(2, (7.0f / 12.0f)));
				solSharpNote->SetPitch(currentOctave * pow(2, 8.0f / 12.0f));
				laNote->SetPitch(currentOctave * pow(2, (9.0f / 12.0f)));
				siFlatNote->SetPitch(currentOctave * pow(2, (10.0f / 12.0f)));
				siNote->SetPitch(currentOctave * pow(2, (11.0f / 12.0f)));
			}
		}
		doNote->Update();
		doSharpNote->Update();

		reNote->Update();
		miFlatNote->Update();

		miNote->Update();
		faNote->Update();
		faSharpNote->Update();

		solNote->Update();
		solSharpNote->Update();

		laNote->Update();
		siFlatNote->Update();
		siNote->Update();

		LowLevelSystem::GetInstance()->Update();
	}
	//Se borran las notas
	delete doNote;
	delete doSharpNote;
	delete reNote;
	delete miNote;
	delete miFlatNote;
	delete faNote;
	delete faSharpNote;
	delete solNote;
	delete solSharpNote;
	delete laNote;
	delete siNote;
	delete siFlatNote;
}
////Se pueden agrupar canales y crear jerarquias
//void ChannelGroup()
//{
//	//TODO: FUNCIONAR
//	// creamos un grupo de canales ``channelGroup''
//	FMOD::ChannelGroup* channelGroup;
//	system->createChannelGroup("grupo1", &channelGroup);
//	// aniadimos un canal existente, channel, al grupo
//	channel->setChannelGroup(channelGroup);
//	// se puede anidir un canal a un grupo directamente con
//	// playSound(...,group,...,...) mas eficiente!
//	// aniadimos este grupo como hijo de otro grupo ``anotherGroup''
//	channelGroup->addGroup(anotherGroup);
//	// hay un ``master'' (raiz del arbol de grupos) que se puede acceder asi:
//	ChannelGroup* masterGroup;
//	system->getMasterChannelGroup(&masterGroup);
//
//	//oPERACIONES SOBRE EL CANAL
//
//	// Parar todos los canales del grupo
//	channelGroup->stop();
//	// Silenciar, pausar
//	channelGroup->setMute(true);
//	channelGroup->setPaused(true);
//	// ajustar volumen
//	channelGroup->setVolume(0.5f);
//	// duplicar pitch
//	channelGroup->setPitch(2.0f);
//}

//
////La reverberación es un fenómeno acústico que permite que el sonido persista en el tiempo cuando la fuente sonora ha dejado de producirlo.
////Es como una sucesión de ecos producido por el rebote de las superficies del recinto. Depende del recinto.
//void ReverbExample()
//{
//	FMOD::Reverb3D *reverb = LowLevelSystem::GetInstance()->CreateReverb();
//
//	//Propiedades de la reverb
//	FMOD_REVERB_PROPERTIES prop = FMOD_PRESET_CONCERTHALL; //Muchos más en FMOD_PRESET_
//	reverb->setProperties(&prop);
//
//	//Posición y zonas de influencia
//	FMOD_VECTOR pos = { -10.0f, 0.0f, 0.0f };
//	float mindist = 10.0f;//Escucha la reverb sin atenuación
//	float maxdist = 20.0f;//Radio en el que escucha la reverb atenuandose
//	reverb->set3DAttributes(&pos, mindist, maxdist);
//
//	//Puede activarse o desactivarse
//	reverb->setActive(true);
//
//	//Debe liberarse el objeto
//	reverb->release();
//
//	//Afectan al canal por Channel::SetReverbProperties
//	//Se escuchará una mezcla ponderada de los reverb que afecten al listener
//
//	//TODO: COsas raras de reverb por convolución
//}

////Aplicación de efectos lowlevel effects: Sonido de radio: distorsion + filtro paso por alto
////TODO: Tutorial FMOD DSP Architecture and Usage
//void DSPExample()
//{
//	// parametros del efecto
//	FMOD::DSP* distorsion = LowLevelSystem::GetInstance()->CreateDSPByType(FMOD_DSP_TYPE_DISTORTION);
//	distorsion->setParameterFloat(FMOD_DSP_DISTORTION_LEVEL, 0.85f);
//
//	FMOD::DSP* highpass = LowLevelSystem::GetInstance()->CreateDSPByType(FMOD_DSP_TYPE_HIGHPASS);
//	highpass->setParameterFloat(FMOD_DSP_HIGHPASS_CUTOFF, 2000.0f);
//
//	// apliacion a un canal (puede aplicarse a un grupo o al sistema)
//	Sound * sound = new Sound("TODO: PONER UN NOMBRE");
//	sound->AddDSP(distorsion);
//	sound->AddDSP(highpass); //TODO: REVISAR QUE FUNCIONA. EL LE PASA UN 0 EN EL INDICE
//}

int main()
{
	//SimplePlayer();
	SimplePiano();
	return 0;
}
