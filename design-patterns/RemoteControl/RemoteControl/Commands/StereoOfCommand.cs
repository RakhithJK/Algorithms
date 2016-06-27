using RemoteControl.Components;

namespace RemoteControl.Commands
{
    public class StereoOfCommand : ICommand
    {
        public StereoOfCommand(Stereo stereo)
        {
            this.stereo = stereo;
        }

        private readonly Stereo stereo;
        public void Execute()
        {
            stereo.Off();
        }
    }
}