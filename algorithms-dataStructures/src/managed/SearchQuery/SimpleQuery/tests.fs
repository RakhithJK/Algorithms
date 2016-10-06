module tests

open SimpleQuery.Querying
open FluentAssertions
open FsUnit.Xunit
open FParsec
open Xunit

let explicitQueries = [
    ":from=12.2.2015, :to=15.3.2015";
    "  :from=12.2.2015  , :to=15.3.2015  ";
    " :userName=Gabrijel Boduljak, :editorName=  Vojko V  ,  :from=12.2.2015  , :to=15.3.2015, ";
]
let implicitQueries = [
    ""
]
let queries = explicitQueries @ implicitQueries

[<Fact>]
let DidParseExplicitQueriesPerformedWell = 
    let parsedExplicitQueries = List.map SimpleQuery.Querying.parse explicitQueries
    let checkParsedResult index parsedResult = 
        match parsedResult with
        | Success(queries : (QueryPart list), _, _) -> 
            match index with 
            | 0 -> (queries.Length.Should().Be(2, "")) |> ignore
            | 1 -> (queries.Length.Should().Be(2, "")) |> ignore
            | 2 -> (queries.Length.Should().Be(4, "")) |> ignore
            | _ -> failwith "unsupported index"        |> ignore
        | Failure(error, _, _) -> failwith "unsupported index" |> ignore

    List.iteri checkParsedResult parsedExplicitQueries