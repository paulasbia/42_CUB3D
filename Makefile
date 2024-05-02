.SILENT:

NAME = cub3D

SRC = check_walls.c controls.c image.c maps.c validation.c
MAIN = main.c
SRCS = $(SRC) $(MAIN)

OBJS = $(addprefix objs/, $(SRCS:.c=.o))

FLAGS = -Wall -Wextra -Werror -g #-fsanitize=address

COLOUR_GREEN=\033[32m
COLOUR_RED=\033[31m
COLOUR_END=\033[0m

ifeq ($(shell uname), Linux)
	INCLUDES = -I/usr/include -Imlx_linux
else
	INCLUDES = -I/opt/X11/include -Imlx
endif

MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a
ifeq ($(shell uname), Linux)
	MLX_DIR = ./mlx_linux
	MLX_FLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz
else
	MLX_DIR = ./mlx
	MLX_FLAGS = -Lmlx -lmlx -L/usr/X11/lib -lXext -lX11 -framework OpenGL -framework AppKit
endif

objs/%.o: */%.c
	@mkdir -p objs
	@cc ${FLAGS} -I/usr/include -Imlx_linux -O3 -c $< -o $@

all: ${NAME}

install:
	python3 -m pip install --upgrade pip setuptools
	python3 -m pip install norminette
	sudo apt install valgrind -y

check:
	norminette $(SRCS)
	norminette ./includes/fdf.h

${NAME}: ${OBJS}
	@echo "$(COLOUR_GREEN)----Compiling lib----"
	@make re -C ./libft
	@make -C ./mlx_linux
	@cc $(FLAGS) $(OBJS) -Llibft -lft -o $(NAME) $(MLX_FLAGS)
	@echo "$(COLOUR_GREEN)fdf Compiled! ᕦ$(COLOUR_RED)♥$(COLOUR_GREEN)_$(COLOUR_RED)♥$(COLOUR_GREEN)ᕤ\n$(COLOUR_END)"

clean:
	@make clean -C ./libft
	@rm -f ${OBJS}
	@echo "$(COLOUR_RED)Deleting all objs! ⌐(ಠ۾ಠ)¬\n$(COLOUR_END)"

fclean: clean
	@make fclean -C ./libft
	@rm -f ${NAME}
	@clear
	
re:			fclean all

valgrind: clean fclean all
	valgrind --leak-check=full ./fdf ./maps/my_teste/pde-souz.fdf

valgrind_c: clean fclean all
	valgrind --leak-check=full ./fdf ./maps/./42maps/t2.fdf

.PHONY: all clean fclean re 


# .SILENT:

# NAME = cub3D

# LIBFT = libft.a

# LIBMLX = ./minilibx-linux/libmlx_Linux.a ./minilibx-linux/libmlx.a

# CC = cc

# CFLAGS = -Wall -Werror -Wextra -g 

# LFLAGS = -L $(LIBMLX) $(LIBFT)

# RM = rm -f

# AR = ar -rsc

# SRC = $(wildcard *.c) 

# OBJ = $(SRC:.c=.o)

# all: $(NAME)

# %.o: %.c
# 	$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3  -c $< -o $@

# $(NAME): $(OBJ)
# 	@make -C ./libft 
# 	@mv ./libft/$(LIBFT) . 
# 	$(CC) $(OBJ) -Lminilibx-linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) libft.a

# clean:
# 	$(RM) $(OBJ)
# 	@make clean -C ./libft

# fclean: clean
# 	$(RM) $(NAME) $(LIBFT)

# re: fclean all
	
# .PHONY: all clean fclean re
	
