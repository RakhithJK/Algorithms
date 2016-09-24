open System
open FParsec
open composition_parser

[<EntryPoint>]
let main argv = 
    let parseCompositionFromStream =
     parse_composition  >>
     (fun result -> 
        match result with
        | Success(result, _, _) -> sprintf "%A" result |> ignore
        | Failure(error, _, _)  -> sprintf "Error"     |> ignore
      )
    let composition = "32f2 32#d2 32f2 8#d2 32#d2 32#d2 32f2 32g2 32f2 16.#d2 32- 16f2 8#d2 16#g2 32#g2 32#g2 32#g2 16g2 16.#d2 32- 8#a2 32#a2 32#a2 16#a2 16f2 16g2 8#g2 16g2 16g2 32g2 16g2 16d2 16#d2 8f2 16f2 8#d2 16#g2 32#g2 32#g2 32#g2 32g2 32#d2 32f2 16#d2"
    parseCompositionFromStream composition 

    Console.ReadKey()
    0 // return an integer exit code
//