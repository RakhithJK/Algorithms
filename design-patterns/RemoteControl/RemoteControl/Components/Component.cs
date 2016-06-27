namespace RemoteControl.Components
{
    public class Component
    {
        public Component(string componentName)
        {
            Name = componentName;
        }

        public string Name { get; private set; }
    }
}
