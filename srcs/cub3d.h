/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 18:01:09 by tcharpen          #+#    #+#             */
/*   Updated: 2022/08/31 18:01:09 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H

# define CUB3D_H

# include "../libft/libft.h" // contains unistd, stdarg, stdlib
# include "../libmlx/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

# define ESC 65307 // ESC key
# define TURN_LEFT 65361 // LEFT ARROW key
# define TURN_RIGHT 65363 // RIGHT ARROW key
# define UP 122 // Z key = 122, W key = 119
# define DOWN 115 // S key = 115
# define LEFT 113 // Q key = 113, A key = 97
# define RIGHT 100 // D key = 100
# define MAX_HEIGHT 1080 // depends on your screen
# define MAX_WIDTH 1920 // depends on your screen
# define MOVESPEED 0.03 // depends on your screen/computer
# define ROTSPEED 0.03 // depends on your screen/computer
# define NO 0
# define SO 1
# define WE 2
# define EA 3
# define F 4
# define C 5

/* --------- STRUCT --------- */

typedef struct s_draw
{
	int		line_height;
	int		start;
	int		end;
	double	wall;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
}				t_draw;

typedef struct s_math
{
	double	side_distx;
	double	side_disty;
	double	delta_distx;
	double	delta_disty;
	double	perpwalldist;
	int		stepx;
	int		stepy;
	int		side;
	int		hit;
}				t_math;

typedef struct s_ray
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planx;
	double	plany;
	int		mapx;
	int		mapy;
	double	camerax;
	double	ray_dirx;
	double	ray_diry;
	t_math	math;
	t_draw	draw;
}				t_ray;

typedef struct s_img
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		height;
	int		width;
	char	*path;
}				t_img;

typedef struct s_map
{
	char	**map;
	int		nbr_x;
	int		nbr_y;
	char	direction;
	int		startx;
	int		starty;
	char	**path;
	int		color_f;
	int		color_c;
}				t_map;

typedef struct s_key
{
	int		up;
	int		down;
	int		left;
	int		right;
	int		turn_left;
	int		turn_right;
	double	movespeed;
	double	rotspeed;
}				t_key;

typedef struct s_win
{
	void	*mlx;
	void	*win;
	t_map	map;
	t_ray	ray;
	t_img	no;
	t_img	so;
	t_img	we;
	t_img	ea;
	t_img	*texture;
	t_img	img_one;
	t_img	img_two;
	t_img	*img_actual;
	t_key	key;
}				t_win;

/* --------- FCT --------- */

/* init */
void	init_cub(t_win *win);
void	init_raycasting(t_win *win, t_map *map, t_ray *ray);

/* parsing */
void	parsing_cub(char *arg, t_win *win);
char	**check_file(char *arg, t_win *win);
int		check_elements(char **file, t_win *win);
int		add_texture(int type, char *line, t_win *win, char **file);
int		add_color(int *color, char *line, t_win *win, char **file);
void	check_map(char **file, int i_file, t_win *win);
char	*strlcpy_malloc(char *str, int len, char **file, t_win *win);

/* utils */
int		ft_isspace(char c);
int		ft_same_str(char *s1, char *s2);
char	*ft_strjoin_free_s1(char *s1, char *s2);
char	**read_file(int fd);
void	free_tabstr(char **tab);
int		ft_stronlyspace(char *str);

/* window */
int		key_press(int keycode, t_win *win);
int		key_release(int keycode, t_win *win);
int		destroy_window(t_win *win);
void	open_window(t_win *win);
void	init_image(t_win *win);
void	destroy_img(t_win *win);

/* raycasting */
int		raycasting(t_win *win);
void	calcul_draw(t_ray *ray, t_math *math, t_win *win, int x);
void	move(t_ray *ray, t_key *key, char **map);
void	rotate(t_ray *ray, t_key *key);

/* error */
void	print_error(char *str, t_win *win);
void	print_error_system(char *str, t_win *win);

/* free */
void	free_cub(t_win *win, int id_exit);

#endif
