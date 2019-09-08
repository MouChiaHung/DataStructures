#ifndef _BMP_H_
#define _BMP_H_

#include <iostream>
#include <stdio.h>
#include <assert.h>
#include <time.h>

namespace amo {

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */

typedef unsigned char BYTE;
typedef unsigned short int UINT16;
typedef unsigned long UINT32;

/*
typedef int WORD;
typedef long DWORD;
typedef unsigned int UWORD;
typedef unsigned long UDWORD;
*/

//#define HEADER_SIZE 14
//#define INFO_SIZE 40

//Little-Endian
#define U16(x) ((unsigned short) (x))
#define U32(x) ((int) (x))
#define B2U16(bytes, offset) (U16(bytes[offset]) | U16(bytes[offset+1]) << 8)
#define B2U32(bytes, offset) (U32(bytes[offset]) | U32(bytes[offset+1]) << 8 | U32(bytes[offset+2]) << 16 | U32(bytes[offset+3]) << 24)

class PX {
protected:	

public:
	/** 
	 * BGR saved in file
	 */
	/* 
	BYTE R;
	BYTE G;
	BYTE B;
	*/
	BYTE B;
	BYTE G;
	BYTE R;
	PX() {}
	~PX() {}

friend std::ostream& operator<<(std::ostream& os, const PX& px) {
	int t = 10;
	os << GREEN;
	while (t-- > 0) os << "-";
	os << "Pixel TOP    ";
	t = 10;
	while (t-- > 0) os << "-";
	os << WHITE << std::endl;
	
	os << "[R]:" << std::hex << (int)px.R << std::endl;
	os << "[G]:" << std::hex << (int)px.G << std::endl;
	os << "[B]:" << std::hex << (int)px.B << std::endl;
	
	t = 10;
	os << GREEN;
	while (t-- > 0) os << "-";
	os << "Pixel BOTTOM ";
	t = 10;
	while (t-- > 0) os << "-";
	os << WHITE << std::endl;
	return os;
}
};

class BMP {
protected:	

public:
	int HEADER_SIZE;
	int INFO_SIZE;
	int PALETTE_SIZE;
    //Header
    UINT16 signature;  //Magic Number 0x4D42 stored in memory (Little-Endian), 0x42 0x4D saved in file as "BM"
    UINT32 fileSize;   //File size in bytes
    UINT32 hreserved;  //unused (=0)
    UINT32 dataOffset; //File offset to Raster Data
    //InfoHeader
    UINT32 size;   //Size of InfoHeader =40 
    UINT32 width;  //Bitmap Width
    UINT16 height; //Bitmap Height
    UINT16 planes; //Number of Planes (=1)
    UINT16 bitsPerPixel; //Bits per Pixel, 1, 4, 8, 16, 24
    UINT32 compression; //Type of Compression, 0 = BI_RGB no compression, 1 = BI_RLE8 8bit RLE encoding, 2 = BI_RLE4 4bit RLE encoding
    UINT32 imageSize; //(compressed) Size of Image, It is valid to set this =0 if Compression = 0
    UINT32 xPixelsPerM; //horizontal resolution: Pixels/meter
    UINT32 yPixelsPerM; //vertical resolution: Pixels/meter
    UINT32 colorsUsed; //Number of actually used colors
    UINT32 colorsImportant; //Number of important colors , 0 = all
    //ColorTable : present only if Info.BitsPerPixel <= 8 colors should be ordered by importance
    BYTE blue; //Blue intensity
    BYTE green; //Green intensity
    BYTE red; //Red intensity
    BYTE creserved; //unused (=0)
    //Raster Data
    BYTE* data;
	//Palette for gray scale
	BYTE* palette;
	//Arrays allocated by specific space which have to be declared last
	BYTE header[14];    
    BYTE info[40];
	
