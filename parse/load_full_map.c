#include "../include/cub3d.h"

int get_line_count(char *path)
{
    int     fd;
    int     line_count;
    char    *line;

    line_count = 0;
    fd = open(path, O_RDONLY);
    if (fd < 0)
        return (err_msg(NOFILE, 0));
    line = get_next_line(fd);
    while (line)
    {
        line_count++;
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (line_count);
}

void    fill_map(t_game *game, int row, int col, int i)
{
    char   *line;

    line = get_next_line(game->map.fd); // Get first line of map
    while (line != NULL)
    {
        game->map.map[row] = malloc(sizeof(char) * ft_strlen(line) + 1);
        if (!game->map.map[row])
        {
            err_msg(MALLOCFAIL, 0);
            free(line);
            game->map.map[row] = NULL;
            return ;
        }
        col = 0;
        while (line[i])
            game->map.map[row][col++] = line[i++];
        game->map.map[row][col] = '\0';
        row++;
        i = 0;
        free(line);
        line = get_next_line(game->map.fd);
    }
    game->map.map[row] = NULL; // Set last element of map array to NULL
}

int load_info(t_game *game, char *path)
{
    int i;
    int row;
    int col;

    i = 0;
    row = 0;
    col = 0;
    game->map.fd = open(path, O_RDONLY); // Open file to struct
    if (game->map.fd < 0) // Check if file exists
        return (err_msg(NOFILE, 0));
    game->map.path = ft_strdup(path); // Save path to struct (argv[1])
    game->map.line_count = get_line_count(path); // Get line count of map
    if (game->map.line_count <= 10) // Check if line count is valid
        return (err_msg(INVMAP, 0));
    game->map.map = ft_calloc(game->map.line_count + 1, sizeof(char *));
    if (!game->map.map) // Check if malloc failed
        return (err_msg(MALLOCFAIL, 0));
    fill_map(game, row, col, i); // Fill map array with map from file
    close(game->map.fd); // Close file
    return (TRUE);
}
