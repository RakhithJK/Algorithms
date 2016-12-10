open System

let parseLength lengthString =  Int32.Parse lengthString

let parseLine (line : string) =
    line.Split(' ') |> Array.filter(fun s -> s.Length > 0) |>
    Array.mapi(fun column size -> column, (parseLength size))

let parseSides (inputString : string) = 
    inputString.Split('\r', '\n')  |> 
    Array.map parseLine |>
    Array.concat |>
    Array.groupBy (fst) |>
    Array.map(fun grouping -> (snd grouping) |> Array.map snd |> Array.chunkBySize 3) |>
    Array.concat
   
let canBeTriangle (sides : int [])  =
    let longestSide = Array.max sides
    let longestSideIndex = sides |> Array.findIndex (fun side -> side = longestSide)
    let otherSides = 
        sides                                              |> 
        Array.mapi (
            fun index side ->
                match index <> longestSideIndex with
                | true -> Some side
                | false -> None
        )                                                   |>
        Array.filter (fun maybeOther ->  maybeOther.IsSome) |>
        Array.map (fun option -> option.Value)

    Array.sum otherSides > longestSide

let countValidTriangles trianglesList = 
    trianglesList              |> 
    Array.filter canBeTriangle |>
    Array.length