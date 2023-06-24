RMDIR = rm -rdf
RM = rm -f
ifeq ($(OS),Windows_NT)
RMDIR = rd /s /q
RM = del /q
endif

BISON = WinBisonFlex/win_bison
CXX = g++
FLEX = WinBisonFlex/win_flex
CXXFLAGS = -std=c++11
DFLAGS = -ggdb -O0 -DDEBUG
SRC_PATH = analise
MAIN = parser

.SECONDARY: sintatico.cc lexico.cc

all: $(MAIN)

%.cc %.hh: $(SRC_PATH)/%.yy
	$(BISON) $(BISONFLAGS) -o $*.cc $<

%.cc: $(SRC_PATH)/%.ll
	$(FLEX) $(FLEXFLAGS) -o $@ $<

%.o: %.cc
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(MAIN): $(MAIN).o sintatico.o lexico.o
	$(CXX) $(CXXFLAGS) -o $@ $^

$(MAIN).o: sintatico.hh
sintatico.o: sintatico.hh
lexico.o: sintatico.hh

debug: CXXFLAGS += $(DFLAGS)
debug: $(MAIN)

CLEANFILES = $(MAIN).exe *.o sintatico.cc sintatico.hh sintatico.output lexico.cc

clean:
	$(RM) $(CLEANFILES)