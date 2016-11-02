type graph(verticesCount) = 
    let mutable connectionsHolder          = Array.init verticesCount (fun index -> index)   
    let mutable subGraphSizesHolder        = Array.init verticesCount (fun index -> index)   
    let mutable modificationsCount         = 0 
    member this.elementsCount              = verticesCount
    member this.findVertexRoot vertexIndex =
        let rec searchForRootRecursively maybeRootIndex =
            let value = connectionsHolder.[maybeRootIndex]
            match maybeRootIndex with 
            | index when index = value -> value
            | _ -> searchForRootRecursively connectionsHolder.[connectionsHolder.[maybeRootIndex]] // flatten tree, nesting reduced
        searchForRootRecursively vertexIndex

    member this.areConnected p q = this.findVertexRoot p = this.findVertexRoot q
    member this.connect      p q = 
        let performConnection =
            let pSubGraphSize = subGraphSizesHolder.[p]
            let qSubGraphSize = subGraphSizesHolder.[q]

            let pRoot = this.findVertexRoot p
            let qRoot = this.findVertexRoot q

            let putPSubgraphUnderQSubgraph() = 
                connectionsHolder.[pRoot]   <- qRoot
                subGraphSizesHolder.[pRoot] <- subGraphSizesHolder.[pRoot] + subGraphSizesHolder.[qRoot]

            let putQSubgraphUnderPSubgraph() = 
                connectionsHolder.[qRoot]   <- pRoot
                subGraphSizesHolder.[qRoot] <- subGraphSizesHolder.[qRoot] + subGraphSizesHolder.[pRoot]

            match (pSubGraphSize, qSubGraphSize) with
            | sizes when qSubGraphSize >= pSubGraphSize -> putPSubgraphUnderQSubgraph()
            | _                                         -> putQSubgraphUnderPSubgraph()
        
            modificationsCount <- modificationsCount + 1
            connectionsHolder

        match this.areConnected p q with
        | true  -> connectionsHolder
        | false -> performConnection 
            
open System

type site = { rowIndex : int; columnIndex : int }


type percolation (n) =
    let mutable currentId = -1
    let grid  = Array2D.init n n (fun i j -> currentId <- currentId + 1
                                             currentId, false)
    let graph = graph (n*n + 2)
    let virtualTopElementId     = n*n 
    let virtualBottomElementId  = n*n + 1

    let isTopElement    site    = site.rowIndex = 0
    let isBottomElement site    = site.rowIndex = n - 1
    let isCoordinateInMap coord = coord >= 0 && coord < n
    let areCoordinatesInMap x y = isCoordinateInMap x && isCoordinateInMap y
    let generator               = new Random()
    member this.isOpen site         = 
        match areCoordinatesInMap site.rowIndex site.columnIndex with 
        | true  -> snd grid.[site.rowIndex, site.columnIndex] = true
        | false -> false
        
    member this.isFull site         = graph.areConnected (fst grid.[site.rowIndex, site.columnIndex]) virtualTopElementId
    member this.connect site1 site2 = graph.connect (fst grid.[site1.rowIndex, site1.columnIndex]) (fst grid.[site2.rowIndex, site2.columnIndex])
    member this.openSite siteToOpen =
        grid.[siteToOpen.rowIndex, siteToOpen.columnIndex]   <- (fst grid.[siteToOpen.rowIndex, siteToOpen.columnIndex]), true

        let leftNeighbourCoordinates   = { rowIndex = siteToOpen.rowIndex;     columnIndex = siteToOpen.columnIndex - 1 }
        let rightNeighbourCoordinates  = { rowIndex = siteToOpen.rowIndex;     columnIndex = siteToOpen.columnIndex + 1 }
        let upperNeighbourCoordinates  = { rowIndex = siteToOpen.rowIndex + 1; columnIndex = siteToOpen.columnIndex     }
        let bottomNeighbourCoordinates = { rowIndex = siteToOpen.rowIndex - 1; columnIndex = siteToOpen.columnIndex     }

        match this.isOpen leftNeighbourCoordinates with
        | true  -> this.connect siteToOpen leftNeighbourCoordinates |> ignore
        | false -> ignore None

        match this.isOpen rightNeighbourCoordinates with
        | true  -> this.connect siteToOpen rightNeighbourCoordinates |> ignore
        | false -> ignore None

        match this.isOpen upperNeighbourCoordinates with
        | true  -> this.connect siteToOpen upperNeighbourCoordinates |> ignore
        | false -> ignore None

        match this.isOpen bottomNeighbourCoordinates with
        | true  -> this.connect siteToOpen bottomNeighbourCoordinates |> ignore
        | false -> ignore None

        match isTopElement siteToOpen with
        | true  -> graph.connect (fst grid.[siteToOpen.rowIndex, siteToOpen.columnIndex]) virtualTopElementId |> ignore
        | false -> ignore None

        match isBottomElement siteToOpen with
        | true  -> graph.connect (fst grid.[siteToOpen.rowIndex, siteToOpen.columnIndex]) virtualBottomElementId |> ignore
        | false -> ignore None
    member this.openRandomSite() = 
        let randomSite = { rowIndex = generator.Next(0, n - 1); columnIndex = generator.Next(0, n - 1) }
        this.openSite randomSite
        printfn "%A" randomSite
        grid
    member this.doesPercolate = graph.areConnected virtualTopElementId virtualBottomElementId