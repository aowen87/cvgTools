SRC=main.C readers.C data.C source.C sink.C writers.C reader.C helpers.C avl.C 
OBJ=$(SRC:.C=.o)

prog: $(OBJ)
	g++ $(OBJ) -o cvgTools -lboost_program_options

.C.o: $<
	g++ -I. -c $< -lboost_program_options

clean:
	rm *.o cvgTools
