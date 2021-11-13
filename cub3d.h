/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yjama <yjama@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/26 18:32:39 by yjama             #+#    #+#             */
/*   Updated: 2021/04/28 12:19:11 by yjama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "minilibx/mlx.h"
# include "libft_c3D/libft.h"
# define MINIMAP_SCALE 0.5
# define STDOUT 1
# define ERROR -1
# define SUCCESS 0
# define W 13
# define S 1
# define A 0
# define D 2
# define LEFT_ARROW 123
# define RIGHT_ARROW 124
# define ESC 53
# define MAX_VALUE 2147483647
# define NUM_TEXTURE 4

typedef struct s_win
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				*img_addr;
}					t_win;

typedef struct s_point
{
	int				x;
	int				y;
}					t_point;

typedef struct s_wall
{
	float			correct_wall_distance;
	float			distance_projection_plane;
	int				wall_strip_height;
	int				wall_top;
	int				wall_bottom;
}					t_wall;

typedef struct s_plr
{
	float			x;
	float			y;
	float			FOV;
	float			angle;
	char			position;
	int				radius;
	int				turn_direction;
	int				walk_direction;
	int				translation;
	float			rotation_angle;
	float			rotation_speed;
	float			move_speed;
}					t_plr;

typedef struct s_ray
{
	int				num_rays;
	float			distance;
	float			ray_angle;
	float			yintercept;
	float			xintercept;
	float			ystep;
	float			xstep;
	float			wall_hit_y;
	float			wall_hit_x;
	float			vert_wall_hit_y;
	float			vert_wall_hit_x;
	float			horz_wall_hit_y;
	float			horz_wall_hit_x;
	int				found_vert_wall_hit;
	int				found_horz_wall_hit;
	int				is_ray_facing_up;
	int				is_ray_facing_down;
	int				is_ray_facing_right;
	int				is_ray_facing_left;
	int				was_hit_vertical;
}					t_ray;

typedef struct s_txtr
{
	char			*path;
	void			*texture_ptr;
	int				*wall_texture;
	int				height;
	int				width;
}					t_txtr;

typedef struct s_sprite
{
	void			*sprite_ptr;
	int				*sprite_texture;
	char			*path;
	float			dir_y;
	float			dir_x;
	float			plan_y;
	float			plan_x;
	float			*distance;
	float			angle;
	int				width;
	int				height;
	float			*x;
	float			*y;
	int				nb_sprite;
	int				sprite_screen_x;
	int				draw_start_y;
	int				draw_end_y;
	int				draw_start_x;
	int				draw_end_x;
}					t_sprite;

typedef struct s_bmp
{
	char			byte_type[2];
	unsigned int	byte_size;
	unsigned int	byte_reserved;
	unsigned int	byte_offset;
	unsigned int	header_size;
	int				image_width;
	int				image_height;
	unsigned short	color_planes;
	unsigned short	bits_per_pixel;
	unsigned int	compression;
	unsigned int	image_size;
	int				bits_xpels_per_meter;
	int				bits_ypels_per_meter;
	unsigned int	total_colors;
	unsigned int	important_colors;
}					t_bmp;

typedef struct s_all
{
	t_win			*win;
	t_plr			*plr;
	t_ray			*ray;
	t_list			*file;
	t_sprite		*sprite;
	t_txtr			txtr[4];
	float			*distances;
	char			**map;
	int				map_w;
	int				map_h;
	int				screen_w;
	int				screen_h;
	int				fd;
	int				screenshoot;
	int				tile_size;
	int				color_up;
	int				color_down;
	int				wall_width;
	int				rays_num;
	int				size;
	char			NEWS;
}					t_all;

void	ft_init_vars(t_all *all);
void	ft_mlx_init(t_all *all);
void	ft_new_window(t_all *all);
void	create_image(t_all *all);

int		ft_read_file(t_list **file, int fd);
int		ft_check_file_extension(char *line, char *extension_name);
void	ft_check_arguments(t_all *all, int ac, char **av);
int		ft_file_descriptor(t_all *all, char *filename);
int		ft_parsing(t_all *all);

int		parsing(t_all *all);
int		ft_check_first_char(char *s);
int		ft_check_last_char(char c);
int		ft_is_good_char(char *s, char c);
int		ft_check_char_around(char **map, int i, int j);
int		ft_map_char_check(t_all *all);
void	ft_no_spaces_in_map(t_all *all);

char	**ft_make_map(t_list **head, int num);
int		ft_check_map(t_all *all);

void	ft_init_plr(t_all *all);
void	ft_plr_position(t_all *all);
void	ft_coordinate_plr(t_all *all);

char	*ft_get_width(char *line, int *screen_width);
char	*ft_get_height(char *line, int *screen_height);
void	ft_check_max_resolution(t_all *all);
int		ft_get_window_size(t_all *all);
int		mlx_get_screen_size(t_win *win, int *sizex, int *sizey);
int		ft_skip_number(char *str);
int		ft_skip_spaces(char *str);
int		ft_nb_line_and_nb_column(t_all *all);

t_list	*ft_node_find(t_list **begin, char *search, int n);
t_list	*ft_list_find(t_list *begin_list, void *data_ref, size_t n, \
		int (*cmp)());
void	ft_list_remove_one_if(t_list **begin_list, void *data_ref, int (*cmp)(), \
		void (*free_fct)(void *));
void	ft_remove_front(t_list **begin_list, void (*free_fct)(void *));

int		ft_delete_spaces(t_all *all);
int		ft_header_spaces(t_list **begin, t_list *node);
int		ft_footer_spaces(t_list **begin);
int		ft_check_that_line_is_wall(char *line);

int		ft_free_all(t_all *all, int error_code);
void	ft_free_map(t_all *all);
void	ft_free_texture(t_all *all);
void	ft_free_sprite(t_all *all);
void	ft_free_content_node(void *line);

int		ft_get_color(t_list **begin, char *name, int *num_color);
char	*ft_get_value_color_start(int *ptr, char *line, int column);
char	*ft_get_value_color_finish(char *line, int column);

void	ft_events(t_all *all);
int		close_window(t_all *all);
int		key_release(int key, t_all *all);
int		key_pressed(int key, t_all *all);

int		game_loop(t_all *all);

void	ft_plr_move(t_all *all, t_plr *plr);
void	ft_position_upd(t_all *all, float y, \
		float x, t_sprite *sprite);
int		ft_plr_angle(float *angle);
float	ft_normalize_angle(float *angle);
int		has_wall_at(t_all *all, float y, float x);

void	ft_init_sprite(t_all *all);
int		ft_sprite_count(char **map);
void	ft_sprite_malloc(t_all *all);
void	ft_sprite_zero_init(t_sprite *sprite);
void	ft_sprite_data_ptr_load(t_all *all);
void	ft_sprite_position(t_all *all);
void	ft_sprite_NEWS(t_all *all);
void	ft_sprite_N(t_sprite *sprite);
void	sprite_put(t_all *all, t_sprite *sprite, t_plr *plr);
void	ft_sprite_distance(t_sprite *sprite, t_plr *plr);
void	ft_sprite_sort(t_sprite *sprite);
void	ft_sprite_zero(t_sprite *sprite);
int		ft_sprite_visible(t_sprite *sprite, t_plr *plr, \
		int id, float sprite_size);
float	ft_get_transform_y(t_all *all, t_sprite *sprite, int id);
void	ft_get_start(t_all *all, t_sprite *sprite, float sprite_size);
void	ft_sprite_switch(t_sprite *sprite, int i, int j);
void	ft_sprite_draw(t_all *all, float transform_y, \
		float sprite_size, int id);
void	ft_sprite_texture_put(t_all *all, t_sprite *sprite, t_point point, \
		float sprite_size);

void	mini_map(t_all *all);
void	orientation_line(t_all *all, t_point point, float distance, \
		float angle);
void	player_rect(t_all *all, t_point point, int width, int height);
void	draw_map(t_all *all);
void	draw_map_utile(t_all *all, t_point *point, int j, int color);

void	cast_all_rays(t_all *all);
float	the_smallest_of_the_distances(t_ray *ray, t_plr *plr);
float	the_smallest_of_the_distances_utile(t_ray *ray, float vert_hit_distance, \
		float horz_hit_distance);
void	ray_facing(t_ray *ray);
void	init_struct_ray(t_ray *ray);
void	ray_horizontal(t_all *all);
void	next_horz_intercept(t_all *all, float next_horz_touch_y, \
		float next_horz_touch_x);
void	ray_vertical(t_all *all);
void	next_vert_intercept(t_all *all, float next_vert_touch_y, \
		float next_vert_touch_x);
float	distance_between_points(float x1, float y1, float x2, float y2);

void	draw_ceiling(t_all *all);
void	draw_floor(t_all *all);
int		choice_of_texture(t_ray *ray);
void	render3d_projection(t_all *all, int column_id);
void	draw_wall(t_all *all, t_wall *wall, int column_id);

void	load_ptr_textures_in_array(t_all *all);

void	bmp_exporter(t_all *all, char *file_name);
int		create_file(t_all *all, char *file_name);
void	write_file(t_all *all, int fd, int imagesize);
void	create_header(t_all *all, t_bmp *info_bmp_file);
void	write_header(int fd, t_bmp info_bmp_file);

int		ft_line_error(void);
int		ft_node_error(void);
void	ft_next(t_list **next);

#endif
