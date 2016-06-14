namespace ForecastApp.Implementation
{
    public interface ISubject
    {
        void RegisterObserver(IObserver observer);
        void RemoveObserver(IObserver observer);
        void BroadcastToObservers(object somethingToSend);
    }
}
