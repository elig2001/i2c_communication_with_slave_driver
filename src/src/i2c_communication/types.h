#ifndef I2C_CLIENT_TYPES_H
#define	I2C_CLIENT_TYPES_H

#include <Arduino.h>

typedef enum
{
    COMMAND_ID__READ,
    COMMAND_ID__WRITE, 
    COMMAND_ID__ABORT_READ,
    COMMAND_ID__SANITY_REQUEST = 255
} command_id_e;


typedef enum
{
    I2C_HANDLER_STATE__WAITING_FOR_COMMAND,
    I2C_HANDLER_STATE__WRITING_DATA,
    I2C_HANDLER_STATE__READING_DATA,
    I2C_HANDLER_STATE__SEND_SANITY
} i2c_handler_state_e;

typedef enum
{
    COMMAND_RESULT__UNINITIALIZED,
    COMMAND_RESULT__SUCCESS,
    COMMAND_RESULT__FAILURE,
    COMMAND_RESULT__INVALID_PARAMS
} command_result_e;

typedef enum
{
    RESOURCE_TYPE__NOT_INITIALIZED,
    RESOURCE_TYPE__COMMAND_RESULT,
    RESOURCE_TYPE__SERIAL_NUMBER,
    RESOURCE_TYPE__BRIDGE_DATA,
    RESOURCE_TYPE__MAX_RESOURCE,

} resource_type_e;

typedef struct i2c_command_s
{
    command_id_e command_id;
    resource_type_e data_type;
    uint8_t read_write_length;
} i2c_command_t;



#endif

