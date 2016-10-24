#pragma once 
#include "bmp.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <stdarg.h>
using namespace std;


bool encrypt(string path, string message,int encryptway) {
	// Initialization
	bmp image;
	if (image.loadImage(path))
	{
		cout << "File " << path << " not exists, broken or not BMP24" << endl;
		return false;
	}
	uint32_t size = 0, messagesize = message.size(),step=0;
	image.getsize(&size);
	if (size <messagesize)
	{
		cout << "File " << path << "cannot embed such long string" << endl;
		return false;
	}
	unsigned char m,messagemask,pixmask,judgeline;
	uint32_t x = 0, y = 0;
	int j=0;
	if (encryptway==SimpleLSB)
	{
		messagemask = 0x80;
		pixmask = 0x01;
		judgeline = 0x81;
		step = 1;
	}
	else if (encryptway == MultipleLSB1)
	{
		messagemask = 0xC0;
		pixmask = 0x03;
		judgeline = 0xC7;
		step = 2;
	}
	else
	{
		messagemask = 0xE0;
		pixmask = 0x07;
		judgeline = 0xE7;
		step = 3;
	}
	RGB8 pixel;
	unsigned char judge;
	uint32_t i = 0;
	// Seting lesser bits of img to meaning bits of message
	for (; i <messagesize; i++)
	{
		m = message[i];
		j = 8;
		while(j>0)
		{
			image.getPixel(x, &pixel);
			judge = (m & messagemask)>> (8 - step);
			if (judge ^ (pixel&pixmask))
			{
				image.setPixel(x, (((0xff) << step)&pixel) + judge);
			}
			x ++;
			j -= step;
            m=m << step;
		}
		
	}
	path.append(".bmp");
	if(image.saveImage(path))
	{
		cout << "Error saving Image." << endl;
		return false;
	}
	return true;
}

string decrypt(const char* path, const unsigned char stop_symbol, int encryptway) {
	// Initialization
	string message = "";
	bmp image;
	image.loadImage(path);
	uint32_t x = 0,size=0,i,step;
	int j=0;
	unsigned char m,mask;
	RGB8 pixel;
	image.getsize(&size);
	if (encryptway == SimpleLSB)
	{
		mask = 0x01;
		step = 1;
	}
	else if (encryptway == MultipleLSB1)
	{
		mask = 0x03;
		step = 2;
	}
	else
	{
		mask = 0x07;
		step = 3;
	}
	// Geting chars from img to message
	for (i = 0; x<size; i++) {

		m = 0x00;
		for(j=8;j>0;j-=step)
		{
			if (j < step)
			{
				m = m << j;
				image.getPixel(x, &pixel);
				m += (pixel & mask)>>(step-j);
				x++;
				break;
			}
			m = m << step;
			image.getPixel(x, &pixel);
			m += pixel & mask;
			x ++;
		}

		if (m == stop_symbol) {
			break;
		}
		message.append(1,(char)m);

	}
	return message + '\n';
}
