#include "../include/cub3d.h"

int valid_texture(char *line)
{
    char **split;

    split = ft_split(line, ' ');
    if (array_size(split) != 2)
    {
        free_char_array(split);
        return (FALSE);
    }
    if (!ft_strcmp(split[0], "NO") && !ft_strcmp(split[0], "SO")
        && !ft_strcmp(split[0], "WE") && !ft_strcmp(split[0], "EA"))
    {
        free_char_array(split);
        return (FALSE);
    }
    if (ext_check_xpm(split[1]))
    {
        free_char_array(split);
        return (TRUE);
    }
    free_char_array(split);
    return (FALSE);
}

char *get_text(char *line)
{
    char **split;
    char *text;

    if (valid_texture(line) == FALSE)
        return (NULL);
    split = ft_split(line, ' ');
    text = rem_nl(split[1]);
    free_char_array(split);
    return (text);
}

int check_validate_textures(t_game *game)
{
    int     i;

    i = 0;
    while (game->map.map[i])
    {
        if (!ft_strncmp(game->map.map[i], "NO", 2))
            game->texture.north = get_text(game->map.map[i]);
        else if (!ft_strncmp(game->map.map[i], "SO", 2))
            game->texture.south = get_text(game->map.map[i]);
        else if (!ft_strncmp(game->map.map[i], "WE", 2))
            game->texture.west = get_text(game->map.map[i]);
        else if (!ft_strncmp(game->map.map[i], "EA", 2))
            game->texture.east = get_text(game->map.map[i]);
        i++;
    }
    if (game->texture.north == NULL || game->texture.south == NULL
        || game->texture.west == NULL || game->texture.east == NULL)
        return (err_msg(INVTEXTURE, FALSE));
    else
        return (TRUE);
}