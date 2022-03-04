# my_ls Makefile
# ©Thomas Stampfl 2021
# Student @ Qwasar (https://qwasar.io)

CC = gcc

# CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
CFLAGS = -Wall -Wextra -Werror

# change output filename >>> HERE <<<
EXE = my_ls

# foldernames end with /
BINDIR = bin/
OBJDIR = obj/
SRCDIR = src/

SRCS = $(wildcard $(SRCDIR)*.c)
OBJS = $(patsubst $(SRCDIR)%.c, $(OBJDIR)%.o, $(SRCS))


.PHONY: all dir clean fclean re 
all: dir $(BINDIR)$(EXE)

dir:
	@mkdir -p $(BINDIR)
	@mkdir -p $(OBJDIR)


$(BINDIR)$(EXE): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^


$(OBJS): $(OBJDIR)%.o : $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@rm -f $(OBJDIR)*.o
	@echo cleanup done

fclean: clean
	@rm -f $(BINDIR)$(EXE)

re: fclean $(BINDIR)$(EXE)

# debugging
# make print-SRCS print-OBJS
print-% :
	@echo $* = $($*)