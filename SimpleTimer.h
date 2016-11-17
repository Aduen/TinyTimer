#ifndef TINYTIMER_H
#define TINYTIMER_H

#include "Arduino.h"

typedef struct {
	// pointer to the callback functions
	void(*callback)(uint8_t);
	// delay values
	uint16_t delay;
	// value returned by the millis() function
	// in the previous run() call
	uint32_t prev_millis;
	// number of runs to be executed for each timer
	uint8_t maxRuns;
	// number of executed runs for each timer
	uint8_t numRuns;
	// optional parameter for callback function, default timer_id is used
	uint8_t params;
	// which timers are enabled
	bool enabled;
} timer_call;

class SimpleTimer {

public:
    // maximum number of timers
    const static uint8_t MAX_TIMERS = 10;

    // setTimer() constants
    enum RunType{RUN_FOREVER, RUN_ONCE};

    // constructor
    SimpleTimer();

    // this function must be called inside loop()
    void run();

    // call function f every d milliseconds
    uint8_t setInterval(long d, void(*f_ptr)(uint8_t));

    // call function f once after d milliseconds
    uint8_t setTimeout(long d, void(*f_ptr)(uint8_t));

    // call function f every d milliseconds for n times
    uint8_t setTimer(long d, void(*f_ptr)(uint8_t), uint8_t n, uint8_t param);
    uint8_t setTimer(long d, void(*f_ptr)(uint8_t), uint8_t n);

    // destroy the specified timer
    void deleteTimer(uint8_t numTimer);

    // returns true if the specified timer is enabled
    bool isEnabled(uint8_t numTimer);

    // enables the specified timer
    void enable(uint8_t numTimer);

    // disables the specified timer
    void disable(uint8_t numTimer);

    // enables or disables the specified timer
    // based on its current state
    void toggle(uint8_t numTimer);

    // change the delay of the timer runtime
    void change_delay(uint8_t numTimer, uint16_t d);

    // returns the number of used timers
    uint8_t getNumTimers();

private:
    // in the previous run() call
    timer_call calls[MAX_TIMERS];

    uint8_t num_timers;

    int8_t getAvailableSpot();
};

#endif
