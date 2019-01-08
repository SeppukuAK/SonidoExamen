#include "fmod.hpp"
#include "LowLevelSystem.h"
#include "Sound3D.h"
#include "Sound2D.h"
#include <conio.h>
#include <windows.h>  
#include "AudioGeometry.h"

#pragma region Hoja1
//Ejemplo de un pequeño reproductor
void SimplePlayer()
{
	LowLevelSystem::GetInstance();

	Sound2D * sound3D = new Sound2D("Battle.wav");
	sound3D->Play();
	printf("[P] Pausar/Despausar\n[V/v] Subir/bajar volumen\n[Q] Salir\n");

	float volume = 1.0f;
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
					volume = volume + 0.1f;
					sound3D->SetVolume(volume);
					printf("Volume: %f\n", volume);
				}
			}
			//BAJAR VOLUMEN
			else if (key == 'B' || key == 'b')
			{
				if (volume > 0)
				{
					volume = volume - 0.1f;
					sound3D->SetVolume(volume);
					printf("Volume: %f\n", volume);
				}
			}
			//FADE IN
			else if (key == 'A' || key == 'a')
			{

				float time = 2.0f;
				float volumeFadeIn = 1.0f;
				sound3D->Fade(time, volumeFadeIn);
				printf("Fade in after %f seconds\n", time);
			}
			//FADE OUT
			else if (key == 'Z' || key == 'z')
			{
				float time = 2.0f;
				float volumeFadeOut = 0.0f;
				sound3D->Fade(time, volumeFadeOut);
				printf("Fade out after %f seconds\n", time);
			}
			//PAN -1 Izq, O por defecto, 1 derecha
			else if (key == 'N' || key == 'n') {
				float n = -1.0f;
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
	float volume = 1.0f;
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

	LowLevelSystem::ResetInstance();

}

#pragma endregion Hoja 1

#pragma region Hoja2

enum TileType { NONE, SOURCE, LISTENER, WALL, REVERB1, REVERB2 };

//Desplaza el cursor de la consola a un punto
void gotoxy(int x, int y) {
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}

//Renderiza el tileMap y los valores
void render(TileType tileMap[30][30], float minD, float maxD, float coneI, float coneO)
{
	gotoxy(0, 0);

	//Dibujar
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 30; j++) {
			switch (tileMap[i][j])
			{
			case NONE:
				printf(". ");

				break;

			case SOURCE:
				printf("S ");

				break;

			case LISTENER:
				printf("L ");

				break;

			case WALL:
				printf("==");

				break;

			case REVERB1:
				printf("1 ");

				break;

			case REVERB2:
				printf("2 ");

				break;


			}
		}
		printf("\n");
	}

	printf("Listener (L): asdw   Source (S): jkli   x: inversion   z: EXIT \n");
	printf("minD: %.1f  maxD: %.1f     coneI: %.0f   coneO: %.0f \n", minD, maxD, coneI, coneO);
}

void createGeometry()
{
	FMOD_VECTOR vertex[4];
	vertex[0] = { 10,-10,15 };
	vertex[1] = { 20,10,15 };
	vertex[2] = { 20,-10,15 };
	vertex[3] = { 10,10,15 };

	FMOD_VECTOR poligons[2][3] =
	{
		{ vertex[0] ,vertex[2] ,vertex[1] },
		{ vertex[1] ,vertex[3] ,vertex[0] }
	};
	AudioGeometry * audioGeometry = new AudioGeometry(2, 3, 1.0f, 0.5f, true, *poligons);
}

