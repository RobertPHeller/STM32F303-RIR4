
#include "Stm32Gpio.hxx"
#include "utils/GpioInitializer.hxx"
#include "BlinkerGPIO.hxx"
#include "DummyGPIO.hxx"
#include "PWM.hxx"

GPIO_PIN(LED_GREEN_RAW, LedPin, A, 5);

GPIO_PIN(SW_USER, GpioInputPU, C, 13);

typedef GpioInitializer<LED_GREEN_RAW_Pin, SW_USER_Pin, //
    DummyPin>
    GpioInit;

typedef LED_GREEN_RAW_Pin BLINKER_RAW_Pin;
typedef BLINKER_Pin LED_GREEN_Pin;

extern PWM* const servo_channels[];
/// @todo: rework the build so this can be moved away from here or turned into
/// a constexpr.
#define servoPwmCountPerMs  (configCPU_CLOCK_HZ / 1000)
