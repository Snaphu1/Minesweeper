#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <vector>
#include "Random.h"
using namespace std;

class Tiles {
public:
	//went through rubric and wrote down anything I needed to do
	bool revealed; // will show background revelead tile
	bool mines;
	bool flagPresent;
	bool tempFlag;
	bool clicked;
	bool numPresent;
	bool debugOn;
	bool winOn;
	bool loseOn;
	int bombNearby;
	sf::Sprite mineSprite;
	sf::Sprite hideSprite; 
	sf::Sprite revealSprite; 
	sf::Sprite flagSprite; 
	sf::Sprite temp;
	sf::Sprite numberSprite;

	sf::Sprite number1Sprite;
	sf::Sprite number2Sprite;
	sf::Sprite number3Sprite;
	sf::Sprite number4Sprite;
	sf::Sprite number5Sprite;
	sf::Sprite number6Sprite;
	sf::Sprite number7Sprite;
	sf::Sprite number8Sprite;

	float xCoordinate;
	float yCoordinate;

	// A vector of tile pointers that will compare to mines (use recursion)
	// if it doesn't have all neighbors, set it to nullptr. This will be any node that doesn't get on the stack.  
	// Use depth-first search algorithm (gets rid of any node on the stack that doesn't have an adjacent)
	//the stack will not repeawt nodes
	//go in a clockwise motino from top left to top right to bottom right to bottom left to bootomm left 
	//make it reveal all surrounding tiles that aren't a mine
	vector<Tiles*> adjacentTiles;

	void SetPosition(float xPosition, float yPosition) {
		xCoordinate = xPosition;
		yCoordinate = yPosition;
		mineSprite.setPosition(xPosition, yPosition);
		hideSprite.setPosition(xPosition, yPosition);
		revealSprite.setPosition(xPosition, yPosition);
		flagSprite.setPosition(xPosition, yPosition);
		temp.setPosition(xPosition, yPosition);

		number1Sprite.setPosition(xPosition, yPosition);
		number2Sprite.setPosition(xPosition, yPosition);
		number3Sprite.setPosition(xPosition, yPosition);
		number4Sprite.setPosition(xPosition, yPosition);
		number5Sprite.setPosition(xPosition, yPosition);
		number6Sprite.setPosition(xPosition, yPosition);
		number7Sprite.setPosition(xPosition, yPosition);
		number8Sprite.setPosition(xPosition, yPosition);
	}
	void setTile() {
		revealed = false;
		mines = false; 
		flagPresent = false;
		clicked = false; 
		numPresent = false; 
		mineSprite.setTexture(TextureManager::GetTexture("mine"));
		hideSprite.setTexture(TextureManager::GetTexture("tile_hidden"));
		revealSprite.setTexture(TextureManager::GetTexture("tile_revealed"));
		flagSprite.setTexture(TextureManager::GetTexture("flag"));

		//if there is no bombs, show revelaed tile
		number1Sprite.setTexture(TextureManager::GetTexture("number_1"));
		number2Sprite.setTexture(TextureManager::GetTexture("number_2"));
		number3Sprite.setTexture(TextureManager::GetTexture("number_3"));
		number4Sprite.setTexture(TextureManager::GetTexture("number_4"));
		number5Sprite.setTexture(TextureManager::GetTexture("number_5"));
		number6Sprite.setTexture(TextureManager::GetTexture("number_6"));
		number7Sprite.setTexture(TextureManager::GetTexture("number_7"));
		number8Sprite.setTexture(TextureManager::GetTexture("number_8"));
	}
	void setNum() { // which number to display
		bombNearby = 0; // have to reset the variable

		for (int i = 1; i < adjacentTiles.size(); i++) {
			if (adjacentTiles[i] != nullptr && adjacentTiles[i]->mines == true) { //if there is an bomb within that specific tile
				bombNearby++;
			}
		}


		if (bombNearby == 0) {
			numPresent = false;
		}
		else {
			numPresent = true;
		}

		if (bombNearby == 1) {
			numberSprite = number1Sprite;
		}
		if (bombNearby == 2) {
			numberSprite = number2Sprite;
		}
		if (bombNearby == 3) {
			numberSprite = number3Sprite;
		}
		if (bombNearby == 4) {
			numberSprite = number4Sprite;
		}
		if (bombNearby == 5) {
			numberSprite = number5Sprite;
		}
		if (bombNearby == 6) {
			numberSprite = number6Sprite;
		}
		if (bombNearby == 7) {
			numberSprite = number7Sprite;
		}
		if (bombNearby == 8) {
			numberSprite = number8Sprite;
		}
		//Had a problem in which the numbers overlayed the bombs
		//this is to reset the number sprite to the bomb sprite
		if (mines) {
			numberSprite = mineSprite; 
		}
	}

