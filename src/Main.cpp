#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <stdint.h>

#include "Elas.h"
#include "Image.h"
#include "Utils.h"
#include "Timer.h"

using namespace cv;
using namespace std;

void process (const char* file_1,const char* file_2) {
    cout << "Processing: " << file_1 << ", " << file_2 << endl;

    // 加载图像
    image<uint8_t> *I1,*I2;
    I1 = loadPGM(file_1);
    I2 = loadPGM(file_2);

    // 检测图像的行列号是否正确
    if (I1->width()<=0 || I1->height() <=0 || I2->width()<=0 || I2->height() <=0 ||
        I1->width()!=I2->width() || I1->height()!=I2->height()) 
	{
      cout << "ERROR: Images must be of same size, but" << endl;
      cout << "       I1: " << I1->width() <<  " x " << I1->height() <<
                   ", I2: " << I2->width() <<  " x " << I2->height() << endl;
      delete I1;
      delete I2;
      return;
    }

	// 拿到图像的宽和高
    int32_t width  = I1->width();
    int32_t height = I1->height();

    // 为视差图分配内存
    const int32_t dims[2] = {width,height};
    float* D1_data = (float*)malloc(width*height*sizeof(float));
    float* D2_data = (float*)malloc(width*height*sizeof(float));

    Timer t;
    Elas elas;

    /*for(int i = 0; i < 10; i++){
        t.start("Exec " + to_string(i+1));
        elas.process(I1->data, I2->data, D1_data, D2_data, dims);
    }
    t.plot();
    */
    elas.process(I1->data, I2->data, D1_data, D2_data, dims);
}

void printDeviceProp()
{
    int nDevices;

    cudaGetDeviceCount(&nDevices);
    for (int i = 0; i < nDevices; i++) {
        cudaDeviceProp prop;
        cudaGetDeviceProperties(&prop, i);
        printf("Device Number: %d\n", i);
        printf("  Device name: %s\n", prop.name);
        printf("  Memory Clock Rate (KHz): %d\n",
               prop.memoryClockRate);
        printf("  Async Engines: %d\n",
               prop.asyncEngineCount);
        printf("  Concurrent Kernels: %d\n",
               prop.concurrentKernels);
        printf("  Memory Bus Width (bits): %d\n",
               prop.memoryBusWidth);
        printf("  Peak Memory Bandwidth (GB/s): %f\n",
               2.0*prop.memoryClockRate*(prop.memoryBusWidth/8)/1.0e6);
        printf("  Max Threads Per Block: %d\n", prop.maxThreadsPerBlock);
        printf("  Max Block Size (X, Y, Z): (%d, %d, %d)\n",
               prop.maxThreadsDim[0], prop.maxThreadsDim[1], prop.maxThreadsDim[2]);
        printf("  Max Grid Size (X, Y, Z): (%d, %d, %d)\n",
               prop.maxGridSize[0], prop.maxGridSize[1], prop.maxGridSize[2]);
        printf("  Shared Mem Per Block: %d bytes\n\n", prop.sharedMemPerBlock);
    }
}

int main( int argc, char* argv[] )
{
    printDeviceProp();
    cudaFree(0);

	const std::string workingDir = "E:\\Code\\CUDAStereoMatching\\img";
	const std::string leftObjectName = workingDir+"\\cones_left.pgm";
	const std::string rightObjectName = workingDir+"\\cones_right.pgm";
	
    // run demo
    if (argc==2 && !strcmp(argv[1],"demo")) 
	{
      process(leftObjectName.c_str(), rightObjectName.c_str());
      cout << "... done!" << endl;
    }
	else if (argc==3) 
	{
      process(argv[1],argv[2]);
      cout << "... done!" << endl;
    } 
	else 
	{
      cout << endl;
      cout << "ELAS demo program usage: " << endl;
      cout << "./elas demo ................ process all test images (image dir)" << endl;
      cout << "./elas left.pgm right.pgm .. process a single stereo pair" << endl;
      cout << "./elas -h .................. shows this help" << endl;
      cout << endl;
      cout << "Note: All images must be pgm greylevel images. All output" << endl;
      cout << "      disparities will be scaled such that disp_max = 255." << endl;
      cout << endl;
    }

	system("pause");
    return 0;
}
