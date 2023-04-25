NAME = miniRT

SRC = src/display.c \
	src/hooks.c \
	src/main.c \

OBJ = $(SRC:.c=.o)

INCLUDES = includes/params.h \
	includes/proto.h

CC = gcc

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

#%.o: %.c
#	@$(CC) -Wall -Wextra -Werror -g -I./includes -I./libft -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJ) $(LIBFT) $(INCLUDES)
	@$(CC) $(OBJ) -L$(LIBFTDIR) -g -lft -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
	@printf "$(YELLOW)------Compilation executed------\n\n"


%.o: %.c
	@$(CC) -Wall -Wextra -Werror -Imlx_macos -I./libft -I/opt/X11/include -c $< -o $@

$(MACOS): $(OBJ) $(LIBFT) $(INCLUDES)
	@$(CC) $(OBJ) -L$(LIBFTDIR) -lft -Lmlx_macos -lmlx_macos -framework OpenGL -framework AppKit -o $(MACOS)
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
