# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lyanga <lyanga@student.42singapore.sg>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/18 05:19:35 by lyanga            #+#    #+#              #
#    Updated: 2026/04/22 07:34:05 by lyanga           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# name
NAME		=	$(OUTDIR)/push_swap
NAME_BONUS	=	$(OUTDIR)/checker

# cc options
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -g -O0
DEBUG_FLAGS		=	-g -O0 
# remove
RM			=	rm -f
# archive
AR			=	ar rcs
# outdir, by default it's current dir
OUTDIR 		?=	.

ifeq ($(DEBUG),1)
    CFLAGS += $(DEBUG_FLAGS)
endif

# **************************************************************************** #
DIR_HEADERS	=	./
DIR_OBJS	=	./
DIR_LIBFT =	libft/
DIR_LIBFT_HEADERS =	libft/headers/
LIBFT	=	$(DIR_LIBFT)libft.a

PUSHSWAP_HDR	=	push_swap.h
PUSHSWAP_SRCS	=	main.c push.c swap.c rotate.c r_rotate.c stack_utils.c sort.c validate.c error.c \
					sort_2.c sort_utils.c
OBJS_PUSHSWAP	=	$(addprefix $(DIR_OBJS), $(PUSHSWAP_SRCS:.c=.o))

CHECKER_HDR		=	checker_bonus.h
CHECKER_SRCS	= 	checker_main_bonus.c checker_line_bonus.c checker_moves_bonus.c \
					checker_utils_bonus.c checker_stack_utils_bonus.c checker_validate_bonus.c
OBJS_CHECKER	=	$(addprefix $(DIR_OBJS), $(CHECKER_SRCS:.c=.o))

.PHONY: all clean fclean re bonus quickclean qre libft

all: $(NAME)

$(NAME): libft $(OBJS_PUSHSWAP)
	@$(CC) $(CFLAGS) -I$(DIR_HEADERS) $(OBJS_PUSHSWAP) $(LIBFT) -o $@
	@echo "$@ created successfully."

libft: 
	@make -C $(DIR_LIBFT) DEBUG=$(DEBUG)

$(OBJS_PUSHSWAP): %.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -I$(DIR_HEADERS) -I$(DIR_LIBFT_HEADERS) -c $< -o $@

clean:
	@echo "Cleaning object files..."
	@make -C $(DIR_LIBFT) clean
	@$(RM) $(OBJS_PUSHSWAP)
	@$(RM) $(OBJS_CHECKER)

fclean: clean
	@echo "Cleaning everything..."
	@make -C $(DIR_LIBFT) fclean
	@$(RM) $(NAME)
	@$(RM) $(NAME_BONUS)

$(OBJS_CHECKER): %.o: %.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -I$(DIR_HEADERS) -I$(DIR_LIBFT_HEADERS) -c $< -o $@

bonus: libft $(OBJS_CHECKER)
	@$(CC) $(CFLAGS) -I$(DIR_HEADERS) $(OBJS_CHECKER) $(LIBFT) -o $(OUTDIR)/checker

quickclean:
	@$(RM) $(OBJS_PUSHSWAP)
	@$(RM) $(OBJS_CHECKER)

qre: quickclean all

re: fclean all
