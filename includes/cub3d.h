/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jamendoe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:00:55 by jamendoe          #+#    #+#             */
/*   Updated: 2023/04/14 21:01:00 by jamendoe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx_linux/mlx.h"
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

// ERROR_MESSAGES -------------------------------------------------------------
# define ERR_MEM_ALLOC "Error\nCouldn't allocate memory\n"
# define ERR_SCENE_FD "Error\nCan't read scene file\n"
# define ERR_SCENE_COLOR "Error\nThe color info isn't well formated\n"
# define ERR_RGB_VALUE "Error\nThe color info must be between 0 and 255\n"
# define ERR_SCENE_TILE "Error\nCan't read one or more scene tiles\n"
# define ERR_SCENE_INFO "Error\nYou have more scene info than you should\n"
# define ERR_SCENE_FIX "Error\nPlease fix the scene fd\n"
# define ERR_MAP_SPACES "Error\nThe map has empty lines\n"
# define ERR_PLAYER_MISS "Error\nThe player is missing on the map\n"
# define ERR_CHAR_MAP "Error\nThe map has invalid characters\n"
# define ERR_WALLS "Error\nThe map is not surrounded by walls\n"

// IMAGE_INFO -----------------------------------------------------------------
# define CUB3D_ARGS 2
# define ARG_SCENE_PATH 1
# define SCENE_CHAR_NBR 4

// TEXTURE_OPERATION ----------------------------------------------------------
# define READ_TEXTURES 0
# define WRITE_TEXTURES 1

// SCREEN_INFO ----------------------------------------------------------------
# define SCREEN_HEIGHT 600
# define SCREEN_WIDTH 800
# define FIELD_OF_VIEW 0.66

// IMAGE_INFO -----------------------------------------------------------------
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

// KEYS -----------------------------------------------------------------------
# define UP 119
# define LEFT 97
# define DOWN 115
# define RIGHT 100
# define ROT_LEFT 65361
# define ESCAPE 65307
# define ROT_RIGHT 65363

// KEY_STATUS -----------------------------------------------------------------
# define KEY_RELEASED 0
# define KEY_PRESSED 1

// PARAMS ---------------------------------------------------------------------
# define MARGIN 0.3
# define SPEED 0.025
# define ROTATION 0.01

typedef struct s_ray
{
	double	screen_column;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_x;
	double	delta_y;
	int		step_x;
	int		step_y;
	double	side_x;
	double	side_y;
	int		hit;
	int		side;
	double	perp_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wall_pixel;
	int		texture_x;
	int		texture_y;
	double	step;
	double	texture_position;
}	t_ray;

typedef struct s_keys
{
	int	up;
	int	down;
	int	right;
	int	left;
	int	rot_right;
	int	rot_left;
	int	esc;
}	t_keys;

typedef struct s_map_info
{
	int	ln;
	int	pl;
	int	nl;
	int	len_ln;
	int	len_pl;
	int	len_nl;
}	t_map_info;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_texture
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	unsigned int	floor;
	unsigned int	ceiling;
	int				nbr_info;
	t_img			img_no;
	t_img			img_so;
	t_img			img_ea;
	t_img			img_we;
}	t_texture;

typedef struct s_cub3d
{
	t_texture		*texture;
	int				map_len;
	int				map_width;
	char			**map;
	double			player_x;
	double			player_y;
	char			orientation;
	double			vision_x;
	double			vision_y;
	double			fov_x;
	double			fov_y;
	void			*mlx;
	void			*mlx_win;
	t_img			screen;
	t_keys			keys;
}	t_cub3d;

int				ft_check_arg(int argc, char **argv);
void			ft_init_cub3d(t_cub3d *cub3d);
int				ft_read_scene(t_cub3d *cub3d, char *argv);
void			ft_safe_exit(t_cub3d *cub3d, char *msg);
void			ft_close_fd(int min, int max);
void			ft_clean_texture(t_cub3d *cub3d);
void			ft_clean_map(t_cub3d *cub3d);
void			ft_clean_images(t_cub3d *cub3d);
int				ft_info_textures(t_cub3d *cub3d, char *scene, int stage);
void			ft_identify_line(t_cub3d *cub3d, char *line);
int				ft_define_color(t_cub3d *cub3d, char *line, char letter);
void			ft_build_map(t_cub3d *cub3d, char *line, int *n_lin);
void			ft_clean_split(char **split);
void			ft_test_textures(t_cub3d *cub3d);
void			ft_error_map_lines(t_cub3d *cub3d, char *line, int n_lin);
void			ft_load_player(t_cub3d *cub3d);
void			ft_set_orientation(t_cub3d *cub3d);
void			ft_check_map(t_cub3d *cub3d);
void			ft_check_chars(t_cub3d *cub3d);
void			ft_check_wall_hor(t_cub3d *cub3d, int j);
void			ft_check_wall_ver(t_cub3d *cub3d, int j);
void			ft_check_spaces(t_cub3d *cub3d, int i, t_map_info ln);
void			ft_init_mlx(t_cub3d *cub3d);
void			ft_load_textures(t_cub3d *cub3d);
void			ft_load_image(t_cub3d *cub3d, t_img *info, char *path);
int				ft_close(t_cub3d *cub3d);
int				ft_press_key(int key_code, t_cub3d *cub3d);
int				ft_release_key(int key_code, t_cub3d *cub3d);
int				ft_run_window(t_cub3d *cub3d);
void			ft_check_move(t_cub3d *cub3d);
void			ft_move(t_cub3d *cub3d, double x, double y);
void			ft_rotate(t_cub3d *cub3d, int dir);
void			ft_get_deltas(t_cub3d *cub3d, t_ray *ray);
void			ft_find_initial_dist(t_cub3d *cub3d, t_ray *ray);
void			ft_hit_the_wall(t_cub3d *cub3d, t_ray *ray);
void			ft_perp_dist_wall(t_cub3d *cub3d, t_ray *ray);
void			ft_find_pixel_hit(t_cub3d *cub3d, t_ray *ray);
void			ft_color_img(t_cub3d *cub3d, t_ray *ray, int x);
void			ft_pixel_color(t_img *img, int x, int y, unsigned int color);
unsigned int	ft_get_pixel(t_cub3d *cub3d, t_ray *ray);
unsigned int	ft_texture_pixel(t_img *img, int x, int y);

#endif
