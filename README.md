# Qwirkle

Computer course project


### Purpose

During our first year we had to work in groups of three on this project. We had a total of one month to produce a reproduction of the board game Qwirkle.


### What is the game

Qwirkle is a board game, each player gets a number of tiles, the goal is to align them either by their same shape or by their same color. The more you line up and complete the rows, the more points you earn. The game ends when there are no more tiles left in the deck, and the player with the most points wins.


### Code Explanations

This project was carried out in C in the form of a console application. The code is split into several source files : 
- **etatJeu.c** : Take care of state of play processing (*new part*) 
- **interfaces.c** : Display of the different game windows (*rules, desk, scores*)
- **tuiles.c** : Treatment of tile structures (*generate deck, swap*)
- **sauvegarde.c** : Open and write to file to save a game
- **plateau.c** : Check the placement on the board according to the rules of the game
- **ia.c** : Bot system to play against non-players


### Credits

Resources created by Martin CONDET, Emma TERRAT and Lisa AMALOU.
Any non-profit use should be credited.