//Notes
//When space is revealed 
//If it’s a mine, the game ends (while loop) //When all of the non-mine spaces have been revealed, the player wins! 
//If it’s not a mine, it shows the number of mines adjacent to that space(anywhere from 0 to 8, with 0 just
//showing as an empty space)
//If a space has no adjacent mines, all non - mine spaces adjacent to it are also revealed The
//player uses the numbers as clues to figure out where other mines may be located.

// Mine variable (mine counter) correlates with the flag variable
// Non-Mine variable
// Flag variable (right click) cant be revelaed with left click or when other spaces are revealed
// reset button. return everything to defualt. 

//Debug button - toggles visiblity of mines
//Test buttons 1-3
#pragma once
#include <SFML/Graphics.hpp>
#include "Tiles.h"
#include "Random.h"
#include<map>
#include <fstream>
#include <sstream> 
#include <vector>
using namespace std;

class board {
public: 
	int width;
	int height;
	int numMines;// number of mines from the config file
	int mineCount;//mines left through the counter on bottom lef
	int tileRevealed; // how many tiles that have been revelead that are not a bomb
	int tileCount;
	int rows;
	int columns; 
	int numMinesTwo; 
	bool debugButton;
	bool face_happy = true; // it is initially happy at the start of the game
	bool face_sad;
	bool face_win;
	bool finishedGame;
	sf::Sprite debugSprite;
	sf::Sprite happySprite; 
	sf::Sprite winSprite;
	sf::Sprite loseSprite;
	sf::Sprite digitsSprite;
	sf::Sprite test1Sprite;
	sf::Sprite test2Sprite;
	sf::Sprite test3Sprite;

	sf::Sprite digitZero;
	sf::Sprite digitOne;
	sf::Sprite digitTwo;
	sf::Sprite digitThree;
	sf::Sprite digitFour;
	sf::Sprite digitFive;
	sf::Sprite digitSix;
	sf::Sprite digitSeven;
	sf::Sprite digitEight;
	sf::Sprite digitNine;
	sf::Sprite digitNegative;
	sf::Sprite digit_1, digit_2, digit_3; //refers to the placement of the digit 

