#ifndef __MY_ENGINE_H__
#define __MY_ENGINE_H__

#include "../EngineCommon.h"
#include "../GraphicsEngine.h"
#include "../EventEngine.h"


class Button {
public:
    Rect rect;
    std::string name;
    int selection;

    Button(int x, int y, int xResolution,
        const std::string& n, int s)
        : rect{ x, y, xResolution * 5 / 32, xResolution * 4 / 32 }, name(n), selection(s)
    {
    }
};

class MyEngineSystem {
	friend class XCube2Engine;
private:
    
public:
    int pRed = 0; int pGreen = 0; int pBlue = 0;
	int xResolution = 1024;
	void applyResolutionSetting(GraphicsEngine& gfx, const std::string& name, int selection, SDL_Color* primaryColor, SDL_Color* secondaryColor, SDL_Color* tertiaryColor);
    bool checkButtonClicked(const Button& b, std::shared_ptr<EventEngine> evt);
    void setDrawColor(SDL_Color&);

};


#endif
