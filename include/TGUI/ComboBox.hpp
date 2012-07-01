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


#ifndef _TGUI_COMBO_BOX_INCLUDED_
#define _TGUI_COMBO_BOX_INCLUDED_

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    struct TGUI_API ComboBox : public OBJECT, OBJECT_BORDERS
    {
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ComboBox();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Copy constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ComboBox(const ComboBox& copy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Destructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ~ComboBox();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Overload of assignment operator
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ComboBox& operator= (const ComboBox& right);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// The path (passed with the comboBoxPathname parameter) should point to a folder with the needed images.
        /// The folder must contain an info.txt file that will give more information about the object.
        /// Apart from the optional images you will always need a normal image.
        ///
        /// The width parameter constains the width before scaling.
        /// The height of the combo box will be the height of the image (scaling included).
        ///
        /// With the nrOfItemsInListToDisplay parameter you can change the amount of items that are displayed when you click on
        /// the arrow. If there is no scrollbar then this will also be the maximum amount of items that the combo box can contain.
        ///
        /// The ScrollbarPathname is the pathname needed to load the scrollbar. If not provided then there will be no possibility
        /// to scroll, thus no items will be added when the combo box is full.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool load(const std::string comboBoxPathname,
                  unsigned int width,
                  unsigned int nrOfItemsInListToDisplay = 10,
                  const std::string scrollbarPathname = "");


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Changes the size of the combo box. Note that this function will undo all scaling.
        /// You are advised to use this function over the setScale function.
        /// Note that the combo box has to be loaded correctly before calling this function.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(float width, float height);


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Returns the size of the combo box, unaffected by scaling.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        Vector2u getSize() const;


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Returns the size of the combo box, after the scaling transformation.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        Vector2f getScaledSize() const;


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Returns the pathname that was used to load the combo box.
        /// When the combo box has not been loaded yet then this function will return an empty string.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        std::string getLoadedPathname();


        //////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Returns the pathname that was used to load the scrollbar.
        /// When no scrollbar was loaded then this function will return an empty string.
        //////////////////////////////////////////////////////////////////////////////////////////////////////
        std::string getLoadedScrollbarPathname();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Changes the width of the combo box (without scaling).
        /// If you use scaling then it should have been set before calling this function.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setWidth(unsigned int width);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Changes the number of items that are displayed in the list.
        /// When there is no scrollbar then this is the maximum number of items.
        /// If there is one, then it will only become visible when there are more items than this number.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setItemsToDisplay(unsigned int nrOfItemsInListToDisplay);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Returns the number of items that are displayed in the list.
        /// When there is no scrollbar then this is the maximum number of items.
        /// If there is one, then it will only become visible when there are more items than this number.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getItemsToDisplay();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Changes the colors of the combo box.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void changeColors(const sf::Color& backgroundColor         = sf::Color::White,
                          const sf::Color& textColor               = sf::Color::Black,
                          const sf::Color& selectedBackgroundColor = sf::Color(50, 100, 200),
                          const sf::Color& selectedTextColor       = sf::Color::White,
                          const sf::Color& borderColor             = sf::Color::Black);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Get the background color that is currently being used inside the combo box.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getBackgroundColor();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Get the text color that is currently being used inside the combo box.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getTextColor();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Get the background color of the selected text that is currently being used inside the combo box.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getSelectedBackgroundColor();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Get the text color of the selected text that is currently being used inside the combo box.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getSelectedTextColor();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Get the border color that is currently being used inside the combo box.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Color& getBorderColor();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Changes the text font.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextFont(const sf::Font& font);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Returns the text font.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        const sf::Font& getTextFont();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Changes the size of the borders.
        /// Note that these borders are scaled together with the combo box!
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setBorders(unsigned int leftBorder   = 0,
                        unsigned int topBorder    = 0,
                        unsigned int rightBorder  = 0,
                        unsigned int bottomBorder = 0);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Adds an item to the list, so that it can be selected later.
        /// Make sure that the borders were already set before calling this function (if you want borders)!
        ///
        /// When the text doesn't fit inside the list then the last characters are removed when cropText is true. Trying to
        /// find the item with the full text later will of course fail. If the text may not be clipped for this reason then you
        /// can set cropText to false, but this might cost some speed when drawing (it has to be clipped there every frame).
        /// If you do decide to clip the text here than make sure that the scaling to the combo box is already done.
        ///
        ///
        /// Return: - 0 when the list is full (m_MaxItems constains the maximum amount, zero means no limit). Note that the
        ///           list can also be full when no scrollbar was loaded and the text no longer fits inside the list.
        ///           When no scrollbar was loaded m_NrOfItemsToDisplay will thus become the maximum items.
        ///           The function can also return 0 when the combo box wasn't loaded correctly (when load function returned false).
        ///         - The id of the item otherwise (when it was successfully added). You will need this id when removing it from
        ///           the list (when using a name to remove it you might remove other items that have the same name).
        ///           Note that this id is no longer correct when an item is removed. Use it immediately or don't use it at all.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int addItem(const std::string itemName, bool cropText = false);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// When adding items to the combo box with the addItem function, none of them will be selected.
        /// If you don't want the combo box to stay empty until the user selects something, but you want a default item instead,
        /// then you can use this function to select an item.
        /// The first item that matches the name will be selected.
        ///
        /// return: true on success
        ///         false when the name was not found
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool setSelectedItem(const std::string itemName);

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// When adding items to the combo box with the addItem function, none of them will be selected.
        /// If you don't want the combo box to stay empty until the user selects something, but you want a default item instead,
        /// then you can use this function to select an item.
        /// Note that if you select it by name, the first matching item will be selected.
        ///
        /// return: true on success
        ///         false when the id was too high
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool setSelectedItem(unsigned int id);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Removes an item from the list with a given id.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeItem(unsigned int id);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Removes all items from the list with a given name.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeItem(const std::string itemName);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Removes all items from the list.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeAllItems();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Returns the item name of the given id. The string will be empty when the id was too high or when it was 0.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::string getItem(unsigned int id);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Returns the id of the first item with the given name. If none of the items matches then the id will be 0.
        /// Note that this id is no longer correct when an item is removed.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getItemID(const std::string itemName);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Returns the list that constains all the items.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::vector<std::string>& getItems();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Returns the currently selected item.
        /// When no item was selected then this function will return an empty string.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::string getSelectedItem() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Get the id of the selected item. Note that this id will become wrong when an item is removed from the list.
        /// When no item was selected then this function returns 0.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getSelectedItemID();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Changes the scrollbar that is displayed next to the list.
        /// Only needed when this wasn't done when creating the combo box or if the scrollbar should be changed.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool setScrollbar(const std::string scrollbarPathname);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// Removes the scrollbar. When there are too many items to fit in the list then the items will be removed.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeScrollbar();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // These functions are used to receive callback from EventManager.
        // You normally don't need them, but you can use them to simulate an event.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool mouseOnObject(float x, float y);
        void leftMousePressed(float x, float y);
        void leftMouseReleased(float x, float y);
        void mouseMoved(float x, float y);
        void mouseNoLongerDown();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Because this struct is derived from sf::Drawable, you can just call the Draw function from your sf::RenderTarget.
        // This function will be called and it will draw the object on the render target.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    private:

        // This boolean becomes true when you clicked on the combo box, when the list should be shown
        bool m_ShowList;

        // When the mouse is on top of the object, it might be on the listbox part.
        bool m_MouseOnListbox;

        // The number of items to display. If there is a scrollbar then you can scroll to see the other.
        // If there is no scrollbar then this will be the maximum amount of items.
        unsigned int m_NrOfItemsToDisplay;

        // Internally a listbox is used to store all items
        Listbox      m_Listbox;

        // The pathname of the loaded scrollbar (if there is one)
        std::string  m_LoadedScrollbarPathname;

        // The textures for the arrow image
        sf::Texture* m_TextureNormal;
        sf::Texture* m_TextureHover;

        // The sprites for the arrow image
        sf::Sprite   m_SpriteNormal;
        sf::Sprite   m_SpriteHover;

        // The pathname that was used to load the combo box
        std::string  m_LoadedPathname;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif //_TGUI_COMBO_BOX_INCLUDED_

