using System;
using System.Collections.Generic;

namespace PizzaStore.Pizzas
{
    public abstract class Pizza
    {
        protected Pizza()
        {
            toppings = new List<string>();
        }

        public                  string     Name    { get; set; }
        public                  string     Dough   { get; set; }
        public                  string     Sauce   { get; set; }

        protected readonly List<string>    toppings;

        public virtual void Prepare()
        {
            Console.WriteLine($"Preparing {Name}");
            Console.WriteLine("Tossing dough...");
            Console.WriteLine("Adding sauce...");
            Console.WriteLine("Adding toppings...");
        }

        public virtual void Bake() => Console.WriteLine("Bake for 25 muntes at 350.");
        public virtual void Cut()  => Console.WriteLine("Cutting the pizzas into diagonal slices.");
        public virtual void Box()  => Console.WriteLine("Placing pizza in the official PizzaStore box.");
    }
}
