module SimpleQuery.Query

type ExplicitQueryPart = { Term: string; Value: string }
type ImplicitQueryPart = { Values: string list }
type QueryPartType     = Implicit | Explicit
type QueryPart         = Implicit of ImplicitQueryPart | Explicit of ExplicitQueryPart
type Query             = { Parts : QueryPart list }