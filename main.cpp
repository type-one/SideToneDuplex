//-----------------------------------------------------------------------------//
// Side Tone Duplex - Spare time development for fun                           //
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

#include "audio/audio_context.hpp"
#include "audio/audio_duplex.hpp"

#include <cstdio>

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    auto context = std::make_shared<audio::audio_context>();
    auto duplex = std::make_unique<audio::audio_duplex>(context);

    duplex->start();

    (void)std::getchar();

    duplex->stop();

    return 0;
}
