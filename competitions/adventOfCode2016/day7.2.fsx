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

let findAnnotationPalindrome (annotationString : string) =
    let rec find maybePalindromeStartIndex searchEndIndex found =
        match maybePalindromeStartIndex with
        | index when index = searchEndIndex -> found
        | _ ->
            let currentChar              = annotationString.[maybePalindromeStartIndex]
            let nextChar                 = annotationString.[maybePalindromeStartIndex + 1]
            match currentChar with
            | char when char = nextChar -> find (maybePalindromeStartIndex + 1) searchEndIndex found
            | _ ->
                let computedPalindrome1      = [currentChar; nextChar; currentChar;] |> charListToString
                let computedPalindrome2      = [nextChar; currentChar; nextChar;] |> charListToString
                let areAllCharsDifferent1 = 
                   (computedPalindrome1.ToCharArray() |>
                    Array.groupBy(fun char -> char)   |>
                    Array.map(fst)                    |>
                    Array.length) = 2    
         
                let areAllCharsDifferent2 = 
                   (computedPalindrome2.ToCharArray() |>
                    Array.groupBy(fun char -> char)   |>
                    Array.map(fst)                    |>
                    Array.length) = 2   
 
                let maybePalindromeSubstring = annotationString.Substring (maybePalindromeStartIndex, 3)
                match maybePalindromeSubstring with
                | substring when substring = computedPalindrome1 && areAllCharsDifferent1 -> 
                    find (maybePalindromeStartIndex + 1) searchEndIndex (computedPalindrome1::found)
                | substring when substring = computedPalindrome2 && areAllCharsDifferent2 -> 
                    find (maybePalindromeStartIndex + 1) searchEndIndex (computedPalindrome2::found)
                | _ -> find (maybePalindromeStartIndex + 1) searchEndIndex found

    find 0 (annotationString.Length - 2) []
    
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

let doesAddressSupportSSL (address : Address) =
    let hasAnnotationPalindrome = address.AnnotationsBlocks.Any(fun block -> (findAnnotationPalindrome block).Length > 0)
    let hasHypernetPalindrome   = address.HypernetBlocks.Any(fun block -> (findAnnotationPalindrome block).Length > 0)
    match hasAnnotationPalindrome, hasHypernetPalindrome with
    | tuple when tuple = (true,  true) ->
        let annotations = address.AnnotationsBlocks |>
            List.map (fun block -> (findAnnotationPalindrome block)) |>
            List.filter(fun annotations -> annotations.Length > 0)   |>
            List.concat
 
        let hypernets = address.HypernetBlocks |>
            List.map (fun block -> (findAnnotationPalindrome block)) |>
            List.filter(fun annotations -> annotations.Length > 0)   |>
            List.concat

        let computeAnnotation (annotation : string) = [annotation.[1]; annotation.[0]; annotation.[1]] |> charListToString
        annotations.Any(fun annotation -> hypernets.Any(fun hypernet -> hypernet = (computeAnnotation annotation) ))    
    | _ -> false

let countAddressesSupportingSSL addresses = addresses |> List.filter doesAddressSupportSSL |> List.length
let solve (input : string) = input |> (parseAddresses >> countAddressesSupportingSSL) 