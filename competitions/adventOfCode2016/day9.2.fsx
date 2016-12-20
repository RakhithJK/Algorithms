let (|Marker|_|) (maybeMarker: string)=
    match maybeMarker.Split([|'x'|], 2) with
    | [| charsCount; repeatNumber |] -> Some (int charsCount, int repeatNumber)
    | _ -> None

let rec decompress (compressedString : string) =
    let rec decompressSubstring (input: string) (accumulatedLength : int) =
        match input.Split([|'('; ')'|], 3) with
        | [|simpleChars|] -> accumulatedLength + simpleChars.Length
        | [|simpleCharsBeforeMarker; Marker(charsCount, repeatNumber); charsAfterMarker|] ->
            let simpleCharsBeforeMarkerLength = simpleCharsBeforeMarker.Length
            let markerAffectedSubstring       = charsAfterMarker.Substring(0, charsCount)
            let substringAfterMarkerAffected  = charsAfterMarker.Substring(charsCount)
            let markerAffectedSubstringLength = decompressSubstring markerAffectedSubstring 0
            let currentLength                 = accumulatedLength + simpleCharsBeforeMarkerLength + repeatNumber * markerAffectedSubstringLength
            decompressSubstring substringAfterMarkerAffected currentLength
        | _ -> failwith "incorrect syntax"
        
    decompressSubstring compressedString 0