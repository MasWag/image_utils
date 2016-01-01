#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cstdio>
#include <unistd.h>
#include <cstdlib>

int main(int argc,const char* argv[])
{
  int loop_times = 1, sleep_time = 0;
  if (argc > 1) {
    loop_times = atoi (argv[1]);
    sleep_time = 1;
  }
  if (argc > 2) {
    sleep_time = atoi (argv[2]);
  }

  Display* display = XOpenDisplay(nullptr);
  Window root = DefaultRootWindow(display);

  XWindowAttributes attributes = {};
  XGetWindowAttributes(display, root, &attributes);

  const int width = attributes.width;
  const int height = attributes.height;

  for (int i = 0;i < loop_times; i++) {
    XImage* img = XGetImage(display, root, 0, 0 , width, height, AllPlanes, ZPixmap);

    printf ("%d %d %d\n",height,width, img->bits_per_pixel / 8);

    fwrite(img->data, img->bits_per_pixel / 8 * width * height,1,stdout);

    XDestroyImage(img);
    sleep (sleep_time);
  }
  fclose (stdout);
  XCloseDisplay(display);
  return 0;
}
