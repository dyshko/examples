#include "displaytask.hpp"

#include "fonts/font7by5.h"
#include "fonts/font8x8_basic.h"

#include <LEDMatrixDriver.hpp>

#include <functional>

using namespace Tasks;
using namespace std;


namespace Tasks {

const int DisplayTask::LEDMATRIX_WIDTH = 31;
const int DisplayTask::LEDMATRIX_HEIGHT = 7;
const int DisplayTask::LEDMATRIX_SEGMENTS = 4;
const int DisplayTask::LEDMATRIX_INTENSITY = 5;
const int DisplayTask::LEDMATRIX_CS_PIN = 16;
const unsigned long DisplayTask::POLL_DELAY_MS = 100;

//! Initializes the LED Matrix display.
DisplayTask::DisplayTask():
   Task(POLL_DELAY_MS , TASK_FOREVER, std::bind(&DisplayTask::execute, this)),
   m_lmd(LEDMATRIX_SEGMENTS, LEDMATRIX_CS_PIN),
   m_speed(10)
{
   m_lmd.setEnabled(true);
   m_lmd.setIntensity(LEDMATRIX_INTENSITY);

   setFont(Font::FONT8x8);

   m_text = " 1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM,./;'[]{}:\"<>?!@#$%^&*()\\|";
   m_strip = fromWord(m_text);
}

void DisplayTask::setPixels(const Strip& img, int offset)
{
    int img_width = img.size();
    for (int i = 0; i < 32; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            int x_img = (img_width + (i - offset)%img_width)%img_width;
            bool light = ((0 <= x_img && x_img < img_width) ? img[x_img][j] : false); 
            m_lmd.setPixel( 8*(i/8) + (7-(i%8)), j, light);
        }
    }
}

void DisplayTask::setText(const String& text)
{
    m_text = text;
    m_strip = fromWord(text);
}

void DisplayTask::setSpeed(int speed)
{
    m_speed = speed;
}

//! Update display
void DisplayTask::execute()
{
    m_lmd.clear();
   
    static int offset = 0;

    if (m_speed == 0){
        delay(1000);
    } else{
        delay(1000/abs(m_speed)); 
        offset += (( m_speed > 0 ) ? 1 : -1);
    }
    
    setPixels(m_strip, -offset);
    m_lmd.display();
}

void DisplayTask::setFont(Font f)
{
    switch(f)
    {
        case FONT7x5:
            createBitmaps(font7by5, false);
            m_fontWidth = 5;
        break;

        case FONT8x8:
            createBitmaps(font8x8_basic, true);
            m_fontWidth = 8;
        break;

        default:
        break;
    }

    m_strip = fromWord(m_text);
}

void DisplayTask::createBitmaps(const char font[][8], bool transpose)
{
    for (int c = 0; c < 128; ++c){
        for (int i = 0; i < 8; ++i){
            for (int j = 0; j < 8; ++j)
                if (transpose)
                    m_fontBitmaps[c][7-j][i] = ( (font[c][j]&(1<<i)) ? '*' : ' ');
                else
                    m_fontBitmaps[c][7-i][j] = ( (font[c][j]&(1<<i)) ? '*' : ' ');
        }
    }
}


Strip DisplayTask::fromWord(const String& word)
{
    Strip s = Strip(word.length()*(m_fontWidth+1), vector<bool>(8, false));

    for (int k = 0; k < word.length(); ++k)
    {
        int c = word[k];
        for (int i = 0; i < 8; ++i){
            for (int j = 0; j < m_fontWidth; ++j)
                s[ k*(m_fontWidth+1) + j ][i] = (m_fontBitmaps[c][i][j] == '*');
        }
    }
    return s;
}

} // namespace Tasks
