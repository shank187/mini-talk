# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/11 00:00:00 by aelbour           #+#    #+#              #
#    Updated: 2025/04/12 12:04:16 by aelbour          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME_CLIENT     = client
NAME_SERVER     = server

CLIENT_BONUS    = client_bonus
SERVER_BONUS    = server_bonus

CC              = cc
CFLAGS          = -Wall -Wextra -Werror
CPPFLAGS        = -Imandatory -Ibonus

MANDATORY_DIR   = mandatory
BONUS_DIR       = bonus

SRCS_CLIENT     = $(MANDATORY_DIR)/client.c \
                  $(MANDATORY_DIR)/client_utils.c
SRCS_SERVER     = $(MANDATORY_DIR)/server.c \
                  $(MANDATORY_DIR)/server_utils.c

SRCS_CLIENT_BONUS  = $(BONUS_DIR)/client_bonus.c \
                     $(BONUS_DIR)/client_utils_bonus.c
SRCS_SERVER_BONUS  = $(BONUS_DIR)/server_bonus.c \
                     $(BONUS_DIR)/server_utils_bonus.c

OBJS_CLIENT     = $(SRCS_CLIENT:.c=.o)
OBJS_SERVER     = $(SRCS_SERVER:.c=.o)

OBJS_CLIENT_BONUS = $(SRCS_CLIENT_BONUS:.c=.o)
OBJS_SERVER_BONUS = $(SRCS_SERVER_BONUS:.c=.o)

all: $(NAME_CLIENT) $(NAME_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) -o $@

$(NAME_SERVER): $(OBJS_SERVER)
	$(CC) $(CFLAGS) $(OBJS_SERVER) -o $@

bonus: $(CLIENT_BONUS) $(SERVER_BONUS)

$(CLIENT_BONUS): $(OBJS_CLIENT_BONUS)
	$(CC) $(CFLAGS) $(OBJS_CLIENT_BONUS) -o $@

$(SERVER_BONUS): $(OBJS_SERVER_BONUS)
	$(CC) $(CFLAGS) $(OBJS_SERVER_BONUS) -o $@


$(OBJS_CLIENT) $(OBJS_SERVER): $(MANDATORY_DIR)/minitalk.h
$(OBJS_CLIENT_BONUS) $(OBJS_SERVER_BONUS): $(BONUS_DIR)/minitalk_bonus.h

clean:
	rm -f $(OBJS_CLIENT) $(OBJS_SERVER) \
	      $(OBJS_CLIENT_BONUS) $(OBJS_SERVER_BONUS)

fclean: clean
	rm -f $(NAME_CLIENT) $(NAME_SERVER) \
	      $(CLIENT_BONUS) $(SERVER_BONUS)

re: fclean all

.PHONY: all bonus clean fclean re
