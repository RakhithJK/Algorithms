using System;
using SimUDuck.Implementation.Behaviors;

namespace SimUDuck.Implementation.Ducks
{
    public sealed class ModelDuck : Duck
    {
        public ModelDuck()
        {
            ChangeFlyBehavior(new DoNotFly());
            ChangeQuackBehavior(new MuteQuack());
        }
        public override void WhoIAm()
        {
            base.WhoIAm();
            Console.WriteLine("I am a real Model duck! \n");
        }
    }
}
