/*
 * Copyright (c) 2016, ARM Limited, All Rights Reserved
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __WRD_RGB_LED_PWM_H__
#define __WRD_RGB_LED_PWM_H__

#include "mbed-drivers/mbed.h"

using namespace mbed::util;

class RGBLEDImplementation
{
public:
    /**
     * @brief Constructor. Implementation of the WRD RGB API.
     * @details Pin configurations are pulled from Yotta config.
     */
    RGBLEDImplementation()
        :   red(YOTTA_CFG_HARDWARE_WRD_RGB_LED_RED_PWM_PIN),
            green(YOTTA_CFG_HARDWARE_WRD_RGB_LED_GREEN_PWM_PIN),
            blue(YOTTA_CFG_HARDWARE_WRD_RGB_LED_BLUE_PWM_PIN)
    { }

    /**
     * @brief Set RGB color.
     *
     * @param red uint8_t red intensity.
     * @param green uint8_t green intensity.
     * @param blue uint8_t blue intensity.
     * @param callback FunctionPointer callback for when setting has been received.
     */
    void set(uint8_t new_red,
             uint8_t new_green,
             uint8_t new_blue,
             FunctionPointer0<void> callback = (void(*)(void)) NULL)
    {
        red.write(new_red / 0xFF);
        green.write(new_green / 0xFF);
        blue.write(new_blue / 0xFF);

        if (callback)
        {
            minar::Scheduler::postCallback(callback)
                .tolerance(1);
        }
    }

private:
    PwmOut red;
    PwmOut green;
    PwmOut blue;
};

#endif // __WRD_RGB_LED_PWM_H__