	bool changeFlag() { //was originally a void function but we need to increment the flag counter in our board class
		if (!revealed) { //can not put a flag on a revealed tile
			//must consider if there is a flag already
			if (!flagPresent) {
				flagPresent = true;
			}
			//when the player wants to take away the falg
			else if (flagPresent) {
				flagPresent = false; 
			}
		}
		return flagPresent;
	}
	void changeMine(bool on_off) { // bool for mine counter
		mines = on_off;
	}
	void changeRevealed(){ //** if revelaed, show the number
		revealed = !revealed;
	}

	void Draw(sf::RenderWindow& window) { //** update the draw for the designated number
		if (debugOn) {
			if (winOn) {
				if (flagPresent) {
					window.draw(hideSprite);
					window.draw(flagSprite);
				}
				else {
					if (revealed) {
						window.draw(revealSprite);
						if (numPresent) {
							window.draw(numberSprite);
						}
						else if (mines) {
							window.draw(mineSprite);
						}
					}
					else {
						window.draw(hideSprite);
					}
				}
			}
			else if (loseOn){
				if (mines) {
					window.draw(revealSprite);
					if (flagPresent) {
						window.draw(flagSprite);
					}
					window.draw(mineSprite);
				}
				else {
					window.draw(hideSprite);
				}
				if (flagPresent && mines == false) {
					window.draw(hideSprite);
					window.draw(flagSprite);
				}
				if (revealed && mines == false) {
					window.draw(revealSprite);
					if (numPresent) {
						window.draw(numberSprite);
					}
				}
			}
			else {
				if (revealed) {
					window.draw(revealSprite);
					if (numPresent) {
						window.draw(numberSprite);
					}
				}
				else {
					window.draw(hideSprite);
					//revealed = false;
					//hidden = true;
				}

				if (flagPresent) {
					window.draw(hideSprite);
					window.draw(flagSprite);
				}
				if (mines) {
					window.draw(mineSprite);
				}
			}
		}
		else {
			if (loseOn) {
				if (mines) {
					window.draw(revealSprite);
					if (flagPresent) {
						window.draw(flagSprite);
					}
					window.draw(mineSprite);
				}
				else {
					window.draw(hideSprite);
				}
				if (flagPresent && mines == false) {
					window.draw(hideSprite);
					window.draw(flagSprite);
				}
				if (revealed && mines == false) {
					window.draw(revealSprite);
					if (numPresent) {
						window.draw(numberSprite);
					}
				}
			}
			else {
				if (flagPresent) {
					window.draw(hideSprite);
					window.draw(flagSprite);
				}
				else {
					if (revealed) {
						window.draw(revealSprite);
						if (numPresent) {
							window.draw(numberSprite);
						}
						else if (mines) {
							window.draw(mineSprite);
						}
					}
					else {
						window.draw(hideSprite);
						//revealed = false;
						//hidden = true;
					}
				}
			}
		}
	}

};
//example structture 
//smileyFace.setTexture(TextureManager::GetTexture("smile");
//sf::Sprite temp;
//temp.setPosition(smilyFace.getPosition())
//this->smileyFace = temp;
// 
// Update visualizaation (function) update textures of each sprite. constnatly check. clears first;
// new sprite no texture with the same position. bool each component.
// 
// Each tile has mutiple layers (background, mine flag number nothing, hidden, flag or not)
// every time tile is reveawled, createa new sprite in the same position. draw on nothiing.
// 