#ifndef TEXTURED_BUTTON_OBJECT
#define TEXTURED_BUTTON_OBJECT

class TexturedButtonObject: public TexturedObject
{
    public:
	TexturedButtonObject(int x, int y, int width, int height, sf::Texture texture);
	bool theMouseHasBeenClickedAtTheSpecifiedCoordinatesHasTheButtonBeenClicked(int mouseX, int mouseY);
    protected:
	//
    private:
	//
}

#endif
