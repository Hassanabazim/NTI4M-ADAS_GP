


#include "MGPIO_int.h"

void IR_Sensor_Init(void)
{
    MGPIO_enSetPinDirection(PORTA, PIN0, IN_PULL_UP_PULL_DOWN);
    MGPIO_enSetPinDirection(PORTA, PIN1, IN_PULL_UP_PULL_DOWN);
}

MGPIO_VALUE_t IR_Sensor_ReadLeft(void)
{
    MGPIO_VALUE_t sensor_value1;

    MGPIO_enGetPinValue(PORTA, PIN7, &sensor_value1);

    return sensor_value1;
}

MGPIO_VALUE_t IR_Sensor_ReadRight(void)
{
    MGPIO_VALUE_t sensor_value2;

    MGPIO_enGetPinValue(PORTA, PIN1, &sensor_value2);

    return sensor_value2;
}

