#pragma once

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#define GLM_FORCE_RADIANS
#include <glm/gtx/quaternion.hpp>

#include <functional>
#include <vector>

#include "gnome_fortress/resource/ResourceManager.h"
#include "gnome_fortress/renderer/SpriteTechnique.h"
#include "gnome_fortress/ui/SpriteNode.h"

namespace gnome_fortress {
namespace game {

class TextNode : public ui::UINode {
public:
    TextNode(resource::ResourceManager &resourceManager, renderer::SpriteTechnique *technique);

    ~TextNode();

    enum Alignment {
        LEFT,
        CENTER,
        RIGHT
    };

    renderer::SpriteTechnique *getTechnique() const;

    std::string getText() const;
    void setText(const std::string &newText);

    Alignment getAlignment() const;
    void setAlignment(Alignment newAlignment);

private:
    void positionSprites();

    static glm::vec4 getCharacterUVs(char c);

    const model::Texture *texture;
    renderer::SpriteTechnique *technique;
    std::string text;
    Alignment alignment;
    std::vector<ui::SpriteNode *> sprites;
};

}
}