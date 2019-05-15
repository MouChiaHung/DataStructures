CFLAG = -O -ansi -Wwrite-strings
CINC = -I ./
CLIB = -L . 
OBJS = cell.o maze.o queen.o char.o move.o number.o sort.o screen.o math.o text.o view.o  text_view.o main.o
EXE	= main

.SUFFIXES: .cpp .o

all: $(EXE)

$(EXE): $(OBJS)
	g++ $(CFLAG) $(CINC) $(OBJS) -o $@
	rm -r $(OBJS) 
	 
screen.o: screen.cpp screen.h
	g++ $(CINC) -c $< 
	
math.o: math.cpp math.h
	g++ $(CINC) -c $< 
	
sort.o: sort.cpp sort.h
	g++ $(CINC) -c $<

char.o: char.cpp char.h
	g++ $(CINC) -c $<

cell.o: cell.cpp cell.h
	g++ $(CINC) -c $<

maze.o: maze.cpp maze.h cell.h
	g++ $(CINC) -c $<

queen.o: queen.cpp queen.h
	g++ $(CINC) -c $<
	
number.o: number.cpp number.h
	g++ $(CINC) -c $<
	
move.o: move.cpp move.h
	g++ $(CINC) -c $<
	
text.o: text.cpp text.h
	g++ $(CINC) -c $< 
	
view.o: view.cpp view.h
	g++ $(CINC) -c $< 
	
text_view.o: text_view.cpp text_view.h view.h text.h screen.h
	g++ $(CINC) -c $< 
	
main.o: main.cpp screen.h text_view.h text.h view.h space.h node.h linked_queue.h \
		queue.h array_queue.h list.h list_node.h stack.h char.h queen.h maze.h cell.h bin_node.h bin_tree.h huffman_tree.h
	g++ $(CINC) -c $<
	
clean:
	rm -r $(EXE) $(OBJS) 
					
