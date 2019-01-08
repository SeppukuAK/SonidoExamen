#include "AudioGeometry.h"
#include "LowLevelSystem.h"

/*
	directOcclusion; // 0.0 no atenua, 1.0 atenua totalmente
	reverbOcclusion; // atenuacion de la reverberacion
	doubleSided; // atenua por ambos lados o no
	Se crea a geometria del cubo
*/
AudioGeometry::AudioGeometry(int maxPoligons, int maxVertex, float directOcclusion, float reverbOcclusion, bool doubleSided, FMOD_VECTOR * poligons)
{
	geometry = LowLevelSystem::GetInstance()->CreateGeometry(maxPoligons, maxPoligons * maxVertex);

	int polygonIndex; // Indice al poligono generado para referenciarlo despues
	for (int i = 0; i < maxPoligons; i++)
		LowLevelSystem::ERRCHECK(geometry->addPolygon(directOcclusion, reverbOcclusion, doubleSided, maxVertex, &poligons[i], &polygonIndex));
}


AudioGeometry::~AudioGeometry()
{
}
