//
// Created by youssef on 11/05/17.
//

#ifndef MYKEYLOGGER_TIMER_H
#define MYKEYLOGGER_TIMER_H
#include<thread>
#include <chrono>

using namespace std;

class Timer {
    thread Thread;
    bool Alive=false;
    long callNumber = -1L;
    long repeatCount= -1L;
    chrono::milliseconds interval=chrono::milliseconds(0);
    function<void (void)> funct= nullptr;

    void sleepAndRun(){

        this_thread::sleep_for(interval);
        if(Alive) {
          f()();
        }
    }
    void T_func(){

        if(callNumber==Infinite)
            while(Alive)
            {
                sleepAndRun();
            }
        else
        {
            while(repeatCount--)
            {
                sleepAndRun();
            }
        }
    }

public:
    static const long Infinite= -1L;
    Timer(function<void(void)> &f) : funct(f){}
    Timer(function<void(void)> &f, const unsigned long &i, const long repeat = Timer::Infinite):funct(f),
                                                                                                interval(chrono::milliseconds(i)), callNumber(repeat){}
    void start(bool t=true)
    {

        if(isAlive())
            return ;
        Alive=true;
        repeatCount=callNumber;
        if(t)
        {
            //Thread=thread(T_func(),this);
        }
        else
        {
            this->T_func();
        }
    }

    void stop(){

        Alive=false;
        Thread.join();
    }

    bool isAlive(){
        return Alive;
    }

    void _repeatCount(const long r)
    {
        if(Alive) {
            return;
        }
        callNumber=r;
    }

    void setFunction(const function<void(void)> &f)
    {
        this->funct=f;
    }

    long getLeftCount() const{

        return repeatCount;
    }

    long _repeatCount() const {
        return this->callNumber;
    }
    void setInterval(const unsigned long &i)
    {
        if(Alive)
        {
            return;
        }
        interval=chrono::milliseconds(i);
    }

    unsigned long Interval() const {
        return interval.count();
    }

     function<void(void)>  f() const {

        return funct;
    }
};

#endif //MYKEYLOGGER_TIMER_H
