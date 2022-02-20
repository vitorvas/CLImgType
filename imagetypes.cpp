#define CL_TARGET_OPENCL_VERSION 110

#include<iostream>
#include<CL/cl.h>

using namespace std;

void printImageFormat(cl_image_format format)
{

#define CASE(order) case order: cout << #order; break;
  switch (format.image_channel_order)
  {
    CASE(CL_R);
    CASE(CL_A);
    CASE(CL_RG);
    CASE(CL_RA);
    CASE(CL_RGB);
    CASE(CL_RGBA);
    CASE(CL_BGRA);
    CASE(CL_ARGB);
    CASE(CL_INTENSITY);
    CASE(CL_LUMINANCE);
    CASE(CL_Rx);
    CASE(CL_RGx);
    CASE(CL_RGBx);
    //    CASE(CL_DEPTH);
    //    CASE(CL_DEPTH_STENCIL);
  }
#undef CASE

  cout << " - ";

#define CASE(type) case type: cout << #type; break;
  switch (format.image_channel_data_type)
  {
    CASE(CL_SNORM_INT8);
    CASE(CL_SNORM_INT16);
    CASE(CL_UNORM_INT8);
    CASE(CL_UNORM_INT16);
    CASE(CL_UNORM_SHORT_565);
    CASE(CL_UNORM_SHORT_555);
    CASE(CL_UNORM_INT_101010);
    CASE(CL_SIGNED_INT8);
    CASE(CL_SIGNED_INT16);
    CASE(CL_SIGNED_INT32);
    CASE(CL_UNSIGNED_INT8);
    CASE(CL_UNSIGNED_INT16);
    CASE(CL_UNSIGNED_INT32);
    CASE(CL_HALF_FLOAT);
    CASE(CL_FLOAT);
    //    CASE(CL_UNORM_INT24);
  }
#undef CASE

  cout << endl;
}


int main(int argc, char* argv[])
{
  cl_platform_id platform;
  cl_device_id device;
  cl_context context;
  cl_command_queue queue;
  cl_kernel kernel;
  cl_int clerr;
  
  clGetPlatformIDs(1, &platform, NULL);
  clerr = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
  if(clerr == CL_DEVICE_NOT_FOUND)
      clerr = clGetDeviceIDs(platform, CL_DEVICE_TYPE_CPU, 1, &device, NULL);
  
  context = clCreateContext(NULL, 1, &device, NULL, NULL, &clerr);

  cl_bool query;
  clerr = clGetDeviceInfo(device, CL_DEVICE_IMAGE_SUPPORT, query, NULL, NULL);

  char devname[255] = {'\0'};
  clGetDeviceInfo(device, CL_DEVICE_NAME, 255, devname, NULL);
  printf("Device name: %s\n", &devname);

  //  cl_image_format format;
  //  format.image_channel_order = CL_A; // o Cochon só aceita CL_A, CL_RGBA, CL_ARGB, CL_BGRA
  //  format.image_channel_data_type = CL_UNSIGNED_INT8;

  cl_uint nformats = 0;
  clGetSupportedImageFormats(context, CL_MEM_READ_WRITE, CL_MEM_OBJECT_IMAGE2D, 0, NULL, &nformats);
    
  // Ver os formatos de imagem suportados
  cl_image_format formlist[nformats];
  clGetSupportedImageFormats(context, CL_MEM_READ_WRITE, CL_MEM_OBJECT_IMAGE2D,
				     nformats, formlist, NULL);
  for(int i=0; i<nformats; i++)
  {
    printf("%d) ", i+1);
    printImageFormat(formlist[i]);
  }
  // Get image types availabe
  
  return 0;
}
