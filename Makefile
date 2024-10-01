CC = g++
CXX = g++
CXXFLAGS = -std=c++20 
CFLAGS = -std=c++20
OBJECTS =

BUILD = ./build
OBJDIR = ./build/obj

CXXSRC = $(wildcard src/*.cc)
CXXFILENAMES := $(notdir $(CXXSRC))
OBJ_FILES := $(patsubst %.cc, $(OBJDIR)/%.o, $(CXXFILENAMES) )

build: $(OBJ_FILES)
	$(shell mkdir -p $(BUILD)/lib)
	ar rcs build/lib/norodb.a $(OBJ_FILES)

$(OBJDIR)/%.o : $(CXXSRC)
	$(shell mkdir -p $(OBJDIR) )
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: build
	@echo "\n\n >>>> RUNNING TESTS <<<<\n\n"
	make -B -C test/

format:
	find . -iname '*.h' -o -iname '*.cc' | xargs clang-format -i

clean:
	rm -rf build || true
