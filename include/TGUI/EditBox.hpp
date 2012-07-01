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


#ifndef _TGUI_EDITBOX_INCLUDED_
#define _TGUI_EDITBOX_INCLUDED_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    struct TGUI_API EditBox : public OBJECT, OBJECT_BORDERS, OBJECT_ANIMATION
    {
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        EditBox();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Copy constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        EditBox(const EditBox & copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ~EditBox();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Overload of assignment operator
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        EditBox& operator= (const EditBox& right);


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// The path to the folder that contains the images.
        /// The folder must also contain an info.txt file, which will give more information about the edit box.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        bool load(const std::string pathname);


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Changes the size of the edit box. Note that this function will undo all scaling, as it just
        /// calculates the correct scale factors for you. It is an alternative to setScale.
        /// Note that the edit box has to be loaded correctly before calling this function.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(float width, float height);


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Returns the size of the edit box, unaffected by scaling.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        Vector2u getSize() const;


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Returns the size of the edit box, after the scaling transformation.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        Vector2f getScaledSize() const;


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Returns the pathname that was used to load the edit box.
        /// When the edit box has not been loaded yet then this function will return an empty string.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        std::string getLoadedPathname();


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// You can change the text of the editbox with this function.
        /// The last characters of the text might be removed in the following situations:
        ///  1. The text has more characters than MaxChars (0 by default, which means unlimited characters)
        ///  2. The text does not fit inside the EditBox and LimitTextWidth is true (false by default)
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        void setText(const std::string text);


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Returns the text inside the edit box. This text is not affected by the password character.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        std::string getText();


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Changes the character size of the text.
        /// If the size is 0 (default) then the text will be scaled to fit in the edit box.
        /// Note that this text size is the size before scaling.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextSize(const unsigned int textSize);


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Returns the character size of the text.
        /// It is possible that this function returns 0, which means that the text is auto-scaled.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getTextSize();


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Changes the font of the text. When you don't call this function then the global font will be use.
        /// This global font can be changed by calling the setGlobalFont function from Panel.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextFont(const sf::Font& font);


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Returns the font of the text.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Font& getTextFont();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// This function will set a password character. If NewPasswordChar is 0 then there is no password character.
        ///
        /// When the text width is limited (default) then this function might remove the last characters in the text if they no
        /// longer fit in the EditBox. You can avoid this by setting LimitTextWidth to false.
        ///
        /// The scale factors are taken into account here, so make sure that they are already set (if you use them).
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setPasswordChar(const char passwordChar = '\0');


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// This function will return the password character. This will be 0 when there is no password character.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        char getPasswordChar();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// This function will change the character limit. Set NewMaxChars to 0 to disable the limit.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setMaximumCharacters(const unsigned int maxChars = 0);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Returns the character limit. Will return 0 when there is no limit.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getMaximumCharacters();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Changes the border width and border height of the edit box.
        /// When the text is autoscaled then it will be drawn within these borders.
        /// Note that these borders are scaled together with the image!
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBorders(unsigned int leftBorder   = 0,
                        unsigned int topBorder    = 0,
                        unsigned int rightBorder  = 0,
                        unsigned int bottomBorder = 0);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Changes the colors from the edit box.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void changeColors(const sf::Color& textColor                            = sf::Color(  0,   0,   0),
                          const sf::Color& selectedTextColor                    = sf::Color(255, 255, 255),
                          const sf::Color& selectedTextBackgroundColor          = sf::Color( 10, 110, 255),
                          const sf::Color& unfocusedSelectedTextBackgroundColor = sf::Color(110, 110, 255));


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Get the text color that is currently being used inside the edit box.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getTextColor();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Get the text color of the selected text that is currently being used inside the edit box.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getSelectedTextColor();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Get the backgroun color of the selected text that is currently being used inside the edit box.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getSelectedTextBackgroundColor();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Get the bacground color of the selected text that is currently being used inside the edit box when the edit box is not focused.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getUnfocusedSelectedTextBackgroundColor();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// This function will set the selection point somewhere, so that when you type something the changes will happen there.
        /// Normally you will not need this function.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSelectionPointPosition(unsigned int charactersBeforeSelectionPoint);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // These functions are used to receive callback from the EventManager.
        // You normally don't need them, but you can use them to simulate an event.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool mouseOnObject(float x, float y);
        void leftMousePressed(float x, float y);
        void leftMouseReleased(float x, float y);
        void mouseMoved(float x, float y);
        void keyPressed(sf::Keyboard::Key Key);
        void textEntered(char Key);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function will search where the selection point should be. It will not change the selection point.
        // It will return after which character the selection point should be.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int findSelectionPointPosition(float PosX);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // When AnimationManager changes the elapsed time then this function is called.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void update();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Because this struct is derived from sf::Drawable, you can just call the draw function from your sf::RenderTarget.
        // This function will be called and it will draw the edit box on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public:

        /// The color of the flickering selection point
        sf::Color     selectionPointColor;

        /// The width in pixels of the flickering selection point
        unsigned int  selectionPointWidth;


    private:

        bool          m_SelectionPointVisible;
        unsigned int  m_SelectionPointPosition;

        // When this boolean is true then you can no longer add text when the EditBox is full.
        // Changing it to false will allow you to scroll the text (default).
        // You can change the boolean with the limitTextWidth(bool) function.
        bool          m_LimitTextWidth;

        std::string   m_DisplayedText;
        std::string   m_SelText;
        std::string   m_Text;

        // This will store the size of the text ( 0 to auto size )
        unsigned int  m_TextSize;

        unsigned int  m_SelChars;
        unsigned int  m_SelStart;
        unsigned int  m_SelEnd;

        char          m_PasswordChar;

        unsigned int  m_MaxChars;

        // If true then the image is split in three parts
        bool          m_SplitImage;

        // When the text width is not limited, you can scroll the edit box.
        // These numbers will hold the first and last visible letter.
        unsigned int  m_LeftTextCrop;
        unsigned int  m_RightTextCrop;

        // The rectangle behind the selected text will have this color
        sf::Color     m_SelectedTextBgrColor;
        sf::Color     m_UnfocusedSelectedTextBgrColor;

        // We need three SFML texts to draw our text.
        sf::Text      m_TextBeforeSelection;
        sf::Text      m_TextSelection;
        sf::Text      m_TextAfterSelection;

        // The SFML textures
        sf::Texture*  m_TextureNormal_L;
        sf::Texture*  m_TextureNormal_M;
        sf::Texture*  m_TextureNormal_R;

        sf::Texture*  m_TextureHover_L;
        sf::Texture*  m_TextureHover_M;
        sf::Texture*  m_TextureHover_R;

        sf::Texture*  m_TextureFocused_L;
        sf::Texture*  m_TextureFocused_M;
        sf::Texture*  m_TextureFocused_R;

        // The SFML sprites
        sf::Sprite   m_SpriteNormal_L;
        sf::Sprite   m_SpriteNormal_M;
        sf::Sprite   m_SpriteNormal_R;

        sf::Sprite   m_SpriteHover_L;
        sf::Sprite   m_SpriteHover_M;
        sf::Sprite   m_SpriteHover_R;

        sf::Sprite   m_SpriteFocused_L;
        sf::Sprite   m_SpriteFocused_M;
        sf::Sprite   m_SpriteFocused_R;

        // The pathname used to load the edit box
        std::string m_LoadedPathname;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    };
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //_TGUI_EDITBOX_INCLUDED_
