//
//  GameViewController.swift
//  HelloMetal3
//
//  Created by Jack Armstrong on 9/30/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

import Cocoa
import MetalKit

// Our macOS specific view controller
class GameViewController: NSViewController {

    var renderer: Renderer!
    var mtkView: MTKView!
    //TODO:
    //HSB or no HSB checkbox
    //Reset xMult button
    //Reset yMult button
    //Reset xOff button
    //Reset yOff button
    //Reset all multipliers button
    //Reset all offsets button
    
    @IBOutlet weak var sliderXMult: NSSlider!
    @IBOutlet weak var sliderYMult: NSSlider!
    @IBOutlet weak var sliderXOff: NSSlider!
    @IBOutlet weak var sliderYOff: NSSlider!
    
    @IBAction func sliderXMultChanged(_ sender: Any) {
        renderer.xMult = sliderXMult.floatValue
    }
    @IBAction func sliderYMultChanged(_ sender: Any) {
        renderer.yMult = sliderYMult.floatValue
    }
    @IBAction func sliderXOffChanged(_ sender: Any) {
        renderer.xOff = sliderXOff.floatValue
    }
    @IBAction func sliderYOffChanged(_ sender: Any) {
        renderer.yOff = sliderYOff.floatValue
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()

        sliderXMult.minValue = -5
        sliderXMult.maxValue = 5
        sliderXMult.floatValue = 0

        sliderYMult.minValue = -5
        sliderYMult.maxValue = 5
        sliderYMult.floatValue = 0

        sliderXOff.minValue = -5
        sliderXOff.maxValue = 5
        sliderXOff.floatValue = 0

        sliderYOff.minValue = -5
        sliderYOff.maxValue = 5
        sliderYOff.floatValue = 0

        guard let mtkView = self.view as? MTKView else {
            print("View attached to GameViewController is not an MTKView")
            return
        }

        // Select the device to render with.  We choose the default device
        guard let defaultDevice = MTLCreateSystemDefaultDevice() else {
            print("Metal is not supported on this device")
            return
        }

        mtkView.device = defaultDevice

        guard let newRenderer = Renderer(mkv: mtkView) else {
            print("Renderer cannot be initialized")
            return
        }

        renderer = newRenderer

        renderer.mtkView(mtkView, drawableSizeWillChange: mtkView.drawableSize)

        mtkView.delegate = renderer
    }
}
