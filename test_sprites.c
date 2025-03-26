#include "mlx.h"

#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

#define TILE_SIZE 32

typedef struct s_game {
    void *mlx;
    void *win;
    void *img_texture;
} t_game;

int exit_game(t_game *game)
{
    if (game->img_texture)
        mlx_destroy_image(game->mlx, game->img_texture);
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    exit(0);
}

int main(void)
{
    t_game game = {0};
    int width, height;

    // Initialize MiniLibX
    game.mlx = mlx_init();
    if (!game.mlx)
    {
        printf("Error initializing MiniLibX\n");
        return (1);
    }

    // Create a small window
    game.win = mlx_new_window(game.mlx, TILE_SIZE, TILE_SIZE, "Screenshot Test");
    if (!game.win)
    {
        printf("Error creating window\n");
        return (1);
    }

    // Load the XPM from your screenshot
    game.img_texture = mlx_xpm_file_to_image(game.mlx, "duck_sprite_32.xpm", &width, &height);
    if (!game.img_texture || width != TILE_SIZE || height != TILE_SIZE)
    {
        printf("Error loading texture.xpm (check path or size)\n");
        exit_game(&game);
    }

    // Display the texture
    mlx_put_image_to_window(game.mlx, game.win, game.img_texture, 0, 0);

    // Hook for closing window
    mlx_hook(game.win, 17, 0, exit_game, &game);

    // Start event loop
    mlx_loop(game.mlx);

    return (0);
}