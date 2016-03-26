#ifndef INTERFACES_H
#define INTERFACES_H

#include <Arduino.h>
#include <StandardCplusplus.h>
#include <functional-vlpp.h>


using Idleloop = vl::Func<void(void)>;
using Runnable = vl::Func<void(void)>;
using Command  = vl::Func<void(void)>;
using Observer = vl::Func<void(void)>;


template<class T>
class Iterator
{
public:

    Iterator(const T *ptr) : _ptr(ptr) {}

    Iterator &operator++(void)
    { ++_ptr; return *this; }

    Iterator operator++(int)
    { return Iterator<T>(_ptr++); }

    bool operator!=(const Iterator &other) const
    { return _ptr != other._ptr; }

    const T &operator*(void) const
    { return *_ptr; }

private:

    const T *_ptr;

};


template<class T>
class Iterable
{
public:

    Iterable(void) : _ptr(NULL), _len(0) {}
    Iterable(const T *ptr, uint16_t len) : _ptr(ptr), _len(len) {}

    Iterator<T> begin(void)
    { return Iterator<T>(_ptr); }

    Iterator<T> end(void)
    { return Iterator<T>(_ptr+_len); }

private:

    const T *_ptr;
    uint16_t _len;
};


using Serializer = vl::Func<void(Iterable<uint8_t>)>;


class BuildFabricator
{
public:

    virtual ~BuildFabricator(void) {}

    virtual void buildDisplayAnimator(void) = 0;
    virtual void buildMatrixAnimator(void) = 0;
    virtual void buildDisplayPin(void) = 0;
};


class Subject
{
public:

    virtual ~Subject(void) {}

    virtual void attach(Observer observer) = 0;
    virtual void detach(Observer observer) = 0;

};


#endif
