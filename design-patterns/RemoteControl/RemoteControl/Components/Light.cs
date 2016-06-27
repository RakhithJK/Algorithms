namespace RemoteControl.Components
{
    public class Light : Component
    {
        public Light(string componentName) : base(componentName) { }
        public bool IsOn       { get; private set; }

        public void On()    => IsOn = true;
        public void Off()   => IsOn = false;
    }
}
