



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


class GameMap3
{
public:
	int width;
	int height;
	sCell* data;

	GameMap3(int w, int h);
	GameMap3();
	sCell& getCell(int x, int y);

	bool loadMap(const char* filename);

};



