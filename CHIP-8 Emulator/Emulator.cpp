#include "Emulator.hpp"
#include <iostream>
#include <cstring>

unsigned char font[80] =                    //the font data for the emulator
{
  0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
  0x20, 0x60, 0x20, 0x20, 0x70, // 1
  0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
  0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
  0x90, 0x90, 0xF0, 0x10, 0x10, // 4
  0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
  0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
  0xF0, 0x10, 0x20, 0x40, 0x40, // 7
  0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
  0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
  0xF0, 0x90, 0xF0, 0x90, 0x90, // A
  0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
  0xF0, 0x80, 0x80, 0x80, 0xF0, // C
  0xE0, 0x90, 0x90, 0x90, 0xE0, // D
  0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
  0xF0, 0x80, 0xF0, 0x80, 0x80  // F
};


void Emulator::load(std::string file)       //to-do: load the rom
{
    reset();


}

void Emulator::reset()
{
    for (int i=0;i<64;i++)
        for (int j=0;j<32;j++)
            gfx[i][j] = false;

    pc = 0x200;
    opcode = 0;
    I = 0;
    sp = 0;
    lastKey = 0;
    newKey = false;
    for (int i=0;i<16;i++)
    {
        V[i] = 0;
        st[i] = 0;
        keys[i] = false;
    }

    memset(memory, sizeof(memory), 0);

    for (int i=0;i<80;i++)
        memory[i] = font[i];


    delayTimer = 0;
    soundTimer = 0;


    //gfx[0][0] = true;
    //gfx[63][31] = true;
}

bool Emulator::getGFX(int x, int y)
{
    return gfx[x][y];
}

bool Emulator::getSound()
{
    return soundTimer>0;
}

void Emulator::sendInput(bool value, unsigned short key)
{
    if (key>15)
    {
        std::cout<<"Invalid key"<<std::endl;
        return;
    }

    if (keys[key] != value && value==true)
    {
        newKey = true;
        lastKey = key;
    }

    keys[key] = value;
}

void Emulator::tick()
{
    opcode = memory[pc]<<8 | memory[pc+1];          //get the opcode


    switch(opcode && 0xF000)                        //and do stuff with it
    {
                                                    //to-do: write the actual emulator
    }

    if (delayTimer>0)                               //update the timers
    {
        delayTimer--;
    }

    //std::cout<<soundTimer<<std::endl;
    if (soundTimer>0)
    {
        soundTimer--;
    }


    newKey = false;                                 //update the newKey;
}
