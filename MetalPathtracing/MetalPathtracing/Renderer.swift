//
//  Renderer.swift
//  MetalPathtracing
//
//  Created by Jack Armstrong on 10/11/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

// Our platform independent renderer class

import Metal
import MetalKit
import simd


class Renderer: NSObject, MTKViewDelegate {
    
    var device: MTLDevice!
    
    var pipelineState: MTLRenderPipelineState! = nil
    
    var metalKitView: MTKView
    var metalLayer: CAMetalLayer

    var commandQueue: MTLCommandQueue! = nil
    
    var vertexBuffer: MTLBuffer! = nil
    var uvBuffer: MTLBuffer! = nil
    
    var windowW: Float
    var windowH: Float
    
    var floatSize: Int
    
    let startTime: NSDate = NSDate()
    
    var vertexData:[Float] = [
        -1,-1,0,
        -1, 1,0,
         1,-1,0,
         
        -1, 1,0,
         1,-1,0,
         1, 1,0
    ]
    
    var uvData:[Float] = [
        0,0,
        0,1,
        1,0,
        
        0,1,
        1,0,
        1,1
    ]

    init?(mkv: MTKView) {
        self.metalKitView = mkv
        self.device = metalKitView.device!
        
        metalLayer = metalKitView.layer as! CAMetalLayer
        
        floatSize=MemoryLayout<Float>.size
        
        let vertSize = vertexData.count*floatSize
        vertexBuffer = device.makeBuffer(bytes: vertexData, length: vertSize, options: [])
        
        let uvSize = uvData.count*floatSize
        uvBuffer = device.makeBuffer(bytes: uvData, length: uvSize, options: [])
        
        let library = device.makeDefaultLibrary()
        let vertexProgram = library?.makeFunction(name: "vertexShader")
        let fragmentProgram = library?.makeFunction(name: "fragmentShader")
        
        let pipelineStateDescriptor = MTLRenderPipelineDescriptor()
        pipelineStateDescriptor.vertexFunction = vertexProgram
        pipelineStateDescriptor.fragmentFunction = fragmentProgram
        pipelineStateDescriptor.colorAttachments[0].pixelFormat = .bgra8Unorm
        pipelineStateDescriptor.sampleCount = metalKitView.sampleCount
        
        pipelineState = try! device.makeRenderPipelineState(descriptor: pipelineStateDescriptor)
        
        commandQueue = device.makeCommandQueue()
        
        windowW = Float(metalLayer.drawableSize.width)
        windowH = Float(metalLayer.drawableSize.height)
        
        super.init()

    }


    func draw(in view: MTKView) {
        var currentTime = Float(NSDate().timeIntervalSince(startTime as Date))
        
        let renderPassDescriptor = MTLRenderPassDescriptor()
        guard let drawable = metalLayer.nextDrawable() else { return }
        renderPassDescriptor.colorAttachments[0].texture = drawable.texture
        renderPassDescriptor.colorAttachments[0].loadAction = .clear
        renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColor(red: 1, green: 1, blue: 1, alpha: 1)
        
        let commandBuffer = commandQueue.makeCommandBuffer()
        
        let renderEncoder = commandBuffer?.makeRenderCommandEncoder(descriptor: renderPassDescriptor)
        renderEncoder?.setRenderPipelineState(pipelineState)
        renderEncoder?.setVertexBuffer(vertexBuffer , offset: 0, index: 0)
        renderEncoder?.setVertexBuffer(uvBuffer     , offset: 0, index: 1)
        renderEncoder?.setFragmentBytes(&windowW    , length: floatSize, index: 0)
        renderEncoder?.setFragmentBytes(&windowH    , length: floatSize, index: 1)
        renderEncoder?.setFragmentBytes(&currentTime, length: floatSize, index: 2)
        renderEncoder?.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 12)
        renderEncoder?.endEncoding()
        
        commandBuffer?.present(drawable)
        commandBuffer?.commit()
    }

    func mtkView(_ view: MTKView, drawableSizeWillChange size: CGSize) {
        windowW = Float(size.width)
        windowH = Float(size.height)
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
