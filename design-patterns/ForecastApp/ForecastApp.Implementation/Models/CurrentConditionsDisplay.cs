using System;

namespace ForecastApp.Implementation.Models
{
    public class CurrentConditionsDisplay : IDisplay,IObserver
    {
        public CurrentConditionsDisplay(ISubject weatherData)
        {
            this.weatherData = weatherData;
            this.weatherData.RegisterObserver(this);
        }
        public  Weather.Measurements Measurements
        {
            get { return measurements; }
            set
            {
                measurements = value;
                Display();
            }
        }
        private Weather.Measurements measurements;
        private ISubject             weatherData;

        public void Update(object newData)
        {
            measurements = newData as Weather.Measurements;
            Display();
        }
        public void Display() => Console.WriteLine($"Current weather conditions are : {measurements.Temperature} F degrees, {measurements.Humidity} percent humidity, and pressure of {measurements.Pressure} kPa. \n");
    }
}
