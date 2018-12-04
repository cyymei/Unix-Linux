CC = gcc
TARGET := smsh2.out
INCLUDES   := -I. -Ismsh2/
CFLAG := -Wall
SRCS    = smsh2.c controlfollow.c excute.c process.c splitline.c
OBJS    = $(SRCS:.c=.o)
.PHONY:all
	$(CC) $(LDFLAG) -o $(TARGET) $^
%.o:%.c
	$(CC) -c $(INCLUDES) $(CFLAG) $(CPPFLAG) $< -o $@
clean:     rm -rf $(basename $(TARGET)) $(SRCS:.c=.o)

