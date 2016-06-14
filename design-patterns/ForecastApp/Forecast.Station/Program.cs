using System;

namespace Forecast.Station
{
    using ForecastApp.Implementation.Models;

    class Program
    {
        static void Main(string[] args)
        {
            var weather         = new Weather();      
            var firstDisplay    = new CurrentConditionsDisplay(weatherData: weather);
            var secondDisplay   = new CurrentConditionsDisplay(weatherData: weather);
            var thirdDisplay    = new CurrentConditionsDisplay(weatherData: weather);

            weather.UpdateMeasurements(new Weather.Measurements
            {
                Temperature = 80,
                Humidity    = 65,
                Pressure    = 30.4f
            });

            weather.UpdateMeasurements(new Weather.Measurements
            {
                Temperature = 82,
                Humidity    = 70,
                Pressure    = 29.2f
            });
            weather.UpdateMeasurements(new Weather.Measurements
            {
                Temperature = 78,
                Humidity    = 90,
                Pressure    = 29.2f
            });

            Console.ReadKey();
        }
    }
}