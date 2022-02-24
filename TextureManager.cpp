#include "TextureManager.h"

//"redclare the variable, so this file know it can use it
unordered_map<string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(string textureName) {
	string path = "images/";
	path += textureName + ".png";

	textures[textureName].loadFromFile(path);
}
sf::Texture& TextureManager::GetTexture(string textureName) {
	if (textures.find(textureName) == textures.end()) {// textures doesnt exist
		LoadTexture(textureName);
	}
	return textures[textureName];
}
void TextureManager::Clear() {
	textures.clear();
}