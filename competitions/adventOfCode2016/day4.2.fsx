open System
open System.Linq

type Room = { Name : string list ; Sector : int; Checksum : string }

let alphabet = "abcdefghijklmnopqrstuvwxyz".ToCharArray()

let decryptChar charToDecrypt sector = 
    let alphabetIndex = (alphabet |> Array.findIndex (fun character -> character = charToDecrypt))
    let rec decrypt currentCharIndex currentCount =
        let nextCharIndex = 
            match currentCharIndex with 
            | index when index = alphabet.Length - 1 -> 0
            | _ -> currentCharIndex + 1
        match currentCount with
        | count when count = sector -> alphabet.[currentCharIndex]
        | _ -> decrypt nextCharIndex (currentCount + 1)

    decrypt alphabetIndex 0

let decryptBlock (block : string) (sector : int) = 
    block.ToCharArray()                                    |>
    Array.map  (fun character -> decryptChar character sector) |>
    Array.fold (fun block currentChar -> block + string currentChar) ""
        
let parseRoom (roomString : string) = 
    let allBlocks = roomString.Split '-'
    let lastBlock =
        allBlocks.[allBlocks.Length - 1].Split('[', ']') |> 
        Array.filter (fun blockPart -> blockPart.Length > 0)

    let nameBlocks = allBlocks                                                  |>
        Array.mapi (fun index block -> index, block)                            |>
        Array.filter (fun blockPair -> fst blockPair < allBlocks.Length - 1)    |>
        Array.map(fun blockPair -> snd blockPair)                               |>
        Array.map (fun block -> decryptBlock block (Int32.Parse lastBlock.[0])) |>
        List.ofArray

    { Name = nameBlocks; Sector = Int32.Parse lastBlock.[0]; Checksum = decryptBlock lastBlock.[1] (Int32.Parse lastBlock.[0]) }

let parseRooms (roomsString : string) =
    roomsString.Split('\n', '\r') |>
    Array.map parseRoom |>
    List.ofArray

let isRoomValid room = 
    let nameChars  = room.Name  |> List.map (fun subName -> subName.ToCharArray()) 
    let nameString = nameChars |> List.fold (fun accumulator current -> accumulator + (current |> Array.fold (fun previous current -> previous + string(current)) "")) ""
    let firstChecksum = nameString.ToCharArray () |>
        Array.take room.Checksum.Length |>
        Array.fold (fun previousChars currentChar -> previousChars + (string currentChar)) ""

    let secondChecksum = 
        nameString.ToCharArray()
                  .OrderBy(fun char -> char)
                  .GroupBy(fun char -> char)
                  .OrderByDescending(fun grouping -> grouping.Count())
                  .ThenBy(fun grouping -> grouping.Key)
                  .Take(room.Checksum.Length)
                  .Select(fun grouping -> grouping.Key)
                  .ToArray() |>
                  Array.fold (fun previousChars currentChar -> previousChars + (string currentChar)) ""

    firstChecksum = room.Checksum || secondChecksum = room.Checksum

let isRoomNorthPole (room : Room) = 
    let nameChars  = room.Name  |> List.map (fun subName -> subName.ToCharArray()) 
    let nameString = nameChars  |> List.fold (fun accumulator current -> accumulator + (current |> Array.fold (fun previous current -> previous + string(current)) "")) ""
    nameString.Contains("object") //northpoleobjects room

let findNorthPoleRoomSector (rooms : Room list) =           
    rooms                                                             |> 
    List.filter(fun room -> isRoomNorthPole room) |> 
    List.map(fun room -> room.Sector)

let solve (input : string) = (parseRooms input) |> findNorthPoleRoomSector