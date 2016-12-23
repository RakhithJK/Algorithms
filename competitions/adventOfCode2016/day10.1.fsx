open System.Text.RegularExpressions
open System.Collections.Generic

type Bot    = { BotId: int    }
type Output = { OutputId: int }

let botsRegex    = Regex (@"bot \d", RegexOptions.Compiled)
let outputsRegex = Regex (@"output \d", RegexOptions.Compiled)

let parse_bot (input: string) = 
    match input.Split([|' '|], 2) with
    | [|_ ; botId|] -> { BotId = int botId }
    | _         -> failwith "incorrect bot syntax"

let parse_output (input: string) = 
    match input.Split([|' '|], 2) with
    | [|_ ; outputId|] -> { OutputId = int outputId }
    | _         -> failwith "incorrect bot syntax"
let detectMaximumBot(input : string) = 
    let results = botsRegex.Matches input
    results                                         |> 
    Seq.cast<Match>                                 |>
    Seq.groupBy(fun regexMatch -> regexMatch.Value) |>
    Seq.map fst                                     |>
    Seq.map parse_bot                               |>
    Seq.maxBy (fun bot -> bot.BotId)
let detectMaximumOutput(input : string) = 
    let results = outputsRegex.Matches input
    results                                         |> 
    Seq.cast<Match>                                 |>
    Seq.groupBy(fun regexMatch -> regexMatch.Value) |>
    Seq.map fst                                     |>
    Seq.map parse_output                            |>
    Seq.maxBy (fun output -> output.OutputId)

let bots    = new Dictionary<Bot, int list>()
let outputs = new Dictionary<Output, int list>()

let initialize (input : string) =
    let maximumBot    = detectMaximumBot input
    let maximumOutput = detectMaximumOutput input

    [1..maximumBot.BotId]       |> List.iter(fun botId    -> bots.Add({ BotId = botId }, []))
    [1..maximumOutput.OutputId] |> List.iter(fun outputId -> outputs.Add({ OutputId = outputId }, []))

    bots.[{ BotId = 1}] <- [3]
    bots.[{ BotId = 2}] <- [2]