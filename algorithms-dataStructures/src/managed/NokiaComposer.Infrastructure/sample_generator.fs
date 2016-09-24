module sample_generator
open System

let generateSamples miliseconds frequency =
    let sampleRate                 = 44100.
    let sixteenBitSampleLimit      = 32767.
    let volumeDownscaleFactor      = 0.7

    let createSoundWaveAmplitude x =
        x
        |> (*) (2. * Math.PI * frequency / sampleRate) 
        |> sin
        |> (*) sixteenBitSampleLimit
        |> (*) volumeDownscaleFactor
        |> int16

    let numberOfSamples  = miliseconds / 1000. * sampleRate
    let generatedSamples = seq { 1.0 .. numberOfSamples }
    
    Seq.map createSoundWaveAmplitude generatedSamples