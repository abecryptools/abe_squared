#!/bin/sh

 #zparser.o: zparser.yy                                                           
 
 $(BISON) -d -v zparser.yy                                                   
# cp *.hh $(OABE_INCLUDE_DIR)                                                 
# $(CXX) $(CXXFLAGS) -c -o zparser.o zparser.tab.cc

zscanner.o: zscanner.ll                                                         
$(FLEX) --outfile=zscanner.cpp  $<                                          
$(CXX) $(CXXFLAGS) -c zscanner.cpp -o zscanner.o

