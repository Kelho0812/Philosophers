NAME = philo_bonus

RED = \033[0;31m
GRN = \033[0;32m
YEL = \033[0;33m
BLU = \033[0;34m
MAG = \033[0;35m
CYN = \033[0;36m
WHT = \033[0;37m
RES = \033[0m

CC = cc

CFLAGS = -Werror -Wall -Wextra -g -pthread

LDFLAGS = -fsanitize=thread

RM = rm -rf

SDIR := src
ODIR := obj

SOURCES := main_bonus.c \
			initializers_bonus.c\
			error_handler_bonus.c \
			utils_bonus.c \
			dinner_bonus.c \
			getters_setters_bonus.c\
			monitor_bonus.c\
			utils_bonus2.c

OBJECTS := $(patsubst %.c,$(ODIR)/%.o,$(SOURCES))


all : ${NAME}

${NAME} : ${OBJECTS}
	@${CC} ${CFLAGS} $(LDFLAGS) ${OBJECTS} -o ${NAME}
	@echo "\n$(GRN)➾ philo_bonus created$(RES)"

$(ODIR)/%.o: $(SDIR)/%.c | $(ODIR)
	@$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $<
	@echo "${GRN}➾ $@ created ${RES}"


$(ODIR):
	@mkdir -p $@	

clean :
	@${RM} ${OBJECTS}
	@${RM} ${ODIR}
	@echo "${RED}➾ philo_bonus objects deleted${RES}"

fclean : clean
	@${RM} ${NAME}
	@echo "${RED}➾ philo_bonus deleted${RES}"

re : fclean all