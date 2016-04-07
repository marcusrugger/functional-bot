#ifndef CONTROLLER_PIN_H
#define CONTROLLER_PIN_H

#include <Arduino.h>


class AnalogPinReader
{
public:

    AnalogPinReader(uint8_t pinNumber) : _pinNumber(pinNumber) {}

    uint16_t operator()(void) const
    { return analogRead(_pinNumber); }

private:

    uint8_t _pinNumber;

};


class DigitalPin
{
public:

    DigitalPin(uint8_t pinNumber, bool pullup = false)
    :   _pin(pinNumber),
        _pullup(pullup)
    {
        setMode(OUTPUT);
    }


    void operator()(bool value)
    {
        setWriteMode();
        digitalWrite(_pin, value ? HIGH : LOW);
    }

    bool operator()(void)
    {
        setReadMode();
        return digitalRead(_pin) == HIGH;
    }

    unsigned long readPulse(bool state, unsigned long timeout)
    {
        setMode(INPUT);
        return pulseIn(_pin, state ? HIGH : LOW, timeout);
    }


private:

    uint8_t _pin;
    uint8_t _mode;
    bool _pullup;

    void setMode(uint8_t mode)
    {
        _mode = mode;
        pinMode(_pin, mode);
    }

    void setReadMode(void)
    {
        if (OUTPUT == _mode)
            setMode(pullupMode());
    }

    void setWriteMode(void)
    {
        if (OUTPUT != _mode)
            setMode(OUTPUT);
    }

    int pullupMode(void)
    {
        return _pullup ? INPUT_PULLUP : INPUT;
    }

};


#endif
