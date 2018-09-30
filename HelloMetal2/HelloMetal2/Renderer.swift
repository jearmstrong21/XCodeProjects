//
//  Renderer.swift
//  HelloMetal2
//
//  Created by Jack Armstrong on 9/29/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

// Our platform independent renderer class

import Metal
import MetalKit
import simd


class Renderer: NSObject, MTKViewDelegate {

    public let device: MTLDevice

    var pipelineState: MTLRenderPipelineState! = nil
    
    var metalKitView: MTKView
    var metalLayer: CAMetalLayer! = nil
    var commandQueue: MTLCommandQueue! = nil
    
    var vertexBuffer: MTLBuffer! = nil
    var colorBuffer: MTLBuffer! = nil
    
    var startTime: NSDate! = nil
    
    var vertexData:[Float] = [
        0,0.5,0,
        -0.5,-0.5,0,
        0.5,-0.5,0
    ]
    
    var colorData:[Float] = [
        1.0,0.0,0.0,
        0.0,1.0,0.0,
        0.0,0.0,1.0
    ]
    
    init?(mkv: MTKView) {
        startTime = NSDate()
        
        metalKitView = mkv
        metalLayer = metalKitView.layer as! CAMetalLayer
        self.device = metalKitView.device!
        
        
        let vertexSize = vertexData.count * MemoryLayout.size(ofValue: vertexData[0])
        vertexBuffer = device.makeBuffer(bytes: vertexData, length: vertexSize, options: [])
        
        let colorSize = colorData.count * MemoryLayout.size(ofValue: colorData[0])
        colorBuffer = device.makeBuffer(bytes: colorData, length: colorSize, options: [])
        
        let defaultLibrary = device.makeDefaultLibrary()
        let vertexProgram = defaultLibrary?.makeFunction(name: "basicVertex")
        let fragmentProgram = defaultLibrary?.makeFunction(name: "basicFragment")
        
        let pipelineStateDescriptor = MTLRenderPipelineDescriptor()
        pipelineStateDescriptor.vertexFunction = vertexProgram
        pipelineStateDescriptor.fragmentFunction = fragmentProgram
        pipelineStateDescriptor.colorAttachments[0].pixelFormat = .bgra8Unorm
        
        do {
            try pipelineState = device.makeRenderPipelineState(descriptor: pipelineStateDescriptor)
        } catch let error {
            print("Failed to create pipeline state, error \(error)")
        }
        
        commandQueue = device.makeCommandQueue()
        
        super.init()

    }
    
    func draw(in view: MTKView) {
        let currentTime = Float(NSDate().timeIntervalSince(startTime as Date))
//        print("\(diff)")
        
        vertexData[0]=0.5*cosf(currentTime)
        vertexBuffer.contents().copyBytes(from: vertexData, count: vertexData.count*MemoryLayout.size(ofValue: vertexData[0]))
        
        colorData[0]=0.5+0.5*cosf(currentTime)
        colorBuffer.contents().copyBytes(from: colorData, count: colorData.count*MemoryLayout.size(ofValue: colorData[0]))
        
        let renderPassDescriptor = MTLRenderPassDescriptor()
        guard let drawable = metalLayer.nextDrawable() else { return }
        renderPassDescriptor.colorAttachments[0].texture = drawable.texture
        renderPassDescriptor.colorAttachments[0].loadAction = .clear
        renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColor(red:0.2,green:0.4,blue:0.2,alpha:1.0)
        
        let commandBuffer = commandQueue.makeCommandBuffer()
        
        let renderEncoder = commandBuffer?.makeRenderCommandEncoder(descriptor: renderPassDescriptor)
        renderEncoder?.setRenderPipelineState(pipelineState)
        renderEncoder?.setVertexBuffer(vertexBuffer, offset: 0, index: 0)
        renderEncoder?.setVertexBuffer(colorBuffer,  offset: 0, index: 1)
//        renderEncoder?.setVertexBuffers([vertexBuffer,colorBuffer], offsets: [0,0], range: 0..<2)
        renderEncoder?.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 3)
        renderEncoder?.endEncoding()
        
        commandBuffer?.present(drawable)
        commandBuffer?.commit()
        
    }

    func mtkView(_ view: MTKView, drawableSizeWillChange size: CGSize) {
        /// Respond to drawable size or orientation changes here

    }
}

// Generic matrix math utility functions
func matrix4x4_rotation(radians: Float, axis: float3) -> matrix_float4x4 {
    let unitAxis = normalize(axis)
    let ct = cosf(radians)
    let st = sinf(radians)
    let ci = 1 - ct
    let x = unitAxis.x, y = unitAxis.y, z = unitAxis.z
    return matrix_float4x4.init(columns:(vector_float4(    ct + x * x * ci, y * x * ci + z * st, z * x * ci - y * st, 0),
                                         vector_float4(x * y * ci - z * st,     ct + y * y * ci, z * y * ci + x * st, 0),
                                         vector_float4(x * z * ci + y * st, y * z * ci - x * st,     ct + z * z * ci, 0),
                                         vector_float4(                  0,                   0,                   0, 1)))
}

func matrix4x4_translation(_ translationX: Float, _ translationY: Float, _ translationZ: Float) -> matrix_float4x4 {
    return matrix_float4x4.init(columns:(vector_float4(1, 0, 0, 0),
                                         vector_float4(0, 1, 0, 0),
                                         vector_float4(0, 0, 1, 0),
                                         vector_float4(translationX, translationY, translationZ, 1)))
}

func matrix_perspective_right_hand(fovyRadians fovy: Float, aspectRatio: Float, nearZ: Float, farZ: Float) -> matrix_float4x4 {
    let ys = 1 / tanf(fovy * 0.5)
    let xs = ys / aspectRatio
    let zs = farZ / (nearZ - farZ)
    return matrix_float4x4.init(columns:(vector_float4(xs,  0, 0,   0),
                                         vector_float4( 0, ys, 0,   0),
                                         vector_float4( 0,  0, zs, -1),
                                         vector_float4( 0,  0, zs * nearZ, 0)))
}

func radians_from_degrees(_ degrees: Float) -> Float {
    return (degrees / 180) * .pi
}
