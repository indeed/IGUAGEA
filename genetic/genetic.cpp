// genetic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CImg.h"
using namespace cimg_library;
int main() {
	CImg<unsigned char> image("lena.bmp");
	int** grid = new int*[image.height];
	for (int i = 0; i < image.height; ++i)
		grid[i] = new int[image.width];

	const unsigned char red[] = { 255,0,0 }, green[] = { 0,255,0 }, blue[] = { 0,0,255 };
	image.blur(2.5);
	CImgDisplay main_disp(image, "Original Image"), gen_disp(500,500, "Intensity profile");
	while (!main_disp.is_closed() && !gen_disp.is_closed()) {
		main_disp.wait();
	}
	return 0;
}


