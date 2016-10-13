#pragma once

#include "bmp.h"
#include <fstream>
#include <cstring>
using namespace std;

 bmp  :: bmp ( )
{
    image = 0;
	FileHeader.data = NULL;
	FileHeader.size = 0;
    size = 0;
}

 bmp  :: ~bmp ( )
{
    delete image ;
}

 void bmp  :: allocImage ( )
 {

    image = new RGB8[FileHeader.size + 1 ];

    memset ( image, 0, FileHeader.size * sizeof( RGB8 ) );
}

 int bmp  :: loadImage ( string path )
{
    ifstream file(path, ios :: in | ios :: binary );
	if (!file)
	{
		return FILEIN;
	}
        
	file.seekg(0, ios::end);
	size = (unsigned long)file.tellg();//�ļ���С
	file.seekg(0, ios::beg);
	unsigned char *IMGtemp = new unsigned char[size];
	file.read((char*)IMGtemp, size);//����ͼƬ
	memcpy(&FileHeader.offset, &IMGtemp[10], 4);//����ƫ����
	numrote(FileHeader.offset);
	memcpy(&FileHeader.size, &IMGtemp[34], 4);//���볤�ȣ�ʵ��������ռ�ռ䣩
	numrote(FileHeader.size);//���η�ת����֤���ݸߵ�λ��ȷ��
	if (FileHeader.size == 0)//��Ϊ0�����ļ���С
	{
		memcpy(&FileHeader.size, &IMGtemp[2], 4);//��ȡλͼ�ļ���С
		numrote(FileHeader.size);
		FileHeader.size -= FileHeader.offset;
	}
	FileHeader.data = new char[FileHeader.offset];
	memcpy(FileHeader.data, IMGtemp, FileHeader.offset);
    this -> allocImage ( );
	memcpy(image, IMGtemp+ FileHeader.offset, FileHeader.size);

	if (!file.good())
	{
		return FILEIN;
	}
	delete[]IMGtemp;
    file.close();
	return FUNCSUCCEED;
}

 int bmp  :: saveImage ( string path )
{

    ofstream file (path, ios :: out | ios :: binary );

	if (!file)
	{
		return FILEOUT;
	}

    file.write ( FileHeader.data ,  FileHeader.offset*sizeof(char) );

    file.write ( ( char * ) image , FileHeader.size * sizeof(unsigned char));
	file.flush();
	if (!file.good())
	{
		return FILEOUT;
	}

    file.close ( );
	return FUNCSUCCEED;
}

 int bmp  :: setPixel ( uint32_t x,  RGB8 color) 
{
    image[x] = color;
	return FUNCSUCCEED;
}

 int bmp  :: getPixel ( uint32_t x,  RGB8 * pixel) 
{
    *pixel = image[x];
	return FUNCSUCCEED;
}

 int bmp::getsize(uint32_t * datasize)
 {
	 *datasize = FileHeader.size;
	 return 0;
 }


/* End of bmp.cpp */