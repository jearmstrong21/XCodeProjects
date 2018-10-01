
import Metal
import MetalKit
import simd
import Foundation

class Renderer: NSObject, MTKViewDelegate {
    
    public let device: MTLDevice
    
    var pipelineState: MTLRenderPipelineState! = nil
    
    var metalKitView: MTKView
    var metalLayer: CAMetalLayer! = nil
    var commandQueue: MTLCommandQueue! = nil
    
    var vertexBuffer: MTLBuffer! = nil
    var colorBuffer: MTLBuffer! = nil
    var uvBuffer: MTLBuffer! = nil
    
    var startTime: NSDate! = nil
    
    var xMult: Float = 0
    var yMult: Float = 0
    var xOff: Float = 0
    var yOff: Float = 0
    
    //    var depthStencilState: MTLDepthStencilState! = nil
    
    //--
    //-+
    //++
    
    //--
    //++
    //+-
    var vertexData:[Float] = [
        0,-1,0,
        0,1,0,
        1,1,0,
        
        0,-1,0,
        1,-1,0,
        1,1,0,
        
        -1,-1,0,
        -1, 1,0,
         0, 1,0,
        
        -1,-1,0,
         0,-1,0,
         0, 1,0
        
    ]
    
    var colorData:[Float] = [
        1,1,1,
        1,1,1,
        1,1,1,
        
        1,1,1,
        1,1,1,
        1,1,1,
        
        0.8,0.8,0.8,
        0.8,0.8,0.8,
        0.8,0.8,0.8,
        0.8,0.8,0.8,
        0.8,0.8,0.8,
        0.8,0.8,0.8,
    ]
    
    var uvData:[Float] = [
        0,0,
        0,1,
        1,1,
        
        0,0,
        1,0,
        1,1,
        
        -500,-500,
        -500,-500,
        -500,-500,
        
        -500,-500,
        -500,-500,
        -500,-500,
    ]
    
    var texture: MTLTexture
    var samplerState: MTLSamplerState?
    
    init?(mkv: MTKView) {
        startTime = NSDate()
        
        metalKitView = mkv
        metalLayer = metalKitView.layer as! CAMetalLayer
        self.device = metalKitView.device!
        
        
        let vertexSize = vertexData.count * MemoryLayout.size(ofValue: vertexData[0])
        vertexBuffer = device.makeBuffer(bytes: vertexData, length: vertexSize, options: [])
        
        let colorSize = colorData.count * MemoryLayout.size(ofValue: colorData[0])
        colorBuffer = device.makeBuffer(bytes: colorData, length: colorSize, options: [])
        
        let uvSize = uvData.count * MemoryLayout.size(ofValue: uvData[0])
        uvBuffer = device.makeBuffer(bytes: uvData, length: uvSize, options: [])
        
        let defaultLibrary = device.makeDefaultLibrary()
        let vertexProgram = defaultLibrary?.makeFunction(name: "basicVertex")
        let fragmentProgram = defaultLibrary?.makeFunction(name: "basicFragment")
        
        
        //https://www.raywenderlich.com/719-metal-tutorial-with-swift-3-part-3-adding-texture
        let samplerDescriptor = MTLSamplerDescriptor()
        samplerDescriptor.minFilter             = .nearest
        samplerDescriptor.magFilter             = .nearest
        samplerDescriptor.mipFilter             = .nearest
        samplerDescriptor.maxAnisotropy         = 1
        samplerDescriptor.sAddressMode          = .clampToEdge
        samplerDescriptor.tAddressMode          = .clampToEdge
        samplerDescriptor.rAddressMode          = .clampToEdge
        samplerDescriptor.normalizedCoordinates = true
        samplerDescriptor.lodMinClamp           = 0
        samplerDescriptor.lodMaxClamp           = .greatestFiniteMagnitude
        samplerState = device.makeSamplerState(descriptor: samplerDescriptor)
        
        //        let depthStateDescriptor = MTLDepthStencilDescriptor()
        //        depthStateDescriptor.isDepthWriteEnabled = true
        //        depthStateDescriptor.depthCompareFunction = .less
        //        depthStencilState = device.makeDepthStencilState(descriptor: depthStateDescriptor)
        
        let pipelineStateDescriptor = MTLRenderPipelineDescriptor()
        pipelineStateDescriptor.vertexFunction = vertexProgram
        pipelineStateDescriptor.fragmentFunction = fragmentProgram
        pipelineStateDescriptor.colorAttachments[0].pixelFormat = .bgra8Unorm
        pipelineStateDescriptor.sampleCount = metalKitView.sampleCount
        pipelineStateDescriptor.depthAttachmentPixelFormat = metalKitView.depthStencilPixelFormat
        pipelineStateDescriptor.stencilAttachmentPixelFormat = metalKitView.depthStencilPixelFormat
        
        do {
            try pipelineState = device.makeRenderPipelineState(descriptor: pipelineStateDescriptor)
        } catch let error {
            print("Failed to create pipeline state, error \(error)")
        }
        
        commandQueue = device.makeCommandQueue()
        
        let textureLoader = MTKTextureLoader(device: device)
        
        texture = try! textureLoader.newTexture(name: "ColorMap", scaleFactor: 1, bundle: Bundle.main, options: [:])
        
        super.init()
        
    }
    
    func draw(in view: MTKView) {
        let renderPassDescriptor = MTLRenderPassDescriptor()
        guard let drawable = metalLayer.nextDrawable() else { return }
        renderPassDescriptor.colorAttachments[0].texture = drawable.texture
        renderPassDescriptor.colorAttachments[0].loadAction = .clear
        renderPassDescriptor.colorAttachments[0].clearColor = MTLClearColor(red:0.2,green:0.2,blue:0.2,alpha:1.0)
        
        let commandBuffer = commandQueue.makeCommandBuffer()
        
        let renderEncoder = commandBuffer?.makeRenderCommandEncoder(descriptor: renderPassDescriptor)
        renderEncoder?.setRenderPipelineState(pipelineState)
        renderEncoder?.setVertexBuffer(vertexBuffer,  offset: 0, index: 0)
        renderEncoder?.setVertexBuffer(colorBuffer,   offset: 0, index: 1)
        renderEncoder?.setVertexBuffer(uvBuffer,      offset: 0, index: 2)
        renderEncoder?.setFragmentTexture(texture, index: 0)
        renderEncoder?.setFragmentSamplerState(samplerState, index: 0)
        renderEncoder?.setFragmentBytes(&xMult, length: MemoryLayout<Float>.size, index: 0)
        renderEncoder?.setFragmentBytes(&yMult, length: MemoryLayout<Float>.size, index: 1)
        renderEncoder?.setFragmentBytes(&xOff, length: MemoryLayout<Float>.size, index: 2)
        renderEncoder?.setFragmentBytes(&yOff, length: MemoryLayout<Float>.size, index: 3)
        renderEncoder?.drawPrimitives(type: .triangle, vertexStart: 0, vertexCount: 36)
        renderEncoder?.endEncoding()
        
//        print("\(xMult) \(yMult) \(xOff) \(yOff)")
        
        commandBuffer?.present(drawable)
        commandBuffer?.commit()
        
    }
    
    func mtkView(_ view: MTKView, drawableSizeWillChange size: CGSize) {
        /// Respond to drawable size or orientation changes here
        
    }
}
