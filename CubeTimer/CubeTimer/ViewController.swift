//
//  ViewController.swift
//  CubeTimer
//
//  Created by Jack Armstrong on 10/4/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

import Cocoa

class ViewController: NSViewController {
    
    @IBOutlet weak var cbxCubeType: NSComboBox!
    @IBOutlet weak var lblCubeType: NSTextField!
    @IBOutlet weak var lblCurrentTime: NSTextField!
    @IBOutlet weak var tblRecords: NSTableView!
    
    var timingNow: Bool = false
    
    @IBAction func btnStartTiming(_ sender: Any) {
        startTime = nil
        timer = Timer.scheduledTimer(timeInterval: 0.1, target: self, selector: (#selector(ViewController.updateTimer)),userInfo: nil,repeats: true)
        
        lblCurrentTime.isEnabled = true
    }
    
    @IBAction func btnEndTiming(_ sender: Any) {
        timer.invalidate()
        lblCurrentTime.stringValue = "Not currently timing"
        lblCurrentTime.isEnabled = false
        let time = Float(NSDate().timeIntervalSince(startTime as Date))
        let cube = cbxCubeType.stringValue
        if confirmDialog(question: "Add time?", text: "Selected cube: \(cube)\nTime: \(time)") {
            let cr: CubeRecord = addCubeRecord(type: cube, time: time, dateStarted: startTime, dateEnded: NSDate())
            tblRecords.reloadData()
            print("Time added: \(time)")
            printRecords()
        }
    }
    
    //https://stackoverflow.com/a/29433631/9609025
    func confirmDialog(question: String, text: String) -> Bool {
        let alert : NSAlert = NSAlert()
        alert.messageText = question
        alert.informativeText = text
        alert.alertStyle = .warning
        alert.addButton(withTitle: "Yes")
        alert.addButton(withTitle: "No")
        return alert.runModal() == .alertFirstButtonReturn
    }
    
    var startTime: NSDate! = nil
    var timer: Timer! = nil

    override func viewDidLoad() {
        super.viewDidLoad()
//        clearRecords()
        printRecords()
        //Add pause button
        
//        tblRecords.delegate = self
        tblRecords.dataSource = self
        tblRecords.reloadData()

        cbxCubeType.removeAllItems()
        cbxCubeType.addItem(withObjectValue: Cube2x2)
        cbxCubeType.addItem(withObjectValue: Cube3x3)
        cbxCubeType.addItem(withObjectValue: Cube4x4)
        cbxCubeType.addItem(withObjectValue: Cube5x5)
        cbxCubeType.selectItem(withObjectValue: Cube3x3)
        
        // Do any additional setup after loading the view.
    }
    
    @objc func updateTimer(){
        if startTime == nil {
            startTime = NSDate()
        }
        let currentTime = Float(NSDate().timeIntervalSince(startTime as Date))
        
        lblCurrentTime.stringValue = "Current time: \(round(currentTime*1000)/1000)"
    }

    override var representedObject: Any? {
        didSet {
        // Update the view, if already loaded.
        }
    }


}

extension ViewController : NSTableViewDataSource {
    
    func numberOfRows(in tableView: NSTableView) -> Int {
        return getNumRecords()
    }
    
    func tableView(_ tableView: NSTableView, objectValueFor tableColumn: NSTableColumn?, row: Int) -> Any? {
        let cr = getCubeRecord(row)
        let df = DateFormatter()
        df.dateStyle = .short
        df.timeStyle = .none
        let nf = NumberFormatter()
        nf.allowsFloats = true
        nf.numberStyle = .decimal
        if tableColumn == tblRecords.tableColumns[0] {
            return "\(cr.index!+1)"
        }
        if tableColumn == tblRecords.tableColumns[1] {
            return "\(cr.cubeType!)"
        }
        if tableColumn == tblRecords.tableColumns[2] {
            return nf.string(from: cr.time as NSNumber)
        }
        if tableColumn == tblRecords.tableColumns[3] {
            return df.string(from: cr.dateStarted as Date)
        }
        if tableColumn == tblRecords.tableColumns[4] {
            return df.string(from: cr.dateEnded as Date)
        }
        return "hi"
    }
    
}
