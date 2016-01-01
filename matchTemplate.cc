#include <cstdlib>
#include <opencv2/opencv.hpp>

int main(int argc, const char *argv[])
{
  using namespace cv;
  const char * pattern_file;
  if (argc <= 1) {
    fprintf (stderr,"Usage: %s filename",argv[0]);
    return 1;
  }
  pattern_file = argv[1];

  int height;
  int width;
  int channels;
  
  Mat pattern = imread (pattern_file);
  cvtColor (pattern,pattern,CV_RGB2GRAY);

  while (scanf ("%d %d %d\n",&height,&width,&channels) == 3) {
    Mat img (height,width,CV_8UC (channels));
    fread (img.data ,1, channels * height * width, stdin);
  
    cvtColor (img,img,CV_RGB2GRAY);
  
    Mat result;
    matchTemplate(img, pattern, result, CV_TM_CCOEFF_NORMED);
  
    // find max score
    cv::Point max_pt;
    double maxVal;
    cv::minMaxLoc(result, NULL, &maxVal, NULL, &max_pt);
  
    const auto centerComplete = max_pt + Point {pattern.cols/2,pattern.rows/2};
  
    printf ("%g %d %d\n",maxVal,centerComplete.x,centerComplete.y);
  }

  return 0;
}

