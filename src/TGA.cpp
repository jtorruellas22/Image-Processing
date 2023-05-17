#include "TGA.h"
#include <vector>
Tfile::Tfile()
{

}

void Tfile::print()
{
	cout << "ID Length: " << (int)header.idLength << endl;
	cout << "Color Map Type: " << (int)header.colorMapType << endl;
	cout << "Data Type Code: " << (int)header.dataTypeCode << endl;
	cout << "Color Map Origin: " << header.colorMapOrigin << endl;
	cout << "Color Map Length: " << header.colorMapLength << endl;
	cout << "Color Map Depth: " << (int)header.colorMapDepth << endl;
	cout << "X Origin: " << header.xOrigin << endl;
	cout << "Y Origin: " << header.yOrigin << endl;
	cout << "Width: " << header.width << endl;
	cout << "Height: " << header.height << endl;
	cout << "Bits Per Pixel: " << (int)header.bitsPerPixel << endl;
	cout << "Image Descriptor: " << (int)header.imageDescriptor << endl;
}

void Tfile::unPackHeader(ifstream& inFile)
{
	inFile.read(reinterpret_cast<char*>(&header.idLength), sizeof(header.idLength));
	inFile.read(reinterpret_cast<char*>(&header.colorMapType), sizeof(header.colorMapType));
	inFile.read(reinterpret_cast<char*>(&header.dataTypeCode), sizeof(header.dataTypeCode));
	inFile.read(reinterpret_cast<char*>(&header.colorMapOrigin), sizeof(header.colorMapOrigin));
	inFile.read(reinterpret_cast<char*>(&header.colorMapLength), sizeof(header.colorMapLength));
	inFile.read(reinterpret_cast<char*>(&header.colorMapDepth), sizeof(header.colorMapDepth));
	inFile.read(reinterpret_cast<char*>(&header.xOrigin), sizeof(header.xOrigin));
	inFile.read(reinterpret_cast<char*>(&header.yOrigin), sizeof(header.yOrigin));
	inFile.read(reinterpret_cast<char*>(&header.width), sizeof(header.width));
	inFile.read(reinterpret_cast<char*>(&header.height), sizeof(header.height));
	inFile.read(reinterpret_cast<char*>(&header.bitsPerPixel), sizeof(header.bitsPerPixel));
	inFile.read(reinterpret_cast<char*>(&header.imageDescriptor), sizeof(header.imageDescriptor));

}

void Tfile::unPackPixel(ifstream& inFile)
{
	int imageSize = header.width * header.height;
	for (int i = 0; i < imageSize; i++) {
		Pixel newPixel;
		inFile.read(reinterpret_cast<char*>(&newPixel.blue), sizeof(newPixel.blue));
		inFile.read(reinterpret_cast<char*>(&newPixel.green), sizeof(newPixel.green));
		inFile.read(reinterpret_cast<char*>(&newPixel.red), sizeof(newPixel.red));
		imageData.push_back(newPixel);
		pixel_count += 1;
	}
	
}

void Tfile::writeFile(string file)
{	
	ofstream outFile(file, ios::binary);
	outFile.write(reinterpret_cast<char*>(&header.idLength), sizeof(header.idLength));
	outFile.write(reinterpret_cast<char*>(&header.colorMapType), sizeof(header.colorMapType));
	outFile.write(reinterpret_cast<char*>(&header.dataTypeCode), sizeof(header.dataTypeCode));
	outFile.write(reinterpret_cast<char*>(&header.colorMapOrigin), sizeof(header.colorMapOrigin));
	outFile.write(reinterpret_cast<char*>(&header.colorMapLength), sizeof(header.colorMapLength));
	outFile.write(reinterpret_cast<char*>(&header.colorMapDepth), sizeof(header.colorMapDepth));
	outFile.write(reinterpret_cast<char*>(&header.xOrigin), sizeof(header.xOrigin));
	outFile.write(reinterpret_cast<char*>(&header.yOrigin), sizeof(header.yOrigin));
	outFile.write(reinterpret_cast<char*>(&header.width), sizeof(header.width));
	outFile.write(reinterpret_cast<char*>(&header.height), sizeof(header.height));
	outFile.write(reinterpret_cast<char*>(&header.bitsPerPixel), sizeof(header.bitsPerPixel));
	outFile.write(reinterpret_cast<char*>(&header.imageDescriptor), sizeof(header.imageDescriptor));

	for (int i = 0; i < pixel_count; i++) {
		outFile.write(reinterpret_cast<char*>(&imageData[i].blue), sizeof(imageData[i].blue));
		outFile.write(reinterpret_cast<char*>(&imageData[i].green), sizeof(imageData[i].green));
		outFile.write(reinterpret_cast<char*>(&imageData[i].red), sizeof(imageData[i].red));
	}
		
}

