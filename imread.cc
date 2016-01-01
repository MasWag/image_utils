#include <cstdlib>
#include <unistd.h>
#include <opencv2/opencv.hpp>

int main(int argc, const char *argv[])
{
  using namespace cv;

  for (int i = 1; i < argc; i++) {
    const char* infile = argv[i];
    Mat img = imread (infile);    

    if (img.data == nullptr) {
      fprintf (stderr,"%s: Unsupported format %s\n",argv[0],infile);
      continue;
    }

    printf ("%d %d %d\n", img.rows, img.cols,img.channels ());
    fwrite (img.data ,1, img.channels() * img.rows * img.cols, stdout);
  }
  
  fclose (stdout);
  return 0;
}

