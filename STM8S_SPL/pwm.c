#include "pwm.h"

#include "stm8s_tim2.h"

void initPwm()
{
    // We have to init timer 1 CH3, CH4 and timer2 CH1, CH2, CH3s
    /* Time base configuration */
    TIM2_TimeBaseInit(TIM2_PRESCALER_1, 999);

    /* PWM1 Mode configuration: Channel1 */
    TIM2_OC1Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,500, TIM2_OCPOLARITY_HIGH);
    TIM2_OC1PreloadConfig(ENABLE);

    /* PWM1 Mode configuration: Channel2 */
    TIM2_OC2Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,250, TIM2_OCPOLARITY_HIGH);
    TIM2_OC2PreloadConfig(ENABLE);

    /* PWM1 Mode configuration: Channel3 */
    TIM2_OC3Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,125, TIM2_OCPOLARITY_HIGH);
    TIM2_OC3PreloadConfig(ENABLE);

    TIM2_ARRPreloadConfig(ENABLE);

    /* TIM2 enable counter */
    TIM2_Cmd(ENABLE);

}
