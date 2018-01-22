# Animal Guessing Game

Author: Lei Mao

Date: 1/22/2018

## Introduction

Animal Guessing Game is a word-based guessing game. Player first think of an animal in the mind. The bot will ask a couple of questions with binary yes/no answers. The player answer the questions with yes/no. If the bot guesses the animal correctly, the bot wins. Otherwise, the player wins. At the cost of winning, the player has to provide a useful question regarding the animal in the mind. There is a such [Animal Game](http://www.animalgame.com/) online which you can play with.

## Demo

```
Please think of an animial in your mind.
Does it fly?
Please input "yes" or "no".
yes
Is it dove?
no
Now I give up.
What is it?
bee
I see. How do I tell it apart from dove?
Please give a question with a yes or no answer.
Is it an insect?
OK. bee. Is it an insect?
yes
Thank you. I have learned a lot about bee.
```

## Usage

The executable file "animal" has been compiled on Ubuntu 16.04 using g++ 5.4.0. Ubuntu users should be able to use the program directly.

```shell
./animal
```

To compile the from the source code, simply run:

```shell
make
```

## Notes

* There is nothing special about this game. The bot basically uses the information that the player provided to construct binary trees.
* There are some other C++ versions of this game on GitHub. However, their game is not able to saved the latest information before closing the program. My Animal Guessing Game saves the animal information in a certain data structure into the file. The game will load the accumulated animal information from the file before the game.
* You are welcome to contribute the data for this game!
