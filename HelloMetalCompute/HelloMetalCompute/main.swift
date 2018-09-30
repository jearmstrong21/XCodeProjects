//
//  main.swift
//  HelloMetalCompute
//
//  Created by Jack Armstrong on 9/30/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//


//https://stackoverflow.com/questions/38164634/compute-sum-of-array-values-in-parallel-with-metal-swift
//https://forums.developer.apple.com/thread/46007

import Foundation
import Metal

let device = MTLCreateSystemDefaultDevice()
let library = device?.makeDefaultLibrary()
let kernelFunction = library?.makeFunction(name: "kernelFunction")
let pipeline = try! device?.makeComputePipelineState(function: kernelFunction!)

var data1: [Int] = [
    0,1,2,3,4,5,6,7,8,9
]

var data2: [Int] = [
    9,8,7,6,5,4,3,2,1,0
]

let dataCount = data1.count
let dataSize = dataCount * MemoryLayout.size(ofValue: data1[0])

let buffer1 = device?.makeBuffer(bytes: data1, length: dataSize, options: [])
let buffer2 = device?.makeBuffer(bytes: data2, length: dataSize, options: [])

let outBuffer = device?.makeBuffer(length: dataSize, options: [])

let commandQueue = device?.makeCommandQueue()
let commandBuffer = commandQueue?.makeCommandBuffer()
let encoder = commandBuffer?.makeComputeCommandEncoder()

encoder?.setComputePipelineState(pipeline!)

encoder?.setBuffer(buffer1, offset: 0, index: 0)
encoder?.setBuffer(buffer2, offset: 0, index: 1)
encoder?.setBuffer(outBuffer, offset: 0, index: 2)

let threadgroupsPerGrid = MTLSize(width: 2, height: 1, depth: 1)
let threadsPerThreadgroups = MTLSize(width: dataCount, height: 1, depth: 1)

encoder?.dispatchThreadgroups(threadgroupsPerGrid, threadsPerThreadgroup: threadsPerThreadgroups)
encoder?.endEncoding()

commandBuffer?.commit()
commandBuffer?.waitUntilCompleted()

let outputArray = unsafeBitCast(outBuffer?.contents(), to: UnsafeMutablePointer<Int>.self)

for i in 0..<dataCount {
    print("outputArray[\(i)] = \(data1[i]) * \(data2[i]) = \(outputArray[i])")
}

