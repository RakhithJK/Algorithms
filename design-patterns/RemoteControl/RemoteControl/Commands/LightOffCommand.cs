using RemoteControl.Components;

namespace RemoteControl.Commands
{
    public class LightOffCommand : ICommand
    {
        public LightOffCommand(Light light)
        {
            this.light = light;
        }

        private readonly Light light;
        public void Execute()
        {
            light.Off();
        }
    }
}
