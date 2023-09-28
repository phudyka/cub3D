/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtassel <dtassel@42.nice.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:49:16 by phudyka           #+#    #+#             */
/*   Updated: 2023/09/28 04:34:05 by dtassel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

// X = WIDTH = abscissa axis
// Y = HEIGHT = ordinate axis

// -- GLOBAL -- //
# define WIDTH 1280  // Window Width
# define HEIGHT 720 // Window Height
# define SPRITE 15  // Sprite Size
# define MOVESPEED 0.03 // Player Move Speed
# define ROTSPEED 0.01
# define PI 3.14159265359
# define FOV (60 * (PI / 180.0))

// -- TEXTURES -- //
# define WALL_MM "./utils/sprite/map/wall_map.xpm"
# define FLOOR_MM "./utils/sprite/map/floor_map.xpm"
# define PLAYER_MM "./utils/sprite/map/player_map.xpm"
# define RED 0xFF0000
# define GREEN_WALL 0x228B22
# define GREEN 0xADFF2F
# define BLUE 0x87CEEB
# define YELLOW 0xFFFF00
# define WHITE 0xFFFFFF
# define GREY 0x505050
# define BROWN 0x7B6D51

// -- BINDING KEYS -- //
# define W      119   //  _______________________
# define A      97    // [Basic WASD Deplacements]
# define S      115   //
# define D      100   //
# define UP     65362 //  ________________________________
# define LEFT   65361 // [Can use Directionnals Arrows too]
# define RIGHT  65363 //
# define DOWN   65364 //
# define ESC    65307 // Quit game
# define Q      113   // Quit game

# include <math.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <stdbool.h>
# include <X11/keysym.h>
# include "get_next_line.h"
# include "../utils/libft/libft.h"
# include "../utils/libft/libft.h"
# include "../minilibx-linux/mlx.h"

typedef struct s_img3D
{
    char    *pixels;
    int     bpp;
    int     size_line;
    int     endian;
	int     width;
    int     height;
}               t_img3D;

typedef struct s_img2D
{
    char    *pixels;
    int     bpp;
    int     size_line;
    int     endian;
	int     width;
    int     height;
}               t_img2D;

typedef struct s_texture
{
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	void	*player_map;
	void	*wall_map;
	void	*floor_map;
}				t_texture;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct s_keys
{
    int w;
    int a;
    int s;
    int d;
	int	left;
	int	right;
}               t_keys;

typedef struct s_engine
{
	int		total_moves;
	int		rotate;
    int		move_x;
    int		move_y;
	char	coord;
    char    **map;      // 2D map
    char    **cub;
    int     width;
    int     height;
	int		wall_side;
}           t_engine;

typedef struct s_ray
{
	int		hit;
	int		mapx;
	int		mapy;
    double  dir_x;		//player direction
    double  dir_y;
    double  player_x;   // player pose in map --mapX
    double  player_y;   
	double	plane_x;	//
	double	plane_y;
	double	ray_x;		// ray
	double	ray_y;
	double	cam_x;		// camera
	double	cam_y;	
	double	dist_x; // Lenght Of The Ray from Player pos to Next Pos -- sideDistX
	double	dist_y;
	double	delta_x; // Distance from player to next Wall impact  -- deltaSideX
	double	delta_y;
	double	wall_dist;
	double	p_angle;	// camera angle FOV
	double	angle;
	double	start;
	double	distance;
	
}			t_ray;

typedef struct  s_cub
{
	void        *mlx;
	void        *window;
	void		*img_map2D;
	void		*img_map3D;
	int         mini;
	int			count_color_c;
	int			count_color_f;
    t_keys      keys;
	t_texture   texture;
	t_color     ceiling;
	t_color     floor;
	t_engine    engine;
	t_ray		ray;
	t_img2D		img2D;
	t_img3D		img3D;
}   t_cub;

int		ft_abs(int nbr);
void	ft_init_ray(t_cub *game);
void    ft_init_direction(t_cub *game);
void    ft_init_minimap(t_cub *game);
void    check_map(t_cub *game);
int     master_parser(t_cub *cub, int argc, char **argv);
void    ft_minimap(t_cub *game);
void    ft_free_map(t_cub *game);
void    ft_error(char *msg);
void    ft_error_free(char *msg, t_cub *game);
int     ft_move(t_cub *game);
int		ft_rotate(double rotation, t_cub *game);
int     check_move(double x, double y, t_cub *game);
int		ft_render(t_cub *game);
int     ft_cub(t_cub *game);
int     game_over(t_cub *game);
int     parse_east_texture(char *line, t_cub *game);
int     parse_west_texture(char *line, t_cub *game);
int     parse_south_texture(char *line, t_cub *game);
int     parse_north_texture(char *line, t_cub *game);
void	floor_ceiling_color(char *line, t_cub *game);
void    free_array(char **array);
int		check_valid_path(t_cub *game);
void	check_valid_conf(t_cub *game);
void	ft_destroy_img(t_cub *game);
void	game_over_error(char *msg, t_cub *game);
void	get_map(t_cub *game, char **argv);
int		is_configuration(char *line);
int		is_map_line(char *line);
void	cast_ray(t_cub *game);
void 	ft_caster(t_cub *game, double ray_angle);
void	render_3D(t_cub *game, int column, double distance);
void	draw_3Dview(t_cub *game);
void	ft_draw_minimap(int x, int y, void *img_src, t_cub *game);
void	draw_ray(t_cub *game, int ray_x, int ray_y);

#endif
