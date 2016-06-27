using RemoteControl.Components;

namespace RemoteControl.Commands
{
    public class GarageCloseCommand : ICommand
    {
        public GarageCloseCommand(Garage garage)
        {
            this.garage = garage;
        }

        private readonly Garage garage;
        public void Execute()
        {
            garage.Close();
        }
    }
}
