#include "gnome_fortress/game/TextNode.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "gnome_fortress/game/Resources.h"

namespace gnome_fortress {
namespace game {

// === PUBLIC ===

TextNode::TextNode(resource::ResourceManager &resourceManager, renderer::SpriteTechnique *technique)
    : UINode(),
      texture(resourceManager.getOrLoadTexture(resources::textures::ui_font)),
      technique(technique),
      text(),
      alignment(Alignment::CENTER),
      sprites() {
}

TextNode::~TextNode() {
    for (auto sprite : sprites) {
        delete sprite;
    }
}

renderer::SpriteTechnique *TextNode::getTechnique() const {
    return technique;
}

std::string TextNode::getText() const {
    return text;
}

void TextNode::setText(const std::string &newText) {
    // add sprites if there are not enough
    while (sprites.size() < newText.size()) {
        auto back = new ui::SpriteNode(texture, technique);
        appendChild(back);
        sprites.push_back(back);
    }

    // remove sprites if there are too many
    while (sprites.size() > newText.size()) {
        auto back = sprites.back();
        removeChild(indexOf(back));
        delete back;
        sprites.pop_back();
    }

    for (int i = 0; i < newText.size(); i++) {
        glm::vec4 uvMinMax = getCharacterUVs(newText[i]);
        sprites[i]->setUVMin(glm::vec2(uvMinMax[0], uvMinMax[1]));
        sprites[i]->setUVMax(glm::vec2(uvMinMax[2], uvMinMax[3]));
    }

    text = newText;

    positionSprites();
}

TextNode::Alignment TextNode::getAlignment() const {
    return alignment;
}

void TextNode::setAlignment(TextNode::Alignment newAlignment) {
    alignment = newAlignment;
    positionSprites();
}

void TextNode::positionSprites() {
    for (int i = 0; i < text.size(); i++) {
        float alignmentOffset = 0.0f;
        if (alignment == CENTER) {
            alignmentOffset = 0.0f - text.size();
        } else if (alignment == RIGHT) {
            alignmentOffset = 0.0f - 2 * text.size();
        }
        sprites[i]->setPosition(2.1*i + alignmentOffset, 0);
    }
}

glm::vec4 TextNode::getCharacterUVs(char c) {
    float w = 247.0f;
    float h = 50.0f;
    float bottom = 26.0f / h;
    float top = 33.0f / h;

    switch (c) {
    case 'A': return glm::vec4(2.0f / w, bottom, 7.0f / w, top);
    case 'B': return glm::vec4(8.0f / w, bottom, 13.0f / w, top);
    case 'C': return glm::vec4(14.0f / w, bottom, 19.0f / w, top);
    case 'D': return glm::vec4(20.0f / w, bottom, 25.0f / w, top);
    case 'E': return glm::vec4(26.0f / w, bottom, 31.0f / w, top);
    case 'F': return glm::vec4(32.0f / w, bottom, 37.0f / w, top);
    case 'G': return glm::vec4(38.0f / w, bottom, 43.0f / w, top);
    case 'H': return glm::vec4(44.0f / w, bottom, 49.0f / w, top);
    case 'I': return glm::vec4(50.0f / w, bottom, 55.0f / w, top);
    case 'J': return glm::vec4(56.0f / w, bottom, 61.0f / w, top);
    case 'K': return glm::vec4(62.0f / w, bottom, 67.0f / w, top);
    case 'L': return glm::vec4(68.0f / w, bottom, 73.0f / w, top);
    case 'M': return glm::vec4(74.0f / w, bottom, 81.0f / w, top);
    case 'N': return glm::vec4(82.0f / w, bottom, 87.0f / w, top);
    case 'O': return glm::vec4(88.0f / w, bottom, 93.0f / w, top);
    case 'P': return glm::vec4(94.0f / w, bottom, 99.0f / w, top);
    case 'Q': return glm::vec4(100.0f / w, bottom, 106.0f / w, top);
    case 'R': return glm::vec4(107.0f / w, bottom, 112.0f / w, top);
    case 'S': return glm::vec4(113.0f / w, bottom, 118.0f / w, top);
    case 'T': return glm::vec4(119.0f / w, bottom, 124.0f / w, top);
    case 'U': return glm::vec4(125.0f / w, bottom, 130.0f / w, top);
    case 'V': return glm::vec4(131.0f / w, bottom, 136.0f / w, top);
    case 'W': return glm::vec4(137.0f / w, bottom, 144.0f / w, top);
    case 'X': return glm::vec4(145.0f / w, bottom, 150.0f / w, top);
    case 'Y': return glm::vec4(151.0f / w, bottom, 156.0f / w, top);
    case 'Z': return glm::vec4(157.0f / w, bottom, 162.0f / w, top);
    case '1': return glm::vec4(163.0f / w, bottom, 168.0f / w, top);
    case '2': return glm::vec4(169.0f / w, bottom, 174.0f / w, top);
    case '3': return glm::vec4(175.0f / w, bottom, 180.0f / w, top);
    case '4': return glm::vec4(181.0f / w, bottom, 186.0f / w, top);
    case '5': return glm::vec4(187.0f / w, bottom, 192.0f / w, top);
    case '6': return glm::vec4(193.0f / w, bottom, 198.0f / w, top);
    case '7': return glm::vec4(199.0f / w, bottom, 204.0f / w, top);
    case '8': return glm::vec4(205.0f / w, bottom, 210.0f / w, top);
    case '9': return glm::vec4(211.0f / w, bottom, 216.0f / w, top);
    case '0': return glm::vec4(217.0f / w, bottom, 222.0f / w, top);
    case '!': return glm::vec4(223.0f / w, bottom, 226.0f / w, top);
    case '?': return glm::vec4(227.0f / w, bottom, 232.0f / w, top);
    case ':': return glm::vec4(233.0f / w, bottom, 236.0f / w, top);
    case '=': return glm::vec4(237.0f / w, bottom, 242.0f / w, top);
    case ',': return glm::vec4(243.0f / w, bottom, 246.0f / w, top);
    default: return glm::vec4();
    }
}

}
}