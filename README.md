# Project Progress

# (21/11/25)
## What the game has currently:
> 1. Basic implementation of player. Moving left/right and jumping. Currently manages states with an enum class within the Player.h file.
> 2. Platforms along with a simple collision system that set the player's ground level to be that of the top of the platform if they collide.

## Need to focus on next:
> 1. Implement an animation loader and put in temporary assets.
> 2. Work on the collision system to include platforms that are like walls which stop the player from going through them, also fix current collision 
(looks choppy).
> 3. Adding more states to the player. (Falling, dashing, double jump ability).

# (22/11/25)
## What was added to the game:
> 1. Animation loader with working idle animation.

## Need to focus on next:
> 1. Implement animation for all current states
> 2. Work on the collision system to include platforms that are like walls which stop the player from going through them, also fix current collision 
(looks choppy).
> 3. Adding more states to the player. (Falling, dashing, double jump ability).

# (24/11/25)
## What was added to the game:
> 1. Added a falling state separate to jumping to distinguish animations.
> 2. Animation frames for running, jumping, falling
> 3. Fixed landing on a platform, now looks like the player lands instead of colliding with the platform and being moved back onto it.

## Need to focus on next:
> 1. Fix platform collisions from sides and below. (Potentially add ledge climbing)
> 2. Work on the collision system to include platforms that are like walls which stop the player from going through them.
> 3. Add a double jump to the player.
> 4. Add a dash to the player.

# (15/12/25)
## What was added to the game:
> 1. Changed character sprite.
> 2. Added dashing, sliding and wall-sliding states with animations.
> 3. Started on making a tile based map. The tile sprites are set dynamically and changing the layout of times changes the sprites accodingly.

## Need to focus on next:
> 1. Change fully from platforms to tiles.
> 2. Make player collision work based on tiles instead.
> 3. Add a double jump to the player.
> 4. Add a dash to the player.

# (18/12/25)
## What was added to the game:
> 1. Added corner tiles and made a setTextureRect function for the intRects for the tile sprites.
> 2. Changed screen size to match 16:9 ratio.
> 3. Removed some unneccessary bits of code and images.

## Need to focus on next:
> 1. Change fully from platforms to tiles.
> 2. Make player collision work based on tiles instead.
> 3. Make levels load tiles from file.
> 4. Add a double jump to the player.
> 5. Add a dash to the player.

# (22/12/25)
## What was added to the game:
> 1. Player now collides with the tiles instead of the platforms.
> 2. Removed platforms from game.

## Need to focus on next:
> 1. Make levels load tiles from file.
> 2. Work on more accurate collisions (player stops on either side and bottom so they cant jump through the tiles or walk through them).
> 3. Add a double jump to the player.
> 4. Add a dash to the player.

# (08/01/26)
## What was added to the game:
> 1. Added a menu.
> 2. Added game states and update and render functions for the gameplay state and menu state rescpectively.

## Need to focus on next:
> 1. Make levels load tiles from file.
> 2. Work on more accurate collisions (player stops on either side and bottom so they cant jump through the tiles or walk through them).
> 3. Add a double jump to the player.
> 4. Add a dash to the player.