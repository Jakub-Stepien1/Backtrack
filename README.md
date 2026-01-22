# Project Progress

# (22/01/26)
## What was added to the game:
> 1. Optimizing code, moved texture int rect constants out of tile class since each tile had a copy of all constants, put the constants into a new "GlobalConstants" file.
> 2. Added brick sprite textures, 1's are grass tiles, 2's are brick tiles.

## Need to focus on next:
> 1. Make a level editor to easily be able to edit and make new levels and be able to save those level as text files.
> 2. Work on more accurate collisions (player stops on either side and bottom so they cant jump through the tiles or walk through them).
> 3. Add a double jump to the player.
> 4. Add a dash to the player.