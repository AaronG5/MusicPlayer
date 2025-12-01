#include "player.h"
#include <SDL.h>
#include <QTimer>
#include <QDebug>


Player::Player(QObject *parent)
    : QObject{parent}
{}

void Player::playSong() {
    const char* fileName = "/Users/aarongandzumian/Code/QT/MusicPlayer/Let It Happen.wav";

    if(SDL_Init(SDL_INIT_AUDIO) < 0) {
        qWarning() << "SDL_Init failed:" << SDL_GetError();
        return;
    }

    SDL_AudioSpec wavSpec;
    Uint8* wavBuffer;
    Uint32 wavLength;

    if(SDL_LoadWAV(fileName, &wavSpec, &wavBuffer, &wavLength) == NULL) {
        qWarning() << "SDL_LoadWAV failed: " << SDL_GetError();
        SDL_Quit();
        return;
    }

    SDL_AudioDeviceID deviceID = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);

    if(deviceID == 0) {
        qWarning() << "SDL_OpenAudioDevice failed: " << SDL_GetError();
        SDL_FreeWAV(wavBuffer);
        SDL_Quit();
        return;
    }

    // int success = SDL_QueueAudio(deviceID, wavBuffer, wavLength);
    if(SDL_QueueAudio(deviceID, wavBuffer, wavLength) < 0) {
        qWarning() << "SDL_QueueAudio failed: " << SDL_GetError();
    }

    SDL_PauseAudioDevice(deviceID, 0);

    int durationMs = 0;
    if(wavSpec.channels > 0) {
        durationMs = (wavLength / (wavSpec.freq * wavSpec.channels * (SDL_AUDIO_BITSIZE(wavSpec.format) / 8))) * 1000;
    }

    int durationSeconds = durationMs / 1000;
    int durationMinutes = durationSeconds / 60;
    durationSeconds -= durationMinutes * 60;

    qDebug() << "Song duration:"<< Qt::endl << "Miliseconds: " << durationMs << Qt::endl << "Normal format: " << durationMinutes << "min." << durationSeconds << "s.";

    QTimer::singleShot(durationMs, [deviceID, wavBuffer]() {
        SDL_CloseAudioDevice(deviceID);
        SDL_FreeWAV(wavBuffer);
        SDL_Quit();
        qDebug() << "Playback finished and cleaned up";
    });
}
