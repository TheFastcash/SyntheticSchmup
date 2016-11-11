# Concept Game Design
Here are all documents about the design of the game.

### Design patterns

Some design patterns are used for the game to simplify conception and understandability.

###### State pattern
The state pattern is used to separate different parts of the game, like the Menu and the Gameplay.
This pattern is pretty simple. All state classes inherit from an interface, this interface will be used by a state manage which will be used on the main program.  
Some links :  
* [General state pattern (wikipedia)]
* [State pattern in game]
[General state pattern (wikipedia)]: https://en.wikipedia.org/wiki/State_pattern
[State pattern in game]: http://www.codeproject.com/Articles/1374/State-Pattern-in-C-Applications
