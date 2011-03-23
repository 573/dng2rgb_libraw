#include "libraw/libraw.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <time.h>
using namespace std;

int process_image(char *file) {
	int i, ret, s;

	// Let us create an image processor
	LibRaw iProcessor;

// http://www.libraw.org/docs/API-datastruct-eng.html#libraw_data_t
// ushort (*image)[4];
#define IMG iProcessor.imgdata.image
#define SZ iProcessor.imgdata.sizes
#define DATA iProcessor.imgdata.idata
#define COL iProcessor.imgdata.color
#define OTH iProcessor.imgdata.other

	// Open the file and read the metadata
	if( (ret = iProcessor.open_file(file)) != LIBRAW_SUCCESS) {
		fprintf(stderr,"Cannot open_file %s: %s\n",file,libraw_strerror(ret));
		// no recycle b/c open file will recycle itself
	}

	// The metadata are accessible through data fields of the class
	printf("Image size: %d x %d\n",SZ.width,SZ.height);

	printf("Number of raw images: %d\n", DATA.raw_count);
	printf("Camera manufacturer: %s\n", DATA.make);
	printf("Camera model: %s\n", DATA.model);
	printf("Number of colors: %d\n", DATA.colors);
	string cdesc = DATA.cdesc;
	printf("Colors description string: %s\n", cdesc.data());

	char c0 = cdesc.at(0);
	char c1 = cdesc.at(1);
	char c2 = cdesc.at(2);
	char c3 = cdesc.at(3);

	// http://www.libraw.org/docs/API-datastruct-eng.html#libraw_colordata_t
	printf("Camera color type: %s\n", COL.cam_xyz[3][0] == 0 && COL.cam_xyz[3][1] == 0 && COL.cam_xyz[3][2] == 0? "RGB":"Non-RGB");

	struct tm * timeinfo;
	timeinfo = localtime ( &OTH.timestamp );
	printf("Photo shot on: %s\n", asctime (timeinfo));

	// Let us unpack the image
	if( (ret = iProcessor.unpack() ) != LIBRAW_SUCCESS) {
		fprintf(stderr,"Cannot unpack %s: %s\n",file,libraw_strerror(ret));
	}

	// And let us print its dump; the data are accessible through data fields of the class
	for(i = 0; i < SZ.iwidth *  SZ.iheight; i++)
		printf("i=%d\t%c=%d\t%c=%d\t%c=%d\t%c=%d\n",
		       i,
		       c0,
		       IMG[i][0],
		       c1,
		       IMG[i][1],
		       c2,
		       IMG[i][2],
		       c3,
		       IMG[i][3]
		      );
	if(LIBRAW_SUCCESS !=ret) {
		fprintf(stderr,"Cannot do postpocessing on %s: %s\n",
		        file,libraw_strerror(ret));
		if(LIBRAW_FATAL_ERROR(ret));
	}

	// Finally, let us free the image processor for work with the next image
	iProcessor.recycle();
}

int main(int ac, char *av[]) {
	int  i;

	if(ac<2) {
		printf(
		    "dump_rgb_libraw_demo - LibRaw %s sample. Dumps R,G,B values.\n"
		    " %d cameras supported\n"
		    "Usage: %s raw-file\n"
		    ,LibRaw::version(),
		    LibRaw::cameraCount(),
		    av[0]);
		return 0;
	}

	for (i=1; i<ac; i++) {
		process_image(av[i]);
	}
	printf("Hit \"Enter\" to leave this program\n");
	fflush(stdin); /* Remove anything that is currently in the standard input */
	getchar();     /* Wait for the user to hit the enter key */
	return 0;
}
