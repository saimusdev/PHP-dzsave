#include <stdio.h>
#include <vips/vips.h>
#include <vips/foreign.h>

int
main(int argc, char **argv)
{
	GOptionContext *context;
	GOptionGroup *main_group;
	GError *error = NULL;
	VipsImage *in;

	if(VIPS_INIT(argv[0])) {
		vips_error_exit(NULL); 
	}

	context = g_option_context_new("simpyr inputSlide outputPyramidFolder - Pyramid builder");

	main_group = g_option_group_new(NULL, NULL, NULL, NULL, NULL);
	g_option_context_set_main_group(context, main_group);
	g_option_context_add_group(context, vips_get_option_group());

	if(!g_option_context_parse(context, &argc, &argv, &error)) {
		if(error) {
			fprintf(stderr, "%s\n", error->message);
			g_error_free(error);
		}

		vips_error_exit(NULL);
	}

	if(argc < 3) {
		vips_error_exit("usage: %s infile outfile dzsave-options...", argv[0]); 
	}	

	if(vips_openslideload(argv[1], &in, NULL) < 0) {
		vips_error_exit(NULL);
	}	

	printf( "image width = %d\n", vips_image_get_width( in ) ); 	

	printf("Argv 2: %s\n", argv[1]);
	printf("Argv 3: %s\n", argv[2]);

	if(im_vips2dz(in, argv[2]) < 0) {
		fprintf(stderr, "im_vips2dz error\n");
		vips_error_exit(NULL);
	}	

	printf("success");

	
	// Free Mem
	g_object_unref(in); 

	return 0;
}
