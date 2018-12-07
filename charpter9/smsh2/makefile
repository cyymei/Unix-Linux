cc = gcc
prom = smsh2.out
INCLUDES   := -I ./
source = smsh2.c controlfollow.c excute.c process.c splitline.c builtin_commands.c
$(prom): $(source)
	$(cc) $(INCLUDES) -o $(prom) $(source)
