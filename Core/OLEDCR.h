/*
  ADE7753CR.h - Library for use with OLED displays.
  Created by Cristian F. Ritter, Octuber 18, 2020.
  Released into the public domain.
*/
#ifndef OLEDCR_h
    #define OLEDCR_h

    #include "SSD1306Wire.h" 

    class OLED
    {
        public:
           // void Init(int SDApin, int SCKpin);
            void ShowMessage(char* message);
            void ShowCompleteView(char* data);
        private:
    };

#endif
