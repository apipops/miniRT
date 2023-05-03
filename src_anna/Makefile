#### NAME

NAME			= minirt

#### PATH TO SOURCES

PATH_SRCS		+= srcs/

#### SOURCES

SRCS			+= error.c
SRCS			+= free.c
SRCS			+= main.c
SRCS			+= ft_atof.c
SRCS			+= parse_ac.c
SRCS			+= parse_checks.c
SRCS			+= parse_cylinders.c
SRCS			+= parse_lights.c
SRCS			+= parse_objects.c
SRCS			+= parse_planes.c
SRCS			+= parse_spheres.c
SRCS			+= parse_utils.c

vpath %.c $(PATH_SRCS)

#### VALGRIND

VALGRIND	+= valgrind
VALGRIND	+= --track-origins=yes
VALGRIND	+= --leak-check=full
VALGRIND	+= --show-leak-kinds=all

#### OBJS

PATH_OBJS		= objs/
OBJS			= $(patsubst %.c, $(PATH_OBJS)/%.o, $(SRCS))

#### LIBRARY

LIBFT_PATH		= libft/
LIBFT			= $(LIBFT_PATH)/libft.a

#### INCLUDES

INCLUDES		= -I./includes -I./$(LIBFT_PATH)/includes
HEADER			= includes/minirt.h

#### COMPILATION

CC			= clang
CFLAGS		+= -Wall -Wextra -Werror
CFLAGS		+= -mavx
SMAKE		= make --no-print-directory

#### RULES

all : $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@ -L $(INCLUDES) -L $(LIBFT_PATH) -lft -lreadline
	@echo "use ./$(NAME) to run basic tests"

$(LIBFT):
	@$(SMAKE) -sC $(LIBFT_PATH)

$(OBJS): $(PATH_OBJS)/%.o: %.c $(HEADER)
	@mkdir -p $(PATH_OBJS)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	@$(RM) -R $(PATH_OBJS)
	@$(SMAKE) -sC $(LIBFT_PATH) clean

fclean: clean
	@$(RM) $(NAME)
	@$(SMAKE) -sC $(LIBFT_PATH) fclean

re: fclean
	@$(SMAKE)


.PHONY: all clean fclean re