void Tfile::writeFileReverse(string file)
{
	ofstream outFile(file, ios::binary);
	outFile.write(reinterpret_cast<char*>(&header.idLength), sizeof(header.idLength));
	outFile.write(reinterpret_cast<char*>(&header.colorMapType), sizeof(header.colorMapType));
	outFile.write(reinterpret_cast<char*>(&header.dataTypeCode), sizeof(header.dataTypeCode));
	outFile.write(reinterpret_cast<char*>(&header.colorMapOrigin), sizeof(header.colorMapOrigin));
	outFile.write(reinterpret_cast<char*>(&header.colorMapLength), sizeof(header.colorMapLength));
	outFile.write(reinterpret_cast<char*>(&header.colorMapDepth), sizeof(header.colorMapDepth));
	outFile.write(reinterpret_cast<char*>(&header.xOrigin), sizeof(header.xOrigin));
	outFile.write(reinterpret_cast<char*>(&header.yOrigin), sizeof(header.yOrigin));
	outFile.write(reinterpret_cast<char*>(&header.width), sizeof(header.width));
	outFile.write(reinterpret_cast<char*>(&header.height), sizeof(header.height));
	outFile.write(reinterpret_cast<char*>(&header.bitsPerPixel), sizeof(header.bitsPerPixel));
	outFile.write(reinterpret_cast<char*>(&header.imageDescriptor), sizeof(header.imageDescriptor));

	for (int i = pixel_count - 1; i >= 0; i--) {
		outFile.write(reinterpret_cast<char*>(&imageData[i].blue), sizeof(imageData[i].blue));
		outFile.write(reinterpret_cast<char*>(&imageData[i].green), sizeof(imageData[i].green));
		outFile.write(reinterpret_cast<char*>(&imageData[i].red), sizeof(imageData[i].red));

	}

}

void Tfile::writeFileSeperate(string file, string file2, string file3)
{
	int temp = 0;
	vector<string> files = { file, file2, file3};
	for (int j = 0; j < 3; j++) {
		ofstream outFile(files[j], ios::binary);
		outFile.write(reinterpret_cast<char*>(&header.idLength), sizeof(header.idLength));
		outFile.write(reinterpret_cast<char*>(&header.colorMapType), sizeof(header.colorMapType));
		outFile.write(reinterpret_cast<char*>(&header.dataTypeCode), sizeof(header.dataTypeCode));
		outFile.write(reinterpret_cast<char*>(&header.colorMapOrigin), sizeof(header.colorMapOrigin));
		outFile.write(reinterpret_cast<char*>(&header.colorMapLength), sizeof(header.colorMapLength));
		outFile.write(reinterpret_cast<char*>(&header.colorMapDepth), sizeof(header.colorMapDepth));
		outFile.write(reinterpret_cast<char*>(&header.xOrigin), sizeof(header.xOrigin));
		outFile.write(reinterpret_cast<char*>(&header.yOrigin), sizeof(header.yOrigin));
		outFile.write(reinterpret_cast<char*>(&header.width), sizeof(header.width));
		outFile.write(reinterpret_cast<char*>(&header.height), sizeof(header.height));
		outFile.write(reinterpret_cast<char*>(&header.bitsPerPixel), sizeof(header.bitsPerPixel));
		outFile.write(reinterpret_cast<char*>(&header.imageDescriptor), sizeof(header.imageDescriptor));
		if (files[j] == file) {
			for (int i = 0; i < pixel_count; i++) {
				for (int k = 0; k < 3; k++) {
					outFile.write(reinterpret_cast<char*>(&imageData[i].red), sizeof(imageData[i].red));
				}
			}
		}
		if (files[j] == file2) {
			for (int i = 0; i < pixel_count; i++) {
				for (int k = 0; k < 3; k++) {
					outFile.write(reinterpret_cast<char*>(&imageData[i].green), sizeof(imageData[i].green));
				}
			}
		}
		if (files[j] == file3) {
			for (int i = 0; i < pixel_count; i++) {
				for (int k = 0; k < 3; k++) {
					outFile.write(reinterpret_cast<char*>(&imageData[i].blue), sizeof(imageData[i].blue));
				}
			}
		}
	}
	

}

