NAME = philo

LIBFT = ./include/libft/libft.a

PRINTF = ./include/ft_printf/libftprintf.a

RED = \033[0;31m
GRN = \033[0;32m
YEL = \033[0;33m
BLU = \033[0;34m
MAG = \033[0;35m
CYN = \033[0;36m
WHT = \033[0;37m
RES = \033[0m

CC = cc

CFLAGS = -Werror -Wall -Wextra -g -pthread -fsanitize=thread

RM = rm -rf

SDIR := src
ODIR := obj

SOURCES := main.c \
			initializers.c\
			error_handler.c \
			utils.c \
			dinner.c \
			getters_setters.c
OBJECTS := $(patsubst %.c,$(ODIR)/%.o,$(SOURCES))


all : ${NAME}

${NAME} : ${OBJECTS}
	@${CC} ${CFLAGS} ${OBJECTS} -o ${NAME}
	@echo "\n$(GRN)➾ philo created$(RES)"

$(ODIR)/%.o: $(SDIR)/%.c | $(ODIR)
	@$(CC) $(CFLAGS) -c -o $@ $<
	@echo "${GRN}➾ $@ created ${RES}"


$(ODIR):
	@mkdir -p $@	

clean :
	@${RM} ${OBJECTS}
	@${RM} ${ODIR}
	@echo "${RED}➾ philo objects deleted${RES}"

fclean : clean
	@${RM} ${NAME}
	@echo "${RED}➾ philo deleted${RES}"

re : fclean all