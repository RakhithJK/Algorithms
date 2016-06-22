using System;
using PizzaStore.Pizzas;
using PizzaStore.Stores;

namespace PizzaStore
{
    class Program
    {
        static void Main(string[] args)
        {
            Stores.IPizzaStore nyStore = new NewYorkPizzaStore();
            Stores.IPizzaStore chicagoStore = new ChicagoPizzaStore();

            Pizza pizza = nyStore.Order(type: PizzaType.Cheese);
            Console.WriteLine($"Ethan ordered a {pizza.Name}");
            Console.WriteLine("\n");

            pizza = chicagoStore.Order(type: PizzaType.Cheese);
            Console.WriteLine($"Joel ordered a {pizza.Name}");

            Console.ReadKey();
        }
    }
}
