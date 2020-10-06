#ifndef MARKET_SCREEN_H
#define MARKET_SCREEN_H

#include <SFML/Graphics.hpp>
#include "oae_screen.h"
#include "../engine/primitive_classes/textured_object.h"
#include "../engine/primitive_classes/textured_button_object.h"
#include "../engine/advanced_classes/number_display_module/number_display_module.h"
#include "../actors/market_offer.h"
#include "../actors/market_offer_list.h"

class MarketScreen: public OAEScreen
{
    public:
        MarketScreen(int x, int y, unsigned int width, unsigned int height);
        void handleEvent(sf::Event event, sf::RenderWindow& window); 
        void forceFullDraw(sf::RenderWindow& windowToDrawIn);
        void update(sf::Int32 millisecondsElapsedSinceLastUpdate, sf::RenderWindow& window);
        bool returnIfShouldSwitchToFarmScreen();
        void acknowledgeShouldSwitchToFarmScreen();
    protected:
        //
    private:
        bool shouldSwitchToFarmScreenFlag;

        //Shared with farm screen
        TexturedObject displaysTheWordDay;
        NumberDisplay dayNumberDisplay;
        TexturedObject displaysAMoneySign;
        NumberDisplay moneyDisplay;

        //Icons for stock
        TexturedObject tomatoIcon;
        NumberDisplay tomatoCount;
        TexturedObject zucchiniIcon;
        NumberDisplay zucchiniCount;
        TexturedObject carrotIcon;
        NumberDisplay carrotCount;

        //Buy/Sell UI
        TexturedObject sellWord;
        MarketOfferList itemsForSale;
        TexturedObject buyWord;
        MarketOfferList itemsToBuy;

        //Misc stuff
        TexturedObject background;
        TexturedButtonObject returnToFarmButton;
};

#endif
