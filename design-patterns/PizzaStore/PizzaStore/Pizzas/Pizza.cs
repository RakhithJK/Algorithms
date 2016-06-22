using System;
using System.Collections.Generic;
using PizzaStore.Ingredients;

namespace PizzaStore.Pizzas
{
    public abstract class Pizza
    {
        protected Pizza(IPizzaIngredientFactory ingredientFactory)
        {
            this.toppings = new List<string>();
            this.ingredientFactory = ingredientFactory;
        }

        public                  string                   Name    { get; protected set; }
        public                  string                   Dough   { get; protected set; }
        public                  string                   Sauce   { get; protected set; }
        public                  string                   Cheese  { get; protected set; }

        protected readonly List<string>                  toppings;
        protected readonly IPizzaIngredientFactory       ingredientFactory;

        public virtual void Prepare()
        {
            Dough  = ingredientFactory.CreateDough();
            Sauce  = ingredientFactory.CreateSauce();
            Cheese = ingredientFactory.CreateSauce();


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
