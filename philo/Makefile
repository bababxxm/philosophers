# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sklaokli <sklaokli@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 19:44:55 by sklaokli          #+#    #+#              #
#    Updated: 2025/01/13 06:14:56 by sklaokli         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

## Libraries
NAME	=	philo
LIBFT	=	$(LIB_DIR)/libft.a

## Paths to files
SRC_DIR	=	sources
OBJ_DIR	=	objects
INC_DIR	=	include
LIB_DIR	=	libft

## Source files
SRC			=	$(addprefix $(SRC_DIR)/, $(FILES))
FILES		=	main.c parser.c init.c philo.c clear.c utils.c

## Include files
INC			=	-I $(INC_DIR) -I $(LIB_DIR)/includes

## Object files
OBJ			=	$(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

## Total number of files
COMPILED	=	0
TOTAL_FILES	=	$(words $(OBJ))

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
CREATED := $(shell sed -n 's/^#    Created: \([0-9]\{4\}\/[0-9]\{2\}\/[0-9]\{2\} [0-9]\{2\}:[0-9]\{2\}:[0-9]\{2\}\).*/\1/p' Makefile)
UPDATED := $(shell sed -n 's/^#    Updated: \([0-9]\{4\}\/[0-9]\{2\}\/[0-9]\{2\} [0-9]\{2\}:[0-9]\{2\}:[0-9]\{2\}\).*/\1/p' Makefile)

ASCII_ART = \
    echo "" ;\
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

$(NAME):	$(OBJ) Makefile
			@$(MAKE) -sC $(LIB_DIR)
			@echo "$(BLUE)Building philo...$(RESET)"
			@$(CC) $(FLAGS) $(OBJ) $(LIBFT) $(INC) -o $(NAME)
			@echo "$(GREEN)Done! philo is now ready.$(RESET)"
			@$(ASCII_ART)

clean:
			@$(RM) -rf $(OBJ_DIR)
			@$(MAKE) -sC $(LIB_DIR) clean
			@echo "$(CYAN)All philo object files have been cleaned.$(RESET)"

fclean:
			@$(RM) -rf $(OBJ_DIR) $(NAME)
			@$(MAKE) -sC $(LIB_DIR) fclean
			@echo "$(CYAN)All philo executable files have been cleaned.$(RESET)"

re:			fclean all

.PHONY:		all clean fclean re