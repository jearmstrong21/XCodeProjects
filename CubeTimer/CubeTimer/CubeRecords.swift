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
    cr.cubeType = getForKey("\(CubeStrings.prefixCubeType)\(cr.index!)") as! CubeType
    cr.time = getForKey("\(CubeStrings.prefixTime)\(cr.index!)") as! Float
    cr.dateStarted = getForKey("\(CubeStrings.prefixDateStarted)\(cr.index!)") as! NSDate
    cr.dateEnded = getForKey("\(CubeStrings.prefixDateEnded)\(cr.index!)") as! NSDate
    return cr
}

func addCubeRecord(type: CubeType, time: Float, dateStarted: NSDate, dateEnded: NSDate) -> CubeRecord {
    let cr: CubeRecord = CubeRecord()
    cr.index = getNumRecords()
    setDefaults(CubeStrings.numRecords, getNumRecords() + 1)
    cr.cubeType = type
    cr.time = time
    cr.dateStarted = dateStarted
    cr.dateEnded = dateEnded
    setDefaults("\(CubeStrings.prefixCubeType)\(cr.index!)", type)
    setDefaults("\(CubeStrings.prefixTime)\(cr.index!)", time)
    setDefaults("\(CubeStrings.prefixDateStarted)\(cr.index!)", dateStarted)
    setDefaults("\(CubeStrings.prefixDateEnded)\(cr.index!)", dateEnded)
    return cr
}

func printCubeRecord(_ cr: CubeRecord) {
    print("\(cr.index!) ... \(cr.cubeType!) ... \(cr.time!)")
}

func clearRecords() {
//    let num: Int = getNumRecords()
//    UserDefaults.standard.removeObject(forKey: "\(CubeStrings.numRecords)")
//    for index in 0..<num {
//        UserDefaults.standard.removeObject(forKey: "\(CubeStrings.prefixCubeType)\(index)")
//        UserDefaults.standard.removeObject(forKey: "\(CubeStrings.prefixTime)\(index)")
//        UserDefaults.standard.removeObject(forKey: "\(CubeStrings.prefixDateStarted)\(index)")
//        UserDefaults.standard.removeObject(forKey: "\(CubeStrings.prefixDateEnded)\(index)")
//    }
    for (key, value) in UserDefaults.standard.dictionaryRepresentation() {
        if key.hasPrefix("CUBETIMER_") {
            UserDefaults.standard.removeObject(forKey: key)
        }
    }
}

func printRecords(){
    /*
     Num records: 0
     CUBETIMER_NumRecords = 0
     CUBETIMER_dateStarted(Function) = 2018-10-05 03:08:07 +0000
     CUBETIMER_timeOptional(1) = 0.5750401
     CUBETIMER_dateEndedOptional(1) = 2018-10-05 03:15:13 +0000
     CUBETIMER_cubeType(Function) = 3x3
     CUBETIMER_dateStartedOptional(1) = 2018-10-05 03:15:11 +0000
     CUBETIMER_cubeTypeOptional(1) = 3x3
     CUBETIMER_time(Function) = 0.760874
     CUBETIMER_dateEnded(Function) = 2018-10-05 03:08:09 +0000
     Time added: 0.720392
     Num records: 1
     CUBETIMER_NumRecords = 1
     CUBETIMER_dateStarted(Function) = 2018-10-05 03:08:07 +0000
     CUBETIMER_timeOptional(1) = 0.720392
     CUBETIMER_dateEndedOptional(1) = 2018-10-05 03:20:57 +0000
     CUBETIMER_cubeType(Function) = 3x3
     CUBETIMER_cubeTypeOptional(1) = 3x3
     CUBETIMER_dateStartedOptional(1) = 2018-10-05 03:20:55 +0000
     CUBETIMER_time(Function) = 0.760874
     CUBETIMER_dateEnded(Function) = 2018-10-05 03:08:09 +0000
     */
    //Unwrap the \(index) into \(index?) or \(index!)
    let num: Int = getNumRecords()
    for index in 0..<num {
        printCubeRecord(getCubeRecord(index))
    }
//    let num: Int = getNumRecords()
//    print("Num records: \(num)")
//
//    for (key, value) in UserDefaults.standard.dictionaryRepresentation() {
//        if key.hasPrefix("CUBETIMER_") {
//            print("\(key) = \(value)")
//        }
//    }
}
