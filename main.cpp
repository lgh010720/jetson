#include "opencv2/opencv.hpp"
#include <iostream>
#include <sys/time.h>
using namespace cv;
using namespace std;
int main()
{
    struct timeval start, end1;
    double time1;

    string src = "nvarguscamerasrc sensor-id=0 ! \
	video/x-raw(memory:NVMM), width=(int)640, height=(int)360, \
    format=(string)NV12, framerate=(fraction)30/1 ! \
	nvvidconv flip-method=0 ! video/x-raw, \
	width=(int)640, height=(int)360, format=(string)BGRx ! \
	videoconvert ! video/x-raw, format=(string)BGR ! appsink"; 

    VideoCapture source(src, CAP_GSTREAMER); 
    if (!source.isOpened()){ cout << "Camera error" << endl; return -1; }

    string dst1 = "appsrc ! videoconvert ! video/x-raw, format=BGRx ! \
	nvvidconv ! nvv4l2h264enc insert-sps-pps=true ! \
	h264parse ! rtph264pay pt=96 ! \
	udpsink host=203.234.58.160 port=8001 sync=false";
	
    VideoWriter writer1(dst1,0, (double)30,Size(640,360),true);
    if(!writer1.isOpened()) {cerr<<"Writer open failed!"<<endl; return -1;}

    string dst2 = "appsrc ! videoconvert ! video/x-raw, format=BGRx ! \
	nvvidconv ! nvv4l2h264enc insert-sps-pps=true ! \
	h264parse ! rtph264pay pt=96 ! \
	udpsink host=203.234.58.160 port=8002 sync=false";
	
    VideoWriter writer2(dst2,0, (double)30,Size(640,360),false);
    if(!writer2.isOpened()) {cerr<<"Writer open failed!"<<endl; return -1;}

    string dst3 = "appsrc ! videoconvert ! video/x-raw, format=BGRx ! \
	nvvidconv ! nvv4l2h264enc insert-sps-pps=true ! \
	h264parse ! rtph264pay pt=96 ! \
	udpsink host=203.234.58.160 port=8003 sync=false";

    VideoWriter writer3(dst3,0, (double)30,Size(640,360),false);
    if(!writer2.isOpened()) {cerr<<"Writer open failed!"<<endl; return -1;}

    Mat frame, gray, thres;
    while (true) {
        gettimeofday(&start,NULL);

      	source >> frame;
        	if (frame.empty()){ cerr << "frame empty!" << endl; break; }

	    cvtColor(frame, gray, COLOR_BGR2GRAY);
        threshold(gray, thres, 127, 255, THRESH_BINARY);

	    writer1 << frame;
	    writer2 << gray;
        writer3 << thres;
	    waitKey(30);

        gettimeofday(&end1,NULL);
        time1=end1.tv_sec-start.tv_sec +(end1.tv_usec-start.tv_usec)/1000000.0;
        cout << "time:" << time1 << endl;
    }
    return 0;
}
