open System
open System.Linq

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

    let calculateDestinationPoint accumulator instruction  = 
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

 
    let mutable destination             = { CurrentDirection = North; X = 0; Y = 0 } 
    let mutable foundIntersection       = false
    let mutable currentInstructionIndex = 0
    let         visitedPoints           = new ResizeArray<TravelAccumulator>()


    while foundIntersection <> true && currentInstructionIndex < instructions.Length do
        let currentInstruction   = instructions.[currentInstructionIndex]
        let nextDestinationPoint = calculateDestinationPoint destination currentInstruction
        
        for i = 1 to currentInstruction.Blocks - 1 do 
            if nextDestinationPoint.CurrentDirection = East then
                visitedPoints.Add { CurrentDirection = East; X = destination.X + i; Y = destination.Y }
            if nextDestinationPoint.CurrentDirection = West then
                visitedPoints.Add { CurrentDirection = West; X = destination.X - i; Y = destination.Y }   
            if nextDestinationPoint.CurrentDirection = North then
                visitedPoints.Add { CurrentDirection = North; X = destination.X; Y = destination.Y + i }
            if nextDestinationPoint.CurrentDirection = South then
                visitedPoints.Add { CurrentDirection = South; X = destination.X; Y = destination.Y - i }

        destination       <- nextDestinationPoint
        foundIntersection <- visitedPoints.GroupBy(fun point -> point.X, point.Y)
                                          .Where(fun group -> group.Count() > 1)
                                          .Any()

        if foundIntersection then
            let intersectionCoords = visitedPoints.GroupBy(fun point -> point.X, point.Y).Where(fun group -> group.Count() > 1)
                                                  .Select(fun group -> group.Key)
                                                  .First()
            destination <- { CurrentDirection = nextDestinationPoint.CurrentDirection; X = fst intersectionCoords; Y = snd intersectionCoords }
            
        currentInstructionIndex <- currentInstructionIndex + 1
        visitedPoints.Add destination

    destination
    
let solve (instructionsAsString : string) =
    let instructions = parseInstructions instructionsAsString
    let destination = travel instructions
    let calculateTaxicabDistance destination = Math.Abs destination.X + Math.Abs destination.Y
    let distance = calculateTaxicabDistance destination
    distance