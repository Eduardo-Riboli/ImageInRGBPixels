#include <stdio.h>
#include "lib_ppm.h"

void changePixels(struct image_s *imageFinal, int linha, int coluna, int r, int g, int b)
{
	imageFinal->pix[linha * imageFinal->width + coluna].r = r;
	imageFinal->pix[linha * imageFinal->width + coluna].g = g;
	imageFinal->pix[linha * imageFinal->width + coluna].b = b;
}

int main()
{
	struct image_s data;
	struct image_s *image = &data;
	struct image_s dataNew;
	struct image_s *imageFinal = &dataNew;
	int rgbs[3];
	int i, j, r;
	int aLinha = 0, bLinha = 1, cLinha = 2, x = 0, y = 1, z = 2;

	r = read_ppm("lena.ppm", image);

	if (r == 0)
	{
		imageFinal->width = image->width * 3;
		imageFinal->height = image->height * 3;

		printf("width: %d, height: %d\n", image->width, image->height);
		printf("widthFinal: %d, heightFinal: %d\n", imageFinal->width, imageFinal->height);

		for (j = 0; j < image->height; j++)
		{
			for (i = 0; i < image->width; i++)
			{
				int r = image->pix[j * image->width + i].r;
				int g = image->pix[j * image->width + i].g;
				int b = image->pix[j * image->width + i].b;

				rgbs[0] = r;
				rgbs[1] = g;
				rgbs[2] = b;
			}
		}

		free_ppm(image);
	}

	int oldImg = new_ppm(imageFinal, imageFinal->width, imageFinal->height);

	if (oldImg == 0)
	{
		for (int j = 0; j < image->height; j++) {
			for (int i = 0; i < image->width; i++) {
				int r = image->pix[j * image->width + i].r;
				int g = image->pix[j * image->width + i].g;
				int b = image->pix[j * image->width + i].b;

				rgbs[0] = r;
				rgbs[1] = g;
				rgbs[2] = b;

				for (int k = 0; k < 3; k++){

					if(rgbs[k] >= 0 && rgbs[k] <= 74) {
						if (k == 0) {
							changePixels(imageFinal, aLinha, x, 0, 0, 0);
							changePixels(imageFinal, bLinha, x, 0, 0, 0);
							changePixels(imageFinal, cLinha, x, 0, 0, 0);
						} else if (k == 1) {
							changePixels(imageFinal, aLinha, y, 0, 0, 0);
							changePixels(imageFinal, bLinha, y, 0, 0, 0);
							changePixels(imageFinal, cLinha, y, 0, 0, 0);
						} else if (k == 2) {
							changePixels(imageFinal, aLinha, z, 0, 0, 0);
							changePixels(imageFinal, bLinha, z, 0, 0, 0);
							changePixels(imageFinal, cLinha, z, 0, 0, 0);
						}
					}
					else if(rgbs[k] >= 75 && rgbs[k] <= 134) {
						if (k == 0) {
							changePixels(imageFinal, aLinha, x, 0, 0, 0);
							changePixels(imageFinal, bLinha, x, 255, 0, 0);
							changePixels(imageFinal, cLinha, x, 0, 0, 0);
						} else if (k == 1) {
							changePixels(imageFinal, aLinha, y, 0, 0, 0);
							changePixels(imageFinal, bLinha, y, 0, 255, 0);
							changePixels(imageFinal, cLinha, y, 0, 0, 0);
						} else if (k == 2) {
							changePixels(imageFinal, aLinha, z, 0, 0, 0);
							changePixels(imageFinal, bLinha, z, 0, 0, 255);
							changePixels(imageFinal, cLinha, z, 0, 0, 0);
						}
					}
					else if(rgbs[k] >= 135 && rgbs[k] <= 179) {
						if (k == 0) {
							changePixels(imageFinal, aLinha, x, 255, 0, 0);
							changePixels(imageFinal, bLinha, x, 0, 0, 0);
							changePixels(imageFinal, cLinha, x, 255, 0, 0);
						} else if (k == 1) {
							changePixels(imageFinal, aLinha, y, 0, 255, 0);
							changePixels(imageFinal, bLinha, y, 0, 0, 0);
							changePixels(imageFinal, cLinha, y, 0, 255, 0);
						} else if (k == 2) {
							changePixels(imageFinal, aLinha, z, 0, 0, 255);
							changePixels(imageFinal, bLinha, z, 0, 0, 0);
							changePixels(imageFinal, cLinha, z, 0, 0, 255);
						}
					}
					else if(rgbs[k] >= 180 && rgbs[k] <= 255) {
						if (k == 0) {
							changePixels(imageFinal, aLinha, x, 255, 0, 0);
							changePixels(imageFinal, bLinha, x, 255, 0, 0);
							changePixels(imageFinal, cLinha, x, 255, 0, 0);
						} else if (k == 1) {
							changePixels(imageFinal, aLinha, y, 0, 255, 0);
							changePixels(imageFinal, bLinha, y, 0, 255, 0);
							changePixels(imageFinal, cLinha, y, 0, 255, 0);
						} else if (k == 2) {
							changePixels(imageFinal, aLinha, z, 0, 0, 255);
							changePixels(imageFinal, bLinha, z, 0, 0, 255);
							changePixels(imageFinal, cLinha, z, 0, 0, 255);
						}
					}
				}
				x +=3;
				y +=3;
				z +=3;
				if (z >= imageFinal->height) {
					x = 0;
					y = 1;
					z = 2;

					aLinha += 3;
					bLinha += 3;
					cLinha += 3;

					if (cLinha >= imageFinal->width) {
						aLinha = 0;
						bLinha = 1;
						cLinha = 2;
					}
				}
			}
		}

		write_ppm("test.ppm", imageFinal);
		free_ppm(imageFinal);
	}

	return 0;
}
