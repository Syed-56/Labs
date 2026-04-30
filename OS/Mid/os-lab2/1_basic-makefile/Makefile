#1 This is the most simplest way to create make file but basic
# hello: hellofunc.c hellomake.c hellomake.h
# 	gcc hellomake.c hellofunc.c -o output

#2 Now we will use variables like for eg putting compiler name in variable so if we change compiler in future it is easy
# CC = gcc
# CFLAGS = -I.	#this flag indicates to look for files in current directory only
# #variables are accessed by $(var)
# hellomake: hellofunc.c hellomake.c hellomake.h
# 	$(CC) hellomake.c hellofunc.c -o output $(CFLAGS)

#3 We can also use macros(variables) to also store headerfiles
# CC = gcc
# CFLAGS = -I.
# DEPS = hellomake.h

#means to look for a file ending with .o for same name ending with .c basically we have replaced the whole target: dependencies with this simple line
#$@ is shortcut for target and $< is shortcut for first file on RHS 
#also we used -c bcz we are only creating object file
#step1: create pattern, step2: link them
# %.o: %.c $(DEPS)
# 	$(CC) -c -o $@ $< $(CFLAGS)
# hellomake: hellomake.o hellofunc.o
# 	$(CC) -o hellomake hellomake.o hellofunc.o

#4 we can also do this pattern thing with .o files too
CC = gcc
CFLAGS = -I.
DEPS = hellomake.h
OBJ = hellomake.o hellofunc.o

%.o: %.c (DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
hellomake: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

#this is the premium template, now in your project if you add a header file, write in DEPS. add a C file, write its .o in OBJ, change output name, replace hellomake with it