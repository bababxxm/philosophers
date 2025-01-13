# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 19:44:55 by sklaokli          #+#    #+#              #
#    Updated: 2025/01/13 07:25:05 by sklaokli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Libraries
NAME	=	libft

## Paths to files
SRC_DIR	=	sources
OBJ_DIR	=	objects
INC_DIR	=	includes

## Subdirectories
CHAR_DIR	=	char/
INT_DIR		=	int/
STR_DIR		=	str/
CONV_DIR	=	conv/
MEM_DIR		=	mem/
FD_DIR		=	fd/
LST_DIR		=	lst/
CUSTOM_DIR	=	custom/

## Files grouped by subdirectory
CHAR_FILES	=	ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
				ft_tolower.c ft_toupper.c ft_issign.c

INT_FILES	=	ft_abs.c ft_is_invalid_int.c

STR_FILES	=	ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
				ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
				ft_strrchr.c ft_strtrim.c ft_substr.c ft_split.c ft_split_free.c

CONV_FILES	=	ft_atoi.c ft_itoa.c ft_atol.c

MEM_FILES	=	ft_bzero.c ft_calloc.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
				ft_memmove.c ft_memset.c

FD_FILES	=	ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

LST_FILES	=	ft_lstnew.c ft_lstlast.c ft_lstadd_front.c ft_lstadd_back.c \
				ft_lstsize.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c \
				ft_lstmap.c

CUSTOM_FILES =	ft_exit.c ft_is_empty_str.c ft_is_invalid_argv.c ft_perror_exit.c

## Combine all files with their respective subdirectories
FILES		=	$(addprefix $(CHAR_DIR), $(CHAR_FILES)) \
				$(addprefix $(INT_DIR), $(INT_FILES)) \
				$(addprefix $(STR_DIR), $(STR_FILES)) \
				$(addprefix $(CONV_DIR), $(CONV_FILES)) \
				$(addprefix $(MEM_DIR), $(MEM_FILES)) \
				$(addprefix $(FD_DIR), $(FD_FILES)) \
				$(addprefix $(LST_DIR), $(LST_FILES)) \
				$(addprefix $(CUSTOM_DIR), $(CUSTOM_FILES))

SRC			=	$(addprefix $(SRC_DIR)/, $(FILES))
OBJ			=	$(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))
TOTAL_FILES	=	$(words $(OBJ))
COMPILED	=	0

## Commands
RM			=	rm -f
CC			=	cc
LIBC		=	ar rcs
FLAGS		=	-Wall -Wextra -Werror

## Color Codes
CYAN		=	\033[0;36m
GREEN		=	\033[0;32m
RED			=	\033[0;31m
BLUE		=	\033[0;34m
YELLOW		=	\033[0;33m
RESET		=	\033[0m

## Custom ASCII Art for Project Completion
CREATED	:=	$(shell sed -n \
			's/^#    Created: \([0-9]\{4\}\/[0-9]\{2\}\/[0-9]\{2\} [0-9]\{2\}:[0-9]\{2\}:[0-9]\{2\}\).*/\1/p' Makefile)
UPDATED	:=	$(shell sed -n \
			's/^#    Updated: \([0-9]\{4\}\/[0-9]\{2\}\/[0-9]\{2\} [0-9]\{2\}:[0-9]\{2\}:[0-9]\{2\}\).*/\1/p' Makefile)

ASCII_ART	=	\
				echo " ___       ___  ________  ________ _________   " ;\
				echo "|\\  \\     |\\  \\|\\   __  \\|\\  _____\\\\___   ___\\ " ;\
				echo "\\ \\  \\    \\ \\  \\ \\  \\|\\ /\\ \\  \\__/\\|___ \\  \\_| " ;\
				echo " \\ \\  \\    \\ \\  \\ \\   __  \\ \\   __\\    \\ \\  \\  " ;\
				echo "  \\ \\  \\____\\ \\  \\ \\  \\|\\  \\ \\  \\_|     \\ \\  \\ " ;\
				echo "   \\ \\_______\\ \\__\\ \\_______\\ \\__\\       \\ \\__\\" ;\
				echo "    \\|_______|\\|__|\\|_______|\\|__|        \\|__|" ;\
				echo "" ;\
				echo "By: sklaokli <sklaokli@student.42.fr>" ;\
				echo "Created: $(CREATED)" ;\
				echo "Last Updated: $(UPDATED)" ;

## Targets
$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
				@ mkdir -p $(dir $@)
				@ $(eval COMPILED=$(shell echo $$(($(COMPILED)+1))))
				@ PERCENT=$$(($(COMPILED)*100/$(TOTAL_FILES))); \
				echo "$(BLUE)[$(COMPILED)/$(TOTAL_FILES)] Compiling $< ($$PERCENT%)$(RESET)\r"; \
				$(CC) $(FLAGS) -I $(INC_DIR) -c $< -o $@

all:		$(NAME)

$(NAME):	$(OBJ)
			@ $(LIBC) $(NAME) $(OBJ)
			@ echo "$(GREEN)Done! $(NAME) is now ready.$(RESET)"
			@ $(ASCII_ART)

clean:
			@ $(RM) -rf $(OBJ_DIR)
			@ echo "$(CYAN)All $(NAME) object files have been cleaned.$(RESET)"

fclean:
			@ $(RM) -rf $(OBJ_DIR) $(NAME)
			@ echo "$(CYAN)All $(NAME) executable files have been cleaned.$(RESET)"

re:			fclean all

.PHONY:		all clean fclean re
