using System;

namespace SimUDuck.Implementation.Behaviors
{
    public interface IQuackBehavior
    {
        void DoQuack();
    }

    public class QuackBehavior : IQuackBehavior
    {
        public void DoQuack()
        {
            Console.WriteLine("Quack!!!! \n");
        }
    }
    public class SqueakBehavior : IQuackBehavior
    {
        public void DoQuack()
        {
            Console.WriteLine("Squeak!!!! \n");
        }
    }
    public class MuteQuack : IQuackBehavior
    {
        public void DoQuack()
        {
            Console.WriteLine("I can't quack! \n");
        }
    }
}