open System.Collections.Generic
open System.IO
open System.Text.RegularExpressions
open System.Linq

type TargetTypeId = Bot of int | Output of int
type Bot          = { BotId: int; BotMicrochips : int list }
type Output       = { OutputId : int; OutputMicrochips : int list }

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

let states  = new Dictionary<int, BotState>()
let outputs = new Dictionary<int, int list>()

let parseCommand (input: string) =
    match input with
    | Command command -> command
    | x ->
        printfn "%A" x 
        failwith "cannot parse command"

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
        let isAlreadyInitialized = states.ContainsKey(args.SourceBotId)
        match isAlreadyInitialized with
        | true ->
            let updated = {
                Bot = states.[args.SourceBotId].Bot;
                Commands = (Transfer args)::states.[args.SourceBotId].Commands
            }
            states.[args.SourceBotId] <- updated;
        | false ->
            let botState = {
                Bot = {
                    BotId         = args.SourceBotId
                    BotMicrochips = []
                };
                Commands = [(Transfer args)]
            }
            states.[args.SourceBotId] <- botState  
let initializeStates (input: string[]) =
    input |> 
    Array.map parseCommand |>
    Array.iter updateBotState 

    states

let transfer value target =
    match target with
    | Bot targetId ->
        let currentState = states.[targetId]
        let updatedState = {
            Bot = {
                BotId = currentState.Bot.BotId;
                BotMicrochips = (value::currentState.Bot.BotMicrochips)
            }
            Commands = currentState.Commands
        }
        states.[targetId] <- updatedState
    | Output outputId -> 
        let isOutputInitialized = outputs.ContainsKey(outputId)

        match isOutputInitialized with
        | true ->
            outputs.[outputId] <- (value::outputs.[outputId])
        | false ->
            outputs.Add(outputId, [value])

let givenChips = new ResizeArray<int*int list>()

let execute command =
    match command with
    | Transfer args ->
        let currentState = states.[args.SourceBotId]
        let loChip = List.min currentState.Bot.BotMicrochips
        let hiChip = List.max currentState.Bot.BotMicrochips

        transfer loChip args.LoTargetId
        transfer hiChip args.HiTargetId

        givenChips.Add (args.SourceBotId, [loChip; hiChip])

        let commandsWithoutCurrent = currentState.Commands |> List.filter (fun cmd -> cmd <> command)
        let updatedState = {
            Bot      = { currentState.Bot with Bot.BotMicrochips = [] };
            Commands = commandsWithoutCurrent
        }
        states.[args.SourceBotId] <- updatedState  
    | Initialize args -> ()

let executeInstructions() = 
    let rec executeIfPossible() =
        let canExecute = 
            not (states |>
            Seq.filter (fun pair -> pair.Value.Bot.BotMicrochips.Length = 2) |>
            Seq.isEmpty)
        match canExecute with
        | true ->
            let stateWithTwoMicrochips = 
                states |>
                Seq.filter (fun pair -> pair.Value.Bot.BotMicrochips.Length = 2) |>
                Seq.map (fun pair -> pair.Value) |>
                Seq.head
            let command = List.head stateWithTwoMicrochips.Commands 
            execute command
            executeIfPossible()
        | false -> ()

    executeIfPossible()

let solve() =
    executeInstructions()
    
    givenChips |>
    Seq.filter (fun pair -> (snd pair).Contains(17) && (snd pair).Contains(61)) |>
    Seq.map fst |>
    List.ofSeq