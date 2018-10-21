//
//  main.swift
//  MetalComputePathtracing
//
//  Created by Jack Armstrong on 10/21/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

import Foundation
import Metal

let intSize = MemoryLayout<Int>.size
let floatSize = MemoryLayout<Float>.size

var device: MTLDevice! = MTLCreateSystemDefaultDevice()

var library: MTLLibrary! = device.makeDefaultLibrary()

var testKernel = library?.makeFunction(name: "testKernel")

let numElements: Int = 10

var arrayA: [Int] = Array(repeating: 0, count: numElements)
var arrayB: [Int] = Array(repeating: 0, count: numElements)
for i in 0..<numElements {
    arrayA[i] = i
    arrayB[i] = numElements - i
}

var bufferA: MTLBuffer! = device.makeBuffer(bytes: arrayA, length: intSize*numElements, options: [])
var bufferB: MTLBuffer! = device.makeBuffer(bytes: arrayB, length: intSize*numElements, options: [])
var bufferC: MTLBuffer! = device.makeBuffer(length: intSize*numElements, options: [])

let commandQueue = device.makeCommandQueue()
let commandBuffer = commandQueue?.makeCommandBuffer()
let encoder = commandBuffer?.makeComputeCommandEncoder()

let pipeline = try! device.makeComputePipelineState(function: testKernel!)

encoder?.setComputePipelineState(pipeline)

encoder?.setBuffer(bufferA, offset: 0, index: 0)
encoder?.setBuffer(bufferB, offset: 0, index: 1)
encoder?.setBuffer(bufferC, offset: 0, index: 2)

let threadgroupsPerGrid = MTLSize(width: 2, height: 1, depth: 1)
let threadsPerThreadgroups = MTLSize(width: numElements, height: 1, depth: 1)

encoder?.dispatchThreadgroups(threadgroupsPerGrid, threadsPerThreadgroup: threadsPerThreadgroups)

encoder?.endEncoding()

commandBuffer?.commit()
commandBuffer?.waitUntilCompleted()

let arrayC = bufferC.contents().assumingMemoryBound(to: Int.self)

for i in 0..<numElements {
    print("\(arrayA[i]) * \(arrayB[i]) = \(arrayC[i])")
}
