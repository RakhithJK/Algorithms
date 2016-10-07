module SimpleQuery.Parser

open SimpleQuery.Query
open FParsec
open System.Text.RegularExpressions

let removeWhitespacesAroundDelimiter (query : string) = query.Replace(" , ", ",")
let sanitizeString (query : string)                   = removeWhitespacesAroundDelimiter (Regex.Replace(query.Trim(), @"\s+", " "))
let parseFirstExplicitTermSplitter = spaces >>. pchar ':' >>. spaces
let parseQuerySplitter             = spaces >>. pchar ',' >>. spaces

let parseExplicitTerm = 
    between 
     parseFirstExplicitTermSplitter 
     (pchar '=') 
     (manyChars (noneOf "="))

let parseExplicitTermValue = manyChars (noneOf ",")

let parseExplicitQueryPart = 
    pipe2 
        parseExplicitTerm
        parseExplicitTermValue
        (fun term value -> Explicit { Term = term; Value = value })

let parseImplicitQueryTerm  = 
    between
        (spaces)
        (spaces)
        (sepBy (manyChars (noneOf " ,")) (pchar ' '))

let parseImplicitQueryTerms = 
    parseImplicitQueryTerm |>>
    (fun values -> Implicit { Values = values })

let parseQueryPart = parseExplicitQueryPart <|> parseImplicitQueryTerms

let parseQuery = sepBy parseQueryPart parseQuerySplitter

let parse queryToParse = 
    match run parseQuery (sanitizeString queryToParse) with
    | Success(queryParts, _, _)   -> { Parts = queryParts }
    | Failure(errorMessage, _, _) -> failwith errorMessage