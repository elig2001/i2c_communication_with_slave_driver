#pragma once


#include <Arduino.h>
#include "types.h"


extern "C" 
{
    command_result_e i2c_communication__check_connection(uint8_t slave_address);
    command_result_e i2c_communication__read_serial_number(uint8_t slave_address, uint8_t* serial_number);
    command_result_e i2c_communication__write_serial_number(uint8_t slave_address, uint8_t* serial_number);
}