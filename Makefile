
JZlib_path = "../JZlib/JZlib.a"


# run
run: clean out
	reset
	./out < test_data

gdb: clean debug_out
	reset
	gdb ./out


# out
debug_out: main.cpp
	g++ -g -o out main.cpp $(JZlib_path)

out: main.o
	#g++ -o out main.o $(JZlib_path)
	g++ -o out main.o


# compile
main.o: main.cpp
	g++ -c main.cpp



# other 
clean:
	rm -rf main.o out

