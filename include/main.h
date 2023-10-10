/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:49:16 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/10 14:07:50 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

// X = WIDTH = abscissa axis
// Y = HEIGHT = ordinate axis

// -- GLOBAL -- //
# define WIDTH 1024  // Window Width
# define HEIGHT 576 // Window Height
# define SPRITE 10  // Sprite Size
# define MOVESPEED 0.06 // Player Move Speed
# define ROTSPEED 0.03
# define PI 3.14159265359
# define HD 256
# define WRAP 20

// -- TEXTURES -- //

# define N_WALL "./sprite/textures/north_wall.xpm"
# define S_WALL "./sprite/textures/south_wall.xpm"
# define E_WALL "./sprite/textures/east_wall.xpm"
# define W_WALL "./sprite/textures/west_wall.xpm"
# define CEILING "./sprite/textures/ceiling.xpm"
# define FLOOR "./sprite/textures/floor.xpm"
# define DOOR "./sprite/textures/door.xpm"
# define OPEN_DOOR "./sprite/textures/door_open.xpm"
# define WEAPON1 "./sprite/weapons/weapon0.xpm"
# define RELOAD "./sprite/weapons/reload0.xpm"
# define SHOOT "./sprite/weapons/shoot0.xpm"
# define AMBIENCE_WAV "./audio/ambience.wav"
# define DOOR_OPEN_WAV "./audio/door_open.wav"
# define DOOR_CLOSE_WAV "./audio/door_close.wav"
# define RELOAD_WAV "./audio/reload0.wav"
# define SHOOT_WAV "./audio/shoot0.wav"
# define TARGET "./sprite/textures/cible.xpm"
# define RED 0xFF0000
# define GREEN_WALL 0x228B22
# define GREEN 0xADFF2F
# define BLUE 0x282828
# define YELLOW 0xFFFF00
# define WHITE 0xFFFFFF
# define GREY 0x505050
# define BROWN 0x353535
# define BLACK 0x000000

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
# define E      101   // Open Door

# include <math.h>
# include <time.h>
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
# include "../mlx/mlx.h"

typedef struct	s_sprite_params
{
	int		x;
	int		y;
	int		sprite_width;
	int		sprite_height;
	int		sprite_screen_x;
}				t_sprite_params;

typedef struct  s_params
{
    double  sprite_x;
    double  sprite_y;
    double  *transform_x;
    double  *transform_y;
    double  inv_det;
}               t_params;

typedef struct s_sprite
{
	double	x;
	double	y;
	double	distance;
	double	relative_x;
	double	relative_y;
	int		is_visible;
	int		width;
	int		height;
}			t_sprite;

typedef struct s_img
{
	char	*pixels;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}			t_img;

typedef struct s_texture
{
	int		direction;
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*ceiling;
	char	*floor;
	char	*weapon1;
	char	*reload;
	char	*shoot;
	char	*door;
	char	*open_door;
	char	*target;
}			t_texture;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}				t_color;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}				t_keys;

typedef struct s_engine
{
	int		total_moves;
	int		rotate;
	int		move_x;
	int		move_y;
	char	coord;
	char	**map;
	char	**cub;
	char	**door;
	int		width;
	int		height;
	int		wall_side;
	double	angle;
}				t_engine;

typedef struct s_ray
{
	int		hit;
	int		mapx;
	int		mapy;
	double	dir_x;
	double	dir_y;
	double	player_x;
	double	player_y;
	double	plane_x;
	double	plane_y;
	double	ray_x;
	double	ray_y;
	double	cam_x;
	double	cam_y;	
	double	dist_x;
	double	dist_y;
	double	delta_x;
	double	delta_y;
	double	wall_x;
	double	p_angle;
	double	angle;
	double	start;
	double	distance;
	int		wall_height;
	double	tex_x;
	int		step_x;
	int		step_y;
	int		side;
	int		draw_start;
	int		draw_end;
	double	*z_buffer;
}				t_ray;

typedef struct s_cub
{
	void		*mlx;
	void		*window;
	void		*img_map2d;
	void		*img_map3d;
	void		*weapon_3d;
	int			mini;
	int			count_color_c;
	int			count_color_f;
	int			num_sprites;
	clock_t		cur;
	t_keys		keys;
	t_texture	texture;
	t_color		ceiling;
	t_color		floor;
	t_engine	engine;
	t_ray		ray;
	t_img		img2d;
	t_img		img3d;
	t_img		weapon;
	t_sprite	*sprite;
	t_params	params;
}				t_cub;

void	ft_init_ray(t_cub *game);
void	ft_init_direction(t_cub *game);
void	check_map(t_cub *game);
int		master_parser(t_cub *cub, int argc, char **argv);
void	ft_minimap(t_cub *game);
void	ft_free_map(t_cub *game);
void	ft_error(char *msg);
void	ft_error_free(char *msg, t_cub *game);
int		ft_move(t_cub *game);
int		ft_rotate(double rotation, t_cub *game);
int		check_move(double x, double y, t_cub *game);
int		ft_render(t_cub *game);
int		ft_cub(t_cub *game);
int		game_over(t_cub *game);
int		parse_east_texture(char *line, t_cub *game);
int		parse_west_texture(char *line, t_cub *game);
int		parse_south_texture(char *line, t_cub *game);
int		parse_north_texture(char *line, t_cub *game);
void	floor_ceiling_color(char *line, t_cub *game);
void	free_array(char **array);
int		check_valid_path(t_cub *game);
void	check_valid_conf(t_cub *game);
void	ft_destroy_img(t_cub *game);
void	game_over_error(char *msg, t_cub *game);
void	get_map(t_cub *game, char **argv);
int		is_configuration(char *line);
int		is_map_line(char *line);
void	cast_ray(t_cub *game);
void	ft_caster(t_cub *game);
void	render_3D(int x, t_cub *game);
void	draw_3Dview(t_cub *game);
void	ft_draw_minimap(int x, int y, int *color, t_cub *game);
void	draw_ray(t_cub *game, int ray_x, int ray_y);
void	ft_input(t_cub *game);
int		key_release(int key, t_cub *game);
int		key_press(int key, t_cub *game);
int		ft_colorpix(int x, int y, void *texture, t_cub *game);
void	ft_init_mlx(t_cub *game);
void	ft_init_dda(int x, t_cub *game);
void	print_cub(void);
void	ft_fraps(t_cub *game);
int		ft_colorpix_ceifloo(int x, int y, void *texture, t_cub *game);
void	ft_draw_weapon(t_cub *game);
void	ft_crosshair(t_cub *game);
void    choose_texture(int x, t_cub *game);
void	draw_texture(int x, void *texture, t_cub *game);
void	init_sprite(t_cub *game);
void	render_sprite(t_cub *game);
void	door_state(int x, int y, t_cub *game);
bool	should_draw_pixel(int pixel_color, int color_to_ignore);

#endif