int Tfile::getPixelCount()
{
	return pixel_count;
}

void Tfile::printPixel()
{
	for (int i = 0; i < pixel_count; i++)
	{
		cout << "Blue: " << (int)imageData[i].blue << endl;
		cout << "Green: " << (int)imageData[i].green << endl;
		cout << "Red: " << (int)imageData[i].red << endl;
	}
}

vector<Tfile::Pixel> Tfile::getImageData()
{
	return imageData;
}

void Tfile::Combine(Tfile x, Tfile y, Tfile z)
{
	header.idLength = x.header.idLength;
	header.colorMapType = x.header.colorMapType;
	header.dataTypeCode = x.header.dataTypeCode;
	header.colorMapOrigin = x.header.colorMapOrigin;
	header.colorMapLength = x.header.colorMapLength;
	header.colorMapDepth = x.header.colorMapDepth;
	header.xOrigin = x.header.xOrigin;
	header.yOrigin = x.header.yOrigin;
	header.width = x.header.width;
	header.height = x.header.height;
	header.bitsPerPixel = x.header.bitsPerPixel;
	header.imageDescriptor = x.header.imageDescriptor;
	
	for (int i = 0; i < x.pixel_count; i++)
	{
		Pixel newPixel;
		newPixel.red = (float)x.imageData[i].red;
		newPixel.green = (float)y.imageData[i].green;
		newPixel.blue = (float)z.imageData[i].blue;
		imageData.push_back(newPixel);
		pixel_count += 1;
	}
}

void Tfile::Multiply(Tfile x, Tfile y)
{
	header.idLength = x.header.idLength;
	header.colorMapType = x.header.colorMapType;
	header.dataTypeCode = x.header.dataTypeCode;
	header.colorMapOrigin = x.header.colorMapOrigin;
	header.colorMapLength = x.header.colorMapLength;
	header.colorMapDepth = x.header.colorMapDepth;
	header.xOrigin = x.header.xOrigin;
	header.yOrigin = x.header.yOrigin;
	header.width = x.header.width;
	header.height = x.header.height;
	header.bitsPerPixel = x.header.bitsPerPixel;
	header.imageDescriptor = x.header.imageDescriptor;
	
	for (int i = 0; i < x.pixel_count; i++) {
		Pixel newPixel;
		newPixel.red = 0.5f + ((float)x.imageData[i].red * (float)y.imageData[i].red) / 255;
		newPixel.green = 0.5f + ((float)x.imageData[i].green * (float)y.imageData[i].green) / 255;
		newPixel.blue = 0.5f + ((float)x.imageData[i].blue * (float)y.imageData[i].blue) / 255;
		imageData.push_back(newPixel);
		pixel_count += 1;
	}
}

