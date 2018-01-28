#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/event_groups.h>

#include <esp_event_loop.h>
#include "driver/mcpwm.h"
#include "soc/mcpwm_reg.h"
#include "soc/mcpwm_struct.h"
#include <soc/rtc.h>
#include <soc/rtc_cntl_reg.h>

#define TAG "led_strip"

void app_main(void)
{
    uint32_t angle1 = 5, angle2 = 5, angle3 = 5;
    
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM0A, CONFIG_LED_STRIP_R_GPIO);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM1A, CONFIG_LED_STRIP_G_GPIO);
    mcpwm_gpio_init(MCPWM_UNIT_0, MCPWM2A, CONFIG_LED_STRIP_B_GPIO);
  
    mcpwm_config_t pwm_config;
    pwm_config.frequency = 100;    //frequency = 100Hz
    pwm_config.cmpr_a = 0;         //duty cycle of PWMxA = 0
    pwm_config.cmpr_b = 0;         //duty cycle of PWMxb = 0
    pwm_config.counter_mode = MCPWM_UP_COUNTER;
    pwm_config.duty_mode = MCPWM_DUTY_MODE_0;
    
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_0, &pwm_config);    //Configure PWM0A & PWM0B with above settings
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_1, &pwm_config);
    mcpwm_init(MCPWM_UNIT_0, MCPWM_TIMER_2, &pwm_config);
    
    while(1) {
        // Ramp up and down the brightness of each colour
        if(angle1 <= 10000)
            mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, angle1);
        else 
            mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_0, MCPWM_OPR_A, 20000-angle1);
            
        if(angle2 <= 10000)
            mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_A, angle2);
        else
            mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_1, MCPWM_OPR_A, 20000-angle2);
           
        if(angle3 <= 10000)
            mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_2, MCPWM_OPR_A, angle3);
        else
            mcpwm_set_duty_in_us(MCPWM_UNIT_0, MCPWM_TIMER_2, MCPWM_OPR_A, 20000-angle3);
           
        vTaskDelay(2);  // Delay between PWM updates (a stupid 2ms for 100Hz PWM)
        angle1+= 150;  // Add 150us to the pulse width
        angle2+= 180;  // Add 180us to the pulse width
        angle3+= 210;  // Add 210us to the pulse width
        if(angle1 >= 20000) angle1 -= 20000;  // Clamp the angle values;
        if(angle2 >= 20000) angle2 -= 20000;
        if(angle3 >= 20000) angle3 -= 20000;
    }
}