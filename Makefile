PROG = project
LIBS = -lopengl32 -lglu32 -lfreeglut -lopenal -lassimp
#source codes
SRCS = $(PROG).cpp
#substitute .cpp by .o to obtain object filenames
OBJS = $(SRCS:.cpp=.o)

#$< evaluates to the target's dependencies,
#$@ evaluates to the target

$(PROG): $(OBJS)
	g++ -o $@ $(OBJS)  $(LIBS)
                                                                                
$(OBJS):
	g++ -c  $*.cpp
                                                                                
clean:
	rm $(OBJS)