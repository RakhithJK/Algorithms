open System;
open System.Linq;

type Connection     = { RelatedMagicId : int; Weight : float }
type MagicVertex    = { MagicId : int; Value : int; Connections: Connection list }
type MagicDto       = { Id : int; Value : int; }
type ConnectionDto  = { LeftId : int; RightId : int }

let connections = [
    { LeftId = 1; RightId = 2 }
    { LeftId = 2; RightId = 4 }
    { LeftId = 1; RightId = 3 }
    { LeftId = 5; RightId = 2 }
]

let magics = [
    { Id = 1; Value = 2 }
    { Id = 2; Value = 1 }
    { Id = 3; Value = 1 }
    { Id = 4; Value = 1 }
]
    

let createVertex (magic: MagicDto) (connections: ConnectionDto list) : MagicVertex = 
    let allConnections = 
        connections 
            |> List.filter (fun connection -> connection.LeftId = magic.Id) 
            |> List.map    (fun connection -> { RelatedMagicId = connection.RightId; Weight = (float connection.LeftId + float connection.RightId) / 2.0 })
    
    { MagicId = magic.Id; Value = magic.Value; Connections = allConnections }

let graph = magics |> List.map (fun magic -> (createVertex magic connections))

let generatePermutations magics = 
    let connectMagics startMagicIndex = 
       magics |> List.mapi(fun connectedMagicIndex magic -> magics.[startMagicIndex], magics.[connectedMagicIndex])  

    magics 
        |> List.mapi (fun startMagicIndex startMagic -> connectMagics startMagicIndex)
  
let perms = generatePermutations graph