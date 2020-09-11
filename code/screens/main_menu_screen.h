#ifndef MAIN_MENU_SCREEN_H
#define MAIN_MENU_SCREEN_H

class MainMenuScreen: public Screen
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
