#ifndef TEXTURE_BANK_H
#define TEXTURE_BANK_H

#include <map>
#include <SFML/Graphics.hpp>

class TextureBank
{
	public:
		TextureBank();
		void saveTextureWithReferenceNumber(int referenceNumber, sf::Texture textureToSave);
		const sf::Texture* getTextureAssociatedWithReferenceNumber(int referenceNumber) const;
		void deleteTextureWithReferenceNumber(int referenceNumber);
	protected:
		//
	private:
		std::map<int, sf::Texture> referenceNumberToTextureMap;
};

#endif
