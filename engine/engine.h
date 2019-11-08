/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncolomer <ncolomer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 11:55:59 by ncolomer          #+#    #+#             */
/*   Updated: 2019/11/08 17:37:59 by ncolomer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENGINE_H
# define ENGINE_H

# include <stdio.h>
# include <math.h>
# include "mlx/mlx.h"
# include "config/config.h"

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_RELEASE	3
# define X_EVENT_MOUSE_PRESS	4
# define X_EVENT_MOUSE_RELEASE	5
# define X_EVENT_MOUSE_MOVE		6
# define X_EVENT_EXIT			17

# define FLAG_UI				0x00000001
# define FLAG_SHADOWS			0x00000010
# define FLAG_CROSSHAIR			0x00000100

typedef struct	s_sprite
{
	t_pos			pos;
	double			distance;
	struct s_sprite	*next;
	struct s_sprite	*sorted;
}				t_sprite;

typedef struct	s_raysult
{
	double		distance;
	int			direction;
	int			side;
	int			height;
	t_pos		ray_pos;
	t_pos		ray_dir;
	t_pos		map_pos;
	t_pos		side_dist;
	t_pos		delta_dist;
	t_pos		step;
	double		wall_x;
	t_sprite	*sprites;
}				t_raysult;

typedef struct	s_image
{
	void	*img;
	void	*ptr;
	int		bpp;
	int		size_line;
	int		endian;
}				t_image;

typedef struct	s_tex
{
	char	*path;
	void	*tex;
	void	*ptr;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}				t_tex;

typedef	struct	s_window
{
	void		*ptr;
	void		*win;
	t_image		screen;
	t_image		ui;
	t_image		*active_img;
	t_pos		size;
	t_pos		half;
}				t_window;

typedef struct	s_camera
{
	t_pos	pos;
	t_pos	dir;
	t_pos	x_dir;
	t_pos	plane;
}				t_camera;

typedef	struct	s_game
{
	t_config	config;
	t_window	window;
	t_camera	camera;
	t_sprite	*sprites;
	t_tex		tex[7];
	t_pos		move;
	t_pos		x_move;
	t_pos		rotate;
	int			options;
	double		camera_x[1920];
	double		depth[1920];
	double		sf_dist[1080];
	double		cos[2];
	double		sin[2];
}				t_game;

void			init_camera(t_config *config, t_camera *camera);

int				move_camera(t_game *game, int direction);

int				move_perp_camera(t_game *game, int direction);

int				rotate_camera(t_game *game, int direction);

int				init_window(t_window *window, t_config *config);

int				clear_window(t_window *window);

int				destroy_window(t_window *win);

int				update_screen(t_game *game);

void			clear_ui(t_window *window);

void			update_ui(t_game *game);

void			write_ui_text(t_game *game);

void			update_window(t_game *game);

int				load_textures(t_game *game);

int				draw_string(t_window *window, t_pos *s_pos, char *str,
					int color);

int				wall_direction(t_raysult *ray);

int				ray_cast(t_game *game, t_raysult *ray, double camera_x);

double			ray_distance(t_game *game, t_raysult *ray);

void			init_image(t_window *window, t_image *img);

void			destroy_image(t_window *window, t_image *img);

void			draw_pixel_img(t_window *w, t_pos *pos, int color);

int				draw_vertical_line_img(t_window *window, t_pos *start,
					int length, int color);

int				draw_rectangle_img(t_window *window, t_pos *p1,
					t_pos *p2, int color);

int				shade_color(int color, double divide);

int				get_tex_color(t_tex *tex, t_pos *pos);

int				find_sprites(t_game *game);

t_sprite		*add_front_sprite(t_sprite **sprites,
					double distance, t_pos *pos);

t_sprite		*add_sorted_sprite(t_sprite **sprites, t_sprite *sprite);

int				draw_sprites(t_game *game);

t_sprite		*add_front_sprite(t_sprite **sprites,
					double distance, t_pos *pos);

t_sprite		*add_sorted_sprite(t_sprite **sorted, t_sprite *sprite);

t_sprite		*sort_sprites(t_game *game, t_sprite *sprites);

void			calculate_camera_x(double width, double r[1080]);

void			calculate_cos_sin(double rotate_speed,
					double cos_r[2], double sin_r[2]);

void			calculate_sf_dist(double height, double r[1080]);

void			display_crosshair(t_game *game);

void 			debug_print_camera(t_game *game);

#endif
