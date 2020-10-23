/*
  ADE7753CR.h - Library for use with OLED displays.
  Created by Cristian F. Ritter, Octuber 18, 2020.
  Released into the public domain.
*/
#ifndef OLEDCR_h
    #define OLEDCR_h
    #include "Arduino.h"
    #include "SSD1306Wire.h" 

    class OLED
    {
        public:
            void Init(SSD1306Wire* display);
            void ShowMessage(SSD1306Wire* display, char* message);
            void ShowCompleteView(SSD1306Wire* display, char* data);
        private:
    };

#endif