void Tfile::Multiply(int x, string color)
{
	float num = 0;
	if (color == "red") {
		for (int i = 0; i < pixel_count; i++) {
			num = (float)imageData[i].red * x;
			if (num > 255) {
				num = 255;
			}
			if (num < 0) {
				num = 0;
			}
			imageData[i].red = (unsigned char)num;
		}
	}
	if (color == "blue") {
		for (int i = 0; i < pixel_count; i++) {
			num = (float)imageData[i].blue * x / 255;
			if (num > 255) {
				num = 255;
			}
			if (num < 0) {
				num = 0;
			}
			imageData[i].blue = (unsigned char)num;
		}
	}
	if (color == "green") {
		for (int i = 0; i < pixel_count; i++) {
			num = (float)imageData[i].green * x / 255;
			if (num > 255) {
				num = 255;
			}
			if (num < 0) {
				num = 0;
			}
			imageData[i].green = (unsigned char)num;
		}
	}
}

void Tfile::Subtract(Tfile x, Tfile y)
{	
	header.idLength = x.header.idLength;
	header.colorMapType = x.header.colorMapType;
	header.dataTypeCode = x.header.dataTypeCode;
	header.colorMapOrigin = x.header.colorMapOrigin;
	header.colorMapLength = x.header.colorMapLength;
	header.colorMapDepth = x.header.colorMapDepth;
	header.xOrigin = x.header.xOrigin;
	header.yOrigin = x.header.yOrigin;
	header.width = x.header.width;
	header.height = x.header.height;
	header.bitsPerPixel = x.header.bitsPerPixel;
	header.imageDescriptor = x.header.imageDescriptor;
	float red, green, blue;
	vector<Pixel> top = x.getImageData();
	vector<Pixel> bottom = y.getImageData();
	int count;
	if (x.getPixelCount() > y.getPixelCount()) {
		count = y.getPixelCount();
	}
	else{ 
		count = x.getPixelCount(); }

	for (int i = 0; i < count; i++)
	{
		Pixel newPixel;
		red = (float)top[i].red - (float)bottom[i].red;
		blue = (float)top[i].blue - (float)bottom[i].blue;
		green = (float)top[i].green - (float)bottom[i].green;
		if (red < 0) {
			red = 0;
		}
		if (blue < 0) {
			blue = 0;
		}
		if (green < 0) {
			green = 0;
		}
		newPixel.red = (unsigned char)red;
		newPixel.blue = (unsigned char)blue;
		newPixel.green = (unsigned char)green;
		imageData.push_back(newPixel);
		pixel_count += 1;
	}
}

void Tfile::Subtract(int x, string color)
{
	int num = 0;
	if (color == "red") {
		for (int i = 0; i < pixel_count; i++) {
			num = (int)imageData[i].red - x;
			if (num > 255) {
				num = 255;
			}
			if (num < 0) {
				num = 0;
			}
			imageData[i].red = num;
		}
	}
	if (color == "blue") {
		for (int i = 0; i < pixel_count; i++) {
			num = (int)imageData[i].blue - x;
			if (num > 255) {
				num = 255;
			}
			if (num < 0) {
				num = 0;
			}
			imageData[i].blue = num;
		}
	}
	if (color == "green") {
		for (int i = 0; i < pixel_count; i++) {
			num = (int)imageData[i].green - x;
			if (num > 255) {
				num = 255;
			}
			if (num < 0) {
				num = 0;
			}
			imageData[i].green = num;
		}
	}
}

void Tfile::Screen(Tfile x, Tfile y)
{
	header.idLength = x.header.idLength;
	header.colorMapType = x.header.colorMapType;
	header.dataTypeCode = x.header.dataTypeCode;
	header.colorMapOrigin = x.header.colorMapOrigin;
	header.colorMapLength = x.header.colorMapLength;
	header.colorMapDepth = x.header.colorMapDepth;
	header.xOrigin = x.header.xOrigin;
	header.yOrigin = x.header.yOrigin;
	header.width = x.header.width;
	header.height = x.header.height;
	header.bitsPerPixel = x.header.bitsPerPixel;
	header.imageDescriptor = x.header.imageDescriptor;


	for (int i = 0; i < x.pixel_count; i++)
	{
		Pixel newPixel;
		newPixel.red = 0.5f +(1 - ((1 - ((float)x.imageData[i].red / 255)) * (1 - ((float)y.imageData[i].red / 255)))) * 255;
		newPixel.green = 0.5f + (1 - ((1 - ((float)x.imageData[i].green / 255)) * (1 - ((float)y.imageData[i].green / 255)))) * 255;
		newPixel.blue = 0.5f + (1 - ((1 - ((float)x.imageData[i].blue / 255)) * (1 - ((float)y.imageData[i].blue / 255)))) * 255;
		imageData.push_back(newPixel);
		pixel_count += 1;
	}
}

