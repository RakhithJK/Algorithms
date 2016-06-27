namespace RemoteControl.Components
{
    using Commands;

    public class SimpleRemoteControl
    {
        public void SetCommand(ICommand command)    => this.command = command;
        public void ButtonDidPress()                => command.Execute();

        private ICommand command;
    }
}