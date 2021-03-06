/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2020 Bruno Van de Velde (vdv_b@tgui.eu)
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


#include <TGUI/Backends/SDL/BackendTextSDL.hpp>
#include <TGUI/Backends/SDL/BackendFontSDL.hpp>
#include <TGUI/Backends/SDL/FontCacheSDL.hpp>
#include <TGUI/OpenGL.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    BackendTextSDL::BackendTextSDL()
    {
        // There must always be a single line of text, even when the text is empty
        m_linesUtf8.emplace_back();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    BackendTextSDL::~BackendTextSDL()
    {
        for (const auto& lineTexture : m_textures)
            TGUI_GL_CHECK(glDeleteTextures(1, &lineTexture.textureId));
        for (const auto& lineTexture : m_outlineTextures)
            TGUI_GL_CHECK(glDeleteTextures(1, &lineTexture.textureId));

        if (m_font)
            FontCacheSDL::unregisterFontSize(m_font.get(), m_characterSize);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2f BackendTextSDL::getSize()
    {
        if (!m_texturesValid)
        {
            if (!updateTextures())
                return {0, 0};
        }

        return m_size;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BackendTextSDL::setString(const String& string)
    {
        const std::vector<String>& lines = string.split('\n');

        m_linesUtf8.clear();
        m_linesUtf8.reserve(lines.size());
        for (const auto& line : lines)
            m_linesUtf8.push_back(line.toAnsiString());

        m_texturesValid = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BackendTextSDL::setCharacterSize(unsigned int characterSize)
    {
        if (m_characterSize == characterSize)
            return;

        if (m_font)
        {
            FontCacheSDL::unregisterFontSize(m_font.get(), m_characterSize);
            FontCacheSDL::registerFontSize(m_font.get(), characterSize);
        }

        m_characterSize = characterSize;
        m_texturesValid = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BackendTextSDL::setFillColor(const Color& color)
    {
        m_textColor.r = color.getRed();
        m_textColor.g = color.getGreen();
        m_textColor.b = color.getBlue();
        m_textColor.a = color.getAlpha();
        m_texturesValid = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BackendTextSDL::setOutlineColor(const Color& color)
    {
        m_outlineColor.r = color.getRed();
        m_outlineColor.g = color.getGreen();
        m_outlineColor.b = color.getBlue();
        m_outlineColor.a = color.getAlpha();
        m_texturesValid = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BackendTextSDL::setOutlineThickness(float thickness)
    {
        m_fontOutline = static_cast<int>(thickness);
        m_texturesValid = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BackendTextSDL::setStyle(TextStyles style)
    {
        m_fontStyle = static_cast<int>(static_cast<unsigned int>(style));
        m_texturesValid = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void BackendTextSDL::setFont(const Font& font)
    {
        // If there was already another font then unregister from it
        if (m_font)
            FontCacheSDL::unregisterFontSize(m_font.get(), m_characterSize);

        TGUI_ASSERT(std::dynamic_pointer_cast<BackendFontSDL>(font.getBackendFont()), "BackendTextSDL::setFont requires font of type BackendFontSDL");
        m_font = std::static_pointer_cast<BackendFontSDL>(font.getBackendFont());

        // Register the text to the new font
        FontCacheSDL::registerFontSize(m_font.get(), m_characterSize);
        m_texturesValid = false;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    Vector2f BackendTextSDL::findCharacterPos(std::size_t index) const
    {
        if (!m_font)
            return {0, 0};

        TGUI_ASSERT(!m_linesUtf8.empty(), "BackendTextSDL::m_linesUtf8 can never be empty");

        std::size_t lineNumber = 0;
        while (index > m_linesUtf8[lineNumber].length())
        {
            index -= m_linesUtf8[lineNumber].length() - 1;
            ++lineNumber;
            TGUI_ASSERT(lineNumber < m_linesUtf8.size(), "Index out-of-range in BackendTextSDL::findCharacterPos");
        }

        const bool bold = ((m_fontStyle & TTF_STYLE_BOLD) == TTF_STYLE_BOLD);

        float x = 0;
        char32_t prevChar = U'\0';
        for (std::size_t i = 0; i < index; ++i)
        {
            const char32_t currentChar = m_linesUtf8[lineNumber][i];
            x += m_font->getGlyph(currentChar, m_characterSize, bold, static_cast<float>(m_fontOutline)).advance;
            x += m_font->getKerning(prevChar, currentChar, m_characterSize);
            prevChar = currentChar;
        }

        if (lineNumber == 0)
            return {x, 0};
        else
            return {x, static_cast<float>(lineNumber * m_font->getLineSpacing(m_characterSize))};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const std::vector<BackendTextSDL::LineTexture>& BackendTextSDL::getInternalTextures()
    {
        if (!m_texturesValid)
            updateTextures();

        return m_textures;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    const std::vector<BackendTextSDL::LineTexture>& BackendTextSDL::getInternalOutlineTextures()
    {
        if (!m_texturesValid)
            updateTextures();

        return m_outlineTextures;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool BackendTextSDL::updateTextures()
    {
        if (!m_font)
            return false;

        TTF_Font* font = m_font->getInternalFont(m_characterSize);
        if (!font)
            return false;

        const float lineSpacing = m_font->getLineSpacing(m_characterSize);

        // If textures already existed then delete them first
        for (const auto& lineTexture : m_textures)
            TGUI_GL_CHECK(glDeleteTextures(1, &lineTexture.textureId));
        for (const auto& lineTexture : m_outlineTextures)
            TGUI_GL_CHECK(glDeleteTextures(1, &lineTexture.textureId));

        m_textures.clear();
        m_outlineTextures.clear();

        m_size.x = 0;
        m_size.y = m_linesUtf8.size() * lineSpacing;

        if (m_fontStyle != TextStyle::Regular)
            TTF_SetFontStyle(font, m_fontStyle);

        std::vector<LineTexture> textures;
        for (std::size_t i = 0; i < m_linesUtf8.size(); ++i)
            textures.push_back(createLineTexture(font, static_cast<int>(i * lineSpacing), m_linesUtf8[i], m_textColor, 0));

        // If an outline exists then create textures for it as well
        std::vector<LineTexture> outlineTextures;
        if (m_fontOutline != 0)
        {
            TTF_SetFontOutline(font, m_fontOutline);

            for (std::size_t i = 0; i < m_linesUtf8.size(); ++i)
                outlineTextures.push_back(createLineTexture(font, static_cast<int>(i * lineSpacing), m_linesUtf8[i], m_outlineColor, m_fontOutline));

            // Reset the outline again so that we can always assume that it is set to 0 everywhere
            TTF_SetFontOutline(font, 0);
        }

        // Restore the font style so that we can always assume that a font from the cache has no special style
        if (m_fontStyle != TextStyle::Regular)
            TTF_SetFontStyle(font, TTF_STYLE_NORMAL);

        // Set the new texture
        m_textures = std::move(textures);
        m_outlineTextures = std::move(outlineTextures);
        m_texturesValid = true;
        return true;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    BackendTextSDL::LineTexture BackendTextSDL::createLineTexture(TTF_Font* font, int verticalOffset, const std::string& line, const SDL_Color& color, int outline)
    {
        LineTexture lineTexture;
        if (line.empty())
        {
            lineTexture.bounding = SDL_Rect{0, 0, 0, 0};
            lineTexture.textureId = 0;
            return lineTexture;
        }

        SDL_Surface* surface = TTF_RenderUTF8_Blended(font, line.c_str(), color);
        if (!surface)
        {
            lineTexture.bounding = SDL_Rect{0, 0, 0, 0};
            lineTexture.textureId = 0;
            return lineTexture;
        }

        const SDL_Rect lineBounding{-outline, verticalOffset - outline, surface->w, surface->h};

        m_size.x = std::max(m_size.x, static_cast<float>(surface->w));

        GLuint textureId;
        TGUI_GL_CHECK(glGenTextures(1, &textureId));
        TGUI_GL_CHECK(glBindTexture(GL_TEXTURE_2D, textureId));
        TGUI_GL_CHECK(glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, surface->w, surface->h));
        TGUI_GL_CHECK(glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, surface->w, surface->h, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels));

        SDL_FreeSurface(surface);

        lineTexture.bounding = lineBounding;
        lineTexture.textureId = textureId;
        return lineTexture;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
