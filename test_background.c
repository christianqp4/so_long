#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

#define TILE_SIZE 32

typedef struct s_game {
    void *mlx;
    void *win;
    void *img_texture;
    void *bg_img;  // Background image
} t_game;

int exit_game(t_game *game)
{
    if (game->img_texture)
        mlx_destroy_image(game->mlx, game->img_texture);
    if (game->bg_img)
        mlx_destroy_image(game->mlx, game->bg_img);
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    exit(0);
}

int main(void)
{
    t_game game = {0};
    int width, height;
    int bpp, size_line, endian;

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

    // Create a background image
    game.bg_img = mlx_new_image(game.mlx, TILE_SIZE, TILE_SIZE);
    char *bg_data = mlx_get_data_addr(game.bg_img, &bpp, &size_line, &endian);

    // Fill the background with black (0x000000)
    int color = 0x000000;  // Black
    int i;
    for (i = 0; i < TILE_SIZE * TILE_SIZE; i++)
    {
        ((int *)bg_data)[i] = color;
    }

    // Draw the background image to the window
    mlx_put_image_to_window(game.mlx, game.win, game.bg_img, 0, 0);

    // Load the sprite
    game.img_texture = mlx_xpm_file_to_image(game.mlx, "duck_sprite_32.xpm", &width, &height);
    if (!game.img_texture || width != TILE_SIZE || height != TILE_SIZE)
    {
        printf("Error loading good_duck_sprite.xpm (check path or size)\n");
        exit_game(&game);
    }

    // Draw the sprite on top of the background
    mlx_put_image_to_window(game.mlx, game.win, game.img_texture, 0, 0);

    // Hook for closing the window
    mlx_hook(game.win, 17, 0, exit_game, &game);

    // Start the event loop
    mlx_loop(game.mlx);

    return (0);
}