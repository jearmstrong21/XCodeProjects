//
//  DebugCL.hpp
//  HelloCLWrapper
//
//  Created by Jack Armstrong on 8/6/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

#ifndef DebugCL_hpp
#define DebugCL_hpp

#include <stdio.h>
#include "cl.hpp"

#include <vector>
#include <string>

using cl::Platform;
using cl::Device;

using std::vector;
using std::string;

vector<Platform> printPlatformInfo();
vector<Device> printDeviceInfo(Platform&, cl_device_type type);

vector<Platform> printPlatformInfo(){
    vector<Platform>platforms;
    Platform::get(&platforms);
    for(int i=0;i<platforms.size();i++){
        Platform pl=platforms[i];
        
        string version;
        pl.getInfo(CL_PLATFORM_VERSION, &version);
        
        string vendor;
        pl.getInfo(CL_PLATFORM_VENDOR, &vendor);
        
        string profile;
        pl.getInfo(CL_PLATFORM_PROFILE, &profile);
        
        string name;
        pl.getInfo(CL_PLATFORM_NAME, &name);
        
        string ext;
        pl.getInfo(CL_PLATFORM_EXTENSIONS, &ext);
        
        printf("Version ....... %s\n",version.c_str());
        printf("Vendor ........ %s\n",vendor.c_str());
        printf("Profile ....... %s\n",profile.c_str());
        printf("Name .......... %s\n",name.c_str());
//        printf("Extensions\n%s\n",ext.c_str());
        
    }
    return platforms;
}

vector<Device> printDeviceInfo(Platform& pl,cl_device_type type){
    vector<Device>devices;
    pl.getDevices(type, &devices);
    
    for(int i=0;i<devices.size();i++){
        Device d=devices[i];
        
        size_t maxWorkGroupSize;
        d.getInfo(CL_DEVICE_MAX_WORK_GROUP_SIZE, &maxWorkGroupSize);
        
        cl_uint maxWorkItemDim;
        d.getInfo(CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, &maxWorkItemDim);
        
        vector<size_t> maxWorkItemSizes;
        d.getInfo(CL_DEVICE_MAX_WORK_ITEM_SIZES, &maxWorkItemSizes);
        
        string name;
        d.getInfo(CL_DEVICE_NAME, &name);
        
        string platform;
        d.getInfo(CL_DEVICE_PLATFORM, &platform);
        
        string profile;
        d.getInfo(CL_DEVICE_PROFILE, &profile);
        
        cl_uint vendorID;
        d.getInfo(CL_DEVICE_VENDOR_ID, &vendorID);
        
        string vendor;
        d.getInfo(CL_DEVICE_VENDOR, &vendor);
        
        string version;
        d.getInfo(CL_DEVICE_VERSION, &version);
        
        string driverVersion;
        d.getInfo(CL_DRIVER_VERSION, &driverVersion);
        
        printf("\nDevice #%i\n",i);
        
        printf("Max work group size ......... %i\n",(int)maxWorkGroupSize);
        printf("Max work item dimensions .... %i\n",(int)maxWorkItemDim);
        printf("Max work item sizes ......... ");
        for(int i=0;i<maxWorkItemDim;i++){
            printf("%i ",(int)maxWorkItemSizes[i]);
        }
        printf("\n");
        printf("Name ........................ %s\n",name.c_str());
        printf("Platform .................... %s\n",platform.c_str());
        printf("Profile ..................... %s\n",profile.c_str());
//        printf("Vendor ID ................... %i\n",vendorID);
        printf("Vendor ...................... %s\n",vendor.c_str());
        printf("Version ..................... %s\n",version.c_str());
        printf("Driver version .............. %s\n",driverVersion.c_str());
        
    }
    
    return devices;
}

#endif /* DebugCL_hpp */
