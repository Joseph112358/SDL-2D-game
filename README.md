Welcome to my C++ SDL game!

Tl;dr: This is my 2D, SDL game. I'm mainly just using it to learn and prototype concepts for now. I might choose
To implement / flesh out these ideas in a custom SDL game engine, or use an existing game engine such as Monogame or godot.

Technology used
Written in C++ (Mingw compiler) with the SDL2 graphics library
Makefile used as a build tool
Most of development done using VS code.

Running the program (WIP)

Ideas (WIP): This is just for me to brainstorm what I want to implement some fun levels and features in the game

Level ideas, find the cake slices? -> 
-- Find all the different slices
-- as you find each one, a sprite in the middle completes itself
-- Once done, confetti + celebration, not enough slices for everyone
-- Player has to go to back room to find more -> level 2

Level 2 repair animatronics?

TODO:
* Create a level class / data object to store level data (room layout etc)
* Migrate static arrays to dynamic array (vector probably)
* Create 2 rooms / levels -> one outside farming game, one inside (existing room)
* Detail room with chairs and tables,
* Add NPC's
* Create Level 2 once basic functionality is fleshed out more.

Retrospective (WIP)

Whilst the rendering system I have used works (and was mostly desgined myself). It is not scalable or optimal