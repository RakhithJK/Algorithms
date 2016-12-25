open System.Collections.Generic
open System.IO
open System.Text.RegularExpressions

type TargetTypeId = Bot of int | Output of int
type Bot    = { BotId: int; BotMicrochips : int list }
type Output = { OutputId : int; OutputMicrochips : int list }

type InitializeCommandArgs = { ChipValue : int; BotId : int }
type TransferCommandArgs = { 
    SourceBotId : int;
    LoTargetId : TargetTypeId;
    HiTargetId : TargetTypeId
}

type Command = Initialize of InitializeCommandArgs | Transfer of TransferCommandArgs
type BotState = { Bot : Bot; Commands : Command list }

let (|Regex|_|) pattern input =
        let result = Regex.Match(input, pattern)
        match result.Success with
        | true  -> Some (List.tail [for group in result.Groups -> group.Value])
        | false -> None

let (|Int|) x = int x
let (|Target|) = function | "bot" -> Bot | _ -> Output

let (|Command|_|) (input : string) =
    match input with 
    | Regex "value (\d*) goes to bot (\d*)" [chipValue; botId] ->
        Some (Initialize { ChipValue = int chipValue; BotId = int botId })
    | Regex "bot (\d*) gives low to (bot|output) (\d*) and high to (bot|output) (\d*)" [Int botId; Target loTargetType; Int loTargetId; Target hiTargetType; Int hiTargetId] ->
        Some (Transfer { SourceBotId = int botId; LoTargetId = loTargetType loTargetId; HiTargetId = hiTargetType hiTargetId })
    | _ -> None

//let input = File.ReadAllText __SOURCE_DIRECTORY__ + "/day10.txt"

let states = new Dictionary<int, BotState>()
let parseCommand (input: string) =
    match input with
    | Command command -> command
    | _ -> failwith "cannot parse command"

let updateBotState (command : Command) =
    match command with
    | Initialize args ->
        let isAlreadyInitialized = states.ContainsKey(args.BotId)
        match isAlreadyInitialized with 
        | true -> 
            let bot = {
                BotId = args.BotId;
                BotMicrochips = args.ChipValue::states.[args.BotId].Bot.BotMicrochips
            }
            states.[args.BotId] <- { Bot = bot; Commands = states.[args.BotId].Commands }

        | false -> 
            let bot = {
                BotId = args.BotId;
                BotMicrochips = [args.ChipValue]
            }
            states.[args.BotId] <- { Bot = bot; Commands = [] } 
    | Transfer args ->
        let updated = {
            Bot = states.[args.SourceBotId].Bot;
            Commands = (Transfer args)::states.[args.SourceBotId].Commands
        }
        states.[args.SourceBotId] <- updated;

let initializeStates (input: string[]) =
    input |> 
    Array.sort |>
    Array.map parseCommand |>
    Array.iter updateBotState
    
    states

let testInputString = "value 5 goes to bot 2
bot 2 gives low to bot 1 and high to bot 0
value 3 goes to bot 1
bot 1 gives low to output 1 and high to bot 0
bot 0 gives low to output 2 and high to output 0
value 2 goes to bot 2"
let testInput = testInputString.Split('\n')

initializeStates testInput