let parseRow(rowString: string) =
    rowString.ToCharArray() |>
    Array.mapi(fun index character -> index, character)
let parse(input: string) =
    input.Split('\r', '\n')                             |> 
    Array.filter(fun substring -> substring.Length > 0) |>
    Array.map parseRow
let collectMostCommonCharactersIntoString (input : (int*char)[][]) =
    let chooseMostCommonCharacter (charsSeq: (int*char)[]) =
         charsSeq |> 
             Array.groupBy(snd) |> 
             Array.maxBy(fun grouping -> (snd grouping).Length) |>
             snd
    input                                                    |> 
    Array.concat                                             |> 
    Array.groupBy (fst)                                      |>
    Array.map (snd)                                          |>
    Array.map chooseMostCommonCharacter                      |>
    Array.concat                                             |>
    Array.groupBy (fst)                                      |>
    Array.map(fun grouping -> (snd grouping) |> Array.head)  |>
    Array.map(snd)                                           |>
    Array.fold(fun accumulator current -> accumulator + string(current)) ""
let solve (input : string) = (parse >> collectMostCommonCharactersIntoString) input