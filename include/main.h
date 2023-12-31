/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phudyka <phudyka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 15:49:16 by phudyka           #+#    #+#             */
/*   Updated: 2023/10/13 17:19:22 by phudyka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

// X = WIDTH = abscissa axis
// Y = HEIGHT = ordinate axis

// -- GLOBAL -- //
# define WIDTH 1024 		// Window Width
# define HEIGHT 576 		// Window Height
# define SPRITE 10 			// Minimap elements Size
# define MOVESPEED 0.06 	// Player Move Speed
# define ROTSPEED 0.03	  	// Cam and arrows rotation speed
# define PI 3.14159265359
# define HD 256 			// Textures Resolution
# define WRAP 20

// -- TEXTURES -- //
# define N_WALL "./sprite/textures/north_wall.xpm"
# define S_WALL "./sprite/textures/south_wall.xpm"
# define E_WALL "./sprite/textures/east_wall.xpm"
# define W_WALL "./sprite/textures/west_wall.xpm"
# define CEILING "./sprite/textures/ceiling.xpm"
# define FLOOR "./sprite/textures/floor.xpm"
# define DOOR "./sprite/textures/door.xpm"
# define WEAPON1 "./sprite/weapons/weapon0.xpm"
# define RELOAD0 "./sprite/weapons/reload0.xpm"
# define RELOAD1 "./sprite/weapons/reload1.xpm"
# define SHOOT "./sprite/weapons/shoot0.xpm"
# define EMPTY "./sprite/weapons/shoot1.xpm"
# define TARGET "./sprite/textures/cible.xpm"
# define AMBIENCE_WAV "./audio/ambience.wav"
# define DOOR_OPEN_WAV "./audio/door_open.wav"
# define DOOR_CLOSE_WAV "./audio/door_close.wav"
# define RELOAD_WAV "./audio/reload0.wav"
# define SHOOT_WAV "./audio/shoot0.wav"
# define EMPTY_WAV "./audio/shoot1.wav"
# define TARGET_WAV "./audio/target.wav"
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
# define W			119   //  _______________________
# define A			97    // [Basic WASD Deplacements]
# define S			115   //
# define D			100   //
# define LEFT		65361 // [Camera Rotation]
# define RIGHT		65363 //
# define ESC		65307 // Quit game
# define Q			113   // Quit game
# define E			101   // Open Door
# define R			114	  // Reload Weapon
# define T 			116	  // Respawn targets
# define SPACE		32 	  // Fire Weapon

# include <math.h>
# include <time.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <X11/keysym.h>
# include "get_next_line.h"
# include "../utils/libft/libft.h"
# include "../mlx/mlx.h"

typedef struct s_sprite_params
{
	int	x;
	int	y;
	int	sprite_width;
	int	sprite_height;
	int	sprite_screen_x;
}		t_sprite_params;

typedef struct s_params
{
	double	sprite_x;
	double	sprite_y;
	double	*transform_x;
	double	*transform_y;
	double	inv_det;
}		t_params;

typedef struct s_mix
{
	unsigned char	fog_r;
	unsigned char	fog_g;
	unsigned char	fog_b;
	unsigned char	new_r;
	unsigned char	new_g;
	unsigned char	new_b;
	unsigned char	og_r;
	unsigned char	og_g;
	unsigned char	og_b;
}			t_mix;

typedef struct s_sprite
{
	int		x;
	int		y;
	double	distance;
	double	relative_x;
	double	relative_y;
	int		is_alive;
	int		width;
	int		height;
}		t_sprite;

typedef struct s_img
{
	char	*pixels;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}			t_img;

typedef struct s_colorpix
{
	int				i;
	int				bpp;
	int				size;
	unsigned int	color;
	char			*pix;
	float			fog;
}			t_colorpix;

typedef struct s_texture
{
	int		color;
	int		repop;
	int		direction;
	char	*north;
	char	*south;
	char	*east;
	char	*west;
	char	*path_north;
	char	*path_south;
	char	*path_east;
	char	*path_west;
	char	*ceiling;
	char	*floor;
	char	*weapon1;
	char	*reload0;
	char	*reload1;
	char	*shoot0;
	char	*shoot1;
	char	*door;
	char	*open_door;
	char	*target;
}			t_texture;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
	int	c_color;
	int	f_color;
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
	int		shoot;
	int		reload;
	int		half;
	time_t	last;
	double	time_shoot;
	double	time_reload;
	double	cooldown;
	double	current_time;
	int		ammo;
}				t_engine;

typedef struct s_ceiling
{
	double	step_x;
	double	step_y;
	double	text_x;
	double	text_y;
	double	floor_x;
	double	floor_y;
	double	row_dist;
}			t_ceiling;

typedef struct s_hitbox
{
	double	inv_det;
	double	new_x;
	double	new_y;
	double	sprite_x;
	double	sprite_height;
	double	hitbox_x;
	double	hitbox_y;
}			t_hitbox;
typedef struct s_floor
{
	double	step_x;
	double	step_y;
	double	text_x;
	double	text_y;
	double	floor_x;
	double	floor_y;
	double	row_dist;
}			t_floor;
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
	void			*mlx;
	void			*window;
	void			*img_map2d;
	void			*img_map3d;
	void			*weapon_3d;
	int				mini;
	int				count_color_c;
	int				count_color_f;
	int				num_sprites;
	clock_t			cur;
	t_keys			keys;
	t_texture		texture;
	t_color			ceiling_col;
	t_color			floor_col;
	t_engine		engine;
	t_ray			ray;
	t_img			img2d;
	t_img			img3d;
	t_img			weapon;
	t_sprite		*sprite;
	t_ceiling		ceiling;
	t_floor			floor;
	t_hitbox		hitbox;
	t_params		params;
	t_mix			mix;
	t_colorpix		colorpix;
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
void	ft_check_one(int i, int j, t_cub *game);
void	ft_check_len(size_t j, t_cub *game);
void	ft_check_close(int i, t_cub *game);
int		contains_map_char(char *line);
int		check_all_configurations(t_cub *game);
int		parse_line(char *line, t_cub *game);
void	initialize_game_settings(t_cub *game);
void	parse_all_lines(t_cub *game, char **argv);
int		process_configuration_lines(char *line, t_cub *game);
long	get_next_number(char **str, int *count);
int		process_map_lines(char *line, t_cub *game);
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
void	render3d(int x, t_cub *game);
void	sort_sprites(t_cub *game);
void	calculate_transform(t_cub *game);
void	calculate_sprite_position(t_cub *game);
void	draw_sprite_pixel(t_cub *game, t_sprite_params *params);
void	draw_3Dview(t_cub *game);
void	ft_draw_minimap(int x, int y, int *color, t_cub *game);
void	draw_ray(t_cub *game, int ray_x, int ray_y);
void	ft_input(t_cub *game);
int		ft_colorpix(int x, int y, void *texture, t_cub *game);
void	ft_init_mlx(t_cub *game);
void	ft_init_dda(int x, t_cub *game);
void	print_cub(void);
void	ft_target_repop(t_cub *game);
void	ft_fraps(t_cub *game);
int		ft_colorpix_ceifloo(int x, int y, void *texture, t_cub *game);
void	ft_draw_weapon(t_cub *game);
void	draw_floor(int x, t_cub *game);
void	draw_ceiling(int x, t_cub *game);
void	ft_crosshair(t_cub *game);
void	choose_texture(int x, t_cub *game);
void	draw_texture(int x, void *texture, t_cub *game);
void	init_sprite(t_cub *game);
void	render_sprite(t_cub *game);
void	door_state(int x, int y, t_cub *game);
bool	should_draw_pixel(int pixel_color, int color_to_ignore);
int		ft_mouse(int x, int y, t_cub *game);
void	mouse_pos(int x, int y, t_cub *game);
void	ft_shoot(t_cub *game);
void	ft_empty(t_cub *game);
void	ft_reload(t_cub *game);
void	ft_doors(t_cub *game);
void	ft_error_parse(char *msg, t_cub *game);
void	free_door(t_cub *game);
void	free_texture(t_cub *game);

#endif
