//
//  decode.c
//  im_comp
//
//  Created by Artem Lenskiy on 5/20/15.
//  Copyright (c) 2015 Artem Lenskiy. All rights reserved.
//

#include <stdio.h>
#include "im_comp.h"
#include "pbm.h"

int main(int argc, const char * argv[]) {
	short row, col, i, j, r;
	unsigned int cur_bnum = 0;
	unsigned char *p;
	unsigned num_blocks = 1024;
	unsigned short blocks8x8[num_blocks][64];
	unsigned short dctBlocks8x8[num_blocks][64];
	unsigned char *data;
	struct image_header ih;
	struct Run3D runs[];
	unsigned long data_size;
	FILE *fp;
	short F[8][8];

//    * Read run-level code from a standard input. To do so, redirect standard input form a keyboard to from a file i.e.
//        __./encode image_t.pbm < run3d.code
//    * Decode run-level code
	run_decode (runs[64],  blocks8x8 )
//    * Apply inverse zigzard ordering
	reverse_reorder ( dctBlocks8x8, blocks8x8 )
//    * Inverse quantize DCT coefficients
	inverse_quantize_block ( dctBlocks8x8[10] );
	printf("Inverse Quantizied DCT: \n");
	print_elements ( 8,  dctBlocks8x8[10] );
//    * Perform IDCT or every DCT block, and assemble the image
	idct ( 8, dctBlocks8x8, &F[0][0] );
//    * Store the reconstructed image into a PBM file
	readImage("/home/hyun/Desktop/flowers64.pbm", &data_size, &ih);
    return 0;
}
