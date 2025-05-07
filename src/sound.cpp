#include "sound.h"

Sound* Sound::instance()
{
    static Sound instance;

    return &instance;
}

bool Sound::initialize(void)
{

    if(SDL_Init(SDL_INIT_AUDIO) == -1) 
    {
        printf("SDL_Init: %s\n", SDL_GetError());

        return false;
    }

    if(Mix_Init(MIX_INIT_MP3|MIX_INIT_OGG) == -1)
    {
        printf("Mix_Init: %s\n", Mix_GetError());

        return false;
    }

    if (Mix_OpenAudio(44100, AUDIO_S16, 2, 1024) == -1)
    {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());

        return false;
    }

    return true;
}

void Sound::load_sounds(vector<string> files, enum sound_type st)
{
    for (int i = 0; i < (int)files.size(); i++)
    {
        const char* file_name = files[i].c_str();

        if(st == sound_type::efx)
        {
            Mix_Chunk* sample = Mix_LoadWAV(file_name);

            if(sample != nullptr)
            {
                printf("File loaded: %s\n", file_name);
                this->sound_efxs.push_back(sample);
            }
            else
            {
                printf("Mix_sample load fail: %s\n", Mix_GetError());
            }
        }

        if(st == sound_type::music)
        {
            Mix_Music* music = Mix_LoadMUS(file_name);

            if(music != nullptr)
            {
                printf("File loaded: %s\n", file_name);
                this->musics.push_back(music);
            }
            else
            {
                printf("Mix_music load fail: %s\n", Mix_GetError());
            }
        }
    }

    if(st == sound_type::efx)
    {
        Mix_AllocateChannels((int)this->sound_efxs.size());
    }
}

void Sound::free_sounds()
{
    for (int i = 0; i < (int)this->sound_efxs.size(); i++)
    {
        Mix_FreeChunk(this->sound_efxs[i]);
    }

    for (int i = 0; i < (int)this->musics.size(); i++)
    {
        Mix_FreeMusic(this->musics[i]);
    }

    this->sound_efxs.clear();
    this->musics.clear();

    Mix_CloseAudio();
    Mix_Quit();
}

void Sound::play_music(int index, int times, int volume)
{
    if(index < 0 || index >= (int)musics.size()) return;

    if(Mix_FadeInMusic(this->musics[index], times, 2000))
    {
        Mix_VolumeMusic(volume);
    }
}

/*
Direction in relation to forward from 0 to 360 degrees. Larger angles will be reduced to this range using angles % 360.
0 = directly in front.
90 = directly to the right.
180 = directly behind.
270 = directly to the left.

The distance from the listener, from 0(near/loud) to 255(far/quiet).
*/
void Sound::play_efx(int index, int times, int angle, float distance)
{
    if(index < 0 || index >= (int)sound_efxs.size()) return;

    int max_distance =  INT_MAX;
    distance = map_values(distance, 0, max_distance, 255, 0);

    if(Mix_PlayChannel(0, this->sound_efxs[index], times))
    {
        Mix_SetPosition(index, angle, (int)floor(distance));
    }
}

void Sound::update_efx(int index, int angle, float distance)
{
    int max_distance =  INT_MAX;
    distance = map_values(distance, 0, max_distance, 255, 0);

    if(Mix_UnregisterAllEffects(index))
    {
        Mix_SetPosition(0, angle, (int)floor(distance));
    }
}
