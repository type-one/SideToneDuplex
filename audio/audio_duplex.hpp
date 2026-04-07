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

#pragma once

#if !defined(__AUDIO_DUPLEX_HPP__)
#define __AUDIO_DUPLEX_HPP__

#include "audio/audio_context.hpp"
#include "tools/non_copyable.hpp"

#include <cstdint>
#include <memory>

struct ma_context;
struct ma_device;

namespace audio
{
    /**
     * @brief Captures audio input and forwards it to the playback device.
     */
    class audio_duplex : public tools::non_copyable
    {
    public:
        /**
         * @brief Disables default construction because a valid audio context is required.
         */
        audio_duplex() = delete;

        /**
         * @brief Creates a duplex audio device bound to the provided context.
         * @param context Shared audio context used to create the duplex device.
         */
        explicit audio_duplex(std::shared_ptr<audio_context> context);

        /**
         * @brief Stops and releases the duplex audio device.
         */
        ~audio_duplex();

        /**
         * @brief Starts audio capture and playback.
         */
        void start();

        /**
         * @brief Stops audio capture and playback.
         */
        void stop();

        /**
         * @brief Processes captured frames and writes them to the playback buffer.
         * @param output Destination buffer for playback samples.
         * @param input Source buffer containing captured samples.
         * @param frames Number of audio frames available in the buffers.
         */
        void on_capture(sample_t* output, const sample_t* input, const std::size_t frames);

    private:
        std::shared_ptr<audio_context> m_context;
        std::unique_ptr<ma_device> m_duplex_device;
    };
}

#endif //  __AUDIO_DUPLEX_HPP__
