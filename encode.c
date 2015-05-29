#include <stdio.h>
#include "pbm.h"
#include "im_comp.h"
#include "dct.h"

int main(int argc, const char * argv[]) {

	unsigned char *data;
	struct image_header ih;
	struct Run3D runs[];
	unsigned long data_size;
	FILE *fp;
	short F[8][8];

	if (argc != 2) {
		printf("Not enough arguments, the program call should as follows: %s <input.pbm>", argv[0]);
		return 0;
	}

	data = readImage(argv[1], &data_size, &ih);

	short row, col, i, j, r;
	unsigned int cur_bnum = 0;
	unsigned char *p;
	unsigned num_blocks = 1024;
	unsigned short blocks8x8[num_blocks][64];
	unsigned short dctBlocks8x8[num_blocks][64];

	for ( row = 0; row < ih.rows; row += 8 ) {
		for ( col = 0; col < ih.cols; col += 8 ) {
			//points to beginning of a 8x8 block
			p = data + (row * ih.cols + col);
			r = 0; //note pointer arithmetic
			for ( i = 0; i < 8; ++i ) {
				for ( j = 0; j < 8; ++j ){
					blocks8x8[cur_bnum][r++] = *p;
					p++;
				}
				p += (ih.cols-8); //points to next row within macroblock
			}
			r = 0;
			cur_bnum++;
		} //for col
	} //for row
	//    * Split into 8 x 8 blocks and apply DCT to every block
	for(cur_bnum = 0; cur_bnum < num_blocks; cur_bnum++)
		dct ( 8, blocks8x8[cur_bnum], dctBlocks8x8[cur_bnum] );
	print_elements ( 8,  dctBlocks8x8[10] );

//    * Quantize DCT coefficients
	quantize_block (dctBlocks8x8[10] );
		printf("Quantizied DCT: \n");
		print_elements ( 8,  dctBlocks8x8[10] );
//    * Apply zigzag reordering
		reorder ( dctBlocks8x8, blocks8x8 );
//    * Apply run-level encoding and store the codes in `Run3D  runs[64];`
		run_block ( dctBlocks8x8, runs[64] );
//    * Print them on the screen, while running the program redirect standard stream to a file i.e.
		print_elements ( 8,  runs[64] );
//        __./encode image.pbm > run3d.code__
    return 0;
}
