open System.Text.RegularExpressions
open System.Linq

type Address = { Annotation: string; Hypernet : string; HypernetBlocks: string list; AnnotationsBlocks : string list }
let charArrayToString (chars: char []) = new string(chars)
let charListToString(chars: char list) = Array.ofList chars |> charArrayToString
let insideBraces = "\[(.*?)\]" 
let (|Regex|_|) pattern input =
        let result = Regex.Matches(input, pattern)
        let removeDelimiter (group: string) = group.Substring(1, group.Length - 2)
        match result.Count > 0 with 
        | true  -> Some([for group in result -> group.Value ] |> List.map removeDelimiter)
        | false -> None
let hasAnnotationPalindrome (annotationString : string) =
    let rec hasAnnotationPalindrome maybePalindromeStartIndex searchEndIndex =
        match maybePalindromeStartIndex with
        | index when index = searchEndIndex -> None
        | _ ->
            let currentChar              = annotationString.[maybePalindromeStartIndex]
            let nextChar                 = annotationString.[maybePalindromeStartIndex + 1]
            match currentChar with
            | char when char = nextChar -> hasAnnotationPalindrome (maybePalindromeStartIndex + 1) searchEndIndex
            | _ ->
                let computedPalindrome       = [currentChar; nextChar; nextChar; currentChar] |> charListToString
                let maybePalindromeSubstring = annotationString.Substring (maybePalindromeStartIndex, 4)
                match maybePalindromeSubstring with
                | substring when substring = computedPalindrome -> Some computedPalindrome
                | _ -> hasAnnotationPalindrome (maybePalindromeStartIndex + 1) searchEndIndex

    hasAnnotationPalindrome 0 (annotationString.Length - 3)
let parseAddress (address: string) =
    let hypernetBlocks = 
        match address with 
        | Regex insideBraces result -> result
        | _ -> failwith "incorrect address syntax"
    
    let notInControlBlock (annotationBlock : string) = hypernetBlocks |> (List.filter(fun hypernetBlock -> hypernetBlock = annotationBlock) >> List.isEmpty)
    let annotationBlocks =
        address.Split('[', ']')        |>
        Array.filter notInControlBlock |> 
        List.ofArray

    let hypernetString   = hypernetBlocks   |> List.fold (fun hypernet block -> hypernet + block) ""
    let annotationString = annotationBlocks |> List.fold (fun annotation block -> annotation + block) ""
    { Annotation = annotationString; AnnotationsBlocks = annotationBlocks; Hypernet = hypernetString; HypernetBlocks = hypernetBlocks }
let parseAddresses (input : string) =
    input.Split('\r', '\n')                          |>
    Array.filter (fun address -> address.Length > 0) |>
    Array.map parseAddress                           |>
    List.ofArray
let doesAddressSupportTls (address : Address) =
    address.AnnotationsBlocks.Any(fun ann -> (hasAnnotationPalindrome ann).IsSome) && 
    address.HypernetBlocks.All(fun ann -> (hasAnnotationPalindrome ann).IsNone)
let countAddressesSupportingTls addresses = addresses |> List.filter doesAddressSupportTls |> List.length
let solve (input : string) = input |> (parseAddresses >> countAddressesSupportingTls) 