
default:
	g++ src/parser.cpp src/compiler.cpp src/neem.cpp ${llvm-config --libs} -o neem
