#include <cstdlib>
#include <sstream>
#include <string>
#include <unistd.h>
#include <opencv2/opencv.hpp>

int main(int argc, const char *argv[])
{
  using namespace std;
  using namespace cv;
  string filename = "out.png";
  if (argc > 1) {
    filename = argv[1];
  }

  const int dotpos = filename.find_last_of('.');
  if (dotpos == string::npos) {
    fprintf (stderr,"%s: invalid filename\n",argv[0]);
    return 1;
  }
  
  const string basename {filename.begin (),filename.begin () + dotpos};
  const string suffix = {filename.begin () + dotpos + 1,filename.end ()};

  int height;
  int width;
  int channels;

  int count = 0;
  while(scanf ("%d %d %d\n",&height,&width,&channels) == 3) {
    Mat img(height,width,CV_8UC (channels));
    fread (img.data ,1, channels * height * width, stdin);
    stringstream outfile;
    outfile << basename << '-' << count << '.' << suffix;

    imwrite (outfile.str (),img);
    count++;
  }
  return 0;
}

