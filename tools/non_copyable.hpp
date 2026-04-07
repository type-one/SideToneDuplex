//-----------------------------------------------------------------------------//
// Helper - Spare time development for fun                                     //
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

#if !defined(__NON_COPYABLE_HPP__)
#define __NON_COPYABLE_HPP__

namespace tools
{
    /**
     * @brief Base class that disables copy and move operations.
     */
    class non_copyable
    {
    public:
        /**
         * @brief Creates a non-copyable base object.
         */
        non_copyable() = default;

        /**
         * @brief Destroys the non-copyable base object.
         */
        ~non_copyable() = default;

        /**
         * @brief Prevents copy construction.
         * @param other Source object that would be copied.
         */
        non_copyable(const non_copyable&) = delete;

        /**
         * @brief Prevents move construction.
         * @param other Source object that would be moved.
         */
        non_copyable(non_copyable&&) = delete;

        /**
         * @brief Prevents assignment from a const rvalue instance.
         * @param other Source object that would be assigned.
         * @return Reference to this object.
         */
        non_copyable& operator=(const non_copyable&&) = delete;

        /**
         * @brief Prevents move assignment.
         * @param other Source object that would be assigned.
         * @return Reference to this object.
         */
        non_copyable& operator=(non_copyable&&) = delete;
    };
}

#endif //  __NON_COPYABLE_HPP__
