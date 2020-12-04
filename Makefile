miniAES: miniAES.o src/nibbleSub.o src/shiftRow.o src/mixColumn.o src/keys.o ; g++ miniAES.o src/nibbleSub.o src/shiftRow.o src/mixColumn.o src/keys.o -o miniAES

miniAES.o: miniAES.cpp ; g++ -c miniAES.cpp
nibbleSub.o: nibbleSub.cpp ; g++ -c nibbleSub.cpp
shiftRow.o: shiftRow.cpp ; g++ -c shiftRow.cpp
mixColumn.o: mixColumn.cpp ; g++ -c mixColumn.cpp
keys.o: keys.cpp ; g++ -c keys.cpp


clean: ; rm *.o
