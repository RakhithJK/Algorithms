open System
open System.Collections.Generic
 
type Magic      = { Id: int; Value : int; } 
type Connection = { LeftMagicIndex : int; RightMagicIndex : int }


let loadConnection = 
    let connectionAsString = Console.ReadLine()
    let connectionParts    = connectionAsString.Split ' '
    { LeftMagicIndex = Int32.Parse connectionParts.[0]; RightMagicIndex = Int32.Parse connectionParts.[1] }

let loadVertexValue id = 
    { Id = id; Value = Int32.Parse (Console.ReadLine()) }
 
let loadData numberOfVertices = 
    let connections = [0..numberOfVertices] |> List.map (fun index -> loadConnection) 
    let magics      = [0..numberOfVertices] |> List.map(loadVertexValue)
    connections, magics   

[<EntryPoint>]
let main argv = 
//    let x                = Console.ReadLine()
//    let numberOfVertices = Int32.Parse(x)
//    let connections      = loadData numberOfVertices
    ignore
    0 