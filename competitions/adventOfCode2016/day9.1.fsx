type accumulator = { CurrentLength : int; IgnoredCharsIndexes: int list }
type marker = { CharsCount : int; RepeatCount : int }

let parseMarker (markerString : string) =
    let markerStringWithoutBraces = markerString.Substring(1, markerString.Length - 2)
    let markerParts = markerStringWithoutBraces.Split ('x')
    printfn "%A" markerString
    { CharsCount = int markerParts.[0]; RepeatCount = int markerParts.[1] }


let rec calculateDecompressedLength (input: string) =
    let chars = input.ToCharArray()
    
    let calculateCharLength accumulator charIndexPair = 
     
        let notIgnoredChar charIndex  = not ((accumulator.IgnoredCharsIndexes |> List.filter (fun index -> index = charIndex) |> List.length) = 1)

        match (snd charIndexPair) with
        | char when char = '(' && notIgnoredChar (fst charIndexPair) ->
            let untilEndSubstring = (input.Substring((fst charIndexPair), input.Length - 1 - (fst charIndexPair)))
            let closingBraceIndex = untilEndSubstring.IndexOf(')') + (fst charIndexPair)                                          
            let markerSubstring = 
                input.ToCharArray() |> 
                Array.mapi   (fun index character -> index, character)                                          |>
                Array.filter (fun pair -> (fst pair) >= (fst charIndexPair) && (fst pair) <= closingBraceIndex) |>
                Array.map snd       |>
                (fun characters -> new string(characters))

            let marker = parseMarker markerSubstring         
            { CurrentLength = accumulator.CurrentLength + (marker.CharsCount * marker.RepeatCount); IgnoredCharsIndexes = [((fst charIndexPair)) .. (closingBraceIndex + marker.CharsCount)]}
        | _ -> 
            let isIgnoredChar = not (notIgnoredChar (fst charIndexPair))
            match isIgnoredChar with 
            | true -> { CurrentLength = accumulator.CurrentLength; IgnoredCharsIndexes = accumulator.IgnoredCharsIndexes }
            | false -> { CurrentLength = accumulator.CurrentLength + 1; IgnoredCharsIndexes = accumulator.IgnoredCharsIndexes }

    chars |> 
    Array.mapi (fun index character -> index, character) |>
    Array.fold calculateCharLength { CurrentLength = 0; IgnoredCharsIndexes= [] } |>
    fun accumulator -> accumulator.CurrentLength