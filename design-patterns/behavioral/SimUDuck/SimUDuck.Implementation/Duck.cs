using System;
using SimUDuck.Implementation.Behaviors;

namespace SimUDuck.Implementation
{
    public abstract class Duck
    {
        protected Duck()
        {
            FlyBehavior   = new FlyWithWings();
            QuackBehavior = new QuackBehavior();
        }

        public virtual void ChangeFlyBehavior(IFlyBehavior flyBehavior)             => FlyBehavior = flyBehavior;
        public virtual void ChangeQuackBehavior(IQuackBehavior quackBehavior)       => QuackBehavior = quackBehavior;
        public virtual void Fly()                                                   => FlyBehavior.DoFly();
        public virtual void Quack()                                                 => QuackBehavior.DoQuack();
        public virtual void WhoIAm()                                                => Console.WriteLine("I am duck! \n");

        protected IFlyBehavior     FlyBehavior     { get; private set; }
        protected IQuackBehavior   QuackBehavior   { get; private set; }
    }
}