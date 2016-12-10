open System
open System.Security.Cryptography
open System.Text

// credits : http://www.fssnip.net/lK/title/Compute-MD5-hash-of-a-string
let hash (input : string) =
      use md5 = MD5.Create()
      input
      |> Encoding.ASCII.GetBytes
      |> md5.ComputeHash
      |> Seq.map (fun c    -> c.ToString("X2"))
      |> Seq.map (fun char -> char.ToLower())
      |> Seq.reduce (+)

let fiveZerosString = "00000"

let comprisePassword (char: char) (charIndex: int) (previousPassword: char[]) =
    previousPassword.[charIndex] <- char
    previousPassword
    
let computePassword (doorId : string) = 
    let rec compute appendInteger computedCharactersCount currentPassword =
        let maybeSolutionHash = hash (doorId + string (appendInteger))
        let isCorrectHash     = maybeSolutionHash.StartsWith(fiveZerosString)
        match computedCharactersCount with
        | count when count = 8 -> currentPassword
        | _ -> 
            match isCorrectHash with
            | true  -> compute (appendInteger + 1) (computedCharactersCount + 1) (comprisePassword maybeSolutionHash.[5] (Int32.Parse (string maybeSolutionHash.[6])) currentPassword)
            | false -> compute (appendInteger + 1) computedCharactersCount currentPassword

    compute 0 0 ("________".ToCharArray())