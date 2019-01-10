#include "fmod.hpp"
#include "LowLevelSystem.h"
#include "Sound3D.h"
#include "Sound2D.h"
#include <conio.h>
#include <windows.h>  
#include "AudioGeometry.h"
#include "fmod_studio.hpp"
#include <chrono>

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
			//PAN -1 Izq, O por defecto, 1 derecha (2D)
			else if (key == 'N' || key == 'n') {
				float n = -1.0f;
				sound3D->SetPan(n);
				printf("Pan: %f\n ", n);
			}
			//SALIR DE LA APLICACIÓN
			else if ((key == 'Q') || (key == 'q'))
				break;

			sound3D->Update();
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

TileType tileMap[30][30];

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
void render(float minD, float maxD, float coneI, float coneO)
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

	for (int i = 0; i < 10; i++) {
		tileMap[14][9 + i] = WALL;
	}
}

FMOD::Reverb3D *reverb1, *reverb2; //Variable global

//La reverberación es un fenómeno acústico que permite que el sonido persista en el tiempo cuando la fuente sonora ha dejado de producirlo.
//Es como una sucesión de ecos producido por el rebote de las superficies del recinto. Depende del recinto.
void createReverbs() {
	reverb1 = LowLevelSystem::GetInstance()->CreateReverb();
	reverb2 = LowLevelSystem::GetInstance()->CreateReverb();

	//Propiedades de la reverb
	FMOD_REVERB_PROPERTIES propR1 = FMOD_PRESET_CAVE; //Muchos más en FMOD_PRESET_
	reverb1->setProperties(&propR1);

	//Propiedades de la reverb
	FMOD_REVERB_PROPERTIES propR2 = FMOD_PRESET_CONCERTHALL; //Muchos más en FMOD_PRESET_
	reverb2->setProperties(&propR2);

	//Posición y zonas de influencia
	FMOD_VECTOR posReverb1 = { 18.0f, 0.0f, 10.0f };
	float mindistR1 = 10.0f;//Escucha la reverb sin atenuación
	float maxdistR1 = 20.0f;//Radio en el que escucha la reverb atenuandose
	reverb1->set3DAttributes(&posReverb1, mindistR1, maxdistR1);

	reverb1->setActive(true);

	//Posición y zonas de influencia
	FMOD_VECTOR posReverb2 = { 14.0f, 0.0f, 20.0f };
	float mindistR2 = 10.0f;//Escucha la reverb sin atenuación
	float maxdistR2 = 20.0f;//Radio en el que escucha la reverb atenuandose
	reverb2->set3DAttributes(&posReverb2, mindistR2, maxdistR2);

	//Puede activarse o desactivarse
	reverb2->setActive(true);
		  //z   x
	tileMap[9][17] = REVERB1;
	tileMap[19][11] = REVERB2;

	//Afectan al canal por Channel::SetReverbProperties
	//Se escuchará una mezcla ponderada de los reverb que afecten al listener

	//TODO: COsas raras de reverb por convolución
}

