#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	fstream fin, fout;
	int width, height;

	// Open the input file
	fin.open( "input.txt", fstream::in );

	// Open the output file
	fout.open( "output.txt", fstream::out );

	fin >> width;
	fin >> height;

	fout << width;
	fout << " ";
	fout << height;
	fout << endl;

	fin.close();
	fout.close();

	return 0;
}
