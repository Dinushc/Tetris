#pragma once
#include <vector>
#include <raylib.h>

class Sounds
{
public:
    Sounds();
    ~Sounds();
    void PlayRotateSound();
    void PlayClearSound();
    Music music;
    Sound rotateSound;
    Sound clearSound;
};