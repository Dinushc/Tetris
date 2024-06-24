#include "sounds.h"

Sounds::Sounds()
{
    music = LoadMusicStream("Sounds/music.mp3");
    PlayMusicStream(music);
    rotateSound = LoadSound("Sounds/rotate.mp3");
    clearSound = LoadSound("Sounds/clear.mp3");
}

Sounds::~Sounds()
{
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadMusicStream(music);
}

void Sounds::PlayRotateSound(){
    PlaySound(rotateSound);
}

void Sounds::PlayClearSound(){
    PlaySound(clearSound);
}