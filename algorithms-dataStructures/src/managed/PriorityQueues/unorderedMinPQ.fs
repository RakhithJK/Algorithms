type UnorderedMinPQ(capacity) =
    let elementsHolder           = Array.zeroCreate(capacity)
    let mutable lastElementIndex = -1;

    member this.isEmpty = lastElementIndex = -1
    member this.size    = lastElementIndex + 1
    member this.insert element =
        lastElementIndex <- lastElementIndex + 1 
        elementsHolder.[lastElementIndex] <- element
    member this.deleteMin =
        // find min
        let mutable minElementIndex = 0;
        for i in [1..lastElementIndex] do   
            if (elementsHolder.[i] < elementsHolder.[minElementIndex]) then
                minElementIndex <- i

        let minElement = elementsHolder.[minElementIndex]

        //exchange minElement with lastElementIndex - 1

        let temp = elementsHolder.[lastElementIndex]
        elementsHolder.[lastElementIndex] <- elementsHolder.[minElementIndex]
        elementsHolder.[minElementIndex]  <- temp

        // delete lastElement
        lastElementIndex <- lastElementIndex - 1
        minElement


let pq = UnorderedMinPQ(5)

pq.insert 1
pq.insert 4
pq.insert 0
pq.insert 3
pq.insert 2


printfn "%A" pq.deleteMin
printfn "%A" pq.deleteMin
printfn "%A" pq.deleteMin
printfn "%A" pq.deleteMin
printfn "%A" pq.deleteMin
