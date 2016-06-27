using RemoteControl.Components;

namespace RemoteControl.Commands
{
    public class StereoOnWithCdCommand : ICommand
    {
        public StereoOnWithCdCommand(Stereo stereo)
        {
            this.stereo = stereo;
        }

        private readonly Stereo stereo;
        public void Execute()
        {
            stereo.On();
        }
    }
}