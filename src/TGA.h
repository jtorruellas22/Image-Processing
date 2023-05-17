#ifndef TGA
#define TGA
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
class Tfile
{
public:
	
	Tfile();
	
	struct Header {
		char idLength;
		char colorMapType;
		char dataTypeCode;
		short colorMapOrigin;
		short colorMapLength;
		char colorMapDepth;
		short xOrigin;
		short yOrigin;
		short width;
		short height;
		char bitsPerPixel;
		char imageDescriptor;
	};
	struct Pixel {
		unsigned char red;
		unsigned char green;
		unsigned char blue;
		vector <unsigned char> color = {red, green, blue};
	};
	void print();
	void unPackHeader(ifstream& inFile);
	void unPackPixel(ifstream& inFile);
	void writeFile(string file);
	void writeFileReverse(string file);
	void writeFileSeperate(string file, string file2, string file3);
	int getPixelCount();
	void printPixel();
	vector<Pixel> getImageData();
	void Combine(Tfile x, Tfile y, Tfile z);
	void Add(int x, string color);
	void Multiply(Tfile x, Tfile y);
	void Multiply(int x, string color);
	void Subtract(Tfile x, Tfile y);
	void Subtract(int x, string color);
	void Screen(Tfile x, Tfile y);
	void Overlay(Tfile x, Tfile y);
	bool operator==(Tfile x) const;

private:
	Header header;
	vector<Pixel> imageData;
	int pixel_count = 0;
};
#endif

