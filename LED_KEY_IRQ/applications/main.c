/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

//°´¼ü³õÊ¼»¯
#define PIN_KEY0 GET_PIN(D, 10) // PD10: KEY0 --> KEY
#define PIN_KEY1 GET_PIN(D, 9) // PD9: KEY1 --> KEY
#define PIN_KEY2 GET_PIN(D, 8) // PD8: KEY2 --> KEY
#define PIN_WK_UP GET_PIN(C,13)//PC13£ºWK_UP

#define PIN_LED_B GET_PIN(E,9)  //À¶
#define PIN_LED_G GET_PIN(E,8)  //ÂÌ
#define PIN_LED_R GET_PIN(E,7)  //ºì

enum
{
    Light_B,
    Light_G,
    Light_R,
    Light_stop,
};

void Light_ctrl(rt_uint32_t turn)
{
    if(turn == Light_B)
    {
        rt_pin_write(PIN_LED_B, PIN_LOW);
        rt_pin_write(PIN_LED_G, PIN_HIGH);
        rt_pin_write(PIN_LED_R, PIN_HIGH);

    }

    else if(turn == Light_G)

    {
        rt_pin_write(PIN_LED_B, PIN_HIGH);
        rt_pin_write(PIN_LED_G, PIN_LOW);
        rt_pin_write(PIN_LED_R, PIN_HIGH);

    }

    else if(turn == Light_R)

    {
        rt_pin_write(PIN_LED_B, PIN_HIGH);
        rt_pin_write(PIN_LED_G, PIN_HIGH);
        rt_pin_write(PIN_LED_R, PIN_LOW);
    }

    else if(turn == Light_stop)

    {
        rt_pin_write(PIN_LED_B, PIN_HIGH);
        rt_pin_write(PIN_LED_G, PIN_HIGH);
        rt_pin_write(PIN_LED_R, PIN_HIGH);

    }
    else
    {
        rt_kprintf("err");

    }
}

void irq_callback(void *args)
{
    rt_uint32_t sign = (rt_uint32_t)args;
    switch (sign)
    {
        case PIN_KEY0:
        Light_ctrl(Light_B);
        rt_kprintf("KEY0 interrupt. light blue.\n");
        break;
        case PIN_KEY1:
        Light_ctrl(Light_G);
        rt_kprintf("KEY1 interrupt. light green.\n");
        break;
        case PIN_KEY2:
        Light_ctrl(Light_R);
        rt_kprintf("KEY2 interrupt. motor red.\n");
        break;
        case PIN_WK_UP:
            Light_ctrl(Light_stop);
            rt_kprintf("KEY_WK_UP interrupt. motor red.\n");
        default:
        rt_kprintf("error sign= %d !", sign);
        break;
    }
}




int main(void)
{
    unsigned int count = 1;
    rt_pin_mode(PIN_KEY0, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(PIN_KEY1, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(PIN_KEY2, PIN_MODE_INPUT_PULLUP);
    rt_pin_mode(PIN_WK_UP, PIN_MODE_INPUT_PULLDOWN);

    rt_pin_mode(PIN_LED_B, PIN_MODE_OUTPUT);
    rt_pin_mode(PIN_LED_G, PIN_MODE_OUTPUT);
    rt_pin_mode(PIN_LED_R, PIN_MODE_OUTPUT);

    rt_pin_attach_irq(PIN_KEY0, PIN_IRQ_MODE_FALLING , irq_callback , (void *)PIN_KEY0);
    rt_pin_attach_irq(PIN_KEY1, PIN_IRQ_MODE_FALLING , irq_callback , (void *)PIN_KEY1);
    rt_pin_attach_irq(PIN_KEY2, PIN_IRQ_MODE_FALLING , irq_callback , (void *)PIN_KEY2);
    rt_pin_attach_irq(PIN_WK_UP, PIN_IRQ_MODE_FALLING , irq_callback , (void *)PIN_WK_UP);

    rt_pin_irq_enable(PIN_KEY0, PIN_IRQ_ENABLE);
    rt_pin_irq_enable(PIN_KEY1, PIN_IRQ_ENABLE);
    rt_pin_irq_enable(PIN_KEY2, PIN_IRQ_ENABLE);
    rt_pin_irq_enable(PIN_WK_UP, PIN_IRQ_ENABLE);
//    while (count > 0)
//        {
//            if (rt_pin_read(PIN_WK_UP) == PIN_HIGH)
//            {
//                rt_thread_mdelay(50);
//                if (rt_pin_read(PIN_WK_UP) == PIN_HIGH)
//                {
//                    rt_kprintf("WK_UP pressed. turn on light.");
//                    Light_ctrl(Light_stop);
//                }
//            }
//            else
//            {
//                beep_ctrl(0);
//            }
//            rt_thread_mdelay(10);
//            count++;
//        }

    return 0;
}
