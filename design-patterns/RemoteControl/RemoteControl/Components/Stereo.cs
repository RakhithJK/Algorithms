namespace RemoteControl.Components
{
    public class Stereo : Component
    {
        public Stereo(string componentName) : base(componentName) { }
        public bool IsOn       { get; private set; }

        public void On()    => IsOn = true;
        public void Off()   => IsOn = false;
    }
}
