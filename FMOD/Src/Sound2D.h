#ifndef __Sound2D_h_
#define __Sound2D_h_
#include "Sound.h"

// Sonido 2D
class Sound2D : public Sound{
public:
	Sound2D(std::string _name, FMOD_MODE mode = NULL, FMOD_CREATESOUNDEXINFO *exinfo = nullptr);
	~Sound2D();
};
#endif // #ifndef __Sound2D_h_
