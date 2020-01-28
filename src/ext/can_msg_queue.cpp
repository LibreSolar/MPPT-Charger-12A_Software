/*
 * Copyright (c) 2017 Martin Jäger / Libre Solar
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#if defined(__MBED__) && !defined(UNIT_TEST)

#include "ext/can_msg_queue.h"

#include "mbed.h"

#ifdef STM32F0  // STM32L0 does not have CAN

bool CANMsgQueue::full()
{
    return _length == CAN_QUEUE_SIZE;
}

bool CANMsgQueue::empty()
{
    return _length == 0;
}

void CANMsgQueue::enqueue(CANMessage msg)
{
    if (!full()) {
        _queue[(_first + _length) % CAN_QUEUE_SIZE] = msg;
        _length++;
    }
}

int CANMsgQueue::dequeue()
{
    if (!empty()) {
        _first = (_first + 1) % CAN_QUEUE_SIZE;
        _length--;
        return 1;
    }
    else {
        return 0;
    }
}

int CANMsgQueue::dequeue(CANMessage& msg)
{
    if (!empty()) {
        msg = _queue[_first];
        _first = (_first + 1) % CAN_QUEUE_SIZE;
        _length--;
        return 1;
    }
    else {
        return 0;
    }
}

int CANMsgQueue::first(CANMessage& msg)
{
    if (!empty()) {
        msg = _queue[_first];
        return 1;
    }
    else {
        return 0;
    }
}

#endif /* STM32F0 */

#endif
