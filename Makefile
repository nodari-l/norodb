CPP = g++-14 
CPPFLAGS = -std=c++20 
CFLAGS = -std=c++20
OBJECTS =

BUILD = ./build
OBJDIR = ./build/obj

CPP_SRC = $(wildcard src/*.cc)
CPP_FILENAMES := $(notdir $(CPP_SRC))
OBJ_FILES := $(patsubst %.cc, $(OBJDIR)/%.o, $(CPP_FILENAMES) )

one:
	echo $(OBJ_FILES)

build: $(OBJ_FILES)
	$(shell mkdir -p $(BUILD)/lib)
	ar rcs build/lib/norodb.a $(OBJ_FILES)

$(OBJDIR)/%.o : 
	$(shell mkdir -p $(OBJDIR) )
	$(CPP) $(CPPFLAGS) -c $(patsubst %.o, src/%.cc, $(notdir $@)) -o $@

test: build
	@echo "\n\n >>>> RUNNING TESTS <<<<\n\n"
	make -B -C test/

format:
	find . -iname '*.h' -o -iname '*.cc' | xargs clang-format -i

clean:
	rm -rf build || true
