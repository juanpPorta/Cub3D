#include "./include/cub3d.h"

/*In summary, the parse_args function is responsible for reading and validating
information from command-line arguments and the configuration file.
It loads information from the specified configuration file using load_info.
It then checks and validates texture paths in the game structure using
check_validate_textures. Similarly, it validates RGB color values in the game
structure using check_validate_rgb, and it also checks and validates the map
data using check_validate_map. After these validations, it fills spaces in the
map and sets map dimensions for consistency using fill_spaces_set_dimensions.
Finally, it ensures the map is square by padding rows/columns if needed using
make_map_square. The function returns TRUE (1) to indicate successful parsing
and validation, and FALSE (0) if any validation fails.*/
int parse_args(t_game *game, char **argv)
{
	// Parse command-line arguments and validate game data
    // This function reads and validates information from command-line arguments.
    
    // Load information from the specified configuration file
	load_info(game, argv[1]);
    // Check and validate texture paths in the game structure
    if (check_validate_textures(game) == FALSE)
        return (FALSE);
    // Check and validate RGB color values in the game structure
    if (check_validate_rgb(game) == FALSE)
        return (FALSE);
	// Check and validate the map data in the game structure
    if (check_validate_map(game) == FALSE)
        return (FALSE);
	// Fill spaces in the map and set map dimensions for consistency
    fill_spaces_set_dimensions(game);
    // Ensure the map is square by padding rows/columns if needed
    make_map_square(game);
    // Return TRUE (1) to indicate successful parsing and validation    
    return (TRUE);
}

int	end_game(t_game *game)
{
	free_exit(game, 0);
	return (0);
}

int main(int argc, char **argv)
{
    t_game  game;

    if (argc != 2)
        return (err_msg(USAGE, 1));
    if (check_arg(argv) == FALSE)
        return (1);
    init_game(&game);
    if (parse_args(&game, argv) == FALSE)
        free_exit(&game, 1);
    init_player_pos(&game);
    init_mlx(&game);
    init_textures(&game);

    print_final_map(&game);

    
    render_frame(&game);
	key_input(&game);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);



    
    print_rgb(&game);
    print_map(&game);
    print_textures(&game);
    print_player(&game);

	
    free_exit(&game, 0);
}

/*This forms the basis for creating a pseudo-3D effect in games like Wolfenstein 3D
and DOOM.

Let's break down the process into steps:

Setup:
Imagine you have a 2D grid representing your game world, where each cell corresponds
to a wall, empty space, or other objects.
You also have the player's position (playerX, playerY) and their direction vector
(dirX, dirY). You also have the camera plane (planeX, planeY) to define the player's
field of view.

Ray Casting Loop:
For each column of pixels on the screen (horizontal lines), cast a ray into the
game world.
Calculate Initial Ray Direction:

The initial ray direction is calculated based on the player's direction and the
camera plane. It determines the angle of the ray relative to the player's field
of view.

Calculate Delta Distance:
The delta distance (deltaX and deltaY) is the distance the ray must travel in the
X and Y directions before crossing one cell of the grid. It's calculated using
trigonometry.

Calculate Step Direction:
The step direction (stepX and stepY) determines whether the ray is moving in a
positive or negative direction in the grid.

Perform Digital Differential Analysis (DDA):
This is the main loop where the ray is cast into the grid. The DDA loop increments
the ray's position in small steps along the ray direction, checking which cell of
the grid the ray is currently in.
It keeps moving the ray until it hits a wall (cell containing a wall) in the grid.

Calculate Wall Distance:
The distance from the player to the wall (perpendicular to the ray) is calculated
using the DDA loop.
This distance will be used to calculate the height of the wall slice to draw on
the screen.

Calculate Wall Slice Height:
The height of the wall slice to draw on the screen is determined by the distance
to the wall and the screen height. Closer walls appear taller, and farther walls
appear shorter.

Calculate Drawing Bounds:
Calculate the upper and lower pixel positions on the screen where the wall
slice should be drawn. This creates a vertical slice representing the wall column.

Draw Wall Slice:
For each column, draw the wall slice using the calculated bounds. You can use the
color of the wall texture at the corresponding position to achieve a textured look.

Render Additional Elements:
After rendering the walls, you can render floors and ceilings to complete the scene.

Legend:
P: Player
W: Wall
R: Ray

Step 1:
##########
#        #
#   P    #
#        #
##########

Step 2:
##########
# R      #
#   P    #
#        #
##########

Step 3:
##########
# R      #
#   P    #
#        #
##########
        ^
        |
     Ray's
     Direction

Step 4:
##########
# R      #
#   P    #
#        #
##########
   ^       
   |       
 Wall      
 Detected  

Step 5:
##########
# R      #
#   P    #
#   W    #
##########
   ^       
   |       
 Wall      
 Hit!     

Step 6:
##########
# R      #
#   P    #
#   W    #
##########
        ^
        |
     Ray's
     Direction

Step 7:
##########
# R      #
#   P    #
#   W    #
##########
        ^
        |
     Wall
     Detected

Step 8:
##########
# R      #
#   P    #
#   W    #
##########
          ^
          |
       Wall
       Hit!

*/