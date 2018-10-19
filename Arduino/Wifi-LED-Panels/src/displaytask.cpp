#include "displaytask.hpp"
#include "letters.h"

#include <LEDMatrixDriver.hpp>

#include <functional>

using namespace Tasks;
using namespace std;


Strip toStrip(char** x)
{
    int len = strlen(x[0]);
    Strip s = Strip(len, vector<bool>(8, false));
    for (int i = 0; i < len; ++i)
        for (int j = 0; j < 8; ++j)
            s[i][j] = (x[7-j][i] == '*');
    return s;
}

void toGlyph(const char glyph[5], char x[8][5])
{
    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 5; ++j)
            x[i][j] = ( (glyph[j]&(1<<i)) ? '*' : ' ');
    }
}

Strip fromWord(const string& word)
{
    Strip s = Strip(word.length()*6, vector<bool>(8, false));

    for (int k = 0; k < word.length(); ++k)
    {
        char c = word[k];
        char glyph[8][5];
        toGlyph(ASCII[c - 32], glyph);
        for (int i = 0; i < 8; ++i){
            for (int j = 0; j < 5; ++j)
                s[ k*6 + j ][i] = (glyph[7-i][j] == '*');
        }
    }
    return s;
}

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
   m_lmd(LEDMATRIX_SEGMENTS, LEDMATRIX_CS_PIN)
{
   m_lmd.setEnabled(true);
   m_lmd.setIntensity(LEDMATRIX_INTENSITY);

   m_text = fromWord(" 1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM,./;'[]{}:\"<>?!@#$%^&*()\\|");
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

void DisplayTask::setText(const string& text)
{
    m_text = fromWord(text);
}

//! Update display
void DisplayTask::execute()
{
   m_lmd.clear();
   
   Strip img = vector<vector<bool>>(32, vector<bool>(8, false));
   static int offset = 0;
   //setPixels(toStrip(x), offset);
   setPixels(m_text, -offset);

   delay(75);
   offset++;
   
   m_lmd.display();
}

} // namespace Tasks
