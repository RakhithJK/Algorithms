using RemoteControl.Components;

namespace RemoteControl.Commands
{
    public class LightOnCommand : ICommand
    {
        public LightOnCommand(Light light)
        {
            this.light = light;
        }

        private readonly Light light;
        public void Execute()
        {
            light.On();
        }
    }
}
