open System
open System.Linq

type State                = Smaller | Bigger | Equal | Undefined
let randomGenerator       = new Random()
let generatedRandomNumber = randomGenerator.Next(0, 100)
let numberInterval        = [0..100]

let getMedian lowerBound upperBound = (lowerBound + upperBound) / 2
let printNumber n = printfn "%A" n
let newState()  = 
    let key = Console.ReadKey().Key
    Console.WriteLine() |> ignore
    match key with 
    | ConsoleKey.S -> Smaller
    | ConsoleKey.B -> Bigger
    | ConsoleKey.E -> Equal
    | _ -> Equal

let rec solve state previousTries = 
    match state with
    | Undefined -> 
        let currentSolution = getMedian 0 100
        printNumber currentSolution
        let state = newState()
        solve state ((state,currentSolution)::previousTries)
    | Smaller -> 
        let between = 
            match previousTries.Length with
            | 1 -> [snd previousTries.Head; 100]
            | _ -> 
                match previousTries.Any(fun trie -> (fst trie) = Bigger) with 
                | true  -> [snd previousTries.Head; (previousTries.Where(fun trie -> (fst trie) = Bigger).Min(fun trie -> (snd trie)))]
                | false -> [snd previousTries.Head; 100]

        let currentSolution = getMedian between.[0] between.[1]
        printNumber currentSolution
        let state = newState()
      
        solve state ((state,currentSolution)::previousTries)
    | Bigger -> 
        let between = 
            match previousTries.Length with
            | 1 -> [snd previousTries.Head; 0]
            | _ ->
                match previousTries.Any(fun trie -> (fst trie) = Smaller) with 
                | true  ->  [snd previousTries.Head; (previousTries.Where(fun trie -> (fst trie) = Smaller).Max(fun trie -> (snd trie)))]
                | false -> [snd previousTries.Head; 0]
                
        let currentSolution = getMedian between.[0] between.[1]
        printNumber currentSolution
        let state = newState()
        solve state ((state,currentSolution)::previousTries) 
    | Equal -> previousTries
    

[<EntryPoint>]
let main argv = 
    let randomNumber = generatedRandomNumber
    printfn "%A" randomNumber
   
    let solution = solve Undefined []
    printfn "number of steps %A" solution.Length
    Console.ReadKey() |> ignore
    0