void Tfile::Overlay(Tfile x, Tfile y)
{
	header.idLength = x.header.idLength;
	header.colorMapType = x.header.colorMapType;
	header.dataTypeCode = x.header.dataTypeCode;
	header.colorMapOrigin = x.header.colorMapOrigin;
	header.colorMapLength = x.header.colorMapLength;
	header.colorMapDepth = x.header.colorMapDepth;
	header.xOrigin = x.header.xOrigin;
	header.yOrigin = x.header.yOrigin;
	header.width = x.header.width;
	header.height = x.header.height;
	header.bitsPerPixel = x.header.bitsPerPixel;
	header.imageDescriptor = x.header.imageDescriptor;

	for (int i = 0; i < x.pixel_count; i++)
	{
		Pixel newPixel;
		if (((float)y.imageData[i].red / 255) <= 0.5) {
			newPixel.red = 0.5f + (2 * ((float)x.imageData[i].red / 255) * ((float)y.imageData[i].red / 255)) * 255;
		}
		else if (((float)y.imageData[i].red / 255) > 0.5) {
			newPixel.red = 0.5f + (1 - (2 * (1 - ((float)x.imageData[i].red / 255)) * (1 - ((float)y.imageData[i].red / 255)))) * 255;
		}
		if (((float)y.imageData[i].green / 255) <= 0.5) {
			newPixel.green = 0.5f + (2 * ((float)x.imageData[i].green / 255) * ((float)y.imageData[i].green / 255)) * 255;
		}
		else if (((float)y.imageData[i].green / 255) > 0.5) {
			newPixel.green = 0.5f + (1 - (2 * (1 - ((float)x.imageData[i].green / 255)) * (1 - ((float)y.imageData[i].green / 255)))) * 255;
		}
		if (((float)y.imageData[i].blue / 255) <= 0.5) {
			newPixel.blue = 0.5f + (2 * ((float)x.imageData[i].blue / 255) * ((float)y.imageData[i].blue / 255)) * 255;
		}
		else if (((float)y.imageData[i].blue / 255) > 0.5) {
			newPixel.blue = 0.5f + (1 - (2 * (1 - ((float)x.imageData[i].blue / 255)) * (1 - ((float)y.imageData[i].blue / 255)))) * 255;
		}
		imageData.push_back(newPixel);
		pixel_count += 1;
	}
}

bool Tfile::operator==(Tfile x) const
{
	int match = 0;
	for (int i = 0; i < pixel_count; i++) {
		if (imageData[i].red == x.imageData[i].red and imageData[i].blue == x.imageData[i].blue and imageData[i].green == x.imageData[i].green) {
			match += 1;
		}
	}
	if (match == pixel_count)
		return true;
	return false;
}

void Tfile::Add(int x, string color)
{
	float num = 0;
	if (color == "red") {
		for (int i = 0; i < pixel_count; i++) {
			num = (float)imageData[i].red + x;
			if (num > 255) {
				num = 255;
			}
			imageData[i].red = num;
		}
	}
	if (color == "blue") {
		for (int i = 0; i < pixel_count; i++) {
			num = (float)imageData[i].blue + x;
			if (num > 255) {
				num = 255;
			}
			imageData[i].blue = num;
		}
	}
	if (color == "green") {
		for (int i = 0; i < pixel_count; i++) {
			num = (float)imageData[i].green + x;
			if (num > 255) {
				num = 255;
			}
			imageData[i].green = num;
		}
	}
}

