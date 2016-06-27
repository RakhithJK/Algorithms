using System.Text;

namespace RemoteControl.Components
{
    using Commands;

    public class RemoteControl
    {
        public RemoteControl()
        {
            onCommands = new ICommand[7];
            offCommands = new ICommand[7];

            DoNothingCommand doNothingCommand = new DoNothingCommand();

            for (int i = 0; i < 7; i++)
            {
                onCommands[i]  = doNothingCommand;
                offCommands[i] = doNothingCommand;
            }
        }
        private readonly ICommand[] onCommands;
        private readonly ICommand[] offCommands;

        public void SetCommandToSlot(int slot, ICommand onCommand, ICommand offCommand)
        {
            onCommands[slot]  = onCommand;
            offCommands[slot] = offCommand;
        }

        public void OnSlotButtonDidPress(int slot)      =>      onCommands[slot].Execute();
        public void OffSlotButtonDidPress(int slot)     =>      offCommands[slot].Execute();

        public override string ToString()
        {
            var stringBuilder = new StringBuilder();
            stringBuilder.AppendLine("----------------- Remote Control -----------------");

            for (int i = 0; i < onCommands.Length; i++)
            {
                stringBuilder.AppendLine($"[slot {i}] {onCommands[i].GetType().Name} {offCommands[i].GetType().Name}");
            }
            return stringBuilder.ToString();
        }
    }
}
