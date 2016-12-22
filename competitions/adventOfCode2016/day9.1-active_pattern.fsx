type Marker = { CharsCount : int; RepeatTimes : int }
let (|Marker|_|) (maybeMarker: string)=
    match maybeMarker.Split([|'x'|], 2) with
    | [| charsCount; repeatNumber |] -> Some ({ CharsCount = int charsCount; RepeatTimes = int repeatNumber})
    | _ -> None

let calculateDecompressedLength (input : string) =
    let rec calculateForSubstring (substring: string) (accumulatedLength : int) = 
        match substring.Split([|'('; ')'|], 3) with
        | [|simpleChars|] -> accumulatedLength + simpleChars.Length
        | [|charsBeforeMarker; Marker(marker); charsAfterMarker|] -> 
            let charsBeforeMarkerLength = charsBeforeMarker.Length
            let currentLength           = accumulatedLength + charsBeforeMarkerLength + marker.CharsCount * marker.RepeatTimes
            let substringAfterMarker    = charsAfterMarker.Substring(marker.CharsCount)
            
            calculateForSubstring substringAfterMarker currentLength
        | [|Marker(_)|] -> accumulatedLength
        | array -> 
            accumulatedLength
    calculateForSubstring input 0