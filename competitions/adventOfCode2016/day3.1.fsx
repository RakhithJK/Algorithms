open System

let parseLength lengthString = 
    Int32.Parse lengthString
let parseTriangle (triangleSidesString: string) = 
    triangleSidesString.Split(' ')               |> 
    Array.filter (fun sides -> sides.Length > 0) |> 
    Array.map parseLength                        |>
    List.ofArray

let parseTriangles (inputString : string) = 
    inputString.Split('\n', '\r') |> 
    Array.map parseTriangle       |> 
    List.ofArray

let isValidTriangle (sides : int list) =
    let longestSide = List.max sides
    let longestSideIndex = sides |> List.findIndex (fun side -> side = longestSide)
    let otherSides = 
        sides                                              |> 
        List.mapi (
            fun index side ->
                match index <> longestSideIndex with
                | true -> Some side
                | false -> None
        )                                                  |>
        List.filter (fun maybeOther ->  maybeOther.IsSome) |>
        List.map (fun option -> option.Value)

    List.sum otherSides > longestSide

let countValidTriangles trianglesList = 
    trianglesList 
        |> List.filter (fun (sides : int list) -> sides.Length = 3) 
        |> List.filter isValidTriangle 
        |> List.length