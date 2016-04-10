#ifndef INTERFACES_H
#define INTERFACES_H

#include <Arduino.h>
#include <StandardCplusplus.h>
#include <functional-vlpp.h>


enum BUTTON_STATE
{
    BUTTON_RELEASED,
    BUTTON_PRESSED
};


using EventLoop     = vl::Func<void(void)>;
using Runnable      = vl::Func<void(void)>;
using Command       = vl::Func<void(void)>;
using Observer      = vl::Func<void(void)>;

using SinkBool      = vl::Func<void(bool)>;
using SinkUint16    = vl::Func<void(uint16_t)>;
using SinkButton    = vl::Func<void(BUTTON_STATE)>;

using SourceBool    = vl::Func<bool(void)>;
using SourceUint16  = vl::Func<uint16_t(void)>;


template<class T>
class ArrayIterator
{
public:

    ArrayIterator(const T *ptr) : _ptr(ptr) {}
    ArrayIterator(const ArrayIterator &other) : _ptr(other._ptr) {}

    ArrayIterator &operator=(const ArrayIterator &other)
    { _ptr = other._ptr; return *this; }

    ArrayIterator operator++(void)
    { return ArrayIterator<T>(++_ptr); }

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
    Array(const Array &other) : _ptr(other._ptr), _len(other._len) {}

    Array &operator=(const Array &other)
    { _ptr = other._ptr; _len = other._len; return *this; }

    ArrayIterator<T> begin(void) const
    { return ArrayIterator<T>(_ptr); }

    ArrayIterator<T> end(void) const
    { return ArrayIterator<T>(_ptr+_len); }

    uint16_t count(void) const
    { return _len; }

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

};


class Subject
{
public:

    virtual ~Subject(void) {}

    virtual void subscribe(Observer observer) = 0;
    virtual void unsubscribe(Observer observer) = 0;

};


#endif
