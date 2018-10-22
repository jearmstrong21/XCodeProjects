//
//  main.swift
//  MetalComputePathtracing
//
//  Created by Jack Armstrong on 10/21/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

import Foundation
import Metal
import MetalKit
import CoreGraphics
import Accelerate

let intSize = MemoryLayout<Int>.size
let floatSize = MemoryLayout<Float>.size

var device: MTLDevice! = MTLCreateSystemDefaultDevice()

var library: MTLLibrary! = device.makeDefaultLibrary()

var grayscaleKernel = library?.makeFunction(name: "grayscaleKernel")

var textureLoader = MTKTextureLoader(device: device)
//var inTexture = try! textureLoader.newTexture(name: "flower", scaleFactor: 1, bundle: Bundle.main, options: [:])
var inTexture = try! textureLoader.newTexture(URL: URL(fileURLWithPath: "flower.jpeg"), options: [:])
var texWidth=inTexture.width
var texHeight=inTexture.height
var outTextureDescriptor: MTLTextureDescriptor = MTLTextureDescriptor()
outTextureDescriptor.textureType = .type2D
outTextureDescriptor.width = texWidth
outTextureDescriptor.height = texHeight
outTextureDescriptor.usage = .shaderWrite
outTextureDescriptor.pixelFormat = .bgra8Unorm
outTextureDescriptor.storageMode = .managed
var outTexture = device.makeTexture(descriptor: outTextureDescriptor)

let commandQueue = device.makeCommandQueue()
let commandBuffer = commandQueue?.makeCommandBuffer()
let encoder = commandBuffer?.makeComputeCommandEncoder()
let pipelineGrayscale = try! device.makeComputePipelineState(function: grayscaleKernel!)

encoder?.setComputePipelineState(pipelineGrayscale)

encoder?.setTexture(inTexture , index: 0)
encoder?.setTexture(outTexture, index: 1)

var threadgroupSize = MTLSizeMake(16, 16, 1)
var threadgroupCount = MTLSizeMake(1,1,1)
threadgroupCount.width = (texWidth+threadgroupSize.width-1)/threadgroupSize.width
threadgroupCount.height = (texHeight+threadgroupSize.height-1)/threadgroupSize.height

encoder?.dispatchThreadgroups(threadgroupCount,threadsPerThreadgroup:threadgroupSize)

encoder?.endEncoding()
if let blitEncoder = commandBuffer?.makeBlitCommandEncoder() {
    blitEncoder.synchronize(resource: outTexture!)
    blitEncoder.endEncoding()
}

commandBuffer?.commit()
commandBuffer?.waitUntilCompleted()



//commandBuffer?.commit()
//commandBuffer?.waitUntilCompleted()

func swizzleBGRA8toRGBA8(_ bytes: UnsafeMutableRawPointer, width: Int, height: Int) {
    var sourceBuffer = vImage_Buffer(data: bytes,
                                     height: vImagePixelCount(height),
                                     width: vImagePixelCount(width),
                                     rowBytes: width * 4)
    var destBuffer = vImage_Buffer(data: bytes,
                                   height: vImagePixelCount(height),
                                   width: vImagePixelCount(width),
                                   rowBytes: width * 4)
    var swizzleMask: [UInt8] = [ 2, 1, 0, 3 ] // BGRA -> RGBA
    vImagePermuteChannels_ARGB8888(&sourceBuffer, &destBuffer, &swizzleMask, vImage_Flags(kvImageNoFlags))
}

func makeImage(for texture: MTLTexture) -> CGImage? {
    assert(texture.pixelFormat == .bgra8Unorm)
    
    let width = texture.width
    let height = texture.height
    let pixelByteCount = 4 * MemoryLayout<UInt8>.size
    let imageBytesPerRow = width * pixelByteCount
    let imageByteCount = imageBytesPerRow * height
    let imageBytes = UnsafeMutableRawPointer.allocate(byteCount: imageByteCount, alignment: pixelByteCount)
    defer {
        imageBytes.deallocate()
    }
    
    texture.getBytes(imageBytes,
                     bytesPerRow: imageBytesPerRow,
                     from: MTLRegionMake2D(0, 0, width, height),
                     mipmapLevel: 0)
    
    swizzleBGRA8toRGBA8(imageBytes, width: width, height: height)
    
    guard let colorSpace = CGColorSpace(name: CGColorSpace.linearSRGB) else { return nil }
    let bitmapInfo = CGImageAlphaInfo.premultipliedLast.rawValue
    guard let bitmapContext = CGContext(data: nil,
                                        width: width,
                                        height: height,
                                        bitsPerComponent: 8,
                                        bytesPerRow: imageBytesPerRow,
                                        space: colorSpace,
                                        bitmapInfo: bitmapInfo) else { return nil }
    bitmapContext.data?.copyMemory(from: imageBytes, byteCount: imageByteCount)
    let image = bitmapContext.makeImage()
    return image
}

func writeTexture(_ texture: MTLTexture, url: URL) {
    guard let image = makeImage(for: texture) else { return }
    
    if let imageDestination = CGImageDestinationCreateWithURL(url as CFURL, kUTTypePNG, 1, nil) {
        CGImageDestinationAddImage(imageDestination, image, nil)
        CGImageDestinationFinalize(imageDestination)
    }
}

writeTexture(outTexture!, url: URL(fileURLWithPath: "grayscale.png"))