void Hoja2()
{
	//Inicialización del TileMap
	for (int i = 0; i < 30; i++)
		for (int j = 0; j < 30; j++)
			tileMap[i][j] = NONE;

	LowLevelSystem * lowLevelSystem = LowLevelSystem::GetInstance();	//Inicializa el motor
	lowLevelSystem->SetNumListeners(1);

	FMOD_VECTOR
		listenerPos = { 15,0,10 }, // posicion del listener
		listenerVel = { 0,0,0 }, // velocidad del listener
		up = { 0,1,0 }, // vector up: hacia la ``coronilla''
		at = { 0,0,1 }; // vector at: hacia donde mira

	//colocamos listener
	lowLevelSystem->SetListener(0, listenerPos, listenerVel, up, at);

	tileMap[(int)listenerPos.z - 1][(int)listenerPos.x - 1] = LISTENER;

	createGeometry();
	createReverbs();

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

	//Establecemos al canal que le afecten las reverb
	footstepSound->SetReverbWet(1); //Afectada al máximo

	footstepSound->Play();

	render(minDistance, maxDistance, insideConeAngle, outsideConeAngle);

	bool moving = false;
	double ZDestination;
	int i = 0;

	//using namespace std::chrono;
	//high_resolution_clock::time_point lastTime = high_resolution_clock::now();
	while (true)
	{
		//high_resolution_clock::time_point current = high_resolution_clock::now();
		//duration<double> time_span = duration_cast<duration<double>>(current - lastTime);
		//lastTime = current;

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
			//Efecto Doppler
			else if (!moving && ((key == 'M') || (key == 'm')))
			{
				//Si estoy abajo
				if (sourcePos.z > 15)
				{
					i = 0;
					moving = true;
					ZDestination = sourcePos.z - 2 * (sourcePos.z - 15);
					footstepSound->SetVel({ 0,0,-10 });
				}
				else if (sourcePos.z < 15)
				{
					i = 0;
					moving = true;
					ZDestination = sourcePos.z + 2 * (15 - sourcePos.z);
					footstepSound->SetVel({ 0,0,10 });
				}
			}

			render(minDistance, maxDistance, insideConeAngle, outsideConeAngle);

		}

		//Comprobar si se tiene que mover el source
		if (moving)
		{
			//Cada cuanto tiempo se mueve el source
			if (i == 100)
			{
				tileMap[(int)sourcePos.z - 1][(int)sourcePos.x - 1] = NONE;

				if (sourcePos.z < ZDestination)
				{
					sourcePos.z++;
					footstepSound->SetPos(sourcePos);
				}

				else if (sourcePos.z > ZDestination)
				{
					sourcePos.z--;
					footstepSound->SetPos(sourcePos);
				}

				//He llegado al destino
				if (sourcePos.z == ZDestination)
				{
					moving = false;
					footstepSound->SetVel({ 0,0,0 });
				}

				tileMap[(int)sourcePos.z - 1][(int)sourcePos.x - 1] = SOURCE;
				render(minDistance, maxDistance, insideConeAngle, outsideConeAngle);

				i = 0;
			}
		}

		footstepSound->Update();

		LowLevelSystem::GetInstance()->Update();

		i++;
	}

	delete footstepSound;

	//Debe liberarse la reverb
	reverb1->release();
	reverb2->release();

	LowLevelSystem::ResetInstance();
}

#pragma endregion Hoja 2

//Se pueden agrupar canales y crear jerarquias
void ChannelGroup()
{
	LowLevelSystem::GetInstance();

	Sound2D * sound3D = new Sound2D("Battle.wav");
	Sound2D * footStep = new Sound2D("footstep.wav");

	//hay un ``master'' (raiz del arbol de grupos) que se puede acceder asi:  1*
	FMOD::ChannelGroup* masterGroup;
	LowLevelSystem::GetInstance()->GetSystem()->getMasterChannelGroup(&masterGroup);

	// creamos un grupo de canales ``channelGroup''
	FMOD::ChannelGroup * channelGroup = LowLevelSystem::GetInstance()->CreateChannelGroup("Ancianitos");
	masterGroup->addGroup(channelGroup); 	// aniadimos este grupo como hijo de otro grupo ``anotherGroup''

	// aniadimos un canal existente, channel, al grupo
	sound3D->SetChannelGroup(channelGroup);
	footStep->SetChannelGroup(channelGroup);//1*
	footStep->SetLoopCount(-1);
	float volume = 1.0f;
	while (true)
	{
		if (_kbhit())
		{
			int key = _getch();

			//PAUSAR SONIDO
			if ((key == 'P') || (key == 'p'))
				sound3D->TogglePaused();

			//REPRODUCIR SONIDO
			else if (key == 'R' || key == 'r') {
				sound3D->Play();
				footStep->Play();
			}

			// Parar todos los canales del grupo
			//Se quita el channelGroup, Hay que volverlo a crear 1*
			else if (key == 'Z' || key == 'z')
				channelGroup->stop();

			else if (key == 'X' || key == 'x')
				channelGroup->setMute(true);

			else if (key == 'C' || key == 'c')
				channelGroup->setPaused(true);

			else if (key == 'V' || key == 'v')
				channelGroup->setVolume(0.5f);

			else if (key == 'B' || key == 'b')
				channelGroup->setPitch(2.0f);

			//SALIR DE LA APLICACIÓN
			else if ((key == 'Q') || (key == 'q'))
				break;

			sound3D->Update();
			footStep->Update();
			LowLevelSystem::GetInstance()->Update();
		}
	}

	delete sound3D;
	LowLevelSystem::ResetInstance();
}

