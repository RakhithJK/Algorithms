using System;

namespace SimUDuck
{
    using Implementation;

    using duck     = Implementation.Ducks;
    using behavior = Implementation.Behaviors;

    class Program
    {
        static void Main()
        {
            Duck mallard = new duck::MallardDuck();
            mallard.WhoIAm();
            mallard.Quack();
            mallard.Fly();

            Console.WriteLine("\n");

            Duck model = new duck::ModelDuck();
            model.WhoIAm();
            model.Quack();
            model.Fly();
            model.ChangeFlyBehavior(new behavior::FlyWithRocket());
            model.Fly();

            Console.ReadKey();
        }
    }
}
