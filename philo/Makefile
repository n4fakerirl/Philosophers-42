# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::   #
#    Makefile                                           :+:      :+:    :+:   #
#                                                     +:+ +:+         +:+     #
#    By: ocviller <ocviller@student.42.fr>          +#+  +:+       +#+        #
#                                                 +#+#+#+#+#+   +#+           #
#    Created: 2025/08/14 20:39:10 by ocviller          #+#    #+#             #
#    Updated: 2025/09/03 15:01:08 by ocviller         ###   ########.fr       #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I.
SRCS = clear.c monitor.c parsing.c philo.c routine.c utils.c
OBJS = $(SRCS:.c=.o)
OBJS_FULL = $(addprefix $(OBJDIR)/, $(OBJS))
OBJDIR = obj

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
RESET = \033[0m

# Header function
define HEADER
	@echo ""
	@echo "$(CYAN)████████████████████████████████████████████████████████████████████████████████$(RESET)"
	@echo "$(CYAN)█$(RESET)                                                                              $(CYAN)█$(RESET)"
	@echo "$(CYAN)█$(RESET)                         $(MAGENTA)██████╗ ██╗  ██╗██╗██╗      ██████╗ $(RESET)                 $(CYAN)█$(RESET)"
	@echo "$(CYAN)█$(RESET)                         $(MAGENTA)██╔══██╗██║  ██║██║██║     ██╔═══██╗$(RESET)                 $(CYAN)█$(RESET)"
	@echo "$(CYAN)█$(RESET)                         $(MAGENTA)██████╔╝███████║██║██║     ██║   ██║$(RESET)                 $(CYAN)█$(RESET)"
	@echo "$(CYAN)█$(RESET)                         $(MAGENTA)██╔═══╝ ██╔══██║██║██║     ██║   ██║$(RESET)                 $(CYAN)█$(RESET)"
	@echo "$(CYAN)█$(RESET)                         $(MAGENTA)██║     ██║  ██║██║███████╗╚██████╔╝$(RESET)                 $(CYAN)█$(RESET)"
	@echo "$(CYAN)█$(RESET)                         $(MAGENTA)╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝$(RESET)                  $(CYAN)█$(RESET)"
	@echo "$(CYAN)█$(RESET)                                                                              $(CYAN)█$(RESET)"
	@echo "$(CYAN)█$(RESET)                                                                              $(CYAN)█$(RESET)"
	@echo "$(CYAN)█$(RESET)                                                                              $(CYAN)█$(RESET)"
	@echo "$(CYAN)█$(RESET)                                 $(WHITE)Par: ocviller$(RESET)                                $(CYAN)█$(RESET)"
	@echo "$(CYAN)█$(RESET)                                 $(WHITE)École: 42$(RESET)                                    $(CYAN)█$(RESET)"
	@echo "$(CYAN)█$(RESET)                                                                              $(CYAN)█$(RESET)"
	@echo "$(CYAN)█$(RESET)                                                                              $(CYAN)█$(RESET)"
	@echo "$(CYAN)████████████████████████████████████████████████████████████████████████████████$(RESET)"
	@echo ""
	@echo "$(YELLOW)🔧 Compilation en cours...$(RESET)"
	@echo ""
endef

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS_FULL)
	$(HEADER)
	@$(CC) $(CFLAGS) $(OBJS_FULL) -o $(NAME)
	@echo "$(MAGENTA)✅ Compilation de l'executable...$(RESET)"

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	@echo "$(GREEN)✓ Compilation de $<$(RESET)"

clean:
	@rm -rf $(OBJDIR)
	@echo "$(YELLOW)⚙️ Nettoyage des objets...$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(YELLOW)⚙️ Nettoyage des objets et programmes...$(RESET)"

re: fclean all

.PHONY: all clean fclean re