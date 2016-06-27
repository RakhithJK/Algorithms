using System;

namespace RemoteControl
{
    using Commands;
    using Components;

    class Program
    {
        static void Main(string[] args)
        {
            RemoteControl remoteControl = new RemoteControl();

            Garage garageDoor                   = new Garage(componentName: "Garage"      );
            Light livingRoomLight               = new Light (componentName: "Living Room" );
            Light kitchenLight                  = new Light (componentName: "Kitchen"     );
            Stereo stereo                       = new Stereo(componentName: "Living Room" );

            ICommand livingRoomLightOnCommand   = new LightOnCommand(livingRoomLight);
            ICommand livingRoomLightOffCommand  = new LightOffCommand(livingRoomLight);
            ICommand kitchenLightOnCommand      = new LightOnCommand(kitchenLight);
            ICommand kitchenLightOffCommand     = new LightOffCommand(kitchenLight);
            ICommand garageDoorUpCommand        = new GarageOpenCommand(garageDoor);
            ICommand garageDoorDownCommand      = new GarageCloseCommand(garageDoor);
            ICommand stereoOnWithCdCommand      = new StereoOnWithCdCommand(stereo);
            ICommand stereoOffCommand           = new StereoOfCommand(stereo);

            remoteControl.SetCommandToSlot(0, livingRoomLightOnCommand, livingRoomLightOffCommand);
            remoteControl.SetCommandToSlot(1, kitchenLightOnCommand, kitchenLightOffCommand);
            remoteControl.SetCommandToSlot(2, garageDoorUpCommand, garageDoorDownCommand);
            remoteControl.SetCommandToSlot(3, stereoOnWithCdCommand, stereoOffCommand);

            remoteControl.OnSlotButtonDidPress(0);
            remoteControl.OffSlotButtonDidPress(0);
            remoteControl.OnSlotButtonDidPress(1);
            remoteControl.OffSlotButtonDidPress(1);
            remoteControl.OnSlotButtonDidPress(2);
            remoteControl.OffSlotButtonDidPress(2);
            remoteControl.OnSlotButtonDidPress(3);
            remoteControl.OffSlotButtonDidPress(3);

            Console.ReadKey();
        }
    }
}
