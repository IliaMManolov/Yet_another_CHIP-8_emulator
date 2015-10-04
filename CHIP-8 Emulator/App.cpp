#include "App.hpp"

App::App()
: mWindow(sf::VideoMode(640, 320), "Yet Another CHIP-8 Emulator Alpha")     //Loads stuff up
{
    mWindow.setVerticalSyncEnabled(true);               //Vsync is nice

    beepBuf.loadFromFile("Resources/beep.ogg");
    beep.setBuffer(beepBuf);
    beep.setLoop(true);                                 //the beep may play for longer than the audio file

    mEmulator.load("Resources/PONG2");                  //loads an example game

    mFont.loadFromFile("Resources/akashi.ttf");


}

void App::run()
{
    sf::Clock timeSinceLastUpdate;                          //with this I guarantee that I get exactly 60 ticks per second
    while (mWindow.isOpen())
    {
        handleEvents();
        if (timeSinceLastUpdate.getElapsedTime()>=sf::seconds(1.f/60))
        {
            timeSinceLastUpdate.restart();
            update();
        }
        render();
    }
}

void App::handleEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)                    //I use events to close the window and for debug stuff
        {
            mWindow.close();
        }

        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::P)
            {
                mEmulator.flipGFX(0, 0);
            }
            if (event.key.code == sf::Keyboard::L)
            {
                mEmulator.flipGFX(63, 31);
            }
            if (event.key.code == sf::Keyboard::M)
            {
                mEmulator.setSound(60);
            }
        }
    }

    mEmulator.sendInput(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1), 1);         //Updating the emulator's input with
    mEmulator.sendInput(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2), 2);         //SFML's real-time input
    mEmulator.sendInput(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3), 3);
    mEmulator.sendInput(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4), 12);
    mEmulator.sendInput(sf::Keyboard::isKeyPressed(sf::Keyboard::Q), 4);
    mEmulator.sendInput(sf::Keyboard::isKeyPressed(sf::Keyboard::W), 5);
    mEmulator.sendInput(sf::Keyboard::isKeyPressed(sf::Keyboard::E), 6);
    mEmulator.sendInput(sf::Keyboard::isKeyPressed(sf::Keyboard::R), 13);
    mEmulator.sendInput(sf::Keyboard::isKeyPressed(sf::Keyboard::A), 7);
    mEmulator.sendInput(sf::Keyboard::isKeyPressed(sf::Keyboard::S), 8);
    mEmulator.sendInput(sf::Keyboard::isKeyPressed(sf::Keyboard::D), 9);
    mEmulator.sendInput(sf::Keyboard::isKeyPressed(sf::Keyboard::F), 14);
    mEmulator.sendInput(sf::Keyboard::isKeyPressed(sf::Keyboard::Z), 10);
    mEmulator.sendInput(sf::Keyboard::isKeyPressed(sf::Keyboard::X), 0);
    mEmulator.sendInput(sf::Keyboard::isKeyPressed(sf::Keyboard::C), 11);
    mEmulator.sendInput(sf::Keyboard::isKeyPressed(sf::Keyboard::V), 15);
}

void App::update()
{
    mEmulator.tick();                       //it only triggers a tick...for now
}

void App::render()                                              //renders all the pixels
{
    sf::RectangleShape hue;
    sf::Vector2f hueSize;
    hueSize.x = mWindow.getSize().x/64;                         //since I later want to make a menu with resolution settings
    hueSize.y = mWindow.getSize().y/32;                         //I keep the pixel size flexible
    hue.setSize(sf::Vector2f(hueSize.x, hueSize.y));

    mWindow.clear();
    for (int i=0;i<64;i++)
        for (int j=0;j<32;j++)
        {
            hue.setPosition(i*hueSize.x, j*hueSize.y);
            if (mEmulator.getGFX(i, j))
                mWindow.draw(hue);
        }
    mWindow.display();

    if (mEmulator.getSound()&& lastSound == false)                      //The sound is here...
    {
        beep.play();
        lastSound = true;
    }
    else if (mEmulator.getSound()==false && lastSound == true)
    {
        beep.pause();
    }

    lastSound = mEmulator.getSound();
}
