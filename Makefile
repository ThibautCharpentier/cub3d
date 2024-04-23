# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/31 17:51:48 by tcharpen          #+#    #+#              #
#    Updated: 2022/08/31 17:51:48 by tcharpen         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
NAME_BONUS = cub3D_bonus

HDR = srcs/cub3d.h
HDR_BONUS = srcs_bonus/cub3d_bonus.h

SRCS = init/init.c init/init_ray.c \
parsing/file.c parsing/parsing.c parsing/elements.c \
parsing/texture_and_color.c parsing/map.c \
raycasting/draw.c raycasting/raycasting.c raycasting/move.c \
raycasting/rotate.c \
utils/ft_strjoin_free_s1.c utils/read_file.c utils/ft_same_str.c \
utils/ft_isspace.c utils/ft_stronlyspace.c utils/free_tabstr.c \
window/image.c window/window.c \
error.c free.c main.c

SRCS_BONUS = init_bonus/init_bonus.c init_bonus/init_ray_bonus.c \
interaction_bonus/door_bonus.c \
parsing_bonus/file_bonus.c parsing_bonus/parsing_bonus.c \
parsing_bonus/elements_bonus.c parsing_bonus/texture_and_color_bonus.c \
parsing_bonus/map_bonus.c parsing_bonus/check_door_bonus.c \
parsing_bonus/fill_bonus.c \
raycasting_bonus/draw_bonus.c raycasting_bonus/raycasting_bonus.c \
raycasting_bonus/move_bonus.c raycasting_bonus/rotate_bonus.c \
raycasting_bonus/ray_utils.c raycasting_bonus/minimap_bonus.c\
utils_bonus/ft_strjoin_free_s1_bonus.c utils_bonus/read_file_bonus.c \
utils_bonus/ft_same_str_bonus.c utils_bonus/ft_isspace_bonus.c \
utils_bonus/ft_stronlyspace_bonus.c utils_bonus/free_tabstr_bonus.c \
window_bonus/image_bonus.c window_bonus/window_bonus.c \
error_bonus.c free_bonus.c main_bonus.c

OBJS = ${addprefix srcs/,${SRCS:.c=.o}}
OBJS_BONUS = ${addprefix srcs_bonus/,${SRCS_BONUS:.c=.o}}

LIBMLX = libmlx

LIBFT_AR = libft/libft.a 
LIBMLX_AR = ${LIBMLX}/libmlx.a

INCLUDES_HOME = -Ilibft -I/usr/include -Ilibmlx
LIBS_HOME = -Llibft -lft -Llibmlx -lmlx -L/usr/lib -lXext -lX11 -lm -lz

INCLUDES_42 = -Ilibft -Ilibmlx_mac
LIBS_42 = -Llibft -lft -Llibmlx_mac -lmlx -framework OpenGL -framework AppKit

CC = gcc
CFLAGS = -Wall -Wextra -Werror -O2

%.o: %.c ${HDR} ${HDR_BONUS} ${LIBFT_AR} ${LIBMLX_AR} Makefile
	${CC} ${CFLAGS} -c $< -o $@ ${INCLUDES_HOME}

all: libft libmlx ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIBS_HOME}

bonus: libft libmlx ${NAME_BONUS}

${NAME_BONUS}: ${OBJS_BONUS}
	${CC} ${CFLAGS} -o ${NAME_BONUS} ${OBJS_BONUS} ${LIBS_HOME}

libft:
	make -C libft

libmlx:
	make -C ${LIBMLX}

clean:
	rm -f ${OBJS} ${OBJS_BONUS}
	make clean -C ${LIBMLX}
	make clean -C libft

fclean: clean
	rm -f ${NAME} ${NAME_BONUS}
	make fclean -C libft

re: fclean all

.PHONY: all bonus libmlx libft clean fclean re
