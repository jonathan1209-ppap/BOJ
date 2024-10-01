open System

let a = [| 65; 17; 4; 4; 64 |]
let b = int (Console.ReadLine())
printfn "%d" a.[b - 1]
