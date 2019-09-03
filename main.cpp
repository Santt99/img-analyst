#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

float maximum(float array[]);
int main()
{

    Mat image;
    image = imread("gorillaz.jpg", IMREAD_GRAYSCALE);
    float colorCount[255];

    for (int i = 0; i < 255; i++)
    {
        colorCount[i] = 0;
    }
    
    if(! image.data)                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    Mat histogramImage(1024,1024,CV_8U,Scalar(0));


    for (int y = 0; y < image.rows; y++)
    {
        for (int x = 0; x < image.cols; x++)
        {
            
            colorCount[image.at<uchar>(y,x)]++;
        }
        
    }
    
 
    for (int i = 0; i < 255; i++)
    {
        colorCount[i] = colorCount[i]/(image.cols*image.rows);
    }
    
    
    float max = maximum(colorCount);
    
    for (int i = 0; i < 255; i++)
    {
        int from = i*4;
        int y = (histogramImage.rows * colorCount[i])/max;
        rectangle(histogramImage,Point(from,histogramImage.rows),Point(from + 2,histogramImage.rows - y),Scalar(255,255,255), FILLED,LINE_8,0);
    }
              
    namedWindow( "Display window4", WINDOW_AUTOSIZE  );
    imshow( "Display window4", histogramImage );         
    waitKey(0);                                         
    return 0;
}

float maximum(float array[]){
    float *max = array;
    for (int i = 1; i < 255; i++)
    {
        if(*max < array[i]){
            max = &array[i];
        }
    }
    return *max;
}