#pragma once

#include "Arduino.h"

#ifndef NC
#define NC 0xFF
#endif

enum CanMode
{
    CAN_STANDARD = 0x00U,
    CAN_LOOPBACK = 0x01U,
    CAN_LOOPBACK_EXTERNAL = 0x02U,
};

enum CanStatus
{
    CAN_OK = 0x00U,
    CAN_ERROR = 0x01U,
    CAN_NO_DATA = 0x02U,
};

enum FilterType
{
    FILTER_DISABLE = 0x00U,
    FILTER_MASK_STANDARD_ID = 0x01U,
    FILTER_MASK_EXTENDED_ID = 0x02U,
    FILTER_ACCEPT_ALL = 0x03U
};

struct CanFrame
{
    uint32_t identifier;
    bool isRTR;
    bool isExtended;
    uint32_t dataLength;
    uint8_t data[8];
};

struct CanTiming
{
    uint32_t prescaler;
    uint32_t sjw;
    uint32_t tseg1;
    uint32_t tseg2;
};

class BaseCan
{

public:
    BaseCan(uint8_t pinRX, uint8_t pinTX, uint8_t pinSHDN = NC);

    // setup methods
    virtual CanStatus init(uint32_t bitrate = 1000000, CanMode mode = CAN_STANDARD) = 0;
    virtual CanStatus deinit() = 0;
    virtual CanStatus filter(FilterType filterType, uint32_t identifier = 0b11111111111, uint32_t mask = 0b11111111111, bool maskRtrBit = false, bool identifierRtrBit = false) = 0;
    virtual CanStatus start() = 0;
    virtual CanStatus stop() = 0;

    // tx methods
    virtual CanStatus writeFrame(CanFrame *txFrame) = 0;

    // rx methods
    virtual CanStatus readFrame(CanFrame *rxMessage) = 0;

protected:
    CanTiming solveCanTiming(uint32_t bitrate);
    uint8_t _pinRX;
    uint8_t _pinTX;
    uint8_t _pinSHDN;
};
