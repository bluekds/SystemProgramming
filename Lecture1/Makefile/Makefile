CC=gcc		# (built-in variable) compiling C programs
CFLAGS=-g -Wall	# (built-in variable) extra flags to give to CC
OBJS=main.o foo.o bar.o
TARGET=app.out
 
$(TARGET): $(OBJS)
	   $(CC) -o $@ $(OBJS)  # $@ : (automatic variables) current target name
	     
main.o: foo.h bar.h main.c
foo.o: foo.h foo.c
bar.o: bar.h bar.c

clean:
	    rm -f *.o
	    rm -f $(TARGET)
		
