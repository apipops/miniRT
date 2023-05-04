NAME = miniRT

SRC = src/main.c \
	src/mlx_init.c \
	src/hooks.c \
	src/display.c \
	src/raytracing.c \
	src/ray_lights.c \
	src/ray_plane.c \
	src/ray_sphere.c \
	src/ray_cylinder.c \
	src/vec3_utils.c \
	src/ray_utils.c \
	src/math.c \
	src/free.c \
	src/error.c \
	src/parse_ac.c \
	src/parse_checks.c \
	src/parse_cylinders.c \
	src/parse_lights.c \
	src/parse_objects.c \
	src/parse_planes.c \
	src/parse_spheres.c \
	src/parse_utils.c \

OBJ = $(SRC:.c=.o)

INCLUDES = includes/params.h \
	includes/proto.h \
	includes/colors.h

CC = cc 

FLAGS = -Wall -Wextra -Werror 

FLAG_MAVX = -mavx

MACOS = miniRT_macos

LIBFT = ./libft/libft.a

LIBFTDIR = ./libft/

MAKEFLAGS += --no-print-directory

BLUE = \033[1;94m

PURPLE = \033[1;95m

GREEN = \033[1;92m


YELLOW = \033[1;93m

all: $(NAME)

macos: $(MACOS)

# A commenter si on utilise macos
%.o: %.c
	@$(CC) $(FLAGS) $(FLAG_MAVX) -g -I./includes -I./libft -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJ) $(LIBFT) $(INCLUDES)
	@$(CC) $(OBJ) $(FLAGS) $(FLAG_MAVX) -L$(LIBFTDIR) -g -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
	@printf "$(YELLOW)------Compilation executed------\n\n"

# A decommenter si on ulitise macos
#%.o: %.c
#	@$(CC) $(FLAGS) -Imlx_macos -I./libft -I/opt/X11/include -c $< -o $@

$(MACOS): $(OBJ) $(LIBFT) $(INCLUDES)
	@$(CC) $(OBJ) $(FLAGS) -L$(LIBFTDIR) -lft -Lmlx_macos -lmlx_macos -framework OpenGL -framework AppKit -o $(MACOS)
	@printf "$(YELLOW)------Compilation executed------\n\n"


$(LIBFT):
	@make -C $(LIBFTDIR) 
	@printf "$(BLUE)--------Libft.a created----------\n\n"

clean:
	@/bin/rm -f $(OBJ) 
	@make clean -C $(LIBFTDIR)
	@printf "$(PURPLE)------Object files deleted-------\n\n"

fclean: clean
	@/bin/rm -f $(NAME) $(MACOS)
	@make fclean -C $(LIBFTDIR)
	@printf "$(GREEN)----Executable files deleted-----\n\n"

re: fclean all

ra: fclean macos
