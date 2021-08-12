#include "Gamemap.h"
#include <iostream>
#include <cmath>
#include <string>
#include <iostream>
#include <assert.h> 
// #include "includes.h" ***DUDA***


sCell& Gamemap::getCell(int x, int y) {

	return data[x + y * width];

}

Gamemap::Gamemap(int w, int h)
{
	width = w;
	height = h;
	data = new sCell[w * h];
}

bool Gamemap::loadMap(const char* filename)
{
	FILE* file = fopen(filename, "rb");
	if (file == NULL) //file not found
		return false;

	sMapHeader header; //read header and store it in the struct
	fread(&header, sizeof(sMapHeader), 1, file);

	assert(header.bytes == 1); //always control bad cases!!

	//allocate memory for the cells data and read it
	unsigned char* cells = new unsigned char[header.w * header.h];
	fread(cells, header.bytes, header.w * header.h, file);

	width = header.w;
	height = header.h;
	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
			getCell(x, y).type = cells[x + y * width];

	delete[] cells; //always free any memory allocated!

	return true;
}
