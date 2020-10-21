/*
  Em construção....
  ADE7753CR.h - Library for use with OLED displays.
  Created by Cristian F. Ritter, Octuber 18, 2020.
  Released into the public domain.
*/
#ifndef OLEDCR.h
    #define OLEDCR.h

    #include "SSD1306Wire.h" 

    class OLED
    {
        public:
            int ChangeView();
            void ShowMessage();
            typedef struct
            {
                

            } Data;
        private:

    };

#endif