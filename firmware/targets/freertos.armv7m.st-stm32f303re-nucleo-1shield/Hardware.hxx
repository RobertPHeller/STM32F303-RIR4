
#include "Stm32Gpio.hxx"
#include "utils/GpioInitializer.hxx"
#include "BlinkerGPIO.hxx"
#include "DummyGPIO.hxx"
#include "PWM.hxx"


GPIO_PIN(LED_GREEN_RAW, LedPin, A, 5);

GPIO_PIN(SW_USER, GpioInputPU, C, 13);


// Servos
GPIO_PIN(SRV1, GpioOutputSafeHigh, C, 8);
GPIO_PIN(SRV2, GpioOutputSafeHigh, C, 6);
GPIO_PIN(SRV3, GpioOutputSafeHigh, C, 5);
GPIO_PIN(SRV4, GpioOutputSafeHigh, C, 4);

// Signals
GPIO_PIN(SIG1, GpioOutputSafeLow, C, 13);
GPIO_PIN(SIG2, GpioOutputSafeLow, C, 14);
GPIO_PIN(SIG3, GpioOutputSafeLow, C, 15);
GPIO_PIN(SIG4, GpioOutputSafeLow, F,  0);

// Stall Motors
GPIO_PIN(StallN, GpioOutputSafeLow, A, 15);
GPIO_PIN(StallM, GpioOutputSafeLow, B, 7);

// Solid State Relays
GPIO_PIN(SSR1, GpioOutputSafeLow, A, 5);
GPIO_PIN(SSR2, GpioOutputSafeLow, A, 6);


typedef GpioInitializer<
    LED_GREEN_RAW_Pin, SW_USER_Pin, //
    SRV1_Pin, SRV2_Pin, SRV3_Pin, SRV4_Pin, 
    SIG1_Pin, SIG2_Pin, SIG3_Pin, SIG4_Pin, 
    StallN_Pin, StallM_Pin, SSR1_Pin, SSR2_Pin,
    DummyPin>
    GpioInit;

typedef LED_GREEN_RAW_Pin BLINKER_RAW_Pin;
typedef BLINKER_Pin LED_GREEN_Pin;

#include "HardwareDEFS.hxx"

extern PWM* const servo_channels[];
/// @todo: rework the build so this can be moved away from here or turned into
/// a constexpr.
#define servoPwmCountPerMs  (configCPU_CLOCK_HZ / 1000)

