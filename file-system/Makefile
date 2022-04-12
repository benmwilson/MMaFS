CXX=g++
COMP = g++
CXXFLAGS += -g -Wall -Wextra -pthread
FLAGS = -Wall -g -std=c++0x

MKDIR_P = mkdir -p

OBJ_DIR = obj


all: create_fs filesystem

${OBJ_DIR}:
	${MKDIR_P} ${OBJ_DIR}

obj/%.o: src/%.cpp ${OBJ_DIR}
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

create_fs: obj/create_fs.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

filesystem: obj/main.o obj/filesystem.o
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

clean:
	rm -f create_fs filesystem disk0
	rm -f *~ obj/*.o obj/*.a

