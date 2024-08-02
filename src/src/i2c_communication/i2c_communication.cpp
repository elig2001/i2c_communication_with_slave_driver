#include <Wire.h>
#include "i2c_commuication.h"

extern "C"
{
    static void send_command(uint8_t slave_address, command_id_e command, resource_type_e resource_type, uint8_t length);
    static bool read_result(uint8_t slave_address, uint8_t length, uint8_t *destination_buffer);
    static bool write_bytes_to_slave(uint8_t slave_address, uint8_t *buffer_to_write, uint8_t buffer_length);

    command_result_e i2c_communication__check_connection(uint8_t slave_address)
    {
        uint8_t temp = 0;
        command_result_e command_result = COMMAND_RESULT__UNINITIALIZED;
        uint8_t amount_of_received_bytes = 0;

        Wire.beginTransmission(slave_address);
        Wire.write(0xff);
        Wire.endTransmission();

        amount_of_received_bytes = Wire.requestFrom(slave_address, (uint8_t)1);

        if (1 != amount_of_received_bytes)
        {
            command_result = COMMAND_RESULT__FAILURE;
            goto l_exit;
        }

        Wire.readBytes(&temp, 1);

        if (0xff != temp)
        {
            command_result = COMMAND_RESULT__FAILURE;
            goto l_exit;
        }

        command_result = COMMAND_RESULT__SUCCESS;

    l_exit:
        return command_result;
    }

    command_result_e i2c_communication__read_serial_number(uint8_t slave_address, uint8_t *serial_number)
    {
        command_result_e command_result = COMMAND_RESULT__UNINITIALIZED;

        if (NULL == serial_number)
        {
            command_result = COMMAND_RESULT__INVALID_PARAMS;
            goto l_exit;
        }

        send_command(slave_address, COMMAND_ID__READ, RESOURCE_TYPE__SERIAL_NUMBER, 4);

        if (!read_result(slave_address, 4, serial_number))
        {
            command_result = COMMAND_RESULT__FAILURE;
            goto l_exit;
        }

        command_result = COMMAND_RESULT__SUCCESS;

    l_exit:
        return command_result;
    }
    command_result_e i2c_communication__write_serial_number(uint8_t slave_address, uint8_t *serial_number)
    {
        command_result_e command_result = COMMAND_RESULT__UNINITIALIZED;

        if (NULL == serial_number)
        {
            command_result = COMMAND_RESULT__INVALID_PARAMS;
            goto l_exit;
        }

        send_command(slave_address, COMMAND_ID__WRITE, RESOURCE_TYPE__SERIAL_NUMBER, 4);

        if (!write_bytes_to_slave(slave_address, serial_number, 4))
        {
            command_result = COMMAND_RESULT__INVALID_PARAMS;
            goto l_exit;
        }

        command_result = COMMAND_RESULT__SUCCESS;

    l_exit:
        return command_result;
    }

    static bool read_result(uint8_t slave_address, uint8_t length, uint8_t *destination_buffer)
    {
        uint8_t amount_of_received_bytes = 0;

        if (NULL == destination_buffer || length == 0)
        {
            return false;
        }
        amount_of_received_bytes = Wire.requestFrom(slave_address, length);

        if (amount_of_received_bytes != length)
        {
            return false;
        }

        Wire.readBytes(destination_buffer, amount_of_received_bytes);

        return true;
    }

    static void send_command(uint8_t slave_address, command_id_e command, resource_type_e resource_type, uint8_t length)
    {
        Wire.beginTransmission(slave_address);

        Wire.write((uint8_t)command);

        Wire.write((uint8_t)resource_type);

        Wire.write(length);

        Wire.endTransmission();
    }

    static bool write_bytes_to_slave(uint8_t slave_address, uint8_t *buffer_to_write, uint8_t buffer_length)
    {
        if (NULL == buffer_to_write || buffer_length == 0)
        {
            return false;
        }

        Wire.beginTransmission(slave_address);

        for (size_t i = 0; i < buffer_length; i++)
        {
            Wire.write(buffer_to_write[i]);
        }

        Wire.endTransmission();

        return true;
    }
}