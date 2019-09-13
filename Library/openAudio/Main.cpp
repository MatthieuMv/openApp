/*
** EPITECH PROJECT, 2019
** openApp
** File description:
** Main
*/

#include <openAudio/Audio.hpp>
#include <openApp/Core/Log.hpp>
#include <openApp/Types/Error.hpp>

#include <SDL2/SDL.h>

int main(void)
{
    try {
        SDL_Init(SDL_INIT_TIMER);
        oA::Audio::Initialize();
        auto voice = oA::Audio::OpenVoice();

        SDL_Delay(3000);
        return 0;
    } catch (const oA::Error &e) {
        oA::cerr << e.what() << oA::endl;
        return 84;
    }
}