#ifndef EMULATOR_HPP
#define EMULATOR_HPP

#include <string>

class Emulator
{



        unsigned char memory[4096];                     //the emulator's memory
        unsigned short opcode;                          //the current opcode
        unsigned char V[16];                            //the V registers

        unsigned short I;                               //the address register
        unsigned short pc;                              //the program counter
        bool keys[16];                                  //the state of the input
        unsigned short lastKey;                         //the number of the last pressed key
        bool newKey;                                    //a flag telling us if a new key has been pressed

        bool gfx[64][32];                               //the graphics data
        unsigned char delayTimer;                       //obvious
        unsigned char soundTimer;                       //obvious

        unsigned short sp;                              //the stack pointer
        unsigned short st[16];                          //and the stack itself


    public:
        void reset();                                   //resets all variables
        void load(std::string file);                    //calls reset and then loads the ROM at file
        void tick();                                    //goes through one emulation cycle
        void sendInput(bool value, unsigned short key); //updates the emulator's input
        bool getGFX(int x, int y);                      //returns the graphics data at position x, y
        bool getSound();                                //returns whether the sound should be playing or not

        void setSound(int hue)                          //sets the sound to hue/for debug purposes
        {
            soundTimer = hue;
        }
        void flipGFX(int x, int y)                      //flips the pixel at (x, y)/for debug purposes
        {
            gfx[x][y] = !gfx[x][y];
        }
};



#endif // EMULATOR_HPP
