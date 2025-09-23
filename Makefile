# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lyanga <lyanga@student.42singapore.sg>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/18 05:19:35 by lyanga            #+#    #+#              #
#    Updated: 2025/09/23 08:06:17 by lyanga           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# name
NAME		=	$(OUTDIR)/push_swap
# cc options
CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra
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

PUSHSWAP_SRCS	=	main.c push.c swap.c rotate.c r_rotate.c stack_utils.c sort.c validate.c error.c
OBJS_PUSHSWAP	=	$(addprefix $(DIR_OBJS), $(PUSHSWAP_SRCS:.c=.o))

.PHONY: all clean fclean re libft

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

fclean: clean
	@echo "Cleaning everything..."
	@make -C $(DIR_LIBFT) fclean
	@$(RM) $(NAME)

re: fclean all
