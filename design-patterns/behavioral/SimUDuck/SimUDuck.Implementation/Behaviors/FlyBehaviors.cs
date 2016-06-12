using System;

namespace SimUDuck.Implementation.Behaviors
{
    public interface IFlyBehavior
    {
        void DoFly();
    }

    public class FlyWithWings : IFlyBehavior
    {
        public void DoFly()
        {
            Console.WriteLine("I am flying with wings! \n");
        }
    }
    public class FlyWithRocket : IFlyBehavior
    {
        public void DoFly()
        {
            Console.WriteLine("I am flying with a rocket! \n");
        }
    }
    public class DoNotFly : IFlyBehavior
    {
        public void DoFly()
        {
            Console.WriteLine("I can't fly! \n");
        }
    }
}