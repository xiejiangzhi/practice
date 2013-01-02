
xlib_path = "../Xlib/xlib.a"


# run
run: clean out
	reset
	./out

gdb: clean debug_out
	reset
	gdb ./out


# out
debug_out: main.cpp
	g++ -g -o out main.cpp $(xlib_path)

out: main.o
	g++ -o out main.o $(xlib_path)



# compile
main.o: main.cpp
	g++ -c main.cpp



# other 
clean:
	rm -rf main.o out

