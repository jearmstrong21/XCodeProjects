//
//  CubeRecords.swift
//  CubeTimer
//
//  Created by Jack Armstrong on 10/4/18.
//  Copyright © 2018 Jack Armstrong. All rights reserved.
//

import Foundation

class CubeRecord {
    
    var cubeType: CubeType! = nil
    var time: Float! = nil
    var dateStarted: NSDate! = nil
    var dateEnded: NSDate! = nil
    var index: Int! = nil
    
    init(){
        
    }
}

struct CubeStrings {
    static let numRecords = "CUBETIMER_NumRecords"
    static let prefixCubeType = "CUBETIMER_cubeType"
    static let prefixTime = "CUBETIMER_time"
    static let prefixDateStarted = "CUBETIMER_dateStarted"
    static let prefixDateEnded = "CUBETIMER_dateEnded"
}

func hasKey(_ key: String) -> Bool {
    return UserDefaults.standard.object(forKey: key) != nil
}

func getForKey(_ key: String) -> Any? {
    return UserDefaults.standard.object(forKey: key)
}

func setDefaults(_ key: String, _ val: Any) {
    UserDefaults.standard.set(val, forKey: key)
}

func getNumRecords() -> Int {
    if !hasKey(CubeStrings.numRecords) {
        setDefaults(CubeStrings.numRecords, 0)
        return 0
    }
    return getForKey(CubeStrings.numRecords) as! Int
}

func getCubeRecord(_ index: Int) -> CubeRecord {
    let cr: CubeRecord = CubeRecord()
    cr.index = index
    cr.cubeType = getForKey("\(CubeStrings.prefixCubeType)\(cr.index)") as! CubeType
    cr.time = getForKey("\(CubeStrings.prefixTime)\(cr.index)") as! Float
    cr.dateStarted = getForKey("\(CubeStrings.prefixDateStarted)\(cr.index)") as! NSDate
    cr.dateEnded = getForKey("\(CubeStrings.prefixDateEnded)\(cr.index)") as! NSDate
    return cr
}

func addCubeRecord(type: CubeType, time: Float, dateStarted: NSDate, dateEnded: NSDate) -> CubeRecord {
    let cr: CubeRecord = CubeRecord()
    cr.index = getNumRecords() + 1
    setDefaults(CubeStrings.numRecords, getNumRecords() + 1)
    cr.cubeType = type
    cr.time = time
    cr.dateStarted = dateStarted
    cr.dateEnded = dateEnded
    setDefaults("\(CubeStrings.prefixCubeType)\(cr.index)", type)
    setDefaults("\(CubeStrings.prefixTime)\(cr.index)", time)
    setDefaults("\(CubeStrings.prefixDateStarted)\(cr.index)", dateStarted)
    setDefaults("\(CubeStrings.prefixDateEnded)\(cr.index)", dateEnded)
    return cr
}

func printCubeRecord(_ cr: CubeRecord) {
    print("\(cr.index) ... \(cr.cubeType) ... \(cr.time)")
}

func clearRecords() {
    let num: Int = getNumRecords()
    UserDefaults.standard.removeObject(forKey: "\(CubeStrings.numRecords)")
    for index in 0..<num {
        UserDefaults.standard.removeObject(forKey: "\(CubeStrings.prefixCubeType)\(index)")
        UserDefaults.standard.removeObject(forKey: "\(CubeStrings.prefixTime)\(index)")
        UserDefaults.standard.removeObject(forKey: "\(CubeStrings.prefixDateStarted)\(index)")
        UserDefaults.standard.removeObject(forKey: "\(CubeStrings.prefixDateEnded)\(index)")
    }
}

func printRecords(){
    let num: Int = getNumRecords()
    for index in 0..<num {
        printCubeRecord(getCubeRecord(index))
    }
//    let num: Int = getNumRecords()
    print("Num records: \(num)")
//    for (key, value) in UserDefaults.standard.dictionaryRepresentation() {
//        print("\(key) = \(value)")
//    }
}
