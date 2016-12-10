open System
open System.Linq

type Room = { Name : string list ; Sector : int; Checksum : string }

let parseRoom (roomString : string) = 
    let allBlocks = roomString.Split '-'
    let lastBlock =
         allBlocks.[allBlocks.Length - 1].Split('[', ']') |> 
         Array.filter (fun blockPart -> blockPart.Length > 0)

    let nameBlocks = allBlocks                                               |>
        Array.mapi (fun index block -> index, block)                         |>
        Array.filter (fun blockPair -> fst blockPair < allBlocks.Length - 1) |>
        Array.map(fun blockPair -> snd blockPair)                            |>
        List.ofArray

    { Name = nameBlocks; Sector = Int32.Parse lastBlock.[0]; Checksum = lastBlock.[1] }

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

let sumSectorsFromValidRooms (rooms : Room list) =
    rooms |>
    List.filter isRoomValid |>
    List.sumBy (fun room -> room.Sector)