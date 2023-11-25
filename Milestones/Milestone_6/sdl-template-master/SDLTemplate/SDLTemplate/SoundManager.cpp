#include "SoundManager.h"

/*--------------------------------------------------------------------------------------------------------------------*/

SoundManager::SoundManager()
{
	music = NULL;
}

/*--------------------------------------------------------------------------------------------------------------------*/

SoundManager::~SoundManager()
{

}

/*--------------------------------------------------------------------------------------------------------------------*/

SoundManager* SoundManager::getInstance()
{
	static SoundManager* soundManager = new SoundManager();
	return soundManager;
}

/*--------------------------------------------------------------------------------------------------------------------*/

Mix_Chunk* SoundManager::loadSound(const char* filename)
{
	Mix_Chunk* sound = getInstance()->getLoadedSound(filename);
	if (sound == NULL)
	{
		sound = Mix_LoadWAV(filename);

		SoundClip clip;
		clip.fileName = filename;
		clip.sound = sound;
		getInstance()->loadedSounds.push_back(clip);
	}
	return sound;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void SoundManager::playSound(const char* filename, int channel)
{
	Mix_Chunk* sound = getInstance()->getLoadedSound(filename);
	if (sound == NULL) loadSound(filename);

	sound = getInstance()->getLoadedSound(filename);
	Mix_PlayChannel(channel, sound, 0);
}

/*--------------------------------------------------------------------------------------------------------------------*/

void SoundManager::playSound(Mix_Chunk* sound, int channel)
{
	if (sound == NULL)
	{
		std::cout << "Warning: Attempting to play a sound with a null pointer" << std::endl;
		return;
	}
	Mix_PlayChannel(channel, sound, 0);
}

/*--------------------------------------------------------------------------------------------------------------------*/

void SoundManager::loadMusic(const char* filename)
{
	if (getInstance()->music != NULL)
	{
		Mix_HaltMusic();
		Mix_FreeMusic(getInstance()->music);
		getInstance()->music = NULL;
	}

	getInstance()->music = Mix_LoadMUS(filename);
}

/*--------------------------------------------------------------------------------------------------------------------*/

void SoundManager::playMusic(int loop)
{
	if (getInstance()->music == NULL)
	{
		std::cout << "Music is not loaded!" << std::endl;
	}
	Mix_PlayMusic(getInstance()->music, (loop) ? -1 : 0);
}

/*--------------------------------------------------------------------------------------------------------------------*/

Mix_Chunk* SoundManager::getLoadedSound(const char* filename)
{
	for (int i = 0; i < loadedSounds.size(); i++)
	{
		if (loadedSounds[i].fileName == filename)
			return loadedSounds[i].sound;
	}

	return NULL;
}