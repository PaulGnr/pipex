SRCDIR	= src

BNSDIR	= bonus

OBJDIR	= obj

BNSOBJDIR	= bonusobj

SRCS	= $(SRCDIR)/main.c $(SRCDIR)/pipex.c $(SRCDIR)/cmd.c $(SRCDIR)/redirection.c $(SRCDIR)/free.c $(SRCDIR)/error.c

BNS	= $(BNSDIR)/main.c $(BNSDIR)/pipex.c $(BNSDIR)/cmd.c $(BNSDIR)/redirection.c $(BNSDIR)/here_doc.c $(BNSDIR)/free.c $(BNSDIR)/error.c

OBJS	= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

BNSOBJS	= $(BNS:$(BNSDIR)/%.c=$(BNSOBJDIR)/%.o)

INCLUDE	= -I include/ -I libft/include/

LIB		= libft/libft.a

CC 		= gcc

CFLAGS	= -Wall -Wextra -Werror

RM		= rm -rf

HEAD	= include/$(NAME).h

HEADBNS	= include/$(BONUS).h

NAME	= pipex

BONUS	= pipex_bonus

all		: $(NAME)

bonus	: $(BONUS)

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME)	: $(OBJS) $(HEAD)
	@make -C libft/ -s
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) $(LIB) -o $@

$(BNSOBJDIR)/%.o : $(BNSDIR)/%.c
	@mkdir -p $(BNSOBJDIR)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(BONUS)	: $(BNSOBJS) $(HEADBNS)
	@make -C libft/ -s
	$(CC) $(CFLAGS) $(BNSOBJS) $(INCLUDE) $(LIB) -o $@

clean	:
	$(RM) libft/obj
	$(RM) $(BNSOBJDIR)
	$(RM) $(OBJDIR)

fclean	: clean
	$(RM) $(LIB)
	$(RM) $(NAME)
	$(RM) $(BONUS)

re		: fclean all
