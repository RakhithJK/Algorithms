using System;

namespace SimUDuck.Implementation.Ducks
{
    public sealed class MallardDuck : Duck
    {
        public override void WhoIAm()
        {
            base.WhoIAm();
            Console.WriteLine("I am a real Mallard duck! \n");
        }
    }
}