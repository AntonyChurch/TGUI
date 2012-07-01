/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012 Bruno Van de Velde (VDV_B@hotmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef _TGUI_RADIO_BUTTON_INCLUDED_
#define _TGUI_RADIO_BUTTON_INCLUDED_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    struct TGUI_API RadioButton : public Checkbox
    {
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        RadioButton();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Copy constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        RadioButton(const RadioButton& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Overload of assignment operator
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        RadioButton& operator= (const RadioButton& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Override the function from Checkbox. The function is called when the RadioButton gets checked.
        /// It will tell the RadioButtonManager to uncheck all the other radio buttons with its id.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void check();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Override the function from Checkbox. The function is called when the RadioButton gets unchecked.
        /// Unchecking a radio button isn't possible so this function makes sure that nothing happens.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void uncheck();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    private:

        // The parent object may change the m_Checked member of the Checkbox struct.
        friend struct Group;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //_TGUI_RADIO_BUTTON_NCLUDED_

