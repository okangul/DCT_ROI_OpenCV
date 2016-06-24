#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>



// For using my code you need to change the output source with name like f1 E1 E1_1 Es1 for different results
//Thanks Okan Gul

using namespace std;
using namespace cv;


int xGradient(Mat image, int x, int y)
{
    return image.at<Vec3b>(y-1, x-1)[2] + 2*image.at<Vec3b>(y, x-1)[2] +image.at<Vec3b>(y+1, x-1)[2] -image.at<Vec3b>(y-1, x+1)[2] -2*image.at<Vec3b>(y, x+1)[2] - image.at<Vec3b>(y+1, x+1)[2];
}
 
// Computes the y component of the gradient vector
// at a given point in a image
// returns gradient in the y direction
 
int yGradient(Mat image, int x, int y)
{
    return image.at<Vec3b>(y-1, x-1)[2] + 2*image.at<Vec3b>(y-1, x)[2] + image.at<Vec3b>(y-1, x+1)[2] - image.at<Vec3b>(y+1, x-1)[2] - 2*image.at<Vec3b>(y+1, x)[2] - image.at<Vec3b>(y+1, x+1)[2];
}


void dct_ii(int N,const double x[], double X[]) {
  for (int k = 0; k < N; ++k) {
    double sum = 0.;
    double s = (k == 0) ? sqrt(.5) : 1.;
    for (int n = 0; n < N; ++n) {
      sum += s * x[n] * cos(M_PI * (n + .5) * k / N);
    }
    X[k] = sum * sqrt(2. / N);
  }
}


int main(int argc, char **argv) {
  


  
  if(argc != 2) {
    cout << "USAGE: skeleton <input file path>" << endl;
    return -1;
  }
  
  //Load two copies of the image. One to leave as the original, and one to be modified.
  //Done for display purposes only
  //Use CV_LOAD_IMAGE_GRAYSCALE for greyscale images
  Mat f1= imread(argv[1], CV_LOAD_IMAGE_COLOR);
  Mat E= imread(argv[1], CV_LOAD_IMAGE_COLOR);
  Mat src= imread(argv[1], CV_LOAD_IMAGE_COLOR);
  Mat f_hsi= imread(argv[1], CV_LOAD_IMAGE_COLOR);
  Mat f1_hsi= imread(argv[1], CV_LOAD_IMAGE_COLOR);
 
  //Create a pointer so that we can quickly toggle between which image is being displayed
  Mat *image = &f1;

  unsigned char *input = (unsigned char*)(f1.data);
 
  //Check that the images loaded
  if(!f1.data || !E.data) {
    cout << "ERROR: Could not load image data." << endl;
    return -1;
  }


  //  1D DCT PART 

  // Output values automaticly print on terminal if you want to control them

  double f_array1[8];
  double f_array2[8];
  double f_array3[16];
  double array1[8] ={10,11,12,11,12,13,12,11};
  double array2[8] ={10,-10,8,-7,8,-8,7,-7};
  double array3[16] ={10,11,12,11,12,13,12,11,10,-10,8,-7,8,-8,7,-7};
  
  

  dct_ii(8,array1, f_array1);
  dct_ii(8,array2, f_array2);
  dct_ii(16,array3, f_array3);

  for(int i=0;i<8;i++){

    cout<<f_array1[i]<<endl;
  }
  cout<<" hobbaaaa "<<endl;
  for(int i=0;i<8;i++){

    cout<<f_array2[i]<<endl;
  }
  cout<<" holleeeee "<<endl;
  for(int i=0;i<16;i++){

    cout<<f_array3[i]<<endl;
  }

  // RGB TO HSI part used the equation to change the pixel values to reach finding hsi values

  // ***** If you only want to see the HSI images you need to change output images  name to hsi ******

  Mat hsi(src.rows, src.cols, src.type());

  float r, g, b, h, s, in;

  for(int i = 0; i < src.rows; i++)
  {
    for(int j = 0; j < src.cols; j++)
      {
        b = src.at<Vec3b>(i, j)[0];
        g = src.at<Vec3b>(i, j)[1];
        r = src.at<Vec3b>(i, j)[2];

        in = (b + g + r) / 3;

        int min_val = 0;
        min_val = std::min(r, std::min(b,g));

        s = 1 - 3*(min_val/(b + g + r));
        if(s < 0.00001)
        {
          s = 0;
        }else if(s > 0.99999){
          s = 1;
        }

        if(s != 0)
        {
          h = 0.5 * ((r - g) + (r - b)) / sqrt(((r - g)*(r - g)) + ((r - b)*(g - b)));
          h = acos(h);

          if(b <= g)
          {
            h = h;
          } else{
            h = ((360 * 3.14159265) / 180.0) - h;
          }
          }

          hsi.at<Vec3b>(i, j)[0] = (h * 180) / 3.14159265;
          hsi.at<Vec3b>(i, j)[1] = s*100;
          hsi.at<Vec3b>(i, j)[2] = in;
        }
  }


  // Sobel operator for HSI image
  // I used my old which I write for assignment 2
  // Just change the Image to HSI components
  // ******  If you want to see the result images for ROI you need to change the result image to f_hsi *****

  int gx, gy, sum;
  for(int y = 0; y < hsi.rows; y++){
    for(int x = 0; x < hsi.cols; x++){

      f_hsi.at<Vec3b>(y, x)[0]= 0.0;
      f_hsi.at<Vec3b>(y, x)[1]= 0.0;
      f_hsi.at<Vec3b>(y, x)[2]= 0.0;
    }
  }
 
  for(int y = 1; y < hsi.rows - 1; y++){
      for(int x = 1; x < hsi.cols - 1; x++){
        gx = xGradient(hsi, x, y);

        gy = yGradient(hsi, x, y);
        
        
        sum = abs(gx) + abs(gy);
        if(sum>255)
          sum=255;
        else if(sum<0)
          sum=0;
        f_hsi.at<Vec3b>(y, x)[2]= sum;
      }
  }

  
  
 //Create the display window
  namedWindow("Unix Sample Skeleton");
  //Display loop
  bool loop = true;
  while(loop) {
    imshow("Unix Sample Skeleton", *image);
    
    switch(cvWaitKey(15)) {
      case 27:  //Exit display loop if ESC is pressed
        loop = false;
        break;
      case 32:  //Swap image pointer if space is pressed
        if(image == &f1) image = &hsi;
        else image = &f1;
        break;
      default:
        break;
    }
  }
}


