#ifndef APP_HPP
#define APP_HPP

#include <SFML/Graphics.hpp>        //for RenderWindow, RectangleShape, Font and Text
#include <SFML/Audio.hpp>           //for Sound and SoundBuffer
#include "Emulator.hpp"             //the Emulator


class App
{
    public:
        App();
        void run();                 //runs the Game loop

    private:
        void handleEvents();        //takes input and does stuff with it
        void update();              //updates the emulator and other stuff
        void render();              //takes the emulator's graphics data and renders it, as well as controlling the sound

        sf::RenderWindow mWindow;   //the window...duh...
        sf::Font mFont;             //the font...duh...
        sf::SoundBuffer beepBuf;
        sf::Sound beep;
        bool lastSound = false;     //tells whether sound was playing on the last render



        Emulator mEmulator;         //the glorious Emulator
};


#endif // APP_HPP
