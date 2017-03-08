# Chess-In-C
This is a Chess game written in C. It uses a borked [Algebraic Chess notation](https://en.wikipedia.org/wiki/Algebraic_notation_(chess)) for entering moves (possibly moving to [PGN](https://en.wikipedia.org/wiki/Portable_Game_Notation) down the road). It currently only has both players' pieces represented, and can move them relatively freely. Currently writing piece specific logic and collision detection.

**Note:** This code is a mess. It's strictly a learning exercise and I am continuing to iterate on it as I learn the language.

# Run It

* `make`
* `./chess`

# To Do

* Code abstraction!
* Code documentation
* Variable name cleanup
* Add automated testing capabilities
* Add logic that ensures movement is valid for each respective piece
* Add collision detection and capturing of opponent pieces
* Add logic for check and checkmate

# Ideas

* Rudimentary visual representation of the board that's not simply Chess notation in a table
* Basic AI (to experiment with algorithm development)
* Basic multiplayer (to experiment with low level network programming)
