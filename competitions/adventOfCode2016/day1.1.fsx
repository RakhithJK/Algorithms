open System;

type Direction            = North | South | East | West
type InstructionDirection = Left | Right
type Instruction          = { Direction : InstructionDirection; Blocks : int }
type TravelAccumulator    = { CurrentDirection : Direction; X : int; Y : int }

let parseInstructionDirection directionCharacter = 
    match directionCharacter with 
    | 'R' -> Right
    | 'L' -> Left
    | _   -> failwith "wrong direction instruction"

let parseInstructions (instructions : string) =  
    instructions.Replace(" ", "").Split(',') |> 
    Array.map (fun instructionAsString -> { Direction = parseInstructionDirection instructionAsString.[0]; Blocks = Int32.Parse (instructionAsString.Substring(1, instructionAsString.Length - 1)) })


let travel (instructions : Instruction[]) = 
   
    let startDirection  = North

    let addToNorth direction =
        match direction with 
        | Right -> East
        | Left  -> West

    let addToEast direction =
        match direction with 
        | Right -> South
        | Left  -> North

    let addToSouth direction =
        match direction with 
        | Right -> West
        | Left  -> East

    let addToWest direction =
        match direction with 
        | Right -> North
        | Left  -> South

    let updateDestination accumulator instruction = 
        let destinationDirection = 
            match accumulator.CurrentDirection with 
            | North -> addToNorth instruction.Direction
            | South -> addToSouth instruction.Direction
            | East  -> addToEast  instruction.Direction
            | West  -> addToWest  instruction.Direction
     
        let x = 
            match destinationDirection with 
            | East -> accumulator.X + instruction.Blocks
            | West -> accumulator.X - instruction.Blocks
            | _ -> accumulator.X

        let y = 
            match destinationDirection with 
            | North -> accumulator.Y + instruction.Blocks
            | South -> accumulator.Y - instruction.Blocks
            | _ -> accumulator.Y

        { CurrentDirection = destinationDirection; X = x; Y = y }

    Array.fold updateDestination { CurrentDirection = North; X = 0; Y = 0 } instructions

   
let solve (instructionsAsString : string) =
    let instructions = parseInstructions instructionsAsString
    let destination = travel instructions
    let calculateTaxicabDistance destination = Math.Abs destination.X + Math.Abs destination.Y
    let distance = calculateTaxicabDistance destination
    distance