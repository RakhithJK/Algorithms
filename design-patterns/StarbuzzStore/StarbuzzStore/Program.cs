using System;

namespace StarbuzzStore
{
    using Domain;
    using condiments = Domain.Condiments;
    using beverages  = Domain.Beverages;

    class Program
    {
        static void Main(string[] args)
        {
            Beverage espresso = new beverages::Espresso();
        
            Beverage houseBlend = new beverages::HouseBlend();
            houseBlend = new condiments::Mocha(houseBlend);
            houseBlend = new condiments::Mocha(houseBlend);
            houseBlend = new condiments::Whip(houseBlend);

            Beverage uberEspresso = new beverages::Espresso();
            uberEspresso = new condiments::Mocha(uberEspresso);
            uberEspresso = new condiments::Soy(uberEspresso);
            uberEspresso = new condiments::Whip(uberEspresso);

            Console.WriteLine($"{espresso.Description}, {espresso.Cost}$");
            Console.WriteLine($"{houseBlend.Description}, {houseBlend.Cost}$");
            Console.WriteLine($"{uberEspresso.Description}, {uberEspresso.Cost}$");
            Console.ReadKey();
        }
    }
}