void Hoja2()
{
	LowLevelSystem * lowLevelSystem = LowLevelSystem::GetInstance();	//Inicializa el motor
	lowLevelSystem->SetNumListeners(1);

	FMOD_VECTOR
		listenerPos = { 15,0,10 }, // posicion del listener
		listenerVel = { 0,0,0 }, // velocidad del listener
		up = { 0,1,0 }, // vector up: hacia la ``coronilla''
		at = { 0,0,1 }; // vector at: hacia donde mira

	//colocamos listener
	lowLevelSystem->SetListener(0, listenerPos, listenerVel, up, at);

	TileType tileMap[30][30];
	createGeometry();

	//Inicialización del TileMap
	for (int i = 0; i < 30; i++)
		for (int j = 0; j < 30; j++)
			tileMap[i][j] = NONE;

	tileMap[(int)listenerPos.z - 1][(int)listenerPos.x - 1] = LISTENER;

	//Creación source
	Sound3D * footstepSound = nullptr;
	footstepSound = new Sound3D("footstep.wav");
	footstepSound->SetLoopCount(-1);

	//Position
	FMOD_VECTOR sourcePos = { 15,0,20 };
	footstepSound->SetPos(sourcePos);
	tileMap[(int)sourcePos.z - 1][(int)sourcePos.x - 1] = SOURCE;

	//Distance
	float minDistance = 2.0f;
	float maxDistance = 10.0f;
	footstepSound->SetMinDistance(minDistance);
	footstepSound->SetMaxDistance(maxDistance);

	//Direction
	FMOD_VECTOR dir = { 0.0f, 0.0f, -1.0f };
	footstepSound->SetConeOrientation(dir);

	//Angle
	float insideConeAngle = 15.0f;
	float outsideConeAngle = 90.0f;
	footstepSound->SetInsideConeAngle(insideConeAngle);
	footstepSound->SetOutsideConeAngle(outsideConeAngle);
	footstepSound->SetOutsideVolume(0.0f);

	footstepSound->Play();

	//Para calcular la velocidad de una fuente de sonido utilizamos la posicion de la entidad
	//vel.x = (pos.x - lastPos.x) * elapsed;


	render(tileMap, minDistance, maxDistance, insideConeAngle, outsideConeAngle);

	while (true)
	{
		if (_kbhit())
		{
			int key = _getche();

			if ((key == 'Z') || (key == 'z'))
				break;

			//Control listener
			else if ((key == 'W') || (key == 'w'))
			{
				tileMap[(int)listenerPos.z - 1][(int)listenerPos.x - 1] = NONE;
				listenerPos.z -= 1;
				lowLevelSystem->SetListenerPos(0, listenerPos);
				tileMap[(int)listenerPos.z - 1][(int)listenerPos.x - 1] = LISTENER;
			}

			else if ((key == 'S') || (key == 's'))
			{
				tileMap[(int)listenerPos.z - 1][(int)listenerPos.x - 1] = NONE;
				listenerPos.z += 1;
				lowLevelSystem->SetListenerPos(0, listenerPos);
				tileMap[(int)listenerPos.z - 1][(int)listenerPos.x - 1] = LISTENER;
			}

			else if ((key == 'A') || (key == 'a'))
			{
				tileMap[(int)listenerPos.z - 1][(int)listenerPos.x - 1] = NONE;
				listenerPos.x -= 1;
				lowLevelSystem->SetListenerPos(0, listenerPos);
				tileMap[(int)listenerPos.z - 1][(int)listenerPos.x - 1] = LISTENER;
			}

			else if ((key == 'D') || (key == 'd'))
			{
				tileMap[(int)listenerPos.z - 1][(int)listenerPos.x - 1] = NONE;
				listenerPos.x += 1;
				lowLevelSystem->SetListenerPos(0, listenerPos);
				tileMap[(int)listenerPos.z - 1][(int)listenerPos.x - 1] = LISTENER;
			}

			//Control source
			else if ((key == 'J') || (key == 'j'))
			{
				tileMap[(int)sourcePos.z - 1][(int)sourcePos.x - 1] = NONE;
				sourcePos.x -= 1;
				footstepSound->SetPos(sourcePos);
				tileMap[(int)sourcePos.z - 1][(int)sourcePos.x - 1] = SOURCE;
			}

			else if ((key == 'K') || (key == 'k'))
			{
				tileMap[(int)sourcePos.z - 1][(int)sourcePos.x - 1] = NONE;
				sourcePos.z += 1;
				footstepSound->SetPos(sourcePos);
				tileMap[(int)sourcePos.z - 1][(int)sourcePos.x - 1] = SOURCE;
			}

			else if ((key == 'L') || (key == 'l'))
			{
				tileMap[(int)sourcePos.z - 1][(int)sourcePos.x - 1] = NONE;
				sourcePos.x += 1;
				footstepSound->SetPos(sourcePos);
				tileMap[(int)sourcePos.z - 1][(int)sourcePos.x - 1] = SOURCE;
			}
			else if ((key == 'I') || (key == 'i'))
			{
				tileMap[(int)sourcePos.z - 1][(int)sourcePos.x - 1] = NONE;

				sourcePos.z -= 1;
				footstepSound->SetPos(sourcePos);

				tileMap[(int)sourcePos.z - 1][(int)sourcePos.x - 1] = SOURCE;
			}

			//Control Angulos source
			//Angulo interior
			else if ((key == 'R') || (key == 'r'))
			{
				insideConeAngle += 5.0f;
				footstepSound->SetInsideConeAngle(insideConeAngle);
			}
			else if ((key == 'F') || (key == 'f'))
			{
				insideConeAngle -= 5.0f;
				footstepSound->SetInsideConeAngle(insideConeAngle);
			}

			//Angulo exterior
			else if ((key == 'T') || (key == 't'))
			{
				outsideConeAngle += 5.0f;
				footstepSound->SetOutsideConeAngle(outsideConeAngle);
			}
			else if ((key == 'G') || (key == 'g'))
			{
				outsideConeAngle -= 5.0f;
				footstepSound->SetOutsideConeAngle(outsideConeAngle);
			}

			//Control Source Distance
			//Min Distance
			else if ((key == 'C') || (key == 'c'))
			{
				minDistance += 0.1f;
				footstepSound->SetMinDistance(minDistance);
			}
			else if ((key == 'V') || (key == 'v'))
			{
				minDistance -= 0.1f;
				footstepSound->SetMinDistance(minDistance);
			}

			//Max Distance
			else if ((key == 'B') || (key == 'b'))
			{
				maxDistance += 0.1f;
				footstepSound->SetMaxDistance(maxDistance);
			}
			else if ((key == 'N') || (key == 'n'))
			{
				maxDistance -= 0.1f;
				footstepSound->SetMaxDistance(maxDistance);
			}

			render(tileMap, minDistance, maxDistance, insideConeAngle, outsideConeAngle);

			//if ((key == 'Y') || (key == 'y'))
			//{
			//	footstepSound->SetConeOrientarion();
			//}
		}

		LowLevelSystem::GetInstance()->Update();
	}

	delete footstepSound;

	LowLevelSystem::ResetInstance();
}



#pragma endregion Hoja 2

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
	//SimplePiano();
	Hoja2();
	return 0;
}
