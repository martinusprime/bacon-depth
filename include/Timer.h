#ifndef TIMER_H
#define TIMER_H
#include <SFML/Graphics.hpp>
using namespace sf;
class Timer
{
    public:
        Timer();
        virtual ~Timer();
    protected:
    private:
Clock clock; // d�marre le chrono

};

#endif // TIMER_H
