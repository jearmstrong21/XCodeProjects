//
//  PrintDeviceInfo.h
//  HelloOpenCL
//
//  Created by Jack Armstrong on 6/24/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef PrintDeviceInfo_h
#define PrintDeviceInfo_h

#include <OpenCL/cl.h>
#include "EasyCL/EasyCL.h"
#include <iostream>

using std::cout;
using std::endl;
using easycl::printPlatformInfoString;
using easycl::printDeviceInfo;
using easycl::printDeviceInfoKB;
using easycl::printDeviceInfoMB;
using easycl::printDeviceInfoArray;
using easycl::printDeviceInfoString;
//using easycl

void printDeviceInfoUtility(){
    cl_int error = 0;   // Used to handle error codes
    cl_platform_id platform_ids[10];
    //    cl_context context;
    //    cl_command_queue queue;
    cl_device_id device;
    
    // Platform
    cl_uint num_platforms;
    error = clGetPlatformIDs(10, platform_ids, &num_platforms);
    cout << "num platforms: " << num_platforms << endl;
    if(num_platforms == 0) {
        cout << "No platforms found => exiting" << endl;
        return;
    }
    assert (error == CL_SUCCESS);
    cout << endl;
    
    for(int i = 0; i < (int)num_platforms; i++) {
        cout << "platform index: " << i << ":" << endl;
        cl_platform_id platform_id = platform_ids[i];
        cout << "platform id: " << platform_id << endl;
        printPlatformInfoString("platform vendor", platform_id, CL_PLATFORM_VENDOR);
        printPlatformInfoString("platform name", platform_id, CL_PLATFORM_NAME);
        cl_uint num_devices;
        error = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, 0, 0, &num_devices);
        if (error != CL_SUCCESS) {
            cout << "Error getting device ids: " << error << endl;
            exit(error);
        }
        cout << "platform num devices: " << num_devices << endl;
        cout << endl;
        cl_device_id *device_ids = new cl_device_id[num_devices];
        error = clGetDeviceIDs(platform_id, CL_DEVICE_TYPE_ALL, num_devices, device_ids, &num_devices);
        if (error != CL_SUCCESS) {
            cout << "Error getting device ids: " << error << endl;
            exit(error);
        }
        for(int i = 0; i < (int)num_devices; i++) {
            device = device_ids[i];
            cout << "   device index: " << i << endl;
            cout << "   device id: " << device << endl;
            printDeviceInfo("   device type", device, CL_DEVICE_TYPE);
            printDeviceInfoMB("   global memory size", device, CL_DEVICE_GLOBAL_MEM_SIZE);
            printDeviceInfoKB("   local memory size", device, CL_DEVICE_LOCAL_MEM_SIZE);
            printDeviceInfoKB("   global cache size", device, CL_DEVICE_GLOBAL_MEM_CACHE_SIZE);
            printDeviceInfo("   global cacheline size", device, CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE);
            printDeviceInfoMB("   max memory alloc size", device, CL_DEVICE_MAX_MEM_ALLOC_SIZE);
            printDeviceInfo("   max compute units", device, CL_DEVICE_MAX_COMPUTE_UNITS);
            printDeviceInfo("   max workgroup size", device, CL_DEVICE_MAX_WORK_GROUP_SIZE);
            printDeviceInfo("   max workitem dimensions", device, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS);
            printDeviceInfoArray("   max workitem sizes", device, CL_DEVICE_MAX_WORK_ITEM_SIZES, 3);
            printDeviceInfoString("   device name", device, CL_DEVICE_NAME);
            printDeviceInfoString("   opencl c version", device, CL_DEVICE_OPENCL_C_VERSION);
            printDeviceInfoString("   opencl device version", device, CL_DEVICE_VERSION);
            printDeviceInfo("   frequency MHz", device, CL_DEVICE_MAX_CLOCK_FREQUENCY);
            cout << endl;
        }
        delete[] device_ids;
    }
}


#endif /* PrintDeviceInfo_h */
