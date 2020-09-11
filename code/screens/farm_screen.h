#ifndef FARM_SCREEN_H
#define FARM_SCREEN_H

class FarmScreen: public Screen
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
