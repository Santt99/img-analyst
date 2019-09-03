#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <cmath>
using namespace cv;
using namespace std;

float maximum(float array[]);
int main()
{

    
    float colorCount[255];

    for (int i = 0; i < 255; i++)
    {
        colorCount[i] = 0;
    }
    
    //Read the image
    Mat image;
    image = imread("one.jpg", IMREAD_GRAYSCALE);
    if(! image.data)                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }

    

    //Get how many times a color ir repeated
    Mat histogramImage(1024,1024,CV_8U,Scalar(0));
    for (int y = 0; y < image.rows; y++)
    {
        for (int x = 0; x < image.cols; x++)
        {
            
            colorCount[image.at<uchar>(y,x)]++;
        }
        
    }
    
    //Calculate PMF values
    for (int i = 0; i < 255; i++)
    {
        colorCount[i] = colorCount[i]/(image.cols*image.rows);
    }
    
    //Get maximum value maximum times that a color repeates in the image.
    float max = maximum(colorCount);
    
    //Calculate CDF histogram
    float CDF[255];
    CDF[0] = colorCount[0];
    for (int i = 1; i < 255; i++)
    {
        CDF[i] = CDF[i - 1] + colorCount[i];
    }
    
    //Draw CDF histogram
    for (int i = 0; i < 255; i++)
    {
        int from = i*4;
        int y = (CDF[i] * 255 *4);
        rectangle(histogramImage,Point(from,histogramImage.rows),Point(from + 2,histogramImage.rows - y),Scalar(255,255,255), FILLED,LINE_8,0);
    }

    //Equalize the image
    Mat equalizedImage = image.clone();

    for (int y = 0; y < equalizedImage.rows; y++)
    {
        for (int x = 0; x < equalizedImage.cols; x++)
        {
            equalizedImage.at<uchar>(y,x) = floor((255) * CDF[image.at<uchar>(y,x)]);
        }
        
    }
    
    //Show the images
    namedWindow( "Display window1", WINDOW_AUTOSIZE  );
    imshow( "Display window1", histogramImage );
    namedWindow( "Display window2", WINDOW_AUTOSIZE  );
    imshow( "Display window2", image ); 
    namedWindow( "Display window3", WINDOW_AUTOSIZE  );
    imshow( "Display window3", equalizedImage );          
    waitKey(0);                                         
    return 0;
}

//Search fot the maximum value 
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