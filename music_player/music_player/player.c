#include <SDL.h>
#include <stdio.h>
#include <SDL_audio.h>
#include <windows.h>


SDL_AudioDeviceID
LoadAudioDevice(char* path) {
	SDL_AudioSpec want;
	SDL_AudioDeviceID deviceId;
	Uint32 wav_length;
	Uint8 *wav_buffer;

	if (SDL_LoadWAV(path, &want, &wav_buffer, &wav_length) == NULL) {
		SDL_Log("Could not open audio: %s\n", SDL_GetError());
		exit(-1);
		}
	// Use this function to open a specific audio device.
	deviceId = SDL_OpenAudioDevice(NULL, 0, &want, NULL, 0);
	if (deviceId == 0) {
		SDL_Log("Failed to open audio: %s", SDL_GetError());
		exit(-1);
	}
	// Use this function to queue more audio on non-callback devices.
	if (SDL_QueueAudio(deviceId, wav_buffer, wav_length) < 0) {
		SDL_Log("Couldn't queue audio: %s\n", SDL_GetError());
		exit(-1);
	}

	return deviceId;
}


void
audioPlay(SDL_AudioDeviceID deviceId) {
	SDL_PauseAudioDevice(deviceId, 0);
}


void
audioPause(SDL_AudioDeviceID deviceId) {
	SDL_PauseAudioDevice(deviceId, 1);
}


int 
main(int argc, char* args[]) {
	//init
	if (SDL_Init(SDL_INIT_AUDIO) != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return 1;
	}

	char *musicPath = "resource/music/song.wav";

	// load audio
	SDL_AudioDeviceID deviceId = LoadAudioDevice(musicPath);

	// play audio
	audioPlay(deviceId);

	//waiting 10 min
	SDL_Delay(10000);

	// stop audio
	audioPause(deviceId);

	//quit
	//SDL_Quit();
	return 0;
}

