#pragma once

using namespace std;

#define _TASK_SLEEP_ON_IDLE_RUN
#define _TASK_STD_FUNCTION
#include <TaskSchedulerDeclarations.h>
#include <LEDMatrixDriver.hpp>

#include <vector>

#include <functional>


namespace Tasks {

using Strip = vector<vector<bool>>;

class DisplayTask : public Task
{
public:
   explicit DisplayTask();
   ~DisplayTask() {};

   // Disallow copy-ing
	DisplayTask(const DisplayTask& other) = delete;
	DisplayTask(DisplayTask&& other) = delete;
	DisplayTask& operator=(const DisplayTask& other) = delete;

   void setText(const string& text);
   void execute();

private:
   static const int LEDMATRIX_WIDTH;
   static const int LEDMATRIX_HEIGHT;
   static const int LEDMATRIX_SEGMENTS;
   static const int LEDMATRIX_INTENSITY;
   static const int LEDMATRIX_CS_PIN;
   static const unsigned long POLL_DELAY_MS;

   LEDMatrixDriver m_lmd;

   Strip m_text;

   void setPixels(const vector<vector<bool>>&, int offset = 0);

};

} // namespace Tasks