//Aplicación de efectos lowlevel effects: Sonido de radio: distorsion + filtro paso por alto
//TODO: Tutorial FMOD DSP Architecture and Usage
void DSPExample()
{
	LowLevelSystem * lowLevelSystem = LowLevelSystem::GetInstance();	//Inicializa el motor

	// parametros del efecto
	FMOD::DSP* distorsion = LowLevelSystem::GetInstance()->CreateDSPByType(FMOD_DSP_TYPE_DISTORTION);
	distorsion->setParameterFloat(FMOD_DSP_DISTORTION_LEVEL, 0.85f);

	FMOD::DSP* highpass = LowLevelSystem::GetInstance()->CreateDSPByType(FMOD_DSP_TYPE_HIGHPASS);
	highpass->setParameterFloat(FMOD_DSP_HIGHPASS_CUTOFF, 2000.0f);

	// apliacion a un canal (puede aplicarse a un grupo o al sistema)
	Sound2D * sound = new Sound2D("footstep.wav");
	sound->AddDSP(distorsion);
	sound->AddDSP(highpass); //TODO: REVISAR QUE FUNCIONA. EL LE PASA UN 0 EN EL INDICE

	sound->SetLoopCount(-1);
	sound->Play();

	while (true)
	{
		if (_kbhit())
		{
			int key = _getch();

			if ((key == 'Q') || (key == 'q'))
				break;

		}
		LowLevelSystem::GetInstance()->Update();

	}

	delete sound;
	LowLevelSystem::ResetInstance();
}

#pragma region FMOD_STUDIO

