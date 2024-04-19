#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool checkDays(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t> shiftsDays,
    size_t day,
    size_t scheduledDays
);

bool checkAvailability(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t> shiftsDays,
    size_t day,
    size_t scheduledDays,
    int workerIndex
);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    size_t k = avail[0].size(); // num of workers
    size_t n = avail.size(); // num of days
    vector<size_t> shifts_days(k, 0); // vector to show how many days each worker has worked.
    sched.resize(n);
    for (size_t i = 0; i < n; i++)
    {
        sched[i].assign(dailyNeed, INVALID_ID);
    }
    return checkDays(avail, dailyNeed, maxShifts, sched, shifts_days, 0, 0);
}

bool checkDays(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t> shiftsDays,
    size_t day,
    size_t scheduledDays
)
{
    if (day == avail.size())
    {
        return true;
    }
    if (scheduledDays == dailyNeed) // all days filled go to next
    {
        return checkDays(avail, dailyNeed, maxShifts, sched, shiftsDays, day + 1, 0);
    }
    return checkAvailability(avail, dailyNeed, maxShifts, sched, shiftsDays, day, scheduledDays, 0);
}

// check availability for all workers in this location
bool checkAvailability(const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t> shiftsDays,
    size_t day,
    size_t scheduledDays,
    int workerIndex
)
{
    if (workerIndex == avail[day].size()) // base case: if all the workers are not available return false
    {
        return false;
    }
    // if available, try next day
    if (avail[day][workerIndex] != 0 && shiftsDays[workerIndex] < maxShifts)
    {
        sched[day][scheduledDays] = workerIndex;
        shiftsDays[workerIndex] += 1;
        if (checkDays(avail, dailyNeed, maxShifts, sched, shiftsDays, day, scheduledDays + 1))
        {
            return true;
        }
        // if not available, delete the id and minus the shiftdays for backtracking
        sched[day][scheduledDays] = INVALID_ID;
        shiftsDays[workerIndex] -= 1; // backtrack
    }
    return checkAvailability(avail, dailyNeed, maxShifts, sched, shiftsDays, day, scheduledDays, workerIndex + 1);
}