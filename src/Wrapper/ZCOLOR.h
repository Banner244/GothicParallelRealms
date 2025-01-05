#pragma once

#include <iostream>
#include <string> 

class ZCOLOR {
    private:
        unsigned char color[4];

    public:

        // Wrapper für den ursprünglichen Konstruktor
        void initialize(int param_1);

        void initialize();

        // Methode zum Ausgeben der Farbwerte
        std::string getColor();
};

/*

void UndefinedFunction_006e1860(void)

{
  DAT_008dcdba = 0xff;
  DAT_008dcdb9 = 0xff;
  GFX_WHITE = (zCOLOR)0xff;
  DAT_008dcdbb = 0xff;
  DAT_008dcb4a = 0xff;
  DAT_008dcb49 = 0xff;
  GFX_YELLOW = (zCOLOR)0x0;
  DAT_008dcb4b = 0xff;
  DAT_008dcba6 = 0xff;
  DAT_008dcba5 = 0xff;
  GFX_LYELLOW = (zCOLOR)0xe0;
  DAT_008dcba7 = 0xff;
  zCOLOR::zCOLOR(&GFX_GOLD,0xff,0xd7,'\0',0xff);
  zCOLOR::zCOLOR(&GFX_ORANGE,0xff,0x80,'\0',0xff);
  zCOLOR::zCOLOR(&GFX_DORANGE,0xff,0x8c,'\0',0xff);
  zCOLOR::zCOLOR(&GFX_CARROT,0xed,0x91,'!',0xff);
  zCOLOR::zCOLOR(&GFX_RED,0xff,'\0','\0',0xff);
  zCOLOR::zCOLOR(&GFX_DRED,0xff,'c','G',0xff);
  zCOLOR::zCOLOR(&GFX_PINK,0xff,0xc0,0xcb,0xff);
  zCOLOR::zCOLOR(&GFX_LPINK,0xff,0xb6,0xc1,0xff);
  zCOLOR::zCOLOR(&GFX_DPINK,0xff,'\x14',0x93,0xff);
  zCOLOR::zCOLOR(&GFX_MAGENTA,0xff,'\0',0xff,0xff);
  zCOLOR::zCOLOR(&GFX_ORCHID,0xda,'p',0xd6,0xff);
  zCOLOR::zCOLOR(&GFX_PURPLE,0xa0,' ',0xf0,0xff);
  zCOLOR::zCOLOR(&GFX_VIOLET,0x8f,'^',0x99,0xff);
  zCOLOR::zCOLOR(&GFX_CYAN,'\0',0xff,0xff,0xff);
  zCOLOR::zCOLOR(&GFX_AQUA,'\x7f',0xff,0xd4,0xff);
  zCOLOR::zCOLOR(&GFX_GREEN,'\0',0xff,'\0',0xff);
  zCOLOR::zCOLOR(&GFX_DGREEN,'\0','d','\0',0xff);
  zCOLOR::zCOLOR(&GFX_PALEGREEN,0x98,0xfb,0x98,0xff);
  zCOLOR::zCOLOR(&GFX_OLIVE,';','^','+',0xff);
  zCOLOR::zCOLOR(&GFX_BLUE,'\0','\0',0xff,0xff);
  zCOLOR::zCOLOR(&GFX_LBLUE,0xad,0xd8,0xe6,0xff);
  zCOLOR::zCOLOR(&GFX_MBLUE,'\0','\0',0xcd,0xff);
  zCOLOR::zCOLOR(&GFX_INDIGO,'\b','.','T',0xff);
  zCOLOR::zCOLOR(&GFX_DBLUE,'\0','\0',0x80,0xff);
  zCOLOR::zCOLOR(&GFX_SKY,0x87,0xce,0xeb,0xff);
  zCOLOR::zCOLOR(&GFX_STEEL,'F',0x82,0xb4,0xff);
  zCOLOR::zCOLOR(&GFX_BROWN,0x80,'*','*',0xff);
  zCOLOR::zCOLOR((zCOLOR *)&DAT_008dcb5c,0x87,'B','\x1f',0xff);
  zCOLOR::zCOLOR(&GFX_DOCHRE,'s','=','\x1a',0xff);
  zCOLOR::zCOLOR(&GFX_BEIGE,0xa3,0x94,0x80,0xff);
  zCOLOR::zCOLOR(&GFX_FLESH,0xff,'}','@',0xff);
  zCOLOR::zCOLOR(&GFX_KHAKI,0xf0,0xe6,0x8c,0xff);
  zCOLOR::zCOLOR(&GFX_GREY,0xc0,0xc0,0xc0,0xff);
  zCOLOR::zCOLOR(&GFX_LGREY,0xd3,0xd3,0xd3,0xff);
  zCOLOR::zCOLOR(&GFX_COLDGREY,0x80,0x8a,0x87,0xff);
  zCOLOR::zCOLOR(&GFX_WARMGREY,0x80,0x80,'i',0xff);
  zCOLOR::zCOLOR(&GFX_BLACK,'\0','\0','\0',0xff);
  zCOLOR::zCOLOR(&GFX_IVORY,')','$','!',0xff);
  return;
}

*/