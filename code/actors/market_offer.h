#ifndef MARKET_OFFER_H
#define MARKET_OFFER_H

#include "../engine/primitive_classes/drawable_object.h"
#include "../engine/primitive_classes/textured_object.h"
#include "../engine/primitive_classes/textured_button_object.h"
#include "../engine/advanced_classes/number_display_module/number_display_module.h"

class MarketOffer: public DrawableObject
{
    public:
        MarketOffer(int x, int y, unsigned int width, unsigned int height);
        void draw(sf::RenderWindow& windowToDrawObjectIn);
    protected:
        //
    private:
        TexturedObject background;
		TexturedObject commodityOneIcon;
		NumberDisplay commodityOneCountDisplay;
		TexturedObject commodityTwoIcon;
		NumberDisplay commodityTwoCountDisplay;
        TexturedButtonObject selectButton;
};

#endif
