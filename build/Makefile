flags = -W -Wall -ansi -pedantic -std=c++17
obj = AIconnectivity.o ChessGame.o Square.o Piece.o Board.o ChessBoard.o Pawn.o Knight.o Bishop.o Rook.o Queen.o King.o 



run: chesso.exe
	./chesso.exe

chesso.exe: main.o $(obj)
	g++ -o chesso.exe $^

%.o: ../src/%.cpp ../src/%.h
	g++ -c $< $(flags)

main.o: ../src/main.cpp
	g++ -c $^ $(flags)

clean:
		rm -rf *.o
