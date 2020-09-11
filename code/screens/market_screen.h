#ifndef MARKET_SCREEN_H
#define MARKET_SCREEN_H

class MarketScreen: public Screen
{
    public:
        void handleEvent(sf::Event); 
        void initializeAssets(int width, int height);
        void forceFullDraw();
        void update(sf::Int32 millisecondsElapsedSinceLastUpdate);
    protected:
        //
    private:
        //
};

#endif
