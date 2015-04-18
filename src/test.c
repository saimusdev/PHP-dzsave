#include <stdio.h>
#include <vips/vips.h>
#include <vips/foreign.h>

int
main(int argc, char **argv)
{
	///GError *error = NULL;
	VipsImage *in;

	if(VIPS_INIT(argv[0])) {
		vips_error_exit(NULL); 
	}


	if(argc < 3) {
		vips_error_exit("usage: %s infile outfile dzsave-options...", argv[0]); 
	}	

	if(vips_openslideload(argv[1], &in, NULL) < 0) {
		vips_error_exit("could not open slide");
	}	

	printf( "filename: %s\n", vips_image_get_filename(in));
	printf( "widthxheight: %dx%d\n", vips_image_get_width(in), vips_image_get_height(in) ); 	

	/*
	VIPS_FOREIGN_DZ_LAYOUT_ZOOMIFY - Zoomify
	VIPS_FOREIGN_DZ_LAYOUT_GOOGLE  - Google Maps
	VIPS_FOREIGN_DZ_LAYOUT_DZ      - Deep Zoom
	*/
	if(vips_dzsave(in, argv[2],
		"layout", VIPS_FOREIGN_DZ_LAYOUT_ZOOMIFY,
		"suffix", ".jpeg",
		"overlap", 0,
		"tile_size", 256,
		"depth", VIPS_FOREIGN_DZ_DEPTH_1TILE,
		"centre", FALSE,
		"angle", VIPS_ANGLE_0,
		NULL)) {
		vips_error_exit("could not save pyramid");
	} 
	
	// Free Mem
	g_object_unref(in); 

	printf("success");
	return 0;
}