	BMP() : HEADER_SIZE(14), INFO_SIZE(40), PALETTE_SIZE(1024) {
		//header = (BYTE*) malloc(HEADER_SIZE);
		//info = (BYTE*) malloc(INFO_SIZE);
	}
	~BMP() {}
	size_t size_data() {
		//return width*height*3;
		return imageSize != 0 ? imageSize : width*height*3;
	}
	bool load(const char* inputFilePath);
	amo::PX getPixel(int x, int y);
	void setPixel(int x, int y, BYTE R, BYTE G, BYTE B);
	void setBox(int start_x, int start_y, int w, int h, BYTE R, BYTE G, BYTE B);
	void setZone(int start_x, int start_y, int w, int h, BYTE R, BYTE G, BYTE B);
	string save(const char* outputFilePath);
	void traverseData();

friend std::ostream& operator<<(std::ostream& os, const BMP& bmp) {
	int t = 10;
	os << GREEN;
	while (t-- > 0) os << "-";
	os << "BMP TOP    ";
	t = 10;
	while (t-- > 0) os << "-";
	os << WHITE << std::endl;
	
	os << "[signature]      :" << std::hex << bmp.signature << std::dec << std::endl; // 0x4d42 = BM
	os << "[file size]      :" << bmp.fileSize << std::endl;
	os << "[data offset]    :" << bmp.dataOffset << std::endl;
	os << "[size]           :" << bmp.size << std::endl;
	os << "[width]          :" << bmp.width << std::endl;
	os << "[height]         :" << bmp.height << std::endl;
	os << "[planes]         :" << bmp.planes << std::endl;
	os << "[bits per pixel] :" << bmp.bitsPerPixel << std::endl;
	os << "[compression]    :" << bmp.compression << std::endl;
	os << "[image size]     :" << bmp.imageSize << std::endl;
	os << "[X pixel/meter]  :" << bmp.xPixelsPerM << std::endl;
	os << "[Y pixel/meter]  :" << bmp.yPixelsPerM << std::endl;
	os << "[color used]     :" << bmp.colorsUsed << std::endl;
	os << "[color important]:" << bmp.colorsImportant << std::endl;
	os << "[blue]           :" << bmp.blue << std::endl;
	os << "[green]          :" << bmp.green << std::endl;
	os << "[red]            :" << bmp.red << std::endl;
	os << "[reserved]       :" << bmp.creserved << std::endl;
	
	t = 10;
	os << GREEN;
	while (t-- > 0) os << "-";
	os << "BMP BOTTOM ";
	t = 10;
	while (t-- > 0) os << "-";
	os << WHITE << std::endl;
	return os;
}
};

bool amo::BMP::load(const char* inputFilePath) {
	std::cout << YELLOW << "Loading... " << inputFilePath << WHITE << std::endl;
	std::ifstream fis(inputFilePath, std::ios::binary|std::ios::in);
	char c;
	int len = 0;
	int l = 0;
	
	//header
	memset(header, 0, HEADER_SIZE);
	fis.seekg(0, fis.end);
	len = fis.tellg();
	fis.seekg(0, fis.beg);
	while (fis.get(c)) {
		header[l] = c;
		if (l == HEADER_SIZE) {
			if (fis.tellg() == (HEADER_SIZE+1)) {
				std::cout << GREEN << "loaded header for " << l << " bytes" << WHITE << std::endl;
				break;
			}
			else {
				std::cout << RED << __func__ << ":Exception case loading header size:" << fis.tellg() << WHITE << std::endl;
				return false;
			}
		}
		l++;
	}
	signature = B2U16(header, 0);
	assert(signature == 0x4D42);
	fileSize = B2U32(header, 2);
	//hreserved = B2U32(header, 6);
	dataOffset = B2U32(header, 10);
	if (dataOffset == 1078) {
		std::cout << YELLOW << "allocates a palette for gray scale" << WHITE << std::endl;
		palette = (BYTE*) malloc(PALETTE_SIZE);
	} 
	else palette = NULL;
	//info
	memset(info, 0, INFO_SIZE);
	l = 0;
	fis.seekg(HEADER_SIZE, fis.beg);
	while (fis.get(c)) {
		info[l] = c;
		if (l == INFO_SIZE) {
			if (fis.tellg() == (HEADER_SIZE+INFO_SIZE+1)) {
				std::cout << GREEN << "loaded info for " << l << " bytes" << WHITE << std::endl;
				break;
			}
			else {
				std::cout << RED << __func__ << ":Exception case loading info size:" << fis.tellg() << WHITE << std::endl;
				return false;
			}
		}
		l++;
	}
	size = B2U32(info, 0);
	assert(size == 40);
	width = B2U32(info, 4);
	height = B2U32(info, 8);
	planes = B2U16(info, 12);
	assert(planes == 1);
	bitsPerPixel = B2U16(info, 14);
	//assert(bitsPerPixel == 24);
	compression = B2U32(info, 16);
	imageSize = B2U32(info, 20);
	xPixelsPerM = B2U32(info, 24);
	yPixelsPerM = B2U32(info, 28);
	colorsUsed = B2U32(info, 32);
	colorsImportant = B2U32(info, 36);
	
	//palette
	if (palette != NULL) {
		fis.seekg(HEADER_SIZE+INFO_SIZE, fis.beg);
		fis.read((char*) palette, PALETTE_SIZE);
	}
	
	//data
	fis.seekg(dataOffset, fis.beg);
	this->data = (BYTE*) malloc(size_data());
	fis.read((char*) data, size_data());
	
	if (fis) {
		std::cout << GREEN << "loaded data for " << fis.gcount() << " bytes" << WHITE << std::endl;
	}
	else {
		std::cout << RED << __func__ << ":Exception case loading data only " << fis.gcount() << " could be read" << WHITE << std::endl;
		return false;
	}
	fis.close();
	return true;
}

string amo::BMP::save(const char* outputFilePath) {
	time_t t;
	struct tm *tm_s;
	int diff;
	char stamp[64] {'S', 'T', 'A', 'M', 'P'};
	
	time(&t);
	tm_s =  localtime(&t);
	tm_s->tm_hour = 0;
	tm_s->tm_min = 0;
	tm_s->tm_sec = 0;
	tm_s->tm_mon = 0;
	tm_s->tm_mday = 0;
	tm_s->tm_year = 119;
	diff = (int)difftime(t, mktime(tm_s))/1000;	
	sprintf(stamp, "%d", diff);	
	std::cout << "stamp:" << stamp << std::endl;
	
	char copy[128];
	char out[128];
	char format[64];
	
	char* pch;
	strcpy(copy, outputFilePath);
	pch = strtok(copy, ".");
	strcpy(out, pch);
	while(pch != NULL) {
		strcpy(format, pch);
		pch = strtok(NULL, ".");
	}
	strcat(out, "_");
	strcat(out, stamp);
	strcat(out, ".");
	strcat(out, format);
	//std::cout << "saved as file:" << out << std::endl;
	
	std::ofstream fos(out, std::ios::binary|std::ios::out);
	fos.write((char*) header, HEADER_SIZE);
	//std::cout << "tellp:" << fos.tellp() << std::endl;
	
	fos.seekp(HEADER_SIZE, fos.beg);
	fos.write((char*) info, INFO_SIZE);
	//std::cout << "tellp:" << fos.tellp() << std::endl;
	
	//palette
	if (palette) {
		fos.seekp(HEADER_SIZE+INFO_SIZE, fos.beg);
		fos.write((char*) palette, PALETTE_SIZE);
	}
	
	fos.seekp(dataOffset, fos.beg);
	fos.write((char*) data, size_data());
	//std::cout << "tellp:" << fos.tellp() << std::endl;
	fos.close();
	
	string str;
	str.assign(out);
	return str;
}

void amo::BMP::traverseData() {
	for (int k=0; k<size_data()/100; k++) 
		printf("data[%d]:%x\n", k, data[k]);
}

amo::PX amo::BMP::getPixel(int x, int y) {
	int i = 0+(y*width)+x;
	int idxB = (i*bitsPerPixel/8)+0;
	int idxG = (i*bitsPerPixel/8)+1;
	int idxR = (i*bitsPerPixel/8)+2;
	
	PX pix;
	printf("data[%d]:%x\n", idxB, data[idxB]);
	printf("data[%d]:%x\n", idxG, data[idxG]);
	printf("data[%d]:%x\n", idxR, data[idxR]);
	pix.B = data[(i*bitsPerPixel/8)+0];
	pix.G = data[(i*bitsPerPixel/8)+1];
	pix.R = data[(i*bitsPerPixel/8)+2];
	return pix;
}


void amo::BMP::setPixel(int x, int y, BYTE R, BYTE G, BYTE B) {
	int i = 0+(y*width)+x;
	PX *pix = (PX*) &data[i*bitsPerPixel/8]; 
	pix->B = B; //&data[(i*bitsPerPixel/8)] + 0;
	pix->G = G; //&data[(i*bitsPerPixel/8)] + sizeof(BYTE);
	pix->R = R; //&data[(i*bitsPerPixel/8)] + sizeof(BYTE) + sizeof(BYTE);
	//std::cout << *pix << std::endl;
}

void amo::BMP::setBox(int start_x, int start_y, int w, int h, BYTE R, BYTE G, BYTE B) {
	int i = 0;
	int j = 0;
	for (i=0; i<start_y+h; i++)
		for (j=0; j<start_x+w; j++)
			setPixel(start_x+j, start_y+i, R, G, B);
}

void amo::BMP::setZone(int start_x, int start_y, int w, int h, BYTE R, BYTE G, BYTE B) {
	int i = 0;
	int j = 0;
	for (i=0; i<h; i++)
		for (j=0; j<w; j++) {
			if (R <= 255) {
				if (R > 0) R--;
				else R++;
			} 
			else {
				R = 255;
			}
			if (G <= 255) {
				if (G > 0) G = G-2;
				else G = G+2;
			} 
			else {
				G = 255;
			}
			if (B <= 255) {
				if (B > 0) B = B-3;
				else B = B+3;
			} 
			else {
				B = 255;
			}
			setPixel(start_x+j, start_y+i, R, G, B);
		}
			
}

















};
#endif