void FMOD_STUDIO_EXAMPLE()
{
	FMOD::Studio::System* system = NULL;
	LowLevelSystem::ERRCHECK(FMOD::Studio::System::create(&system));

	//Obtenemos el Low Level System a partir del System del Studio(No el nuestro)
	// The example Studio project is authored for 5.1 sound, so set up the system output mode to match
	FMOD::System* lowLevelSystem = NULL;
	LowLevelSystem::ERRCHECK(system->getLowLevelSystem(&lowLevelSystem));
	LowLevelSystem::ERRCHECK(lowLevelSystem->setSoftwareFormat(0, FMOD_SPEAKERMODE_5POINT1, 0));

	LowLevelSystem::ERRCHECK(system->initialize(1024, FMOD_STUDIO_INIT_NORMAL, FMOD_INIT_NORMAL, nullptr));

	FMOD::Studio::Bank* masterBank = NULL;
	LowLevelSystem::ERRCHECK(system->loadBankFile("../../Media/Desktop/Master Bank.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &masterBank));

	FMOD::Studio::Bank* stringsBank = NULL;
	LowLevelSystem::ERRCHECK(system->loadBankFile("../../Media/Desktop/Master Bank.strings.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &stringsBank));

	FMOD::Studio::Bank* pasosBank = NULL;
	LowLevelSystem::ERRCHECK(system->loadBankFile("../../Media/Desktop/Pasos.bank", FMOD_STUDIO_LOAD_BANK_NORMAL, &pasosBank));

	FMOD::Studio::EventDescription* pasosDescription = NULL;
	LowLevelSystem::ERRCHECK(system->getEvent("event:/Pasos", &pasosDescription));

	//Variable para obtener los tributos del parámetro(nombre,maximo value,type..)
	FMOD_STUDIO_PARAMETER_DESCRIPTION *hola = NULL;
	pasosDescription->getParameter("Velocidad", hola);

	FMOD::Studio::EventInstance* pasosInstance = NULL;
	LowLevelSystem::ERRCHECK(pasosDescription->createInstance(&pasosInstance));

	//Esto sería para efectos de sonido que se reproducen una vez. Se creará la instancia en el momento
	//FMOD::Studio::EventDescription* pasosDescription = NULL;
	//LowLevelSystem::ERRCHECK(system->getEvent("event:/Pasos", &pasosDescription));

	//// Start loading explosion sample data and keep it in memory
	//LowLevelSystem::ERRCHECK(pasosDescription->loadSampleData());

	float velocity = 5.0f, recinto = 0.5f;

	//Inicializamos los parámetros por defecto
	LowLevelSystem::ERRCHECK(pasosInstance->setParameterValue("Velocidad", velocity));
	LowLevelSystem::ERRCHECK(pasosInstance->setParameterValue("Recinto", recinto));

	while (true)
	{
		if (_kbhit())
		{
			int key = _getch();

			//REPRODUCIR EFECTO DE SONIDO
			//if ((key == 'P') || (key == 'p'))
			//{
			//	//Los efectos de sonido crean la instancia cuando se reproduce su evento
			//	FMOD::Studio::EventInstance* eventInstance = NULL;
			//	LowLevelSystem::ERRCHECK(pasosDescription->createInstance(&eventInstance));

			//	LowLevelSystem::ERRCHECK(eventInstance->start());

			//	// Release will clean up the instance when it completes
			//	LowLevelSystem::ERRCHECK(eventInstance->release());
			//}

			if ((key == 'O') || (key == 'o')) {
				LowLevelSystem::ERRCHECK(pasosInstance->start());
			}

			else if ((key == 'I') || (key == 'i')) {
				LowLevelSystem::ERRCHECK(pasosInstance->stop(FMOD_STUDIO_STOP_IMMEDIATE));
			}

			else if ((key == 'U') || (key == 'u'))
			{
				if (velocity < 10)
					velocity++;

				LowLevelSystem::ERRCHECK(pasosInstance->setParameterValue("Velocidad", velocity));
			}

			else if ((key == 'J') || (key == 'j'))
			{
				if (velocity > 0)
					velocity--;

				LowLevelSystem::ERRCHECK(pasosInstance->setParameterValue("Velocidad", velocity));
			}

			else if ((key == 'Y') || (key == 'y'))
			{
				if (recinto < 1.0f)
					recinto += 0.1f;

				LowLevelSystem::ERRCHECK(pasosInstance->setParameterValue("Recinto", recinto));
			}

			else if ((key == 'H') || (key == 'h'))
			{
				if (recinto > 0.0f)
					recinto -= 0.1f;

				LowLevelSystem::ERRCHECK(pasosInstance->setParameterValue("Recinto", recinto));
			}

			//SALIR DE LA APLICACIÓN
			else if ((key == 'Q') || (key == 'q'))
				break;

		}

		LowLevelSystem::ERRCHECK(system->update());
	}

	LowLevelSystem::ERRCHECK(pasosBank->unload());
	LowLevelSystem::ERRCHECK(stringsBank->unload());
	LowLevelSystem::ERRCHECK(masterBank->unload());

	LowLevelSystem::ERRCHECK(system->release());
}


#pragma endregion FMOD_STUDIO

int main()
{
	//SimplePlayer();
	//SimplePiano();
	Hoja2();
	//DSPExample();
	//ChannelGroup();
	//FMOD_STUDIO_EXAMPLE();
	return 0;
}


