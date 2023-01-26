//-----------------------------------------------------------------------------//
// Audio Context - Spare time development for fun                              //
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

#include "audio_context.hpp"

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio/miniaudio.h"

#include <iostream>
#include <memory>

namespace audio
{
    audio_context::audio_context()
        : m_context(std::make_unique<ma_context>())
    {
        auto context_config = ma_context_config_init();

        if (MA_SUCCESS != ma_context_init(NULL, 0, &context_config, m_context.get()))
        {
            std::cerr << "Failed to initialize context" << std::endl;
            return;
        }

        std::cout << "MAL context initialized, backend is " << ma_get_backend_name(m_context->backend) << std::endl;
    }

    audio_context::~audio_context() { ma_context_uninit(m_context.get()); }

    ma_context& audio_context::context() { return *(m_context.get()); }
}
