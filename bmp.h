#pragma once

#include "dataType.h"
#include <string>


#define SimpleLSB 1
#define MultipleLSB1 2
#define MultipleLSB2 3
#define EncryptedLSB 4

using namespace std;
class bmp
{
    public:
    bmp ( void );
    ~bmp ( void );

    // Load an image from a bmp file
	int loadImage ( string path ) ;
    // Save the current bitmap image in a file
	int saveImage ( string path ) ;

    // Set a pixel with cartesian coordinates ( x, y ) and a RGB8 color
	int setPixel ( uint32_t x,RGB8 pix ) ;
    // Get a pixel with cartesian coordinates ( x, y )
	int getPixel ( uint32_t x , RGB8 *pix  );
	
	int getsize(uint32_t *datasize);


    private:
    void allocImage ();

    RGB8 * image;
    uint32_t size;

    fileHeader FileHeader;
};
template <class T>
T numrote(T a)//����������ֵ��ת���ֲ�memcpy�����鿽��������ֵʱ�����ķ�ת
{
	int s = sizeof(a);
	T temp = 0;

	if (s == 2) {//������
		T temp1 = a >> 8 & 0x00ff;
		T temp2 = a & 0x00ff;
		temp = (temp2 << 8 & 0xff00) | (temp1 & 0xff00);
	}
	if (s == 4) {//������
		T temp1 = a >> 24 & 0x000000ff;
		T temp2 = a >> 16 & 0x000000ff;
		T temp3 = a >> 8 & 0x000000ff;
		T temp4 = a & 0x000000ff;
		temp = (temp4 << 24 & 0xff000000) |
			(temp3 << 16 & 0x00ff0000) |
			(temp2 << 8 & 0x0000ff00) |
			(temp1 & 0x000000ff);
	}
	a = temp;
	return a;
}



/* End of bmp.h */