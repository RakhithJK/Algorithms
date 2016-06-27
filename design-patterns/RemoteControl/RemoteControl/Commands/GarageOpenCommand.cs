using RemoteControl.Components;

namespace RemoteControl.Commands
{
    public class GarageOpenCommand : ICommand
    {
        public GarageOpenCommand(Garage garage)
        {
            this.garage = garage;
        }

        private readonly Garage garage;
        public void Execute()
        {
            garage.Open();
        }
    }
}
