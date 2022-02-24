#Minesweeper
Minesweeper game made using C++ and Simple and Fast Multimedia Library.

The rules of the game are as follows:
There exists a board, which contains a grid of spaces. A space could be a mine, or not. The player clicks
on a space, and it gets revealed. The goal of the game is to reveal all the spaces that are not mines, while
avoiding the spaces that are.
When a space is revealed:
  -If it’s a mine, the game ends
  -If it’s not a mine, it shows the number of mines adjacent to that space (anywhere from 0 to 8, with 0 just
  showing as an empty space)
  -If a space has no adjacent mines, all non-mine spaces adjacent to it are also revealed The
  player uses the numbers as clues to figure out where other mines may be located.
  -When all of the non-mine spaces have been revealed, the player wins! 
