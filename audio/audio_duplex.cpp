//-----------------------------------------------------------------------------//
// Audio Capture/Playback - Spare time development for fun                     //
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

#include "audio_duplex.hpp"

#include "miniaudio/miniaudio.h"

#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <numeric>
#include <type_traits>
#include <utility>

namespace audio
{
    namespace
    {
        void frame_capture(ma_device* device, void* output, const void* input, ma_uint32 frame_count)
        {
            auto* samples_out = reinterpret_cast<sample_t*>(output);
            const auto* samples_in = reinterpret_cast<const sample_t*>(input);
            auto* instance = reinterpret_cast<audio_duplex*>(device->pUserData);
            if (instance)
            {
                instance->on_capture(samples_out, samples_in, static_cast<std::size_t>(frame_count));
            }
        }
    }

    audio_duplex::audio_duplex(std::shared_ptr<audio_context> context)
        : m_context(context)
        , m_duplex_device(std::make_unique<ma_device>())
    {
        ma_device_config config = ma_device_config_init(ma_device_type_duplex);
        config.capture.pDeviceID = nullptr;
        config.playback.pDeviceID = nullptr;

        if constexpr (std::is_same<float, sample_t>::value)
        {
            config.capture.format = ma_format_f32;
            config.playback.format = ma_format_f32;
        }
        else if constexpr (std::is_same<std::int16_t, sample_t>::value)
        {
            config.capture.format = ma_format_s16;
            config.playback.format = ma_format_s16;
        }
        else if constexpr (std::is_same<std::int32_t, sample_t>::value)
        {
            config.capture.format = ma_format_s32;
            config.playback.format = ma_format_s32;
        }
        else
        {
            config.capture.format = ma_format_unknown;
            config.playback.format = ma_format_unknown;
        }

        config.capture.channels = audio_channels;
        config.playback.channels = audio_channels;
        config.sampleRate = audio_frequency;
        config.periodSizeInMilliseconds = audio_period_ms;
        config.dataCallback = frame_capture;
        config.pUserData = this;
        config.performanceProfile = ma_performance_profile_low_latency;

        if (MA_SUCCESS != ma_device_init(&(m_context->context()), &config, m_duplex_device.get()))
        {
            std::cerr << "Failed to initialize duplex device" << std::endl;
            return;
        }

        std::cout << "Capture Device " << m_duplex_device->capture.name << std::endl;
        std::cout << "Playback Device " << m_duplex_device->playback.name << std::endl;
    }

    audio_duplex::~audio_duplex() { ma_device_uninit(m_duplex_device.get()); }

    void audio_duplex::start()
    {
        if (MA_SUCCESS != ma_device_start(m_duplex_device.get()))
        {
            std::cerr << "Failed to start duplex device" << std::endl;
        }
    }

    void audio_duplex::stop()
    {
        if (MA_SUCCESS != ma_device_stop(m_duplex_device.get()))
        {
            std::cerr << "Failed to stop duplex device" << std::endl;
        }
    }

    void audio_duplex::on_capture(sample_t* output, const sample_t* input, const std::size_t frames)
    {
        std::memcpy(output, input, frames * audio_channels * sizeof(sample_t));

        // compute attenuated sidetone (-6dB)
        if constexpr (std::is_same<float, sample_t>::value)
        {
            std::transform(input, input + frames * audio_channels, output, [](sample_t v) { return 0.5f * v; });
        }
        else if constexpr (std::is_same<std::int16_t, sample_t>::value || std::is_same<std::int32_t, sample_t>::value)
        {
            std::transform(input, input + frames * audio_channels, output, [](sample_t v) { return v / 2; });
        }

#if defined(DISPLAY_PROGRESS)
        std::cout << ".-";
#endif
    }
}
