using System.Collections.Generic;

namespace ForecastApp.Implementation.Models
{
    public class Weather : ISubject
    {
        public Weather()
        {
            observers       = new List<IObserver>();
            measurements    = new Measurements();
        }

        private          Measurements       measurements;
        private readonly List<IObserver>    observers;

        public void RegisterObserver(IObserver observer) => observers.Add(observer);
        public void RemoveObserver(IObserver observer) => observers.Remove(observer);
        public void BroadcastToObservers(object newMeasurements) => observers.ForEach(observer => observer.Update(newMeasurements));

        public void UpdateMeasurements(Measurements measurements)
        {
            this.measurements = measurements;
            BroadcastToObservers(newMeasurements: measurements);
        }

        public class Measurements
        {
            public double   Temperature   { get; set; }
            public double   Humidity      { get; set; }
            public double   Pressure      { get; set; }
        }
    }
}
