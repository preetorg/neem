
default:
	g++ src/parser.cpp src/neem.cpp ${llvm-config --libs} -o neem
