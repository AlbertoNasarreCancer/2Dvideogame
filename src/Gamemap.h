#ifndef INPUT_H
#define INPUT_H




struct sMapHeader {
	int w;
	int h;
	unsigned char bytes;
	unsigned char extra[7];
};

struct sCell {
	unsigned char type;
	unsigned char item;
};


class Gamemap
{
public:
	int width;
	int height;
	sCell* data;

	Gamemap(int w, int h);

	sCell& getCell(int x, int y);

	bool loadMap(const char* filename);

};


#endif