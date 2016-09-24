module composition_parser
open FParsec

type measureFraction = Half | Quarter | Eight | Sixteen | Thirtysecond
type note            = A | ASharp | B | C | CSharp | D | DSharp | E | F | FSharp | G | GSharp
type octave          = One | Two | Three
type sound           = Rest | Tone of note : note * octave : octave

type length          = { fraction : measureFraction; isExtended : bool }
type token           = { length : length; sound : sound }

let parse_measureFraction = 
    (stringReturn "2"  Half)            <|> 
    (stringReturn "4"  Quarter)         <|>
    (stringReturn "8"  Eight)           <|>
    (stringReturn "16" Sixteen)         <|>
    (stringReturn "32" Thirtysecond)
let parse_extended_measureFraction = (stringReturn "." true) <|> (stringReturn "" false)
let parse_length = 
    pipe2 
        parse_measureFraction
        parse_extended_measureFraction
        (fun parsedFraction parsedIsExtended -> { fraction = parsedFraction; isExtended = parsedIsExtended })
         
let parse_nonSharpNote = 
    anyOf "be" |>> (function 
    | 'b' -> B
    | 'e' -> E
    | unknown -> failwith <| string unknown)
let parse_sharp = (stringReturn "#" true) <|> (stringReturn "" false)
let parse_sharpNote =
    pipe2
        parse_sharp
        (anyOf "acdefg")
        (fun isNoteSharp note ->
            match (isNoteSharp, note) with 
            | (false, 'a') -> A      
            | (true,  'a') -> ASharp 
            | (false, 'c') -> C      
            | (true,  'c') -> CSharp 
            | (false, 'd') -> D      
            | (true,  'd') -> DSharp 
            | (false, 'f') -> F    
            | (true,  'f') -> FSharp 
            | (false, 'g') -> G   
            | (true,  'g') -> GSharp
            | (_, unknown) -> failwith <| string unknown 
        )

let parse_note = parse_nonSharpNote <|> parse_sharpNote
let parse_octave = anyOf "123" |>> (function
    | '1' -> One
    | '2' -> Two
    | '3' -> Three
    | unknown -> failwith <| string unknown)

let parse_tone  = pipe2 parse_note parse_octave (fun parsedNote parsedOctave -> Tone(parsedNote, parsedOctave))
let parse_rest  = stringReturn "-" Rest
let parse_token = pipe2 parse_length (parse_rest <|> parse_tone) (fun length tone -> { length = length; sound = tone })

let parse_allTokens         = sepBy parse_token (pstring " ")
let parse_composition input = run parse_allTokens input