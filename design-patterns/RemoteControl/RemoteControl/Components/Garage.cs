namespace RemoteControl.Components
{
    public class Garage : Component
    {
        public Garage(string componentName) : base(componentName) { }
        public bool IsOpened       { get; private set; }

        public void Open()    => IsOpened = true;
        public void Close()   => IsOpened = false;
    }
}
