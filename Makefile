CC := gcc-8
CXX := g++-8
INCLUDE_PATH := include

CXXHEAD := $(foreach ipath,$(INCLUDE_PATH),$(wildcard $(ipath)/**/*.hpp) $(wildcard $(ipath)/**/*.inl))
CCHEAD := $(foreach ipath,$(INCLUDE_PATH),$(wildcard $(ipath)/**/*.h))



OBJECT_FILES := out/Main.o out/QuizOption.o


CC_DIALECT = -std=c11
CXX_DIALECT = -std=c++17

CC_FLAGS = -g $(CC_DIALECT) -w -fwrapv
COMPILE_FLAGS = -g $(CXX_DIALECT) -w -fpermissive -fwrapv
LINKER_FLAGS = -pthread
LIBS = -llc -lcrypto -lssl
OUTPUT = main
INCLUDE = $(foreach ipath,$(INCLUDE_PATH),-I$(ipath))
DEFINES = 

LIBNAME =

DIRS := out/

BASE_DIR := out/

define gethead0
$(wordlist 2,$(words $(1)),$(1)) 
endef

define gethead
$(call gethead0,$(shell $(CXX) -MM $(CXX_DIALECT) $(INCLUDE) $(1))) 
endef

.PHONY: all FORCE clean rebuild relink version
.DEFAULT: all
.PRECIOUS: Makefile $(DIRS)
.SECONDEXPANSION:

all: $(DIRS) $(OUTPUT)

version:
	@echo $(CXX) version
	@$(CXX) --version
	@echo $(CC) verison
	@$(CC) --version

FORCE: ;

$(OUTPUT): $(OBJECT_FILES) $(LINFO_OBJ)
	$(CXX) $(LINKER_FLAGS) $(LIBNAME) -o $@ $^ $(LIBS) 

$(BASE_DIR):
	mkdir $(BASE_DIR)
	
$(BASE_DIR)/%/: $(BASE_DIR)
	mkdir -p $@


relink:
	rm -rf $(OUTPUT)
	$(MAKE) $(OUTPUT)

run: $(OUTPUT)
	./$(OUTPUT)

clean:
	rm -rf $(OBJECT_FILES)
	rm -rf $(LINFO_OBJ)
	rm -f $(OUTPUT)
	rm -f $(CXXHEAD:%.hpp=%.hpp.gch)
	rm -f $(CCHEAD:%.h=%.h.gch)

rebuild:
	$(MAKE) clean
	$(MAKE) $(OUTPUT)


out/%.o: src/%.cpp $$(D@) $(CXXHEAD:%.hpp=%.hpp.gch) $(CCHEAD:%.h=%.h.gch)
	$(CXX) $(COMPILE_FLAGS) $(DEFINES) -c $(INCLUDE) -o $@ $<

out/%.o: src/%.cpp $$(D@) $(CCHEAD:%.h=%.h.gch)
	$(CC) $(COMPILE_FLAGS) $(DEFINES) -c $(INCLUDE) -o $@ $<

%.hpp.gch: %.hpp
	$(CXX) $(COMPILE_FLAGS) $(DEFINES) -c $(INCLUDE) -o $@ $<

%.h.gch: %.h 
	$(CC) $(COMPILE_FLAGS) $(DEFINES) -c $(INCLUDE) -o $@ $<