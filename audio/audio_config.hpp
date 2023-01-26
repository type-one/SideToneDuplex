//-----------------------------------------------------------------------------//
// Audio Config - Spare time development for fun                               //
// (c) 2023 Laurent Lardinois https://be.linkedin.com/in/laurentlardinois      //
//                                                                             //
// https://github.com/type-one/SideToneDuplex                                  //
//                                                                             //
// This software is provided 'as-is', without any express or implied           //
// warranty.In no event will the authors be held liable for any damages        //
// arising from the use of this software.                                      //
//                                                                             //
// Permission is granted to anyone to use this software for any purpose,       //
// including commercial applications, and to alter itand redistribute it       //
// freely, subject to the following restrictions :                             //
//                                                                             //
// 1. The origin of this software must not be misrepresented; you must not     //
// claim that you wrote the original software.If you use this software         //
// in a product, an acknowledgment in the product documentation would be       //
// appreciated but is not required.                                            //
// 2. Altered source versions must be plainly marked as such, and must not be  //
// misrepresented as being the original software.                              //
// 3. This notice may not be removed or altered from any source distribution.  //
//-----------------------------------------------------------------------------//

#pragma once

#if !defined(__AUDIO_CONFIG_HPP__)
#define __AUDIO_CONFIG_HPP__

#include <cstdint>

namespace audio
{
    // uncomment to display producer/consumer progress
    // #define DISPLAY_PROGRESS

    // parameters to tune
#if defined(_WIN32)
    // increase if not audible
    constexpr const int audio_period_ms = 1; // Windows 10, Corei7
#else
    constexpr const int audio_period_ms = 1; // Linux native host
    //constexpr const int audio_period_ms = 20; // Linux in VMPlayer
#endif

    constexpr const int audio_frequency = 22050;
    constexpr const int audio_frame_size = ((audio_frequency * audio_period_ms) / 1000);
    constexpr const int audio_channels = 1; // mono (1), stereo (2)
    using sample_t = std::int16_t;          // S16_LE
    // using sample_t = float; // F32
}

#endif //  __AUDIO_CONFIG_HPP__
