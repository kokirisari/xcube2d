#include "MyEngineSystem.h"

// apply resolution based on a resolution button's name and selection.
void MyEngineSystem::applyResolutionSetting(GraphicsEngine& gfx, const std::string& name, int selection, SDL_Color* primaryColor, SDL_Color* secondaryColor, SDL_Color* tertiaryColor)
{
    // only work if name is "Resolution Setting"
    if (name == "Resolution Setting") {
        switch (selection) { // width of window based on some typical 16:9 display sizes, 1024x576, 1280x720, 1600x900, 1920x1080
        case 0: xResolution = 1024; break;
        case 1: xResolution = 1280; break;
        case 2: xResolution = 1600; break;
        case 3: xResolution = 1920; break;
        default: xResolution = 1024; break;
        }

        gfx.setWindowSize(xResolution, xResolution * 9 / 16);

    }
    if (name == "Primary Colour Setting") {
        switch (selection) {
        case 0: *primaryColor = SDL_Color{255, 255, 255}; break;
        case 1: *primaryColor = SDL_Color{ 255, 0, 0 }; break;
        case 2: *primaryColor = SDL_Color{ 0, 255, 0 }; break;
        case 3: *primaryColor = SDL_Color{ 0, 0, 255 }; break;
        default:; break;
        }

    }
    if (name == "Secondary Colour Setting") {
        switch (selection) {
        case 0: *secondaryColor = SDL_Color{ 255, 255, 255 }; break;
        case 1: *secondaryColor = SDL_Color{ 255, 0, 0 }; break;
        case 2: *secondaryColor = SDL_Color{ 0, 255, 0 }; break;
        case 3: *secondaryColor = SDL_Color{ 0, 0, 255 }; break;
        default:; break;
        }

    }
    if (name == "Tertiary Colour Setting") {
        switch (selection) {
        case 0: *secondaryColor = SDL_Color{ 255, 255, 255 }; break;
        case 1: *secondaryColor = SDL_Color{ 255, 0, 0 }; break;
        case 2: *secondaryColor = SDL_Color{ 0, 255, 0 }; break;
        case 3: *secondaryColor = SDL_Color{ 0, 0, 255 }; break;
        default:; break;
        }

    }
}

void MyEngineSystem::setDrawColor(SDL_Color& color) {
    SDL_SetRenderDrawColor(GraphicsEngine::renderer, color.r, color.g, color.b, 255);	// may need to be adjusted for allowing alpha
}

bool MyEngineSystem::checkButtonClicked(const Button& b, std::shared_ptr<EventEngine> evt)
{
    if (!evt) return false;

    Point2 mousePos = evt->getMousePos();

    if (evt->isPressed(BTN_LEFT)) {
        if (mousePos.x >= b.rect.x && mousePos.x <= b.rect.x + b.rect.w &&
            mousePos.y >= b.rect.y && mousePos.y <= b.rect.y + b.rect.h) {
            return true;
            
        }
    }
    return false;
}


