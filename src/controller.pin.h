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


class BaseAnalogPinReader
{
public:

    virtual ~BaseAnalogPinReader(void) {}

    virtual int16_t readPin(void) const = 0;
    virtual BaseAnalogPinReader *clone(void) const = 0;

};


class ControllerPin : public BaseAnalogPinReader
{
public:

    ControllerPin(uint8_t pin) : _pin(pin) {}

    int16_t readPin(void) const
    { return analogRead(_pin); }

    BaseAnalogPinReader *clone(void) const
    { return new ControllerPin(_pin); }

private:

    uint8_t _pin;

};


class DigitalPinWriter
{
public:

    virtual ~DigitalPinWriter() {}

    virtual void setLow(void) = 0;
    virtual void setHigh(void) = 0;
    virtual void set(bool value) = 0;

};


class DigitalPinReader
{
public:

    virtual ~DigitalPinReader() {}

    virtual bool get(void) = 0;
    virtual unsigned long readPulse(bool state, unsigned long timeout) = 0;

};


class DigitalPin : public DigitalPinWriter,
                   public DigitalPinReader 
{
public:

    virtual DigitalPin *clone(void) = 0;

};


class ControllerDigitalPin : public DigitalPin
{
public:

    ControllerDigitalPin(uint8_t pin, bool pullup = false)
    :   _pin(pin),
        _pullup(pullup)
    { setMode(OUTPUT); }

    ControllerDigitalPin(const ControllerDigitalPin &src)
    :   _pin(src._pin),
        _mode(src._mode),
        _pullup(src._pullup)
    {}

    void setLow(void)
    { setWriteMode(); digitalWrite(_pin, LOW); }

    void setHigh(void)
    { setWriteMode(); digitalWrite(_pin, HIGH); }

    void set(bool value)
    { value ? setHigh() : setLow(); }

    bool get(void)
    { setReadMode(); return digitalRead(_pin) == HIGH; }

    unsigned long readPulse(bool state, unsigned long timeout)
    { setMode(INPUT); return pulseIn(_pin, state ? HIGH : LOW, timeout); }

    DigitalPin *clone(void)
    { return new ControllerDigitalPin(*this); }


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


class DigitalPinFunctor
{
public:

    DigitalPinFunctor(uint8_t pinNumber, bool pullup = false)
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
