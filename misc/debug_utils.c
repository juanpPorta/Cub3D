#include "../include/cub3d.h"

void print_map(t_game *game)
{
    int i;

    i = 0;
    printf("\n");
    while (game->map.map[i])
    {
        printf("%s", game->map.map[i]);
        i++;
    }
    printf("\n");
}

void print_final_map(t_game *game)
{
    int i;

    i = 0;
    if (game->f_map == NULL)
        return ;
    printf("\n");
    while (game->f_map[i])
    {
        printf("%s\n", game->f_map[i]);
        i++;
    }
    printf("\n");
}

void print_rgb(t_game *game)
{
    printf("Floor: %d, %d, %d\n", game->texture.floor.r, game->texture.floor.g, game->texture.floor.b);
    printf("Ceiling: %d, %d, %d\n", game->texture.ceiling.r, game->texture.ceiling.g, game->texture.ceiling.b);
    printf("Floor Hex: %lx\n", rgb_to_hex(game, "F"));
    printf("Ceiling Hex: %lx\n", rgb_to_hex(game, "C"));
    printf("\n");
}

void print_textures(t_game *game)
{
    printf("\n");
    printf("North: %s\n", game->texture.north);
    printf("South: %s\n", game->texture.south);
    printf("West: %s\n", game->texture.west);
    printf("East: %s\n", game->texture.east);
    printf("\n");
}

void print_player(t_game *game)
{
    printf("\n");
    printf("Player Dir: %c\n", game->player.dir);
    printf("Player Pos: %f, %f\n", game->player.pos_x, game->player.pos_y);
    printf("Player Dir: %f, %f\n", game->player.dir_x, game->player.dir_y);
    printf("Player Plane: %f, %f\n", game->player.plane_x, game->player.plane_y);
    printf("Player has moved: %d\n", game->player.has_moved);
    printf("Player moved x: %d\n", game->player.move_x);
    printf("Player moved y: %d\n", game->player.move_y);
    printf("Player rotated: %d\n", game->player.rotate);
    printf("\n");
}