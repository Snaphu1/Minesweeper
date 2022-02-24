#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <ctime>
#include <map>
#include "TextureManager.h"
#include "Random.h"
#include "board.h"
#include "Tiles.h"
using namespace std;

void uploadConfig(string filename, board &boardData) {
    //Loading config file
    fstream inFile(filename);
    string widthString;
    string heightString;
    string mineString;
    int width;
    int columns;
    int height;
    int rows;
    int numMines;
    int tileCount;

    getline(inFile, widthString);
    width = stoi(widthString);
    tileCount = width;
    columns = width;
    width = width * 32;
    getline(inFile, heightString);
    height = stoi(heightString); 
    tileCount = tileCount * height;
    rows = height;
    height = (height * 32) + 88;
    getline(inFile, mineString);
    numMines = stoi(mineString);

    //Tried putting into an object
    //Put the new data into the board coming in
    boardData.columns = columns;
    boardData.rows = rows;
    boardData.numMines = numMines;
    boardData.width = width;
    boardData.height = height;
    boardData.tileCount = tileCount;
    boardData.tileRevealed = 0;
    boardData.mineCount = numMines;
}

int main()
{
    board gameBoard;
    uploadConfig("boards/config.cfg", gameBoard);
    sf::RenderWindow window(sf::VideoMode(gameBoard.width, gameBoard.height), "Minesweeper");
    vector<vector <Tiles>> boardTiles;
    gameBoard.getBoard(boardTiles);
    gameBoard.setNumsOnBoard(boardTiles);
    gameBoard.setSprites();
    gameBoard.numMinesTwo = gameBoard.numMines;//this is for the fact that we need to save the original config numMines, as the numMines changes with the test board

    //As long as SFMl is open, keep looping
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                sf::Vector2f mousePosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                //Has to be in bounds of baoard. Could use get global bounds. Figured out how to use it later on
                int xPosition = sf::Mouse::getPosition(window).x;
                int yPosition = sf::Mouse::getPosition(window).y;
                int columnTile = xPosition / 32; // every single tile is 32 bits
                int rowTile = yPosition / 32;
                //Set flag down on tile
                if (!gameBoard.finishedGame) { // if game is over, we can't change it's components
                    if (columnTile <= (gameBoard.columns - 1) && rowTile <= (gameBoard.rows - 1)) {
                        gameBoard.setFlag(boardTiles, columnTile, rowTile);
                    }
                }
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2f mousePosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
                int xPosition = sf::Mouse::getPosition(window).x;
                int yPosition = sf::Mouse::getPosition(window).y;
                int columnTile = xPosition / 32;
                int rowTile = yPosition / 32;
                if (!gameBoard.finishedGame) {
                    //Reveals the tile and increments clicked by one
                    if (columnTile <= (gameBoard.columns - 1) && rowTile <= (gameBoard.rows - 1)) {
                        gameBoard.revealTile(boardTiles, columnTile, rowTile);
                        }
                    //Flips the switch for debug and reveals all mines/removing any flags on them (they appear back if debug button is pressed again
                    if (gameBoard.debugSprite.getGlobalBounds().contains(mousePosition)) {
                        gameBoard.switchDebug();
                        gameBoard.debug(boardTiles);
                    }
                }
                //Reset button
                 // The happy, sad, win face all overlap in the same location, so only have to do an if statement for one of them
                if (gameBoard.happySprite.getGlobalBounds().contains(mousePosition)) {
                    //don't need to reset the sprites as we need the same ones
                    window.clear();
                    boardTiles.clear();
                    gameBoard.numMines = gameBoard.numMinesTwo;
                    gameBoard.mineCount = gameBoard.numMines;
                    gameBoard.tileRevealed = 0;
                    gameBoard.debugButton = false; 
                    gameBoard.face_happy = true; 
                    gameBoard.face_sad = false; 
                    gameBoard.face_win = false;
                    gameBoard.finishedGame = false;
                    // Will set new bombs and tiles. everything should go back to normal due to setTile() function
                    gameBoard.getBoard(boardTiles);
                    gameBoard.setNumsOnBoard(boardTiles);
                }
                if (gameBoard.test1Sprite.getGlobalBounds().contains(mousePosition)) {
                    gameBoard.uploadBoard("boards/testboard1.brd", boardTiles, window);
                    gameBoard.setNumsOnBoard(boardTiles);
                }
                if (gameBoard.test2Sprite.getGlobalBounds().contains(mousePosition)) {
                    gameBoard.uploadBoard("boards/testboard2.brd", boardTiles, window);
                    gameBoard.setNumsOnBoard(boardTiles);
                }
                if (gameBoard.test3Sprite.getGlobalBounds().contains(mousePosition)) {
                    gameBoard.uploadBoard("boards/testboard3.brd", boardTiles, window);
                    gameBoard.setNumsOnBoard(boardTiles);
                }
            }
        }   

        //1. Gets rid of anything that was previously drawn
        window.clear();

        //2. Draw anything we want to appear on the screen
        //Makes background white
        sf::RectangleShape rectangle(sf::Vector2f(gameBoard.width, gameBoard.height));
        rectangle.setFillColor(sf::Color(255., 255, 255));
        window.draw(rectangle);

       //You can still win and lose in debug mode
        gameBoard.minesCounter();
        gameBoard.drawDigits(window);
        gameBoard.drawButtons(window);
        gameBoard.drawBoardTiles(window, boardTiles);
        gameBoard.drawFace(window);
        gameBoard.youLose(boardTiles);
        gameBoard.youWin(boardTiles);
   
        //3. Presents the results of the drawings for rendering
        window.display();
    }

    //Clear out any textures before program ends
    TextureManager::Clear();
    return 0;
}