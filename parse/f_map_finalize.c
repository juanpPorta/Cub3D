#include "../include/cub3d.h"

void    resize_line(t_game *game, int i)
{
    char    *new_line;
    int     j;

    new_line = malloc(sizeof(char) * (game->map.width + 1));
    if (new_line == NULL)
        return ;
    j = 0;
    while (game->f_map[i][j])
    {
        new_line[j] = game->f_map[i][j];
        j++;
    }
    while (j < game->map.width)
    {
        new_line[j] = '1';
        j++;
    }
    new_line[j] = '\0';
    free(game->f_map[i]);
    game->f_map[i] = new_line;
}

void    make_map_square(t_game *game)
{
    int i;

    i = 0;
    while (game->f_map[i])
    {
        if (ft_strlen(game->f_map[i]) < game->map.width)
            resize_line(game, i);
        i++;
    }
}

void    fill_spaces_set_dimensions(t_game *game)
{
    int i;
    int j;
    int max_len;

    i = 0;
    max_len = 0;
    while (game->f_map[i])
    {
        j = 0;
        while (game->f_map[i][j])
        {
            if (game->f_map[i][j] == ' ')
                game->f_map[i][j] = '1';
            j++;
        }
        if (j > max_len)
            max_len = j;
        i++;
    }
    game->map.width = max_len;
}
