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
   m_speed(50),
   m_snake(32, 8, analogRead(0)),
   m_solver(&m_snake),
   m_mode(SnakeAuto)
//   m_parola(MD_MAX72XX::ICSTATION_HW, LEDMATRIX_CS_PIN, 4)
{
   m_lmd.setEnabled(true);
   m_lmd.setIntensity(LEDMATRIX_INTENSITY);

   setFont(Font::FONT7x5);

//   m_parola.begin();  // Start Parola

//   m_parola.displayText("", PA_LEFT, 1000, 0, PA_SCROLL_LEFT, PA_SCROLL_LEFT);
   setText("1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM,./;'[]{}:\"<>?!@#$%^&*()\\|");
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
//    char buff[text.length()+1];
//    text.toCharArray(buff, text.length()+1);

    m_text = text;
    m_strip = fromWord(text);
//    int speed;
//    if (m_speed == 0)
//        speed = 1000000;
//    else
//        speed = 2000/m_speed;
//
//    m_parola.setTextBuffer(buff);
//    m_parola.setSpeed(speed);
}

void DisplayTask::setSpeed(int speed)
{
    m_speed = speed;
}

void DisplayTask::setMode(DisplayMode m)
{
    m_mode = m;
}

//! Update display
void DisplayTask::execute()
{
    m_lmd.clear();
    
    switch (m_mode){
        case Image:
        break;
        case Text:
        {
            static int offset = 0;

            if (m_speed == 0){
                delay(1000);
            } else {
                delay(1000/abs(m_speed)); 
                offset += (( m_speed > 0 ) ? 1 : -1);
            }
    
            setPixels(m_strip, -offset);
        }
        break;
        case SnakeManual:
        {
            delay(100);
            Strip snake_board = fromSnake();
            setPixels(snake_board);
            m_snake.move();
        }
        break;
        case SnakeAuto:
        {
            delay(100);
            Strip snake_board = fromSnake();
            setPixels(snake_board);
            m_solver.move();
        }
        break;
    }
   
    m_lmd.display();

//    if (m_parola.displayAnimate()) // If finished displaying message
//    {
//        m_parola.displayReset();  // Reset and display it again
//    }
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

Strip DisplayTask::fromSnake()
{
    Strip s = Strip(32, vector<bool>(8, false));

    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 32; ++j){
            Snake::Cell c(j, i);
            if (m_snake.cellFood(c))
                s[j][i] = true;
            else
                s[j][i] = !m_snake.cellFree(c);
        }
    }
    return s;
}

void DisplayTask::setSnakeDir(int d){
    m_snake.setDir(static_cast<Snake::Dir>(d));
}

} // namespace Tasks
