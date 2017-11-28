Main.exe: $(patsubst %.cpp, %.o, $(wildcard *.cpp))
	g++ -o $@ $^

%.o: %.cpp $(wildcard *.h)
	g++ -c $<