	board() {};
	void setSprites() {
		happySprite.setTexture(TextureManager::GetTexture("face_happy"));
		winSprite.setTexture(TextureManager::GetTexture("face_win"));
		loseSprite.setTexture(TextureManager::GetTexture("face_lose"));
		debugSprite.setTexture(TextureManager::GetTexture("debug"));
		test1Sprite.setTexture(TextureManager::GetTexture("test_1"));
		test2Sprite.setTexture(TextureManager::GetTexture("test_2"));
		test3Sprite.setTexture(TextureManager::GetTexture("test_3"));
	}
	void getBoard(vector<vector<Tiles>>& boardTiles) { //** have to set the numbers here b/c this is where we set the mines
		vector <Tiles> storeTiles;
		//set the tiles down
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
				Tiles tile;
				tile.setTile();
				tile.SetPosition(j*32, i*32);
				storeTiles.push_back(tile);
            }
			boardTiles.push_back(storeTiles);
			storeTiles.clear();
        }
		//set the mines dowm
		for (int i = 0; i < numMines; i++) {
			//we techincally start at row and column 0 due to our index
			int randomRow = Random::Int(0, rows - 1);
			int randomColumn = Random::Int(0, columns - 1);

			if (boardTiles.at(randomRow).at(randomColumn).mines == true) {
				i--; // if this is true, then this run doesn't count as there are already bombs
			}
			else {
				boardTiles.at(randomRow).at(randomColumn).changeMine(true);
			}
		}
	}
	void setNumsOnBoard(vector<vector<Tiles>>& boardTiles) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				for (int k = 0; k <= 8; k++) { 
					// TA helped fix. Had a vector error in which nothing was initialized and couldn't access a certain spot. 
					boardTiles.at(i).at(j).adjacentTiles.push_back(nullptr);
				}
				//remember to clear it in the reset option
				//You wanna make sure you check the corners first. Work in a clockwise motion for the adjacent tiles
				if (i == 0 && j == 0) { // top left corner of baord
					boardTiles.at(i).at(j).adjacentTiles[4] = &boardTiles.at(i).at(j+1);
					boardTiles.at(i).at(j).adjacentTiles[5] = &boardTiles.at(i + 1).at(j + 1);
					boardTiles.at(i).at(j).adjacentTiles[6] = &boardTiles.at(i + 1).at(j);
				}
				else if (i == 0 && j == (columns - 1)) { // top right corner of board
					boardTiles.at(i).at(j).adjacentTiles[6] = &boardTiles.at(i + 1).at(j);
					boardTiles.at(i).at(j).adjacentTiles[7] = &boardTiles.at(i + 1).at(j -1);
					boardTiles.at(i).at(j).adjacentTiles[8] = &boardTiles.at(i).at(j-1);
				}
				else if (i == (rows - 1) && j == (columns - 1)) { // bottom right corner
					boardTiles.at(i).at(j).adjacentTiles[1] = &boardTiles.at(i - 1).at(j);
					boardTiles.at(i).at(j).adjacentTiles[2] = &boardTiles.at(i - 1).at(j - 1);
					boardTiles.at(i).at(j).adjacentTiles[8] = &boardTiles.at(i).at(j - 1);
				}
				else if (i == (rows - 1) && j == 0) { // bottom left corner
					boardTiles.at(i).at(j).adjacentTiles[1] = &boardTiles.at(i - 1).at(j);
					boardTiles.at(i).at(j).adjacentTiles[2] = &boardTiles.at(i - 1).at(j + 1);
					boardTiles.at(i).at(j).adjacentTiles[3] = &boardTiles.at(i).at(j + 1);
				}
				else if (i == 0) {// top side of the baord
					boardTiles.at(i).at(j).adjacentTiles[4] = &boardTiles.at(i).at(j + 1);
					boardTiles.at(i).at(j).adjacentTiles[5] = &boardTiles.at(i + 1).at(j + 1);
					boardTiles.at(i).at(j).adjacentTiles[6] = &boardTiles.at(i + 1).at(j);
					boardTiles.at(i).at(j).adjacentTiles[7] = &boardTiles.at(i + 1).at(j - 1);
					boardTiles.at(i).at(j).adjacentTiles[8] = &boardTiles.at(i).at(j - 1);
				}
				else if (j == (columns - 1)) { // right side of the board
					boardTiles.at(i).at(j).adjacentTiles[1] = &boardTiles.at(i - 1).at(j - 1);
					boardTiles.at(i).at(j).adjacentTiles[2] = &boardTiles.at(i - 1).at(j);
					boardTiles.at(i).at(j).adjacentTiles[6] = &boardTiles.at(i + 1).at(j);
					boardTiles.at(i).at(j).adjacentTiles[7] = &boardTiles.at(i + 1).at(j - 1);
					boardTiles.at(i).at(j).adjacentTiles[8] = &boardTiles.at(i).at(j - 1);
				}

				else if (i == (rows - 1)) {// bottom side of the board
					boardTiles.at(i).at(j).adjacentTiles[1] = &boardTiles.at(i - 1).at(j - 1);
					boardTiles.at(i).at(j).adjacentTiles[2] = &boardTiles.at(i - 1).at(j);
					boardTiles.at(i).at(j).adjacentTiles[3] = &boardTiles.at(i - 1).at(j + 1);
					boardTiles.at(i).at(j).adjacentTiles[4] = &boardTiles.at(i).at(j + 1);
					boardTiles.at(i).at(j).adjacentTiles[8] = &boardTiles.at(i).at(j - 1);
				}

				else if (j == 0) { // left side of the board
					boardTiles.at(i).at(j).adjacentTiles[2] = &boardTiles.at(i - 1).at(j);
					boardTiles.at(i).at(j).adjacentTiles[3] = &boardTiles.at(i - 1).at(j + 1);
					boardTiles.at(i).at(j).adjacentTiles[4] = &boardTiles.at(i).at(j + 1);
					boardTiles.at(i).at(j).adjacentTiles[5] = &boardTiles.at(i + 1).at(j + 1);
					boardTiles.at(i).at(j).adjacentTiles[6] = &boardTiles.at(i + 1).at(j);
				}
				else { //anywhere else in the board
					boardTiles.at(i).at(j).adjacentTiles[1] = &boardTiles.at(i - 1).at(j - 1);
					boardTiles.at(i).at(j).adjacentTiles[2] = &boardTiles.at(i - 1).at(j);
					boardTiles.at(i).at(j).adjacentTiles[3] = &boardTiles.at(i-1).at(j + 1);
					boardTiles.at(i).at(j).adjacentTiles[4] = &boardTiles.at(i).at(j + 1);
					boardTiles.at(i).at(j).adjacentTiles[5] = &boardTiles.at(i + 1).at(j + 1);
					boardTiles.at(i).at(j).adjacentTiles[6] = &boardTiles.at(i + 1).at(j);
					boardTiles.at(i).at(j).adjacentTiles[7] = &boardTiles.at(i + 1).at(j - 1);
					boardTiles.at(i).at(j).adjacentTiles[8] = &boardTiles.at(i).at(j - 1);
				}
			}
		}
		//set the nums in comparison to the mines
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				boardTiles.at(i).at(j).setNum();
			}
		}
	}

	void switchDebug() {
		debugButton = !debugButton;
	}
	void debug(vector<vector<Tiles>>& boardTiles) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
					//we want to be able to turn debug on and off
					//the comment out code was if we wanted to toggle the flag on and off when we pressed the debug button (i misread the instructions)
					if (debugButton == true) { // debug mode on
						if (boardTiles.at(i).at(j).revealed == false && boardTiles.at(i).at(j).mines == true) {
							//boardTiles.at(i).at(j).revealed = true;
							//if (boardTiles.at(i).at(j).flagPresent == true){
							//	boardTiles.at(i).at(j).tempFlag = true; // if there was a flag on the tile, we want it to reappear
							//}
							//boardTiles.at(i).at(j).flagPresent = false;
							boardTiles.at(i).at(j).debugOn = true;
						}
						//debugButton = false; // will be in debug mode until we press it again. So this assignment will let us turn it off as it will go to the "else"
					}
					else if (debugButton == false) {
						if ( boardTiles.at(i).at(j).mines == true) {
							//boardTiles.at(i).at(j).revealed = false;
							//if (boardTiles.at(i).at(j).tempFlag == true) {
							//	boardTiles.at(i).at(j).flagPresent = true; // if there was a flag on the tile, we want it to reappear
							//}
							boardTiles.at(i).at(j).debugOn = false;

						}
						//debugButton = true;
					}
			}
		}
	}

	void setFlag(vector<vector<Tiles>>& boardTiles, int _column, int _row) {
		bool flagPlaced = boardTiles.at(_row).at(_column).changeFlag();
		if (!boardTiles.at(_row).at(_column).revealed) {
			if (flagPlaced) { // if we put down a flag, we get one less mine (theoritically)
				mineCount--;
			}
			else { // take away a flag, we get one more mine (theoritically)
				mineCount++;
			}
		}
		
	}
	//Figure out: out of range??? 
	void revealTile(vector<vector<Tiles>>& boardTiles, int _column, int _row) {
		if (_column <= (columns - 1) && _row <= (rows - 1)) { // if it's in the bounds
			boardTiles.at(_row).at(_column).clicked = true; //sometimes gets out of range exception
			if (!boardTiles.at(_row).at(_column).revealed) {
				if (boardTiles.at(_row).at(_column).flagPresent == false) {
					boardTiles.at(_row).at(_column).changeRevealed();
					tileRevealed++;
					//if there is a mine, don't do the next recursion
					//if there is an adjacent tile that isn't a mine or null ptr
					if (boardTiles.at(_row).at(_column).bombNearby == 0) {
						for (int i = 1; i <= 8; i++) {
							if (boardTiles.at(_row).at(_column).adjacentTiles[i] != nullptr) {
								if (boardTiles.at(_row).at(_column).adjacentTiles[i]->mines == false && boardTiles.at(_row).at(_column).flagPresent == false) {
									revealTile(boardTiles, boardTiles.at(_row).at(_column).adjacentTiles[i]->xCoordinate / 32, boardTiles.at(_row).at(_column).adjacentTiles[i]->yCoordinate / 32);// take the location of the adjacent tile
								}
							}
						}
					}
				}
			}

		}
	}

	void youWin(vector<vector<Tiles>>& boardTiles) {
		if (tileCount - numMines == tileRevealed) {
			finishedGame = true;
			mineCount = 0;
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < columns; j++) {
					if (boardTiles.at(i).at(j).mines) { // if there is a mine, a flag is put over a hidden tile (which it should already be hidden)
						boardTiles.at(i).at(j).flagPresent = true;
						boardTiles.at(i).at(j).winOn = true;
						face_win = true;
						face_happy = false;
					}
				}
			}
		}
	}
	void youLose(vector<vector<Tiles>>& boardTiles) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				if (boardTiles.at(i).at(j).mines == true && boardTiles.at(i).at(j).revealed == true && boardTiles.at(i).at(j).clicked == true && boardTiles.at(i).at(j).flagPresent == false) {
					face_sad = true;
					face_happy = false;
					mineCount = numMines;
					finishedGame = true;
					//if there is mine and a tile revealed, reveal all mines 
					for (int k = 0; k < rows; k++) {
						for (int l = 0; l < columns; l++) {
							if (boardTiles.at(k).at(l).mines) { 
								boardTiles.at(k).at(l).revealed = true;
								boardTiles.at(k).at(l).loseOn = true;
							}
						}
					}
				}
			}
		}
	}
	void getMineNumber(int mineTransformation,int &_temp1, int &_temp2, int &_temp3) {
		if (mineTransformation >= 100) {
			_temp1 = mineTransformation / 100;
			_temp2 = (mineTransformation / 10) % 10;
			_temp3 = mineTransformation % 10;
		}
		else if (mineTransformation >= 10) {
			_temp1 = 0;
			_temp2 = mineTransformation / 10;
			_temp3 = mineTransformation % 10;
		}
		else if (mineTransformation < 10) {
			_temp1 = 0;
			_temp2 = 0;
			_temp3 = mineTransformation;
		}
	}
	void minesCounter() {
		//from SFML how to get part of an image
		//sprite.setTextureRect(sf::IntRect(10, 10, 32, 32));
		//Note: Rect (T rectLeft, T rectTop, T rectWidth, T rectHeight) these are the parameters
		//Each digit will have a recWidth and recHeight of 21x32, as those are the dimensions of one digit
		//To get next digit, just mutiply by the number you want be 21 (the width)
		//The top never changes as we want the texture from top to bottom (the whole number)
		digitZero.setTexture(TextureManager::GetTexture("digits"));
		digitZero.setTextureRect(sf::IntRect(0, 0, 21, 32));
		digitOne.setTexture(TextureManager::GetTexture("digits"));
		digitOne.setTextureRect(sf::IntRect(21 * 1, 0, 21, 32));
		digitTwo.setTexture(TextureManager::GetTexture("digits"));
		digitTwo.setTextureRect(sf::IntRect(21 * 2, 0, 21, 32));
		digitThree.setTexture(TextureManager::GetTexture("digits"));
		digitThree.setTextureRect(sf::IntRect(21 * 3, 0, 21, 32));
		digitFour.setTexture(TextureManager::GetTexture("digits"));
		digitFour.setTextureRect(sf::IntRect(21 * 4, 0, 21, 32));
		digitFive.setTexture(TextureManager::GetTexture("digits"));
		digitFive.setTextureRect(sf::IntRect(21 * 5, 0, 21, 32));
		digitSix.setTexture(TextureManager::GetTexture("digits"));
		digitSix.setTextureRect(sf::IntRect(21 * 6, 0, 21, 32));
		digitSeven.setTexture(TextureManager::GetTexture("digits"));
		digitSeven.setTextureRect(sf::IntRect(21 * 7, 0, 21, 32));
		digitEight.setTexture(TextureManager::GetTexture("digits"));
		digitEight.setTextureRect(sf::IntRect(21 * 8, 0, 21, 32));
		digitNine.setTexture(TextureManager::GetTexture("digits"));
		digitNine.setTextureRect(sf::IntRect(21 * 9, 0, 21, 32));
		digitNegative.setTexture(TextureManager::GetTexture("digits"));
		digitNegative.setTextureRect(sf::IntRect(21 * 10, 0, 21, 32));
		//make a map so that it's easier to refrence these objects, as they are actually numbers
		map<int, sf::Sprite> numberDisplay;
		numberDisplay.emplace(0, digitZero);
		numberDisplay.emplace(1, digitOne);
		numberDisplay.emplace(2, digitTwo);
		numberDisplay.emplace(3, digitThree);
		numberDisplay.emplace(4, digitFour);
		numberDisplay.emplace(5, digitFive);
		numberDisplay.emplace(6, digitSix);
		numberDisplay.emplace(7, digitSeven);
		numberDisplay.emplace(8, digitEight);
		numberDisplay.emplace(9, digitNine);
		numberDisplay.emplace(10, digitNegative);
		//There are three placements of numbers. 
		// All the possiblities:
		// Number over 100 
		// Number is negative as the person places more flags than there are mines (first placement is negative)
		// Number is over 10 (we only care about the last two placements)
		// Number is less than 10 (we only care about the last placement)
		int temp1, temp2, temp3;
		if (mineCount < 0) {
			int fakeMineCount = mineCount * -1;
			getMineNumber(fakeMineCount, temp1, temp2, temp3);
			temp1 = 10; // this will be the negativeSprite
		}
		if (mineCount > 0) {
			getMineNumber(mineCount, temp1, temp2, temp3);
		}
		if (mineCount == 0) {
			temp1 = 0;
			temp2 = 0;
			temp3 = 0;
		}
		digit_1 = numberDisplay[temp1];
		digit_2 = numberDisplay[temp2];
		digit_3 = numberDisplay[temp3];
	}
	void uploadBoard(string fileName, vector<vector<Tiles>>& boardTiles, sf::RenderWindow& window) { // just refrence the getBoard and setNumsBoard
		window.clear();
		boardTiles.clear();
		numMines = 0;
		tileRevealed = 0;
		debugButton = false;
		face_happy = true;
		face_sad = false;
		face_win = false;
		finishedGame = false;

		vector <Tiles> storeTiles;
		for (int i = 0; i < rows; i++) { // this will have the config rows and columns
			for (int j = 0; j < columns; j++) {
				Tiles tile;
				tile.setTile();
				tile.SetPosition(j *32, i *32);
				storeTiles.push_back(tile);
			}
			boardTiles.push_back(storeTiles);
			storeTiles.clear();
		}

		fstream inFile(fileName);
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				// a local variable to tell if it's a 0 or a 1
				char mine;
				//moves on to next character every time we use this
				inFile >> mine;
				if (mine == '1') {
					boardTiles.at(i).at(j).changeMine(true);
					numMines++;
				}
				//gets a weird diagonal. it shifts the columnn over to the right by its current row number.
			}
		}
		mineCount = numMines;
	}

	void drawBoardTiles( sf::RenderWindow &window, vector<vector<Tiles>>& boardTiles) {
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				boardTiles.at(i).at(j).SetPosition(j* 32, i* 32);
				boardTiles.at(i).at(j).Draw(window);
			}
		}
	}
	void drawButtons(sf::RenderWindow& window) {
		//every button is two tiles so that is (2*32) We mutiply by a large number to move it over to the left more
		test1Sprite.setPosition(sf::Vector2f(width - (6*32.0f), height - 88.0f));
		window.draw(test1Sprite);
		test2Sprite.setPosition(sf::Vector2f(width - (4*32.0f), height - 88.f));
		window.draw(test2Sprite);
		test3Sprite.setPosition(sf::Vector2f(width - (2*32.0f), height - 88.f));
		window.draw(test3Sprite);
		debugSprite.setPosition(sf::Vector2f(width - 256.0f, height - 88.f));
		window.draw(debugSprite);
	}
	void drawFace( sf::RenderWindow& window) {
		winSprite.setPosition(sf::Vector2f(width / 2.f, height - 88.f));
		loseSprite.setPosition(sf::Vector2f(width / 2.f, height - 88.f));
		happySprite.setPosition(sf::Vector2f(width / 2.f, height - 88.f));
		if (face_win == true) {
			window.draw(winSprite);
		}
		else if (face_sad == true) {
			window.draw(loseSprite);
		}
		else if (face_happy == true) {
			window.draw(happySprite);
		}
	}
	void drawDigits(sf::RenderWindow& window) {
		//Each digit is 21 units long y direction and 32 units wide
		//shift it downward after all the columns
		//place is on the next row
		//Could do width but its a lot of counting and multiplying
		digit_1.setPosition(sf::Vector2f(columns , height - 88.0f));
		window.draw(digit_1);
		digit_2.setPosition(sf::Vector2f(columns + 21 , height - 88.0f));
		window.draw(digit_2);
		digit_3.setPosition(sf::Vector2f(columns + (21 * 2), height - 88.0f));
		window.draw(digit_3);

	}
};


