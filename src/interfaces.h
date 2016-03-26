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
class ArrayIterator
{
public:

    ArrayIterator(const T *ptr) : _ptr(ptr) {}

    ArrayIterator &operator++(void)
    { ++_ptr; return *this; }

    ArrayIterator operator++(int)
    { return ArrayIterator<T>(_ptr++); }

    bool operator==(const ArrayIterator &other) const
    { return _ptr == other._ptr; }

    bool operator!=(const ArrayIterator &other) const
    { return _ptr != other._ptr; }

    const T &operator*(void) const
    { return *_ptr; }

    const T *operator->(void) const
    { return _ptr; }

private:

    const T *_ptr;

};


template<class T>
class Array
{
public:

    Array(void) : _ptr(NULL), _len(0) {}
    Array(const T *ptr, uint16_t len) : _ptr(ptr), _len(len) {}

    ArrayIterator<T> begin(void)
    { return ArrayIterator<T>(_ptr); }

    ArrayIterator<T> end(void)
    { return ArrayIterator<T>(_ptr+_len); }

private:

    const T *_ptr;
    uint16_t _len;

};


using Serializer = vl::Func<void(Array<uint8_t>)>;


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
