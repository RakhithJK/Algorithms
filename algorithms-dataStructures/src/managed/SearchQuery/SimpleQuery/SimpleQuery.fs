module SimpleQuery.Querying

open FParsec
open System.Text.RegularExpressions

let removeWhitespacesBeforeDelimiter (query : string) = query.Replace(" , ", ",")
let sanitizeString (query : string)                   = removeWhitespacesBeforeDelimiter (Regex.Replace(query.Trim(), @"\s+", " "))

type ExplicitQueryPart = { Term: string; Value: string }
type ImplicitQueryPart = { Values: string list }
type QueryPartType     = Implicit | Explicit
type QueryPart         = Implicit of ImplicitQueryPart | Explicit of ExplicitQueryPart

let parseFirstExplicitTermSplitter = spaces >>. pchar ':'
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

let parse (queryToParse) = run parseQuery (sanitizeString queryToParse) 