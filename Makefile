SRCDIR	= src

BONUSSRCDIR	= bonus

OBJDIR	= obj

BONUSOBJDIR	= bonusobj

SRCS	= $(SRCDIR)/main.c $(SRCDIR)/pipex.c $(SRCDIR)/free.c $(SRCDIR)/error.c

BONUSSRCS	= $(BONUSSRCDIR)/main.c $(BONUSSRCDIR)/pipex.c $(BONUSSRCDIR)/here_doc.c $(BONUSSRCDIR)/free.c $(BONUSSRCDIR)/error.c

OBJS	= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

BONUSOBJS	= $(BONUSSRCS:$(BONUSSRCDIR)/%.c=$(BONUSOBJDIR)/%.o)

INCLUDE	= -I include/ -I libft/include/

LIB		= libft/libft.a

CC 		= gcc

CFLAGS	= -Wall -Wextra -Werror

RM		= rm -rf

NAME	= pipex

BONUS	= pipex_bonus

all		: $(NAME)

bonus	: $(BONUS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME)	: $(OBJS)
	@make -C libft/ -s
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) $(LIB) -o $@

$(BONUSOBJDIR)/%.o : $(BONUSSRCDIR)/%.c
	@mkdir -p $(BONUSOBJDIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(BONUS)	: $(BONUSOBJS)
	@make -C libft/ -s
	$(CC) $(CFLAGS) $(BONUSOBJS) $(INCLUDE) $(LIB) -o $@

clean	:
	$(RM) libft/obj
	$(RM) $(BONUSOBJDIR)
	$(RM) $(OBJDIR)

fclean	: clean
	$(RM) $(LIB)
	$(RM) $(NAME)
	$(RM) $(BONUS)

re		: fclean all
