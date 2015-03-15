/* compile with:
 *
 *      gcc -g -Wall test.c `pkg-config vips --cflags --libs` -o test
 */

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

//int vips_openslideload(const char *filename, VipsImage **out, ...)
//int vips_dzsave(VipsImage *in, const char *name, ...)

	if(argc < 3) {
		vips_error_exit("usage: %s infile outfile dzsave-options...", argv[0]); 
	}	

	if(vips_openslideload(argv[1], &in, NULL) < 0) {
		vips_error_exit(NULL);
	}	

	printf( "image width = %d\n", vips_image_get_width( in ) ); 	

	if(vips_dzsave(in, argv[2], &argv[3]) < 0) {
		vips_error_exit(NULL);
	}	

	printf("success");

	
	// Free Mem
	g_object_unref(in); 

	return 0;
}
